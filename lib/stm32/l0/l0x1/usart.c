/*
 * USART functions
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
#include <usart.h>

static const int base[] = {
	USART1_BASE,
	USART2_BASE,
	USART4_BASE,
	USART5_BASE
};

void usart_set_baudrate(enum usart usart, int clock, int baud)
{
	int usartdiv;

	if (clock < 0 || baud <= 0 || clock < baud)
		return;
	usartdiv = (2 * clock + baud) / (2 * baud);
	if (usartdiv > 65535)
		return;
	MMIO32(USART_CR1(base[usart])) &= ~USART_CR1_OVER8;
	MMIO32(USART_BRR(base[usart])) = usartdiv;
}

void usart_set_baudrate_over8(enum usart usart, int clock, int baud)
{
	int usartdiv;

	if (clock < 0 || baud <= 0 || clock < baud)
		return;
	usartdiv = (4 * clock + baud) / (2 * baud);
	if (usartdiv > 65535)
		return;
	MMIO32(USART_CR1(base[usart])) |= USART_CR1_OVER8;
	MMIO32(USART_BRR(base[usart])) = (usartdiv & ~0xf) |
		(usartdiv & 0xf) >> 1;
}

void usart_enable_autobaudrate(enum usart usart, enum usart_autobaud mode)
{
	int r;

	r = MMIO32(USART_CR2(base[usart]));
	r &= ~(USART_CR2_ABRMOD1 | USART_CR2_ABRMOD0);
	MMIO32(USART_CR2(base[usart])) = r | mode | USART_CR2_ABREN;
}

void usart_disable_autobaudrate(enum usart usart)
{
	MMIO32(USART_CR2(base[usart])) &= ~USART_CR2_ABREN;
}

void usart_set_databits(enum usart usart, int bits)
{
	int r;

	r = MMIO32(USART_CR1(base[usart]));
	r &= ~(USART_CR1_M1 | USART_CR1_M0);
	if (bits == 9)
		r |= USART_CR1_M0;
	else if (bits == 7)
		r |= USART_CR1_M1;
	MMIO32(USART_CR1(base[usart])) = r;
}

void usart_set_stopbits(enum usart usart, enum usart_stop stopbits)
{
	int r;

	r = MMIO32(USART_CR2(base[usart]));
	r &= ~(USART_CR2_STOP1 | USART_CR2_STOP0);
	MMIO32(USART_CR2(base[usart])) = r | stopbits;
}

void usart_set_parity(enum usart usart, enum usart_parity parity)
{
	int r;

	r = MMIO32(USART_CR1(base[usart]));
	r &= ~(USART_CR1_PCE | USART_CR1_PS);
	MMIO32(USART_CR1(base[usart])) = r | parity;
}

void usart_set_flow_control(enum usart usart, enum usart_flow flow)
{
	int r;

	r = MMIO32(USART_CR3(base[usart]));
	r &= ~(USART_CR3_CTSE | USART_CR3_RTSE);
	MMIO32(USART_CR3(base[usart])) = r | flow;
}

void usart_set_txrx(enum usart usart, enum usart_txrx txrx, int option)
{
	int r;

	r = MMIO32(USART_CR2(base[usart]));
	r &= ~(USART_CR2_MSBFIRST | USART_CR2_DATAINV | USART_CR2_TXINV |
	       USART_CR2_RXINV | USART_CR2_SWAP);
	MMIO32(USART_CR2(base[usart])) = r | (option & (USART_CR2_MSBFIRST |
							USART_CR2_DATAINV |
							USART_CR2_TXINV |
							USART_CR2_RXINV |
							USART_CR2_SWAP));
	r = MMIO32(USART_CR3(base[usart]));
	r &= ~USART_CR3_HDSEL;
	MMIO32(USART_CR3(base[usart])) = r | (option & USART_CR3_HDSEL);
	r = MMIO32(USART_CR1(base[usart]));
	r &= ~(USART_CR1_TE | USART_CR1_RE);
	MMIO32(USART_CR1(base[usart])) = r | txrx;
}

void usart_set_node_address(enum usart usart, int addr, int length)
{
	int r;

	r = MMIO32(USART_CR2(base[usart]));
	r &= ~(USART_CR2_ADD7 | USART_CR2_ADD6 | USART_CR2_ADD5 |
	       USART_CR2_ADD4 | USART_CR2_ADD3 | USART_CR2_ADD2 |
	       USART_CR2_ADD1 | USART_CR2_ADD0);
	if (length > 4)
		r |= USART_CR2_ADDM7;
	else
		r &= ~USART_CR2_ADDM7;
	MMIO32(USART_CR2(base[usart])) = r | addr << 24;
}

void usart_enable_mute(enum usart usart, bool wake_addr_mark)
{
	int r;

	r = MMIO32(USART_CR1(base[usart]));
	if (wake_addr_mark)
		r |= USART_CR1_WAKE;
	else
		r &= ~USART_CR1_WAKE;
	MMIO32(USART_CR1(base[usart])) = r | USART_CR1_MME;
}

void usart_disable_mute(enum usart usart)
{
	MMIO32(USART_CR1(base[usart])) &= ~USART_CR1_MME;
}

void usart_enable_de(enum usart usart, int deat, int dedt, bool active_low)
{
	int r;

	r = MMIO32(USART_CR1(base[usart]));
	r &= ~(USART_CR1_DEAT4 | USART_CR1_DEAT3 | USART_CR1_DEAT2 |
	       USART_CR1_DEAT1 | USART_CR1_DEAT0 |
	       USART_CR1_DEDT4 | USART_CR1_DEDT3 | USART_CR1_DEDT2 |
	       USART_CR1_DEDT1 | USART_CR1_DEDT0);
	MMIO32(USART_CR1(base[usart])) = r | (deat & 0x1f) << 21 |
		(dedt & 0x1f) << 16;
	r = MMIO32(USART_CR3(base[usart]));
	if (active_low)
		r |= USART_CR3_DEP;
	else
		r &= ~USART_CR3_DEP;
	MMIO32(USART_CR3(base[usart])) = r | USART_CR3_DEM;
}

void usart_disable_de(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) &= ~USART_CR3_DEM;
}

void usart_disable_dma_on_reception_error(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) |= USART_CR3_DDRE;
}

void usart_enable_dma_on_reception_error(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) &= ~USART_CR3_DDRE;
}

void usart_disable_overrun(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) |= USART_CR3_OVRDIS;
}

void usart_enable_overrun(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) &= ~USART_CR3_OVRDIS;
}

void usart_enable_receiver_timeout(enum usart usart)
{
	MMIO32(USART_CR2(base[usart])) |= USART_CR2_RTOEN;
}

void usart_disable_receiver_timeout(enum usart usart)
{
	MMIO32(USART_CR2(base[usart])) &= ~USART_CR2_RTOEN;
}

void usart_enable_one_sample_bit(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) |= USART_CR3_ONEBIT;
}

void usart_disable_one_sample_bit(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) &= ~USART_CR3_ONEBIT;
}

void usart_enable_irda_mode(enum usart usart, int prescaler, bool low_power)
{
	int r;

	if (!(prescaler & 0xff))
		return;
	r = MMIO32(USART_GTPR(base[usart]));
	r &= ~0xff;
	MMIO32(USART_GTPR(base[usart])) = r | (prescaler & 0xff);
	r = MMIO32(USART_CR3(base[usart]));
	if (low_power)
		r |= USART_CR3_IRLP;
	else
		r &= ~USART_CR3_IRLP;
	MMIO32(USART_CR3(base[usart])) = r | USART_CR3_IREN;
}

void usart_disable_irda_mode(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) &= ~USART_CR3_IREN;
}

void usart_enable_lin_mode(enum usart usart, int break_detection_length)
{
	int r;

	r = MMIO32(USART_CR2(base[usart]));
	if (break_detection_length == 11)
		r |= USART_CR2_LBDL;
	else
		r &= ~USART_CR2_LBDL;
	MMIO32(USART_CR2(base[usart])) = r | USART_CR2_LINEN;
}

void usart_disable_lin_mode(enum usart usart)
{
	MMIO32(USART_CR2(base[usart])) &= ~USART_CR2_LINEN;
}

void usart_enable_sync_mode(enum usart usart, bool cpol, bool cpha, bool lbcl)
{
	int r;

	r = MMIO32(USART_CR2(base[usart]));
	if (cpol)
		r |= USART_CR2_CPOL;
	else
		r &= ~USART_CR2_CPOL;
	if (cpha)
		r |= USART_CR2_CPHA;
	else
		r &= ~USART_CR2_CPHA;
	if (lbcl)
		r |= USART_CR2_LBCL;
	else
		r &= ~USART_CR2_LBCL;
	MMIO32(USART_CR2(base[usart])) = r | USART_CR2_CLKEN;
}

void usart_disable_sync_mode(enum usart usart)
{
	MMIO32(USART_CR2(base[usart])) &= ~USART_CR2_CLKEN;
}

void usart_enable_smartcard_mode(enum usart usart, int prescaler,
				 int guard_time, bool clken,
				 int auto_retry_count, bool nack)
{
	int r;

	if (!((prescaler >> 1) & 0x1f))
		return;
	r = MMIO32(USART_CR3(base[usart]));
	r &= ~(USART_CR3_SCARCNT2 | USART_CR3_SCARCNT1 | USART_CR3_SCARCNT0);
	if (nack)
		r |= USART_CR3_NACK;
	else
		r &= ~USART_CR3_NACK;
	MMIO32(USART_CR3(base[usart])) = r | (auto_retry_count & 7) << 17 |
		USART_CR3_SCEN;
	MMIO32(USART_GTPR(base[usart])) = (guard_time & 0xff) << 8 |
		((prescaler >> 1) & 0x1f);
	if (clken)
		MMIO32(USART_CR2(base[usart])) |= USART_CR2_CLKEN;
	else
		MMIO32(USART_CR2(base[usart])) &= ~USART_CR2_CLKEN;
}

void usart_disable_smartcard_mode(enum usart usart)
{
	MMIO32(USART_CR2(base[usart])) &= ~USART_CR2_CLKEN;
	MMIO32(USART_CR3(base[usart])) &= ~USART_CR3_SCEN;
}

void usart_init(enum usart usart, int clock, int baud, int bits,
		enum usart_stop stopbits, enum usart_parity parity,
		enum usart_flow flow, enum usart_txrx txrx)
{
	int r;
	int cr1;

	if (clock < 0 || baud <= 0 || clock < baud)
		return;
	r = (2 * clock + baud) / (2 * baud);
	if (r > 65535)
		return;
	/* Data bits */
	cr1 = MMIO32(USART_CR1(base[usart]));
	cr1 &= ~(USART_CR1_M1 | USART_CR1_M0);
	if (bits == 9)
		cr1 |= USART_CR1_M0;
	else if (bits == 7)
		cr1 |= USART_CR1_M1;
	cr1 &= ~USART_CR1_OVER8;
	MMIO32(USART_CR1(base[usart])) = cr1;
	/* Baud rate */
	MMIO32(USART_BRR(base[usart])) = r;
	/* Stop bits */
	r = MMIO32(USART_CR2(base[usart]));
	r &= ~(USART_CR2_STOP1 | USART_CR2_STOP0);
	MMIO32(USART_CR2(base[usart])) = r | stopbits;
	/* Parity */
	cr1 &= ~(USART_CR1_PCE | USART_CR1_PS);
	cr1 |= parity;
	MMIO32(USART_CR1(base[usart])) = cr1;
	/* Flow control */
	r = MMIO32(USART_CR3(base[usart]));
	r &= ~(USART_CR3_CTSE | USART_CR3_RTSE);
	MMIO32(USART_CR3(base[usart])) = r | flow;
	/* Enable USART */
	cr1 |= USART_CR1_UE;
	MMIO32(USART_CR1(base[usart])) = cr1;
	/* Tx, Rx */
	cr1 &= ~(USART_CR1_TE | USART_CR1_RE);
	MMIO32(USART_CR1(base[usart])) = cr1 | txrx;
}

