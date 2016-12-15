/*
 * USART
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
 * 24  Universal synchronous asynchronous receiver transmitter (USART)
 */

/* --- USART registers ----------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		USARTx_CR1	Control register 1
 * 0x04		USARTx_CR2	Control register 2
 * 0x08		USARTx_CR3	Control register 3
 * 0x0c		USARTx_BRR	Baud rate register
 * 0x10		USARTx_GTPR	Guard time and prescaler register
 * 0x14		USARTx_RTOR	Receiver timeout register
 * 0x18		USARTx_RQR	Request register
 * 0x1c		USARTx_ISR	Interrupt & status register
 * 0x20		USARTx_ICR	Interrupt flag clear register
 * 0x24		USARTx_RDR	Receive data register
 * 0x28		USARTx_TDR	Transmit data register
 */

#define USART_CR1(base)			((base) + 0x00)
#define USART1_CR1			USART_CR1(USART1_BASE)
#define USART2_CR1			USART_CR1(USART2_BASE)
#define USART4_CR1			USART_CR1(USART4_BASE)
#define USART5_CR1			USART_CR1(USART5_BASE)

#define USART_CR2(base)			((base) + 0x04)
#define USART1_CR2			USART_CR2(USART1_BASE)
#define USART2_CR2			USART_CR2(USART2_BASE)
#define USART4_CR2			USART_CR2(USART4_BASE)
#define USART5_CR2			USART_CR2(USART5_BASE)

#define USART_CR3(base)			((base) + 0x08)
#define USART1_CR3			USART_CR3(USART1_BASE)
#define USART2_CR3			USART_CR3(USART2_BASE)
#define USART4_CR3			USART_CR3(USART4_BASE)
#define USART5_CR3			USART_CR3(USART5_BASE)

#define USART_BRR(base)			((base) + 0x0c)
#define USART1_BRR			USART_BRR(USART1_BASE)
#define USART2_BRR			USART_BRR(USART2_BASE)
#define USART4_BRR			USART_BRR(USART4_BASE)
#define USART5_BRR			USART_BRR(USART5_BASE)

#define USART_GTPR(base)		((base) + 0x10)
#define USART1_GTPR			USART_GTPR(USART1_BASE)
#define USART2_GTPR			USART_GTPR(USART2_BASE)
#define USART4_GTPR			USART_GTPR(USART4_BASE)
#define USART5_GTPR			USART_GTPR(USART5_BASE)

#define USART_RTOR(base)		((base) + 0x14)
#define USART1_RTOR			USART_RTOR(USART1_BASE)
#define USART2_RTOR			USART_RTOR(USART2_BASE)
#define USART4_RTOR			USART_RTOR(USART4_BASE)
#define USART5_RTOR			USART_RTOR(USART5_BASE)

#define USART_RQR(base)			((base) + 0x18)
#define USART1_RQR			USART_RQR(USART1_BASE)
#define USART2_RQR			USART_RQR(USART2_BASE)
#define USART4_RQR			USART_RQR(USART4_BASE)
#define USART5_RQR			USART_RQR(USART5_BASE)

#define USART_ISR(base)			((base) + 0x1c)
#define USART1_ISR			USART_ISR(USART1_BASE)
#define USART2_ISR			USART_ISR(USART2_BASE)
#define USART4_ISR			USART_ISR(USART4_BASE)
#define USART5_ISR			USART_ISR(USART5_BASE)

#define USART_ICR(base)			((base) + 0x20)
#define USART1_ICR			USART_ICR(USART1_BASE)
#define USART2_ICR			USART_ICR(USART2_BASE)
#define USART4_ICR			USART_ICR(USART4_BASE)
#define USART5_ICR			USART_ICR(USART5_BASE)

#define USART_RDR(base)			((base) + 0x24)
#define USART1_RDR			USART_RDR(USART1_BASE)
#define USART2_RDR			USART_RDR(USART2_BASE)
#define USART4_RDR			USART_RDR(USART4_BASE)
#define USART5_RDR			USART_RDR(USART5_BASE)

