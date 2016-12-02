/*
 * SPI functions
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
#include <stdbool.h>

#include <mmio.h>
#include <memorymap.h>
#include <spi.h>

static const int base[] = {
	SPI1_BASE,
	SPI2_BASE
};

void spi_init_master(enum spi spi, int prescaler, int bits, int config)
{
	int i;
	int r;

	if (config & SPI_I2S_MODE) {
		r = prescaler / 2;
		if (r < 2 || r > 255)
			return;
		if (bits > 32)
			return;
		MMIO32(SPI_I2SPR(base[spi])) = r |
			((config >> 16) & (SPI_I2SPR_MCKOE | SPI_I2SPR_ODD));
		if (bits <= 16)
			r = SPI_I2SCFGR_DATLEN_16;
		else if (bits <= 24)
			r = SPI_I2SCFGR_DATLEN_24;
		else
			r = SPI_I2SCFGR_DATLEN_32;
		MMIO32(SPI_I2SCFGR(base[spi])) = r | SPI_I2SCFGR_I2SCFG1 |
			(config & (SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SE |
				   SPI_I2SCFGR_I2SCFG0 | SPI_I2SCFGR_PCMSYNC |
				   SPI_I2SCFGR_I2SSTD1 | SPI_I2SCFGR_I2SSTD0 |
				   SPI_I2SCFGR_CKPOL | SPI_I2SCFGR_CHLEN));
	} else {
		for (i = 0; i < 8; i++) {
			if (prescaler == 2 << i)
				break;
		}
		if (i >= 8)
			return;
		if (bits > 16)
			return;
		r = MMIO32(SPI_CR2(base[spi]));
		r &= ~(SPI_CR2_FRF | SPI_CR2_SSOE | SPI_CR2_TXDMAEN |
		       SPI_CR2_RXDMAEN);
		MMIO32(SPI_CR2(base[spi])) = r |
			((config >> 16) & (SPI_CR2_FRF | SPI_CR2_SSOE |
					   SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN));
		r = i << 3;
		if (bits > 8)
			r |= SPI_CR1_DFF;
		MMIO32(SPI_CR1(base[spi])) = r | SPI_CR1_MSTR |
			(config & (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE |
				   SPI_CR1_CRCEN | SPI_CR1_RXONLY |
				   SPI_CR1_SSM | SPI_CR1_SSI |
				   SPI_CR1_LSBFIRST | SPI_CR1_SPE |
				   SPI_CR1_CPOL | SPI_CR1_CPHA));
	}
}

void spi_init_slave(enum spi spi, int bits, int config)
{
	int r;

	if (config & SPI_I2S_MODE) {
		if (bits > 32)
			return;
		if (bits <= 16)
			r = SPI_I2SCFGR_DATLEN_16;
		else if (bits <= 24)
			r = SPI_I2SCFGR_DATLEN_24;
		else
			r = SPI_I2SCFGR_DATLEN_32;
		MMIO32(SPI_I2SCFGR(base[spi])) = r |
			(config & (SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SE |
				   SPI_I2SCFGR_I2SCFG0 | SPI_I2SCFGR_PCMSYNC |
				   SPI_I2SCFGR_I2SSTD1 | SPI_I2SCFGR_I2SSTD0 |
				   SPI_I2SCFGR_CKPOL | SPI_I2SCFGR_CHLEN));
	} else {
		if (bits > 16)
			return;
		r = MMIO32(SPI_CR2(base[spi]));
		r &= ~(SPI_CR2_FRF | SPI_CR2_SSOE | SPI_CR2_TXDMAEN |
		       SPI_CR2_RXDMAEN);
		MMIO32(SPI_CR2(base[spi])) = r |
			((config >> 16) & (SPI_CR2_FRF | SPI_CR2_SSOE |
					   SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN));
		MMIO32(SPI_CR1(base[spi])) = (bits > 8 ? SPI_CR1_DFF : 0) |
			(config & (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE |
				   SPI_CR1_CRCEN | SPI_CR1_RXONLY |
				   SPI_CR1_SSM | SPI_CR1_SSI |
				   SPI_CR1_LSBFIRST | SPI_CR1_SPE |
				   SPI_CR1_CPOL | SPI_CR1_CPHA));
	}
}

void spi_set_spi_mode(enum spi spi)
{
	MMIO32(SPI_I2SCFGR(base[spi])) &= ~SPI_I2SCFGR_I2SMOD;
}

void spi_set_i2s_mode(enum spi spi)
{
	MMIO32(SPI_I2SCFGR(base[spi])) |= SPI_I2SCFGR_I2SMOD;
}

void spi_enable(enum spi spi)
{
	MMIO32(SPI_CR1(base[spi])) |= SPI_CR1_SPE;
}

void spi_disable(enum spi spi)
{
	MMIO32(SPI_CR1(base[spi])) &= ~SPI_CR1_SPE;
}

void spi_i2s_enable(enum spi spi)
{
	MMIO32(SPI_I2SCFGR(base[spi])) |= SPI_I2SCFGR_I2SE;
}

void spi_i2s_disable(enum spi spi)
{
	MMIO32(SPI_I2SCFGR(base[spi])) &= ~SPI_I2SCFGR_I2SE;
}

void spi_set_ss(enum spi spi, bool value)
{
	if (value)
		MMIO32(SPI_CR1(base[spi])) |= SPI_CR1_SSI;
	else
		MMIO32(SPI_CR1(base[spi])) &= ~SPI_CR1_SSI;
}

void spi_set_bidi_output(enum spi spi)
{
	MMIO32(SPI_CR1(base[spi])) |= SPI_CR1_BIDIOE;
}

void spi_set_bidi_input(enum spi spi)
{
	MMIO32(SPI_CR1(base[spi])) &= ~SPI_CR1_BIDIOE;
}

void spi_enable_interrupt(enum spi spi, int interrupt)
{
	int r;

	if (interrupt & (SPI_TXE | SPI_RXNE | SPI_ERROR)) {
		r = MMIO32(SPI_CR2(base[spi]));
		if (interrupt & SPI_TXE)
			r |= SPI_CR2_TXEIE;
		if (interrupt & SPI_RXNE)
			r |= SPI_CR2_RXNEIE;
		if (interrupt & SPI_ERROR)
			r |= SPI_CR2_ERRIE;
		MMIO32(SPI_CR2(base[spi])) = r;
	}
}

void spi_disable_interrupt(enum spi spi, int interrupt)
{
	int r;

	if (interrupt & (SPI_TXE | SPI_RXNE | SPI_ERROR)) {
		r = MMIO32(SPI_CR2(base[spi]));
		if (interrupt & SPI_TXE)
			r &= ~SPI_CR2_TXEIE;
		if (interrupt & SPI_RXNE)
			r &= ~SPI_CR2_RXNEIE;
		if (interrupt & SPI_ERROR)
			r &= ~SPI_CR2_ERRIE;
		MMIO32(SPI_CR2(base[spi])) = r;
	}
}

int spi_get_interrupt_mask(enum spi spi, int interrupt)
{
	int r;
	int m;

	r = MMIO32(SPI_CR2(base[spi]));
	m = 0;
	if (r & SPI_CR2_TXEIE)
		m |= SPI_TXE;
	if (r & SPI_CR2_RXNEIE)
		m |= SPI_RXNE;
	if (r & SPI_CR2_ERRIE)
		m |= SPI_ERROR;
	return m & interrupt;
}

int spi_get_interrupt_status(enum spi spi, int interrupt)
{
	return MMIO32(SPI_SR(base[spi])) & interrupt;
}

void spi_clear_interrupt(enum spi spi, int interrupt)
{
	if (interrupt & SPI_CRCERR)
		MMIO32(SPI_SR(base[spi])) &= ~SPI_SR_CRCERR;
}

void spi_enable_dma(enum spi spi, enum spi_dma request)
{
	MMIO32(SPI_CR2(base[spi])) |= request >> 16;
}

void spi_disable_dma(enum spi spi, enum spi_dma request)
{
	MMIO32(SPI_CR2(base[spi])) &= ~(request >> 16);
}

void spi_set_crc_polynomial(enum spi spi, int polynomial)
{
	MMIO32(SPI_CRCPR(base[spi])) = polynomial & 0xffff;
}

void spi_enable_crc_phase(enum spi spi)
{
	MMIO32(SPI_CR1(base[spi])) |= SPI_CR1_CRCNEXT;
}

void spi_disable_crc_phase(enum spi spi)
{
	MMIO32(SPI_CR1(base[spi])) &= ~SPI_CR1_CRCNEXT;
}

int spi_get_rx_crc(enum spi spi)
{
	return MMIO32(SPI_RXCRCR(base[spi]));
}

int spi_get_tx_crc(enum spi spi)
{
	return MMIO32(SPI_TXCRCR(base[spi]));
}

void spi_send(enum spi spi, int data)
{
	MMIO32(SPI_DR(base[spi])) = data & 0xffff;
}

int spi_recv(enum spi spi)
{
	return MMIO32(SPI_DR(base[spi]));
}

void spi_send_blocking(enum spi spi, int data)
{
	while (!(MMIO32(SPI_SR(base[spi])) & SPI_SR_TXE))
		;
	MMIO32(SPI_DR(base[spi])) = data & 0xffff;
}

int spi_recv_blocking(enum spi spi)
{
	while (!(MMIO32(SPI_SR(base[spi])) & SPI_SR_RXNE))
		;
	return MMIO32(SPI_DR(base[spi]));
}