void usart_enable(enum usart usart)
{
	MMIO32(USART_CR1(base[usart])) |= USART_CR1_UE;
}

void usart_disable(enum usart usart)
{
	MMIO32(USART_CR1(base[usart])) &= ~USART_CR1_UE;
}

void usart_enable_in_stop_mode(enum usart usart)
{
	MMIO32(USART_CR1(base[usart])) |= USART_CR1_UESM;
}

void usart_disable_in_stop_mode(enum usart usart)
{
	MMIO32(USART_CR1(base[usart])) &= ~USART_CR1_UESM;
}

void usart_send(enum usart usart, int data)
{
	int r;

	r = MMIO32(USART_TDR(base[usart]));
	r &= ~0x1ff;
	MMIO32(USART_TDR(base[usart])) = r | (data & 0x1ff);
}

int usart_recv(enum usart usart)
{
	return MMIO32(USART_RDR(base[usart])) & 0x1ff;
}

void usart_send_blocking(enum usart usart, int data)
{
	int r;

	while (!(MMIO32(USART_ISR(base[usart])) & USART_ISR_TXE))
		;
	r = MMIO32(USART_TDR(base[usart]));
	r &= ~0x1ff;
	MMIO32(USART_TDR(base[usart])) = r | (data & 0x1ff);
}

