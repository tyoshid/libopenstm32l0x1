/*
 * LPUART functions
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
#include <lpuart.h>

static const int base[] = {
	LPUART1_BASE
};

void lpuart_set_baudrate(enum lpuart lpuart, int clock, int baud)
{
	if (clock < 0 || baud <= 0 || clock / baud < 3 || clock / baud >= 4096)
		return;
	MMIO32(LPUART_BRR(base[lpuart])) = clock / baud * 256 +
		clock % baud * 256 / baud;
}

void lpuart_set_databits(enum lpuart lpuart, int bits)
{
	int r;

	r = MMIO32(LPUART_CR1(base[lpuart]));
	r &= ~(LPUART_CR1_M1 | LPUART_CR1_M0); /* 8 data bits */
	if (bits == 9)
		r |= LPUART_CR1_M0;
	else if (bits == 7)
		r |= LPUART_CR1_M1;
	MMIO32(LPUART_CR1(base[lpuart])) = r;
}

void lpuart_set_stopbits(enum lpuart lpuart, enum lpuart_stop stopbits)
{
	int r;

	r = MMIO32(LPUART_CR2(base[lpuart]));
	r &= ~(LPUART_CR2_STOP1 | LPUART_CR2_STOP0);
	MMIO32(LPUART_CR2(base[lpuart])) = r | stopbits;
}

void lpuart_set_parity(enum lpuart lpuart, enum lpuart_parity parity)
{
	int r;

	r = MMIO32(LPUART_CR1(base[lpuart]));
	r &= ~(LPUART_CR1_PCE | LPUART_CR1_PS);
	MMIO32(LPUART_CR1(base[lpuart])) = r | parity;
}

void lpuart_set_flow_control(enum lpuart lpuart, enum lpuart_flow flow)
{
	int r;

	r = MMIO32(LPUART_CR3(base[lpuart]));
	r &= ~(LPUART_CR3_CTSE | LPUART_CR3_RTSE);
	MMIO32(LPUART_CR3(base[lpuart])) = r | flow;
}

void lpuart_set_txrx(enum lpuart lpuart, enum lpuart_txrx txrx, int option)
{
	int r;

	r = MMIO32(LPUART_CR2(base[lpuart]));
	r &= ~(LPUART_CR2_MSBFIRST | LPUART_CR2_DATAINV | LPUART_CR2_TXINV |
	       LPUART_CR2_RXINV | LPUART_CR2_SWAP);
	MMIO32(LPUART_CR2(base[lpuart])) = r | (option & (LPUART_CR2_MSBFIRST |
							  LPUART_CR2_DATAINV |
							  LPUART_CR2_TXINV |
							  LPUART_CR2_RXINV |
							  LPUART_CR2_SWAP));
	r = MMIO32(LPUART_CR3(base[lpuart]));
	r &= ~LPUART_CR3_HDSEL;
	MMIO32(LPUART_CR3(base[lpuart])) = r | (option & LPUART_CR3_HDSEL);
	r = MMIO32(LPUART_CR1(base[lpuart]));
	r &= ~(LPUART_CR1_TE | LPUART_CR1_RE);
	MMIO32(LPUART_CR1(base[lpuart])) = r | txrx;
}

void lpuart_set_node_address(enum lpuart lpuart, int addr, int length)
{
	int r;

	r = MMIO32(LPUART_CR2(base[lpuart]));
	r &= ~(LPUART_CR2_ADD7 | LPUART_CR2_ADD6 | LPUART_CR2_ADD5 |
	       LPUART_CR2_ADD4 | LPUART_CR2_ADD3 | LPUART_CR2_ADD2 |
	       LPUART_CR2_ADD1 | LPUART_CR2_ADD0);
	if (length > 4)
		r |= LPUART_CR2_ADDM7;
	else
		r &= ~LPUART_CR2_ADDM7;
	MMIO32(LPUART_CR2(base[lpuart])) = r | (addr << 24);
}

void lpuart_enable_mute(enum lpuart lpuart, bool wake_addr_mark)
{
	int r;

	r = MMIO32(LPUART_CR1(base[lpuart]));
	if (wake_addr_mark)
		r |= LPUART_CR1_WAKE;
	else
		r &= ~LPUART_CR1_WAKE;
	MMIO32(LPUART_CR1(base[lpuart])) = r | LPUART_CR1_MME;
}

void lpuart_disable_mute(enum lpuart lpuart)
{
	MMIO32(LPUART_CR1(base[lpuart])) &= ~LPUART_CR1_MME;
}

