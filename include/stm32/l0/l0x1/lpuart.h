/*
 * LPUART
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

/*
 * STMicroelectronics(www.st.com)
 *
 * RM0377: Reference manual
 * Ultra-low-power STM32L0x1 advanced ARM-based 32-bit MCUs
 * (14-Nov-2016 Rev 7)
 *
 * 25  Low-power universal asynchronous receiver transmitter (LPUART)
 */

/* --- LPUART registers ---------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		LPUART_CR1	Control register 1
 * 0x04		LPUART_CR2	Control register 2
 * 0x08		LPUART_CR3	Control register 3
 * 0x0c		LPUART_BRR	Baud rate register
 * 0x18		LPUART_RQR	Request register
 * 0x1c		LPUART_ISR	Interrupt & status register
 * 0x20		LPUART_ICR	Interrupt flag clear register
 * 0x24		LPUART_RDR	Receive data register
 * 0x28		LPUART_TDR	Transmit data register
 */

#define LPUART_CR1(base)		((base) + 0x00)
#define LPUART1_CR1			LPUART_CR1(LPUART1_BASE)

#define LPUART_CR2(base)		((base) + 0x04)
#define LPUART1_CR2			LPUART_CR2(LPUART1_BASE)

#define LPUART_CR3(base)		((base) + 0x08)
#define LPUART1_CR3			LPUART_CR3(LPUART1_BASE)

#define LPUART_BRR(base)		((base) + 0x0c)
#define LPUART1_BRR			LPUART_BRR(LPUART1_BASE)

#define LPUART_RQR(base)		((base) + 0x18)
#define LPUART1_RQR			LPUART_RQR(LPUART1_BASE)

#define LPUART_ISR(base)		((base) + 0x1c)
#define LPUART1_ISR			LPUART_ISR(LPUART1_BASE)

#define LPUART_ICR(base)		((base) + 0x20)
#define LPUART1_ICR			LPUART_ICR(LPUART1_BASE)

#define LPUART_RDR(base)		((base) + 0x24)
#define LPUART1_RDR			LPUART_RDR(LPUART1_BASE)

#define LPUART_TDR(base)		((base) + 0x28)
#define LPUART1_TDR			LPUART_TDR(LPUART1_BASE)

/* --- LPUART_CR1 values --------------------------------------------------- */

#define LPUART_CR1_M1			(1 << 28)
#define LPUART_CR1_DEAT4		(1 << 25)
#define LPUART_CR1_DEAT3		(1 << 24)
#define LPUART_CR1_DEAT2		(1 << 23)
#define LPUART_CR1_DEAT1		(1 << 22)
#define LPUART_CR1_DEAT0		(1 << 21)
#define LPUART_CR1_DEDT4		(1 << 20)
#define LPUART_CR1_DEDT3		(1 << 19)
#define LPUART_CR1_DEDT2		(1 << 18)
#define LPUART_CR1_DEDT1		(1 << 17)
#define LPUART_CR1_DEDT0		(1 << 16)
#define LPUART_CR1_CMIE			(1 << 14)
#define LPUART_CR1_MME			(1 << 13)
#define LPUART_CR1_M0			(1 << 12)
#define LPUART_CR1_WAKE			(1 << 11)
#define LPUART_CR1_PCE			(1 << 10)
#define LPUART_CR1_PS			(1 << 9)
#define LPUART_CR1_PEIE			(1 << 8)
#define LPUART_CR1_TXEIE		(1 << 7)
#define LPUART_CR1_TCIE			(1 << 6)
#define LPUART_CR1_RXNEIE		(1 << 5)
#define LPUART_CR1_IDLEIE		(1 << 4)
#define LPUART_CR1_TE			(1 << 3)
#define LPUART_CR1_RE			(1 << 2)
#define LPUART_CR1_UESM			(1 << 1)
#define LPUART_CR1_UE			(1 << 0)

/* --- LPUART_CR2 values --------------------------------------------------- */

#define LPUART_CR2_ADD7			(1 << 31)
#define LPUART_CR2_ADD6			(1 << 30)
#define LPUART_CR2_ADD5			(1 << 29)
#define LPUART_CR2_ADD4			(1 << 28)
#define LPUART_CR2_ADD3			(1 << 27)
#define LPUART_CR2_ADD2			(1 << 26)
#define LPUART_CR2_ADD1			(1 << 25)
#define LPUART_CR2_ADD0			(1 << 24)
#define LPUART_CR2_MSBFIRST		(1 << 19)
#define LPUART_CR2_DATAINV		(1 << 18)
#define LPUART_CR2_TXINV		(1 << 17)
#define LPUART_CR2_RXINV		(1 << 16)
#define LPUART_CR2_SWAP			(1 << 15)
#define LPUART_CR2_STOP1		(1 << 13)
#define LPUART_CR2_STOP0		(1 << 12)
#define LPUART_CR2_ADDM7		(1 << 4)