int usart_recv_blocking(enum usart usart)
{
	while (!(MMIO32(USART_ISR(base[usart])) & USART_ISR_RXNE))
		;
	return MMIO32(USART_RDR(base[usart])) & 0x1ff;
}

void usart_enable_dma(enum usart usart, enum usart_dma request)
{
	MMIO32(USART_CR3(base[usart])) |= request;
}

void usart_disable_dma(enum usart usart, enum usart_dma request)
{
	MMIO32(USART_CR3(base[usart])) &= ~request;
}

void usart_enable_interrupt(enum usart usart, int interrupt)
{
	int r;

	if (interrupt & (USART_CMF | USART_EOBF | USART_RTOF | USART_TXE |
			 USART_TC | USART_RXNE | USART_IDLE | USART_PE)) {
		r = MMIO32(USART_CR1(base[usart]));
		if (interrupt & USART_CMF)
			r |= USART_CR1_CMIE;
		if (interrupt & USART_EOBF)
			r |= USART_CR1_EOBIE;
		if (interrupt & USART_RTOF)
			r |= USART_CR1_RTOIE;
		if (interrupt & USART_TXE)
			r |= USART_CR1_TXEIE;
		if (interrupt & USART_TC)
			r |= USART_CR1_TCIE;
		if (interrupt & USART_RXNE)
			r |= USART_CR1_RXNEIE;
		if (interrupt & USART_IDLE)
			r |= USART_CR1_IDLEIE;
		if (interrupt & USART_PE)
			r |= USART_CR1_PEIE;
		MMIO32(USART_CR1(base[usart])) = r;
	}
	if (interrupt & USART_LBDF)
		MMIO32(USART_CR2(base[usart])) |= USART_CR2_LBDIE;
	if (interrupt & (USART_TCBGT | USART_WUF | USART_CTSIF | USART_ORE |
			 USART_NF | USART_FE)) {
		r = MMIO32(USART_CR3(base[usart]));
		if (interrupt & USART_TCBGT)
			r |= USART_CR3_TCBGTIE;
		if (interrupt & USART_WUF)
			r |= USART_CR3_WUFIE;
		if (interrupt & USART_CTSIF)
			r |= USART_CR3_CTSIE;
		if (interrupt & (USART_ORE | USART_NF | USART_FE))
			r |= USART_CR3_EIE;
		MMIO32(USART_CR3(base[usart])) = r;
	}
}