#define USART_TDR(base)			((base) + 0x28)
#define USART1_TDR			USART_TDR(USART1_BASE)
#define USART2_TDR			USART_TDR(USART2_BASE)
#define USART4_TDR			USART_TDR(USART4_BASE)
#define USART5_TDR			USART_TDR(USART5_BASE)

/* --- USARTx_CR1 values --------------------------------------------------- */

#define USART_CR1_M1			(1 << 28)
#define USART_CR1_EOBIE			(1 << 27)
#define USART_CR1_RTOIE			(1 << 26)
#define USART_CR1_DEAT4			(1 << 25)
#define USART_CR1_DEAT3			(1 << 24)
#define USART_CR1_DEAT2			(1 << 23)
#define USART_CR1_DEAT1			(1 << 22)
#define USART_CR1_DEAT0			(1 << 21)
#define USART_CR1_DEDT4			(1 << 20)
#define USART_CR1_DEDT3			(1 << 19)
#define USART_CR1_DEDT2			(1 << 18)
#define USART_CR1_DEDT1			(1 << 17)
#define USART_CR1_DEDT0			(1 << 16)
#define USART_CR1_OVER8			(1 << 15)
#define USART_CR1_CMIE			(1 << 14)
#define USART_CR1_MME			(1 << 13)
#define USART_CR1_M0			(1 << 12)
#define USART_CR1_WAKE			(1 << 11)
#define USART_CR1_PCE			(1 << 10)
#define USART_CR1_PS			(1 << 9)
#define USART_CR1_PEIE			(1 << 8)
#define USART_CR1_TXEIE			(1 << 7)
#define USART_CR1_TCIE			(1 << 6)
#define USART_CR1_RXNEIE		(1 << 5)
#define USART_CR1_IDLEIE		(1 << 4)
#define USART_CR1_TE			(1 << 3)
#define USART_CR1_RE			(1 << 2)
#define USART_CR1_UESM			(1 << 1)
#define USART_CR1_UE			(1 << 0)

/* --- USARTx_CR2 values --------------------------------------------------- */

#define USART_CR2_ADD7			(1 << 31)
#define USART_CR2_ADD6			(1 << 30)
#define USART_CR2_ADD5			(1 << 29)
#define USART_CR2_ADD4			(1 << 28)
#define USART_CR2_ADD3			(1 << 27)
#define USART_CR2_ADD2			(1 << 26)
#define USART_CR2_ADD1			(1 << 25)
#define USART_CR2_ADD0			(1 << 24)
#define USART_CR2_RTOEN			(1 << 23)
#define USART_CR2_ABRMOD1		(1 << 22)
#define USART_CR2_ABRMOD0		(1 << 21)
#define USART_CR2_ABREN			(1 << 20)
#define USART_CR2_MSBFIRST		(1 << 19)
#define USART_CR2_DATAINV		(1 << 18)
#define USART_CR2_TXINV			(1 << 17)
#define USART_CR2_RXINV			(1 << 16)
#define USART_CR2_SWAP			(1 << 15)
#define USART_CR2_LINEN			(1 << 14)
#define USART_CR2_STOP1			(1 << 13)
#define USART_CR2_STOP0			(1 << 12)
#define USART_CR2_CLKEN			(1 << 11)
#define USART_CR2_CPOL			(1 << 10)
#define USART_CR2_CPHA			(1 << 9)
#define USART_CR2_LBCL			(1 << 8)
#define USART_CR2_LBDIE			(1 << 6)
#define USART_CR2_LBDL			(1 << 5)
#define USART_CR2_ADDM7			(1 << 4)

/* Auto baud rate mode */
#define USART_CR2_ABRMOD_START_BIT	(0 << 21)
#define USART_CR2_ABRMOD_FALLING_EDGE	(1 << 21)
#define USART_CR2_ABRMOD_7F		(2 << 21)
#define USART_CR2_ABRMOD_55		(3 << 21)

/* STOP bits */
#define USART_CR2_STOPBITS_1		(0 << 12)     /* 1 stop bit */
#define USART_CR2_STOPBITS_0_5		(1 << 12)     /* 0.5 stop bit */
#define USART_CR2_STOPBITS_2		(2 << 12)     /* 2 stop bits */
#define USART_CR2_STOPBITS_1_5		(3 << 12)     /* 1.5 stop bits */