void lpuart_enable_de(enum lpuart lpuart, int deat, int dedt, bool active_low)
{
	int r;

	r = MMIO32(LPUART_CR1(base[lpuart]));
	r &= ~(LPUART_CR1_DEAT4 | LPUART_CR1_DEAT3 | LPUART_CR1_DEAT2 |
	       LPUART_CR1_DEAT1 | LPUART_CR1_DEAT0 |
	       LPUART_CR1_DEDT4 | LPUART_CR1_DEDT3 | LPUART_CR1_DEDT2 |
	       LPUART_CR1_DEDT1 | LPUART_CR1_DEDT0);
	MMIO32(LPUART_CR1(base[lpuart])) = r | (deat & 0x1f) << 21 |
		(dedt & 0x1f) << 16;
	r = MMIO32(LPUART_CR3(base[lpuart]));
	if (active_low)
		r |= LPUART_CR3_DEP;
	else
		r &= ~LPUART_CR3_DEP;
	MMIO32(LPUART_CR3(base[lpuart])) = r | LPUART_CR3_DEM;
}

void lpuart_disable_de(enum lpuart lpuart)
{
	MMIO32(LPUART_CR3(base[lpuart])) &= ~LPUART_CR3_DEM;
}

void lpuart_disable_dma_on_reception_error(enum lpuart lpuart)
{
	MMIO32(LPUART_CR3(base[lpuart])) |= LPUART_CR3_DDRE;
}

void lpuart_enable_dma_on_reception_error(enum lpuart lpuart)
{
	MMIO32(LPUART_CR3(base[lpuart])) &= ~LPUART_CR3_DDRE;
}

void lpuart_disable_overrun(enum lpuart lpuart)
{
	MMIO32(LPUART_CR3(base[lpuart])) |= LPUART_CR3_OVRDIS;
}

void lpuart_enable_overrun(enum lpuart lpuart)
{
	MMIO32(LPUART_CR3(base[lpuart])) &= ~LPUART_CR3_OVRDIS;
}

void lpuart_init(enum lpuart lpuart, int clock, int baud, int bits,
		 enum lpuart_stop stopbits, enum lpuart_parity parity,
		 enum lpuart_flow flow, enum lpuart_txrx txrx)
{
	int cr1;
	int r;

	if (clock < 0 || baud <= 0 || clock < 3 * baud || clock >= 4096 * baud)
		return;
	/* Data bits */
	cr1 = MMIO32(LPUART_CR1(base[lpuart]));
	cr1 &= ~(LPUART_CR1_M1 | LPUART_CR1_M0);
	if (bits == 9)
		cr1 |= LPUART_CR1_M0;
	else if (bits == 7)
		cr1 |= LPUART_CR1_M1;
	MMIO32(LPUART_CR1(base[lpuart])) = cr1;
	/* Baud rate */
	MMIO32(LPUART_BRR(base[lpuart])) = clock / baud * 256 +
		clock % baud * 256 / baud;
	/* Stop bits */
	r = MMIO32(LPUART_CR2(base[lpuart]));
	r &= ~(LPUART_CR2_STOP1 | LPUART_CR2_STOP0);
	MMIO32(LPUART_CR2(base[lpuart])) = r | stopbits;
	/* Parity */
	cr1 &= ~(LPUART_CR1_PCE | LPUART_CR1_PS);
	cr1 |= parity;
	MMIO32(LPUART_CR1(base[lpuart])) = cr1;
	/* Flow control */
	r = MMIO32(LPUART_CR3(base[lpuart]));
	r &= ~(LPUART_CR3_CTSE | LPUART_CR3_RTSE);
	MMIO32(LPUART_CR3(base[lpuart])) = r | flow;
	/* Enable LPUART */
	cr1 |= LPUART_CR1_UE;
	MMIO32(LPUART_CR1(base[lpuart])) = cr1; 
	/* Tx, Rx */
	cr1 &= ~(LPUART_CR1_TE | LPUART_CR1_RE);
	MMIO32(LPUART_CR1(base[lpuart])) = cr1 | txrx;
}

void lpuart_enable(enum lpuart lpuart)
{
	MMIO32(LPUART_CR1(base[lpuart])) |= LPUART_CR1_UE;
}

void lpuart_disable(enum lpuart lpuart)
{
	MMIO32(LPUART_CR1(base[lpuart])) &= ~LPUART_CR1_UE;
}

void lpuart_enable_in_stop_mode(enum lpuart lpuart)
{
	MMIO32(LPUART_CR1(base[lpuart])) |= LPUART_CR1_UESM;
}