/* STOP bits */
#define LPUART_CR2_STOPBITS_1		(0 << 12)     /* 1 stop bit */
#define LPUART_CR2_STOPBITS_2		(2 << 12)     /* 2 stop bits */

/* --- LPUART_CR3 values --------------------------------------------------- */

#define LPUART_CR3_UCESM		(1 << 23)
#define LPUART_CR3_WUFIE		(1 << 22)
#define LPUART_CR3_WUS1			(1 << 21)
#define LPUART_CR3_WUS0			(1 << 20)
#define LPUART_CR3_DEP			(1 << 15)
#define LPUART_CR3_DEM			(1 << 14)
#define LPUART_CR3_DDRE			(1 << 13)
#define LPUART_CR3_OVRDIS		(1 << 12)
#define LPUART_CR3_CTSIE		(1 << 10)
#define LPUART_CR3_CTSE			(1 << 9)
#define LPUART_CR3_RTSE			(1 << 8)
#define LPUART_CR3_DMAT			(1 << 7)
#define LPUART_CR3_DMAR			(1 << 6)
#define LPUART_CR3_HDSEL		(1 << 3)
#define LPUART_CR3_EIE			(1 << 0)

/* Wakeup from stop mode interrupt flag selction */
#define LPUART_CR3_WUS_ADDR_MATCH	(0 << 20)
#define LPUART_CR3_WUS_START_BIT	(2 << 20)
#define LPUART_CR3_WUS_RXNE		(3 << 20)

/* --- LPUART_BRR values --------------------------------------------------- */

/* LPUART_BRR[19:0]: BRR[19:0] */

/* --- LPUART_RQR values --------------------------------------------------- */

#define LPUART_RQR_RXFRQ		(1 << 3)
#define LPUART_RQR_MMRQ			(1 << 2)
#define LPUART_RQR_SBKRQ		(1 << 1)

/* --- LPUART_ISR values --------------------------------------------------- */

#define LPUART_ISR_REACK		(1 << 22)
#define LPUART_ISR_TEACK		(1 << 21)
#define LPUART_ISR_WUF			(1 << 20)
#define LPUART_ISR_RWU			(1 << 19)
#define LPUART_ISR_SBKF			(1 << 18)
#define LPUART_ISR_CMF			(1 << 17)
#define LPUART_ISR_BUSY			(1 << 16)
#define LPUART_ISR_CTS			(1 << 10)
#define LPUART_ISR_CTSIF		(1 << 9)
#define LPUART_ISR_TXE			(1 << 7)
#define LPUART_ISR_TC			(1 << 6)
#define LPUART_ISR_RXNE			(1 << 5)
#define LPUART_ISR_IDLE			(1 << 4)
#define LPUART_ISR_ORE			(1 << 3)
#define LPUART_ISR_NF			(1 << 2)
#define LPUART_ISR_FE			(1 << 1)
#define LPUART_ISR_PE			(1 << 0)

/* --- LPUART_ICR values --------------------------------------------------- */

#define LPUART_ICR_WUCF			(1 << 20)
#define LPUART_ICR_CMCF			(1 << 17)
#define LPUART_ICR_CTSCF		(1 << 9)
#define LPUART_ICR_TCCF			(1 << 6)
#define LPUART_ICR_IDLECF		(1 << 4)
#define LPUART_ICR_ORECF		(1 << 3)
#define LPUART_ICR_NCF			(1 << 2)
#define LPUART_ICR_FECF			(1 << 1)
#define LPUART_ICR_PECF			(1 << 0)

/* --- LPUART_RDR values --------------------------------------------------- */

/* LPUART_RDR[8:0]: RDR[8:0]: Receive data value */

/* --- LPUART_TDR values --------------------------------------------------- */

/* LPUART_TDR[8:0]: TDR[8:0]: Transmit data value */

/* --- Function prototypes ------------------------------------------------- */

/* Device number */
enum lpuart {
	LPUART1
};

/* Stop bits */
enum lpuart_stop {
	LPUART_STOP_1 = (0 << 12),
	LPUART_STOP_2 = (2 << 12)
};

/* Parity */
enum lpuart_parity {
	LPUART_PARITY_NONE = 0,
	LPUART_ODD = (3 << 9),
	LPUART_EVEN = (2 << 9)
};

/* Flow control */
enum lpuart_flow {
	LPUART_FLOW_NONE = 0,
	LPUART_FLOW_RTS = (1 << 8),
	LPUART_FLOW_CTS = (2 << 8),
	LPUART_RTS_CTS = (3 << 8)
};