void usart_disable_interrupt(enum usart usart, int interrupt)
{
	int r;

	if (interrupt & (USART_CMF | USART_EOBF | USART_RTOF | USART_TXE |
			 USART_TC | USART_RXNE | USART_IDLE | USART_PE)) {
		r = MMIO32(USART_CR1(base[usart]));
		if (interrupt & USART_CMF)
			r &= ~USART_CR1_CMIE;
		if (interrupt & USART_EOBF)
			r &= ~USART_CR1_EOBIE;
		if (interrupt & USART_RTOF)
			r &= ~USART_CR1_RTOIE;
		if (interrupt & USART_TXE)
			r &= ~USART_CR1_TXEIE;
		if (interrupt & USART_TC)
			r &= ~USART_CR1_TCIE;
		if (interrupt & USART_RXNE)
			r &= ~USART_CR1_RXNEIE;
		if (interrupt & USART_IDLE)
			r &= ~USART_CR1_IDLEIE;
		if (interrupt & USART_PE)
			r &= ~USART_CR1_PEIE;
		MMIO32(USART_CR1(base[usart])) = r;
	}
	if (interrupt & USART_LBDF)
		MMIO32(USART_CR2(base[usart])) &= ~USART_CR2_LBDIE;
	if (interrupt & (USART_TCBGT | USART_WUF | USART_CTSIF | USART_ORE |
			 USART_NF | USART_FE)) {
		r = MMIO32(USART_CR3(base[usart]));
		if (interrupt & USART_TCBGT)
			r &= ~USART_CR3_TCBGTIE;
		if (interrupt & USART_WUF)
			r &= ~USART_CR3_WUFIE;
		if (interrupt & USART_CTSIF)
			r &= ~USART_CR3_CTSIE;
		if (interrupt & (USART_ORE | USART_NF | USART_FE))
			r &= ~USART_CR3_EIE;
		MMIO32(USART_CR3(base[usart])) = r;
	}
}