void lpuart_disable_in_stop_mode(enum lpuart lpuart)
{
	MMIO32(LPUART_CR1(base[lpuart])) &= ~LPUART_CR1_UESM;
}

void lpuart_send(enum lpuart lpuart, int data)
{
	int r;

	r = MMIO32(LPUART_TDR(base[lpuart]));
	r &= ~0x1ff;
	MMIO32(LPUART_TDR(base[lpuart])) = r | (data & 0x1ff);
}

int lpuart_recv(enum lpuart lpuart)
{
	return MMIO32(LPUART_RDR(base[lpuart])) & 0x1ff;
}

void lpuart_send_blocking(enum lpuart lpuart, int data)
{
	int r;

	while (!(MMIO32(LPUART_ISR(base[lpuart])) & LPUART_ISR_TXE))
		;
	r = MMIO32(LPUART_TDR(base[lpuart]));
	r &= ~0x1ff;
	MMIO32(LPUART_TDR(base[lpuart])) = r | (data & 0x1ff);
}

int lpuart_recv_blocking(enum lpuart lpuart)
{
	while (!(MMIO32(LPUART_ISR(base[lpuart])) & LPUART_ISR_RXNE))
		;
	return MMIO32(LPUART_RDR(base[lpuart])) & 0x1ff;
}

void lpuart_enable_dma(enum lpuart lpuart, enum lpuart_dma request)
{
	MMIO32(LPUART_CR3(base[lpuart])) |= request;
}

void lpuart_disable_dma(enum lpuart lpuart, enum lpuart_dma request)
{
	MMIO32(LPUART_CR3(base[lpuart])) &= ~request;
}

void lpuart_enable_interrupt(enum lpuart lpuart, int interrupt)
{
	int r;

	if (interrupt & (LPUART_CMF | LPUART_PE | LPUART_TXE | LPUART_TC |
			 LPUART_RXNE | LPUART_IDLE)) {
		r = MMIO32(LPUART_CR1(base[lpuart]));
		if (interrupt & LPUART_CMF)
			r |= LPUART_CR1_CMIE;
		if (interrupt & LPUART_PE)
			r |= LPUART_CR1_PEIE;
		if (interrupt & LPUART_TXE)
			r |= LPUART_CR1_TXEIE;
		if (interrupt & LPUART_TC)
			r |= LPUART_CR1_TCIE;
		if (interrupt & LPUART_RXNE)
			r |= LPUART_CR1_RXNEIE;
		if (interrupt & LPUART_IDLE)
			r |= LPUART_CR1_IDLEIE;
		MMIO32(LPUART_CR1(base[lpuart])) = r;
	}
	if (interrupt & (LPUART_WUF | LPUART_CTSIF | LPUART_ORE | LPUART_NF |
			 LPUART_FE)) {
		r = MMIO32(LPUART_CR3(base[lpuart]));
		if (interrupt & LPUART_WUF)
			r |= LPUART_CR3_WUFIE;
		if (interrupt & LPUART_CTSIF)
			r |= LPUART_CR3_CTSIE;
		if (interrupt & (LPUART_ORE | LPUART_NF | LPUART_FE))
			r |= LPUART_CR3_EIE;
		MMIO32(LPUART_CR3(base[lpuart])) = r;
	}
}

void lpuart_disable_interrupt(enum lpuart lpuart, int interrupt)
{
	int r;

	if (interrupt & (LPUART_CMF | LPUART_PE | LPUART_TXE | LPUART_TC |
			 LPUART_RXNE | LPUART_IDLE)) {
		r = MMIO32(LPUART_CR1(base[lpuart]));
		if (interrupt & LPUART_CMF)
			r &= ~LPUART_CR1_CMIE;
		if (interrupt & LPUART_PE)
			r &= ~LPUART_CR1_PEIE;
		if (interrupt & LPUART_TXE)
			r &= ~LPUART_CR1_TXEIE;
		if (interrupt & LPUART_TC)
			r &= ~LPUART_CR1_TCIE;
		if (interrupt & LPUART_RXNE)
			r &= ~LPUART_CR1_RXNEIE;
		if (interrupt & LPUART_IDLE)
			r &= ~LPUART_CR1_IDLEIE;
		MMIO32(LPUART_CR1(base[lpuart])) = r;
	}
	if (interrupt & (LPUART_WUF | LPUART_CTSIF | LPUART_ORE | LPUART_NF |
			 LPUART_FE)) {
		r = MMIO32(LPUART_CR3(base[lpuart]));
		if (interrupt & LPUART_WUF)
			r &= ~LPUART_CR3_WUFIE;
		if (interrupt & LPUART_CTSIF)
			r &= ~LPUART_CR3_CTSIE;
		if (interrupt & (LPUART_ORE | LPUART_NF | LPUART_FE))
			r &= ~LPUART_CR3_EIE;
		MMIO32(LPUART_CR3(base[lpuart])) = r;
	}
}