/* --- USARTx_CR3 values --------------------------------------------------- */

#define USART_CR3_TCBGTIE		(1 << 24)
#define USART_CR3_UCESM			(1 << 23)
#define USART_CR3_WUFIE			(1 << 22)
#define USART_CR3_WUS1			(1 << 21)
#define USART_CR3_WUS0			(1 << 20)
#define USART_CR3_SCARCNT2		(1 << 19)
#define USART_CR3_SCARCNT1		(1 << 18)
#define USART_CR3_SCARCNT0		(1 << 17)
#define USART_CR3_DEP			(1 << 15)
#define USART_CR3_DEM			(1 << 14)
#define USART_CR3_DDRE			(1 << 13)
#define USART_CR3_OVRDIS		(1 << 12)
#define USART_CR3_ONEBIT		(1 << 11)
#define USART_CR3_CTSIE			(1 << 10)
#define USART_CR3_CTSE			(1 << 9)
#define USART_CR3_RTSE			(1 << 8)
#define USART_CR3_DMAT			(1 << 7)
#define USART_CR3_DMAR			(1 << 6)
#define USART_CR3_SCEN			(1 << 5)
#define USART_CR3_NACK			(1 << 4)
#define USART_CR3_HDSEL			(1 << 3)
#define USART_CR3_IRLP			(1 << 2)
#define USART_CR3_IREN			(1 << 1)
#define USART_CR3_EIE			(1 << 0)

/* Wakeup from stop mode interrupt flag selection */
#define USART_CR3_WUS_ADDR_MATCH	(0 << 20)
#define USART_CR3_WUS_START_BIT		(2 << 20)
#define USART_CR3_WUS_RXNE		(3 << 20)

/* --- USARTx_BRR values --------------------------------------------------- */

/* USART_BRR[15:4]: USARTDIV[15:4] */
/*
 * USART_BRR[3:0]: When OVER8 = 0, USARTDIV[3:0]
 *                 When OVER8 = 1:
 *                 BRR[2:0] = USARTDIV[3:0] shifted 1 bit to the right.
 *                 BRR[3] must be kept cleared.
 */

/* --- USARTx_GTPR values -------------------------------------------------- */

/* USART_GTPR[15:8]: GT[7:0]: Guard time value */
/* USART_GTPR[7:0]: PSC[7:0]: Prescaler value */

/* --- USARTx_RTOR values -------------------------------------------------- */

/* USART_RTOR[31:24]: BLEN[7:0]: Block Length */
/* USART_RTOR[23:0]: RTO[23:0]: Receiver timeout value */

/* --- USARTx_RQR values --------------------------------------------------- */

#define USART_RQR_TXFRQ			(1 << 4)
#define USART_RQR_RXFRQ			(1 << 3)
#define USART_RQR_MMRQ			(1 << 2)
#define USART_RQR_SBKRQ			(1 << 1)
#define USART_RQR_ABRRQ			(1 << 0)

/* --- USARTx_ISR values --------------------------------------------------- */

#define USART_ISR_TCBGT			(1 << 25)
#define USART_ISR_REACK			(1 << 22)
#define USART_ISR_TEACK			(1 << 21)
#define USART_ISR_WUF			(1 << 20)
#define USART_ISR_RWU			(1 << 19)
#define USART_ISR_SBKF			(1 << 18)
#define USART_ISR_CMF			(1 << 17)
#define USART_ISR_BUSY			(1 << 16)
#define USART_ISR_ABRF			(1 << 15)
#define USART_ISR_ABRE			(1 << 14)
#define USART_ISR_EOBF			(1 << 12)
#define USART_ISR_RTOF			(1 << 11)
#define USART_ISR_CTS			(1 << 10)
#define USART_ISR_CTSIF			(1 << 9)
#define USART_ISR_LBDF			(1 << 8)
#define USART_ISR_TXE			(1 << 7)
#define USART_ISR_TC			(1 << 6)
#define USART_ISR_RXNE			(1 << 5)
#define USART_ISR_IDLE			(1 << 4)
#define USART_ISR_ORE			(1 << 3)
#define USART_ISR_NF			(1 << 2)
#define USART_ISR_FE			(1 << 1)
#define USART_ISR_PE			(1 << 0)