int usart_get_interrupt_mask(enum usart usart, int interrupt)
{
	int r;
	int f;

	f = 0;
	if (interrupt & (USART_CMF | USART_EOBF | USART_RTOF | USART_TXE |
			 USART_TC | USART_RXNE | USART_IDLE | USART_PE)) {
		r = MMIO32(USART_CR1(base[usart]));
		if (interrupt & USART_CMF) {
			if (r & USART_CR1_CMIE)
				f |= USART_CMF;
		}
		if (interrupt & USART_EOBF) {
			if (r & USART_CR1_EOBIE)
				f |= USART_EOBF;
		}
		if (interrupt & USART_RTOF) {
			if (r & USART_CR1_RTOIE)
				f |= USART_RTOF;
		}
		if (interrupt & USART_TXE) {
			if (r & USART_CR1_TXEIE)
				f |= USART_TXE;
		}
		if (interrupt & USART_TC) {
			if (r & USART_CR1_TCIE)
				f |= USART_TC;
		}
		if (interrupt & USART_RXNE) {
			if (r & USART_CR1_RXNEIE)
				f |= USART_RXNE;
		}
		if (interrupt & USART_IDLE) {
			if (r & USART_CR1_IDLEIE)
				f |= USART_IDLE;
		}
		if (interrupt & USART_PE) {
			if (r & USART_CR1_PEIE)
				f |= USART_PE;
		}
	}
	if (interrupt & USART_LBDF) {
		if (MMIO32(USART_CR2(base[usart])) & USART_CR2_LBDIE)
			f |= USART_LBDF;
	}
	if (interrupt & (USART_TCBGT | USART_WUF | USART_CTSIF | USART_ORE |
			 USART_NF | USART_FE)) {
		r = MMIO32(USART_CR3(base[usart]));
		if (interrupt & USART_TCBGT) {
			if (r & USART_CR3_TCBGTIE)
				f |= USART_TCBGT;
		}
		if (interrupt & USART_WUF) {
			if (r & USART_CR3_WUFIE)
				f |= USART_WUF;
		}
		if (interrupt & USART_CTSIF) {
			if (r & USART_CR3_CTSIE)
				f |= USART_CTSIF;
		}
		if (interrupt & (USART_ORE | USART_NF | USART_FE)) {
			if (r & USART_CR3_EIE)
				f |= interrupt & (USART_ORE | USART_NF |
						  USART_FE);
		}
	}
	return f;
}