int lpuart_get_interrupt_mask(enum lpuart lpuart, int interrupt)
{
	int r;
	int f;

	f = 0;
	if (interrupt & (LPUART_CMF | LPUART_PE | LPUART_TXE | LPUART_TC |
			 LPUART_RXNE | LPUART_IDLE)) {
		r = MMIO32(LPUART_CR1(base[lpuart]));
		if (interrupt & LPUART_CMF) {
			if (r & LPUART_CR1_CMIE)
				f |= LPUART_CMF;
		}
		if (interrupt & LPUART_PE) {
			if (r & LPUART_CR1_PEIE)
				f |= LPUART_PE;
		}
		if (interrupt & LPUART_TXE) {
			if (r & LPUART_CR1_TXEIE)
				f |= LPUART_TXE;
		}
		if (interrupt & LPUART_TC) {
			if (r & LPUART_CR1_TCIE)
				f |= LPUART_TC;
		}
		if (interrupt & LPUART_RXNE) {
			if (r & LPUART_CR1_RXNEIE)
				f |= LPUART_RXNE;
		}
		if (interrupt & LPUART_IDLE) {
			if (r & LPUART_CR1_IDLEIE)
				f |= LPUART_IDLE;
		}
	}
	if (interrupt & (LPUART_WUF | LPUART_CTSIF | LPUART_ORE | LPUART_NF |
			 LPUART_FE)) {
		r = MMIO32(LPUART_CR3(base[lpuart]));
		if (interrupt & LPUART_WUF) {
			if (r & LPUART_CR3_WUFIE)
				f |= LPUART_WUF;
		}
		if (interrupt & LPUART_CTSIF) {
			if (r & LPUART_CR3_CTSIE)
				f |= LPUART_CTSIF;
		}
		if (interrupt & (LPUART_ORE | LPUART_NF | LPUART_FE)) {
			if (r & LPUART_CR3_EIE)
				f |= interrupt & (LPUART_ORE | LPUART_NF |
						   LPUART_FE);
		}
	}
	return f;
}

int lpuart_get_interrupt_status(enum lpuart lpuart, int interrupt)
{
	return MMIO32(LPUART_ISR(base[lpuart])) & interrupt;
}

void lpuart_clear_interrupt(enum lpuart lpuart, int interrupt)
{
	MMIO32(LPUART_ICR(base[lpuart])) = interrupt & (LPUART_ICR_WUCF |
							LPUART_ICR_CMCF |
							LPUART_ICR_CTSCF |
							LPUART_ICR_TCCF |
							LPUART_ICR_IDLECF |
							LPUART_ICR_ORECF |
							LPUART_ICR_NCF |
							LPUART_ICR_FECF |
							LPUART_ICR_PECF);
}

void lpuart_set_wakeup_interrupt(enum lpuart lpuart, enum lpuart_wuf wuf)
{
	int r;

	r = MMIO32(LPUART_CR3(base[lpuart]));
	r &= ~(LPUART_CR3_WUS1 | LPUART_CR3_WUS0);
	MMIO32(LPUART_CR3(base[lpuart])) = r | wuf;
}

void lpuart_flush_receive_data(enum lpuart lpuart)
{
	MMIO32(LPUART_RQR(base[lpuart])) = LPUART_RQR_RXFRQ;
}

void lpuart_enter_mute_mode(enum lpuart lpuart)
{
	MMIO32(LPUART_RQR(base[lpuart])) = LPUART_RQR_MMRQ;
}

void lpuart_send_break(enum lpuart lpuart)
{
	MMIO32(LPUART_RQR(base[lpuart])) = LPUART_RQR_SBKRQ;
}

void lpuart_enable_clock_in_stop_mode(enum lpuart lpuart)
{
	MMIO32(LPUART_CR3(base[lpuart])) |= LPUART_CR3_UCESM;
}

void lpuart_disable_clock_in_stop_mode(enum lpuart lpuart)
{
	MMIO32(LPUART_CR3(base[lpuart])) &= ~LPUART_CR3_UCESM;
}