/* --- USARTx_ICR values --------------------------------------------------- */

#define USART_ICR_WUCF			(1 << 20)
#define USART_ICR_CMCF			(1 << 17)
#define USART_ICR_EOBCF			(1 << 12)
#define USART_ICR_RTOCF			(1 << 11)
#define USART_ICR_CTSCF			(1 << 9)
#define USART_ICR_LBDCF			(1 << 8)
#define USART_ICR_TCBGTCF		(1 << 7)
#define USART_ICR_TCCF			(1 << 6)
#define USART_ICR_IDLECF		(1 << 4)
#define USART_ICR_ORECF			(1 << 3)
#define USART_ICR_NCF			(1 << 2)
#define USART_ICR_FECF			(1 << 1)
#define USART_ICR_PECF			(1 << 0)

/* --- USARTx_RDR values --------------------------------------------------- */

/* USART_RDR[8:0]: RDR[8:0]: Receive data value */

/* --- USARTx_TDR values --------------------------------------------------- */

/* USART_TDR[8:0]: TDR[8:0]: Transmit data value */

/* --- Function prototypes ------------------------------------------------- */

/* Device number */
enum usart {
	USART1,
	USART2,
	USART4,
	USART5
};

/* Auto baud rate mode */
enum usart_autobaud {
	USART_AUTOBAUD_START_BIT = (0 << 21),
	USART_AUTOBAUD_FALLING_EDGE = (1 << 21),
	USART_AUTOBAUD_7F = (2 << 21),
	USART_AUTOBAUD_55 = (3 << 21),

	USART_AUTOBAUD_MODE0 = (0 << 21),
	USART_AUTOBAUD_MODE1 = (1 << 21),
	USART_AUTOBAUD_MODE2 = (2 << 21),
	USART_AUTOBAUD_MODE3 = (3 << 21)
};

/* Stop bits */
enum usart_stop {
	USART_STOP_1 = (0 << 12),
	USART_STOP_0_5 = (1 << 12),
	USART_STOP_2 = (2 << 12),
	USART_STOP_1_5 = (3 << 12)
};

/* Parity */
enum usart_parity {
	USART_PARITY_NONE = 0,
	USART_ODD = (3 << 9),
	USART_EVEN = (2 << 9)
};

/* Flow control */
enum usart_flow {
	USART_FLOW_NONE = 0,
	USART_FLOW_RTS = (1 << 8),
	USART_FLOW_CTS = (2 << 8),
	USART_RTS_CTS = (3 << 8)
};

/* Tx, Rx */
enum usart_txrx {
	USART_TXRX_DISABLE = 0,
	USART_TX = (2 << 2),
	USART_RX = (1 << 2),
	USART_TX_RX = (3 << 2)
};

/* Option */
enum {
	USART_SWAP = (1 << 15),
	USART_RXINV = (1 << 16),
	USART_TXINV = (1 << 17),
	USART_DATAINV = (1 << 18),
	USART_MSBFIRST = (1 << 19),
	USART_HALF_DUPLEX = (1 << 3)
};

/* DMA request */
enum usart_dma {
	USART_DMA_TX = (2 << 6),
	USART_DMA_RX = (1 << 6),
	USART_DMA_TX_RX = (3 << 6)
};

/* Interrupt and status */
enum {
	USART_PE = (1 << 0),
	USART_FE = (1 << 1),
	USART_NF = (1 << 2),
	USART_ORE = (1 << 3),
	USART_IDLE = (1 << 4),
	USART_RXNE = (1 << 5),
	USART_TC = (1 << 6),
	USART_TXE = (1 << 7),
	USART_LBDF = (1 << 8),
	USART_CTSIF = (1 << 9),
	USART_RTOF = (1 << 11),
	USART_EOBF = (1 << 12),
	USART_CMF = (1 << 17),
	USART_WUF = (1 << 20),
	USART_TCBGT = (1 << 25),
	