int usart_get_interrupt_status(enum usart usart, int interrupt)
{
	return MMIO32(USART_ISR(base[usart])) & interrupt;
}

void usart_clear_interrupt(enum usart usart, int interrupt)
{
	if (interrupt & USART_TCBGT)
		interrupt |= USART_ICR_TCBGTCF;
	else
		interrupt &= ~USART_ICR_TCBGTCF;
	MMIO32(USART_ICR(base[usart])) = interrupt & (USART_ICR_WUCF |
						      USART_ICR_CMCF |
						      USART_ICR_EOBCF |
						      USART_ICR_RTOCF |
						      USART_ICR_CTSCF |
						      USART_ICR_LBDCF |
						      USART_ICR_TCBGTCF |
						      USART_ICR_TCCF |
						      USART_ICR_IDLECF |
						      USART_ICR_ORECF |
						      USART_ICR_NCF |
						      USART_ICR_FECF |
						      USART_ICR_PECF);
}

void usart_set_wakeup_interrupt(enum usart usart, enum usart_wuf wuf)
{
	int r;

	r = MMIO32(USART_CR3(base[usart]));
	r &= ~(USART_CR3_WUS1 | USART_CR3_WUS0);
	MMIO32(USART_CR3(base[usart])) = r | wuf;
}

void usart_set_receiver_timeout(enum usart usart, int rto)
{
	int r;

	r = MMIO32(USART_RTOR(base[usart]));
	r &= ~0xffffff;
	MMIO32(USART_RTOR(base[usart])) = r | (rto & 0xffffff);
}

void usart_set_block_length(enum usart usart, int blen)
{
	int r;

	r = MMIO32(USART_RTOR(base[usart]));
	r &= ~(0xff << 24);
	MMIO32(USART_RTOR(base[usart])) = r | (blen & 0xff) << 24;
}

void usart_flush_transmit_data(enum usart usart)
{
	MMIO32(USART_RQR(base[usart])) = USART_RQR_TXFRQ;
}

void usart_flush_receive_data(enum usart usart)
{
	MMIO32(USART_RQR(base[usart])) = USART_RQR_RXFRQ;
}

void usart_enter_mute_mode(enum usart usart)
{
	MMIO32(USART_RQR(base[usart])) = USART_RQR_MMRQ;
}

void usart_send_break(enum usart usart)
{
	MMIO32(USART_RQR(base[usart])) = USART_RQR_SBKRQ;
}

void usart_restart_autobaudrate(enum usart usart)
{
	MMIO32(USART_RQR(base[usart])) = USART_RQR_ABRRQ;
}

void usart_enable_clock_in_stop_mode(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) |= USART_CR3_UCESM;
}

void usart_disable_clock_in_stop_mode(enum usart usart)
{
	MMIO32(USART_CR3(base[usart])) &= ~USART_CR3_UCESM;
}