/* Tx, Rx */
enum lpuart_txrx {
	LPUART_TXRX_DISABLE = 0,
	LPUART_TX = (2 << 2),
	LPUART_RX = (1 << 2),
	LPUART_TX_RX = (3 << 2)
};

/* Option */
enum {
	LPUART_SWAP = (1 << 15),
	LPUART_RXINV = (1 << 16),
	LPUART_TXINV = (1 << 17),
	LPUART_DATAINV = (1 << 18),
	LPUART_MSBFIRST = (1 << 19),
	LPUART_HALF_DUPLEX = (1 << 3)
};

/* DMA request */
enum lpuart_dma {
	LPUART_DMA_TX = (2 << 6),
	LPUART_DMA_RX = (1 << 6),
	LPUART_DMA_TX_RX = (3 << 6)
};

/* Interrupt and status */
enum {
	LPUART_PE = (1 << 0),
	LPUART_FE = (1 << 1),
	LPUART_NF = (1 << 2),
	LPUART_ORE = (1 << 3),
	LPUART_IDLE = (1 << 4),
	LPUART_RXNE = (1 << 5),
	LPUART_TC = (1 << 6),
	LPUART_TXE = (1 << 7),
	LPUART_CTSIF = (1 << 9),
	LPUART_CMF = (1 << 17),
	LPUART_WUF = (1 << 20),
	
	LPUART_CTS = (1 << 10),
	LPUART_BUSY = (1 << 16),
	LPUART_SBKF = (1 << 18),
	LPUART_RWU = (1 << 19),
	LPUART_TEACK = (1 << 21),
	LPUART_REACK = (1 << 22)
};

/* Wakeup from Stop mode interrupt flag selection */
enum lpuart_wuf {
	LPUART_WUF_ADDRESS_MATCH = (0 << 20),
	LPUART_WUF_START_BIT = (2 << 20),
	LPUART_WUF_RXNE = (3 << 20)
};

void lpuart_set_baudrate(enum lpuart lpuart, int clock, int baud);
void lpuart_set_databits(enum lpuart lpuart, int bits);
void lpuart_set_stopbits(enum lpuart lpuart, enum lpuart_stop stopbits);
void lpuart_set_parity(enum lpuart lpuart, enum lpuart_parity parity);
void lpuart_set_flow_control(enum lpuart lpuart, enum lpuart_flow flow);
void lpuart_set_txrx(enum lpuart lpuart, enum lpuart_txrx txrx, int option);
void lpuart_set_node_address(enum lpuart lpuart, int addr, int length);
void lpuart_enable_mute(enum lpuart lpuart, bool wake_addr_mark);
void lpuart_disable_mute(enum lpuart lpuart);
void lpuart_enable_de(enum lpuart lpuart, int deat, int dedt, bool active_low);
void lpuart_disable_de(enum lpuart lpuart);
void lpuart_disable_dma_on_reception_error(enum lpuart lpuart);
void lpuart_enable_dma_on_reception_error(enum lpuart lpuart);
void lpuart_disable_overrun(enum lpuart lpuart);
void lpuart_enable_overrun(enum lpuart lpuart);
void lpuart_init(enum lpuart lpuart, int clock, int baud, int bits,
		 enum lpuart_stop stopbits, enum lpuart_parity parity,
		 enum lpuart_flow flow, enum lpuart_txrx txrx);
void lpuart_enable(enum lpuart lpuart);
void lpuart_disable(enum lpuart lpuart);
void lpuart_enable_in_stop_mode(enum lpuart lpuart);
void lpuart_disable_in_stop_mode(enum lpuart lpuart);
void lpuart_send(enum lpuart lpuart, int data);
int lpuart_recv(enum lpuart lpuart);
void lpuart_send_blocking(enum lpuart lpuart, int data);
int lpuart_recv_blocking(enum lpuart lpuart);
void lpuart_enable_dma(enum lpuart lpuart, enum lpuart_dma request);
void lpuart_disable_dma(enum lpuart lpuart, enum lpuart_dma request);
void lpuart_enable_interrupt(enum lpuart lpuart, int interrupt);
void lpuart_disable_interrupt(enum lpuart lpuart, int interrupt);
int lpuart_get_interrupt_mask(enum lpuart lpuart, int interrupt);
int lpuart_get_interrupt_status(enum lpuart lpuart, int interrupt);
void lpuart_clear_interrupt(enum lpuart lpuart, int interrupt);
void lpuart_set_wakeup_interrupt(enum lpuart lpuart, enum lpuart_wuf wuf);
void lpuart_flush_receive_data(enum lpuart lpuart);
void lpuart_enter_mute_mode(enum lpuart lpuart);
void lpuart_send_break(enum lpuart lpuart);
void lpuart_enable_clock_in_stop_mode(enum lpuart lpuart);
void lpuart_disable_clock_in_stop_mode(enum lpuart lpuart);