	USART_CTS = (1 << 10),
	USART_ABRE = (1 << 14),
	USART_ABRF = (1 << 15),
	USART_BUSY = (1 << 16),
	USART_SBKF = (1 << 18),
	USART_RWU = (1 << 19),
	USART_TEACK = (1 << 21),
	USART_REACK = (1 << 22)
};

/* Wakeup from Stop mode interrupt flag selection */
enum usart_wuf {
	USART_WUF_ADDRESS_MATCH = (0 << 20),
	USART_WUF_START_BIT = (2 << 20),
	USART_WUF_RXNE = (3 << 20)
};

void usart_set_baudrate(enum usart usart, int clock, int baud);
void usart_set_baudrate_over8(enum usart usart, int clock, int baud);
void usart_enable_autobaudrate(enum usart usart, enum usart_autobaud mode);
void usart_disable_autobaudrate(enum usart usart);
void usart_set_databits(enum usart usart, int bits);
void usart_set_stopbits(enum usart usart, enum usart_stop stopbits);
void usart_set_parity(enum usart usart, enum usart_parity parity);
void usart_set_flow_control(enum usart usart, enum usart_flow flow);
void usart_set_txrx(enum usart usart, enum usart_txrx txrx, int option);
void usart_set_node_address(enum usart usart, int addr, int length);
void usart_enable_mute(enum usart usart, bool wake_addr_mark);
void usart_disable_mute(enum usart usart);
void usart_enable_de(enum usart usart, int deat, int dedt, bool active_low);
void usart_disable_de(enum usart usart);
void usart_disable_dma_on_reception_error(enum usart usart);
void usart_enable_dma_on_reception_error(enum usart usart);
void usart_disable_overrun(enum usart usart);
void usart_enable_overrun(enum usart usart);
void usart_enable_receiver_timeout(enum usart usart);
void usart_disable_receiver_timeout(enum usart usart);
void usart_enable_one_sample_bit(enum usart usart);
void usart_disable_one_sample_bit(enum usart usart);
void usart_enable_irda_mode(enum usart usart, int prescaler, bool low_power);
void usart_disable_irda_mode(enum usart usart);
void usart_enable_lin_mode(enum usart usart, int break_detection_length);
void usart_disable_lin_mode(enum usart usart);
void usart_enable_sync_mode(enum usart usart, bool cpol, bool cpha, bool lbcl);
void usart_disable_sync_mode(enum usart usart);
void usart_enable_smartcard_mode(enum usart usart, int prescaler,
				 int guard_time, bool clken,
				 int auto_retry_count, bool nack);
void usart_disable_smartcard_mode(enum usart usart);
void usart_init(enum usart usart, int clock, int baud, int bits,
		enum usart_stop stopbits, enum usart_parity parity,
		enum usart_flow flow, enum usart_txrx txrx);
void usart_enable(enum usart usart);
void usart_disable(enum usart usart);
void usart_enable_in_stop_mode(enum usart usart);
void usart_disable_in_stop_mode(enum usart usart);
void usart_send(enum usart usart, int data);
int usart_recv(enum usart usart);
void usart_send_blocking(enum usart usart, int data);
int usart_recv_blocking(enum usart usart);
void usart_enable_dma(enum usart usart, enum usart_dma request);
void usart_disable_dma(enum usart usart, enum usart_dma request);
void usart_enable_interrupt(enum usart usart, int interrupt);
void usart_disable_interrupt(enum usart usart, int interrupt);
int usart_get_interrupt_mask(enum usart usart, int interrupt);
int usart_get_interrupt_status(enum usart usart, int interrupt);
void usart_clear_interrupt(enum usart usart, int interrupt);
void usart_set_wakeup_interrupt(enum usart usart, enum usart_wuf wuf);
void usart_set_receiver_timeout(enum usart usart, int rto);
void usart_set_block_length(enum usart usart, int blen);
void usart_flush_transmit_data(enum usart usart);
void usart_flush_receive_data(enum usart usart);
void usart_enter_mute_mode(enum usart usart);
void usart_send_break(enum usart usart);
void usart_restart_autobaudrate(enum usart usart);
void usart_enable_clock_in_stop_mode(enum usart usart);
void usart_disable_clock_in_stop_mode(enum usart usart);
