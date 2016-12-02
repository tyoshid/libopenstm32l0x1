/*
 * I2C functions
 *
 * Copyright 2015 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include <mmio.h>
#include <memorymap.h>
#include <i2c.h>

static const int base[] = {
	I2C1_BASE,
	I2C2_BASE,
	I2C3_BASE
};

void i2c_set_digital_noise_filter(enum i2c i2c, int dnf)
{
	int r;

	r = MMIO32(I2C_CR1(base[i2c]));
	r &= ~(I2C_CR1_DNF3 | I2C_CR1_DNF2 | I2C_CR1_DNF1 | I2C_CR1_DNF0);
	MMIO32(I2C_CR1(base[i2c])) = r | (dnf & 0xf) << 8;
}

void i2c_set_delay(enum i2c i2c, int sdadel, int scldel)
{
	int r;

	r = MMIO32(I2C_TIMINGR(base[i2c]));
	r &= 0xff00ffff;
	MMIO32(I2C_TIMINGR(base[i2c])) = r | (scldel & 0xf) << 20 |
		(sdadel & 0xf) << 16;
}

void i2c_init_master(enum i2c i2c, int prescaler, int scl_hi, int scl_lo,
		     int config)
{
	int r;

	r = MMIO32(I2C_TIMINGR(base[i2c]));
	r &= 0x0fff0000;
	MMIO32(I2C_TIMINGR(base[i2c])) = r | ((prescaler - 1) & 0xf) << 28 |
		((scl_hi - 1) & 0xff) << 8 | ((scl_lo - 1) & 0xff);
	r = MMIO32(I2C_CR1(base[i2c]));
	r &= ~(I2C_CR1_PECEN | I2C_CR1_ALERTEN | I2C_CR1_SMBDEN |
	       I2C_CR1_SMBHEN | I2C_CR1_GCEN | I2C_CR1_WUPEN |
	       I2C_CR1_NOSTRETCH | I2C_CR1_SBC | I2C_CR1_ANFOFF);
	MMIO32(I2C_CR1(base[i2c])) = r | (config & 0xffdfff);
}

void i2c_enable(enum i2c i2c)
{
	MMIO32(I2C_CR1(base[i2c])) |= I2C_CR1_PE;
}

void i2c_disable(enum i2c i2c)
{
	MMIO32(I2C_CR1(base[i2c])) &= ~I2C_CR1_PE;
}

void i2c_enable_dma(enum i2c i2c, enum i2c_dma request)
{
	MMIO32(I2C_CR1(base[i2c])) |= request;
}

void i2c_disable_dma(enum i2c i2c, enum i2c_dma request)
{
	MMIO32(I2C_CR1(base[i2c])) &= ~request;
}

void i2c_start(enum i2c i2c, int sadd, int nbytes)
{
	MMIO32(I2C_CR2(base[i2c])) = I2C_CR2_START | (nbytes & 0xff) << 16 |
		(sadd & 0x3ff) | ((nbytes | sadd) & (I2C_CR2_AUTOEND |
						     I2C_CR2_RELOAD |
						     I2C_CR2_HEAD10R |
						     I2C_CR2_ADD10 |
						     I2C_CR2_RD_WRN));
}

void i2c_stop(enum i2c i2c)
{
	MMIO32(I2C_CR2(base[i2c])) |= I2C_CR2_STOP;
}

void i2c_reload(enum i2c i2c, int nbytes)
{
	int r;

	r = MMIO32(I2C_CR2(base[i2c]));
	r &= ~(I2C_CR2_RELOAD | 0xff << 16);
	MMIO32(I2C_CR2(base[i2c])) = r | (nbytes & 0xff) << 16 |
		(nbytes & I2C_CR2_RELOAD);
}

void i2c_pecbyte(enum i2c i2c)
{
	MMIO32(I2C_CR2(base[i2c])) |= I2C_CR2_PECBYTE;
}

void i2c_init_slave(enum i2c i2c, int oa1, int oa2, int config)
{
	int r;

	MMIO32(I2C_OAR1(base[i2c])) = oa1 & 0x87ff;
	MMIO32(I2C_OAR2(base[i2c])) = oa2 & 0x87fe;
	r = MMIO32(I2C_CR1(base[i2c]));
	r &= ~(I2C_CR1_PECEN | I2C_CR1_ALERTEN | I2C_CR1_SMBDEN |
	       I2C_CR1_SMBHEN | I2C_CR1_GCEN | I2C_CR1_WUPEN |
	       I2C_CR1_NOSTRETCH | I2C_CR1_SBC | I2C_CR1_ANFOFF);
	MMIO32(I2C_CR1(base[i2c])) = r | (config & 0xffdfff);
}

void i2c_nack(enum i2c i2c)
{
	MMIO32(I2C_CR2(base[i2c])) |= I2C_CR2_NACK;
}

void i2c_enable_wakeup(enum i2c i2c)
{
	MMIO32(I2C_CR1(base[i2c])) |= I2C_CR1_WUPEN;
}

void i2c_disable_wakeup(enum i2c i2c)
{
	MMIO32(I2C_CR1(base[i2c])) &= ~I2C_CR1_WUPEN;
}

void i2c_set_timeout(enum i2c i2c, int timeouta, int timeoutb)
{
	MMIO32(I2C_TIMEOUTR(base[i2c])) = (timeoutb & 0x8fff) << 16 |
		(timeouta & 0x9fff);
}

void i2c_enable_interrupt(enum i2c i2c, int interrupt)
{
	int r;

	r = MMIO32(I2C_CR1(base[i2c]));
	if (interrupt & I2C_TXIS)
		r |= I2C_CR1_TXIE;
	if (interrupt & I2C_RXNE)
		r |= I2C_CR1_RXIE;
	if (interrupt & I2C_ADDR)
		r |= I2C_CR1_ADDRIE;
	if (interrupt & I2C_NACKF)
		r |= I2C_CR1_NACKIE;
	if (interrupt & I2C_STOPF)
		r |= I2C_CR1_STOPIE;
	if (interrupt & (I2C_TCR | I2C_TC))
		r |= I2C_CR1_TCIE;
	if (interrupt & (I2C_ARLO | I2C_BERR | I2C_OVR | I2C_TIMEOUT |
			 I2C_PECERR | I2C_ALERT))
		r |= I2C_CR1_ERRIE;
	MMIO32(I2C_CR1(base[i2c])) = r;
}

void i2c_disable_interrupt(enum i2c i2c, int interrupt)
{
	int r;

	r = MMIO32(I2C_CR1(base[i2c]));
	if (interrupt & I2C_TXIS)
		r &= ~I2C_CR1_TXIE;
	if (interrupt & I2C_RXNE)
		r &= ~I2C_CR1_RXIE;
	if (interrupt & I2C_ADDR)
		r &= ~I2C_CR1_ADDRIE;
	if (interrupt & I2C_NACKF)
		r &= ~I2C_CR1_NACKIE;
	if (interrupt & I2C_STOPF)
		r &= ~I2C_CR1_STOPIE;
	if (interrupt & (I2C_TCR | I2C_TC))
		r &= ~I2C_CR1_TCIE;
	if (interrupt & (I2C_ARLO | I2C_BERR | I2C_OVR | I2C_TIMEOUT |
			 I2C_PECERR | I2C_ALERT))
		r &= ~I2C_CR1_ERRIE;
	MMIO32(I2C_CR1(base[i2c])) = r;
}

int i2c_get_interrupt_mask(enum i2c i2c, int interrupt)
{
	int r;
	int m;

	r = MMIO32(I2C_CR1(base[i2c]));
	m = 0;
	if (r & I2C_CR1_TXIE)
		m |= I2C_TXIS;
	if (r & I2C_CR1_RXIE)
		m |= I2C_RXNE;
	if (r & I2C_CR1_ADDRIE)
		m |= I2C_ADDR;
	if (r & I2C_CR1_NACKIE)
		m |= I2C_NACKF;
	if (r & I2C_CR1_STOPIE)
		m |= I2C_STOPF;
	if (r & I2C_CR1_TCIE)
		m |= I2C_TCR | I2C_TC;
	if (r & I2C_CR1_ERRIE)
		m |= I2C_ARLO | I2C_BERR | I2C_OVR | I2C_TIMEOUT | I2C_PECERR |
			I2C_ALERT;
	return m & interrupt;
}

int i2c_get_interrupt_status(enum i2c i2c, int interrupt)
{
	return MMIO32(I2C_ISR(base[i2c])) & interrupt;
}

void i2c_clear_interrupt(enum i2c i2c, int interrupt)
{
	MMIO32(I2C_ICR(base[i2c])) = interrupt & (I2C_ICR_ALERTCF |
						  I2C_ICR_TIMOUTCF |
						  I2C_ICR_PECCF |
						  I2C_ICR_OVRCF |
						  I2C_ICR_ARLOCF |
						  I2C_ICR_BERRCF |
						  I2C_ICR_STOPCF |
						  I2C_ICR_NACKCF |
						  I2C_ICR_ADDRCF);
}

void i2c_generate_txis(enum i2c i2c)
{
	MMIO32(I2C_ISR(base[i2c])) = I2C_ISR_TXIS;
}

void i2c_flush_txdr(enum i2c i2c)
{
	MMIO32(I2C_ISR(base[i2c])) = I2C_ISR_TXE;
}

int i2c_get_pec(enum i2c i2c)
{
	return MMIO32(I2C_PECR(base[i2c]));
}

void i2c_send(enum i2c i2c, int data)
{
	MMIO32(I2C_TXDR(base[i2c])) = data & 0xff;
}

int i2c_recv(enum i2c i2c)
{
	return MMIO32(I2C_RXDR(base[i2c]));
}

void i2c_send_blocking(enum i2c i2c, int data)
{
	while (!(MMIO32(I2C_ISR(base[i2c])) & (I2C_ISR_TIMEOUT | I2C_ISR_ARLO |
					       I2C_ISR_STOPF | I2C_ISR_NACKF |
					       I2C_ISR_TXIS)))
		;
	if (!(MMIO32(I2C_ISR(base[i2c])) & I2C_ISR_TXIS))
		return;
	MMIO32(I2C_TXDR(base[i2c])) = data & 0xff;
}

int i2c_recv_blocking(enum i2c i2c)
{
	while (!(MMIO32(I2C_ISR(base[i2c])) & (I2C_ISR_TIMEOUT | I2C_ISR_ARLO |
					       I2C_ISR_STOPF | I2C_ISR_NACKF |
					       I2C_ISR_RXNE)))
		;
	if (!(MMIO32(I2C_ISR(base[i2c])) & I2C_ISR_RXNE))
		return 0;
	return MMIO32(I2C_RXDR(base[i2c]));
}
