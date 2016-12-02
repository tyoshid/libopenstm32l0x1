/*
 * I2C
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
 * (30-Aug-2016 Rev 6)
 *
 * 23  Inter-integrated circuit (I2C) interface
 */

/* --- I2C registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		I2C_CR1		Control register 1
 * 0x04		I2C_CR2		Control register 2
 * 0x08		I2C_OAR1	Own address 1 register
 * 0x0c		I2C_OAR2	Own address 2 register
 * 0x10		I2C_TIMIMGR	Timing register
 * 0x14		I2C_TIMEOUTR	Timeout register
 * 0x18		I2C_ISR		Interrupt and status register
 * 0x1c		I2C_ICR		Interrupt clear register
 * 0x20		I2C_PECR	PEC register
 * 0x24		I2C_RXDR	Receive data register
 * 0x28		I2C_TXDR	Transmit data register
 */

#define I2C_CR1(base)			((base) + 0x00)
#define I2C1_CR1			I2C_CR1(I2C1_BASE)
#define I2C2_CR1			I2C_CR1(I2C2_BASE)
#define I2C3_CR1			I2C_CR1(I2C3_BASE)

#define I2C_CR2(base)			((base) + 0x04)
#define I2C1_CR2			I2C_CR2(I2C1_BASE)
#define I2C2_CR2			I2C_CR2(I2C2_BASE)
#define I2C3_CR2			I2C_CR2(I2C3_BASE)

#define I2C_OAR1(base)			((base) + 0x08)
#define I2C1_OAR1			I2C_OAR1(I2C1_BASE)
#define I2C2_OAR1			I2C_OAR1(I2C2_BASE)
#define I2C3_OAR1			I2C_OAR1(I2C3_BASE)

#define I2C_OAR2(base)			((base) + 0x0c)
#define I2C1_OAR2			I2C_OAR2(I2C1_BASE)
#define I2C2_OAR2			I2C_OAR2(I2C2_BASE)
#define I2C3_OAR2			I2C_OAR2(I2C3_BASE)

#define I2C_TIMINGR(base)		((base) + 0x10)
#define I2C1_TIMINGR			I2C_TIMINGR(I2C1_BASE)
#define I2C2_TIMINGR			I2C_TIMINGR(I2C2_BASE)
#define I2C3_TIMINGR			I2C_TIMINGR(I2C3_BASE)

#define I2C_TIMEOUTR(base)		((base) + 0x14)
#define I2C1_TIMEOUTR			I2C_TIMEOUTR(I2C1_BASE)
#define I2C2_TIMEOUTR			I2C_TIMEOUTR(I2C2_BASE)
#define I2C3_TIMEOUTR			I2C_TIMEOUTR(I2C3_BASE)

#define I2C_ISR(base)			((base) + 0x18)
#define I2C1_ISR			I2C_ISR(I2C1_BASE)
#define I2C2_ISR			I2C_ISR(I2C2_BASE)
#define I2C3_ISR			I2C_ISR(I2C3_BASE)

#define I2C_ICR(base)			((base) + 0x1c)
#define I2C1_ICR			I2C_ICR(I2C1_BASE)
#define I2C2_ICR			I2C_ICR(I2C2_BASE)
#define I2C3_ICR			I2C_ICR(I2C3_BASE)

#define I2C_PECR(base)			((base) + 0x20)
#define I2C1_PECR			I2C_PECR(I2C1_BASE)
#define I2C2_PECR			I2C_PECR(I2C2_BASE)
#define I2C3_PECR			I2C_PECR(I2C3_BASE)

#define I2C_RXDR(base)			((base) + 0x24)
#define I2C1_RXDR			I2C_RXDR(I2C1_BASE)
#define I2C2_RXDR			I2C_RXDR(I2C2_BASE)
#define I2C3_RXDR			I2C_RXDR(I2C3_BASE)

#define I2C_TXDR(base)			((base) + 0x28)
#define I2C1_TXDR			I2C_TXDR(I2C1_BASE)
#define I2C2_TXDR			I2C_TXDR(I2C2_BASE)
#define I2C3_TXDR			I2C_TXDR(I2C3_BASE)

/* --- I2C_CR1 values ------------------------------------------------------ */

#define I2C_CR1_PECEN			(1 << 23)
#define I2C_CR1_ALERTEN			(1 << 22)
#define I2C_CR1_SMBDEN			(1 << 21)
#define I2C_CR1_SMBHEN			(1 << 20)
#define I2C_CR1_GCEN			(1 << 19)
#define I2C_CR1_WUPEN			(1 << 18)
#define I2C_CR1_NOSTRETCH		(1 << 17)
#define I2C_CR1_SBC			(1 << 16)
#define I2C_CR1_RXDMAEN			(1 << 15)
#define I2C_CR1_TXDMAEN			(1 << 14)
#define I2C_CR1_ANFOFF			(1 << 12)
#define I2C_CR1_DNF3			(1 << 11)
#define I2C_CR1_DNF2			(1 << 10)
#define I2C_CR1_DNF1			(1 << 9)
#define I2C_CR1_DNF0			(1 << 8)
#define I2C_CR1_ERRIE			(1 << 7)
#define I2C_CR1_TCIE			(1 << 6)
#define I2C_CR1_STOPIE			(1 << 5)
#define I2C_CR1_NACKIE			(1 << 4)
#define I2C_CR1_ADDRIE			(1 << 3)
#define I2C_CR1_RXIE			(1 << 2)
#define I2C_CR1_TXIE			(1 << 1)
#define I2C_CR1_PE			(1 << 0)

/* --- I2C_CR2 values ------------------------------------------------------ */

#define I2C_CR2_PECBYTE			(1 << 26)
#define I2C_CR2_AUTOEND			(1 << 25)
#define I2C_CR2_RELOAD			(1 << 24)
#define I2C_CR2_NBYTES7			(1 << 23)
#define I2C_CR2_NBYTES6			(1 << 22)
#define I2C_CR2_NBYTES5			(1 << 21)
#define I2C_CR2_NBYTES4			(1 << 20)
#define I2C_CR2_NBYTES3			(1 << 19)
#define I2C_CR2_NBYTES2			(1 << 18)
#define I2C_CR2_NBYTES1			(1 << 17)
#define I2C_CR2_NBYTES0			(1 << 16)
#define I2C_CR2_NACK			(1 << 15)
#define I2C_CR2_STOP			(1 << 14)
#define I2C_CR2_START			(1 << 13)
#define I2C_CR2_HEAD10R			(1 << 12)
#define I2C_CR2_ADD10			(1 << 11)
#define I2C_CR2_RD_WRN			(1 << 10)
#define I2C_CR2_SADD9			(1 << 9)
#define I2C_CR2_SADD8			(1 << 8)
#define I2C_CR2_SADD7			(1 << 7)
#define I2C_CR2_SADD6			(1 << 6)
#define I2C_CR2_SADD5			(1 << 5)
#define I2C_CR2_SADD4			(1 << 4)
#define I2C_CR2_SADD3			(1 << 3)
#define I2C_CR2_SADD2			(1 << 2)
#define I2C_CR2_SADD1			(1 << 1)
#define I2C_CR2_SADD0			(1 << 0)

/* --- I2C_OAR1 values ----------------------------------------------------- */

#define I2C_OAR1_OA1EN			(1 << 15)
#define I2C_OAR1_OA1MODE		(1 << 10)
#define I2C_OAR1_OA19			(1 << 9)
#define I2C_OAR1_OA18			(1 << 8)
#define I2C_OAR1_OA17			(1 << 7)
#define I2C_OAR1_OA16			(1 << 6)
#define I2C_OAR1_OA15			(1 << 5)
#define I2C_OAR1_OA14			(1 << 4)
#define I2C_OAR1_OA13			(1 << 3)
#define I2C_OAR1_OA12			(1 << 2)
#define I2C_OAR1_OA11			(1 << 1)
#define I2C_OAR1_OA10			(1 << 0)

/* --- I2C_OAR2 values ----------------------------------------------------- */

#define I2C_OAR2_OA2EN			(1 << 15)
#define I2C_OAR2_OA2MSK2		(1 << 10)
#define I2C_OAR2_OA2MSK1		(1 << 9)
#define I2C_OAR2_OA2MSK0		(1 << 8)
#define I2C_OAR2_OA27			(1 << 7)
#define I2C_OAR2_OA26			(1 << 6)
#define I2C_OAR2_OA25			(1 << 5)
#define I2C_OAR2_OA24			(1 << 4)
#define I2C_OAR2_OA23			(1 << 3)
#define I2C_OAR2_OA22			(1 << 2)
#define I2C_OAR2_OA21			(1 << 1)

/* --- I2C_TIMINGR values -------------------------------------------------- */

#define I2C_TIMINGR_PRESC3		(1 << 31)
#define I2C_TIMINGR_PRESC2		(1 << 30)
#define I2C_TIMINGR_PRESC1		(1 << 29)
#define I2C_TIMINGR_PRESC0		(1 << 28)
#define I2C_TIMINGR_SCLDEL3		(1 << 23)
#define I2C_TIMINGR_SCLDEL2		(1 << 22)
#define I2C_TIMINGR_SCLDEL1		(1 << 21)
#define I2C_TIMINGR_SCLDEL0		(1 << 20)
#define I2C_TIMINGR_SDADEL3		(1 << 19)
#define I2C_TIMINGR_SDADEL2		(1 << 18)
#define I2C_TIMINGR_SDADEL1		(1 << 17)
#define I2C_TIMINGR_SDADEL0		(1 << 16)
#define I2C_TIMINGR_SCLH7		(1 << 15)
#define I2C_TIMINGR_SCLH6		(1 << 14)
#define I2C_TIMINGR_SCLH5		(1 << 13)
#define I2C_TIMINGR_SCLH4		(1 << 12)
#define I2C_TIMINGR_SCLH3		(1 << 11)
#define I2C_TIMINGR_SCLH2		(1 << 10)
#define I2C_TIMINGR_SCLH1		(1 << 9)
#define I2C_TIMINGR_SCLH0		(1 << 8)
#define I2C_TIMINGR_SCLL7		(1 << 7)
#define I2C_TIMINGR_SCLL6		(1 << 6)
#define I2C_TIMINGR_SCLL5		(1 << 5)
#define I2C_TIMINGR_SCLL4		(1 << 4)
#define I2C_TIMINGR_SCLL3		(1 << 3)
#define I2C_TIMINGR_SCLL2		(1 << 2)
#define I2C_TIMINGR_SCLL1		(1 << 1)
#define I2C_TIMINGR_SCLL0		(1 << 0)

/* --- I2C_TIMEOUTR values ------------------------------------------------- */

#define I2C_TIMEOUTR_TEXTEN		(1 << 31)
#define I2C_TIMEOUTR_TIMEOUTB11		(1 << 27)
#define I2C_TIMEOUTR_TIMEOUTB10		(1 << 26)
#define I2C_TIMEOUTR_TIMEOUTB9		(1 << 25)
#define I2C_TIMEOUTR_TIMEOUTB8		(1 << 24)
#define I2C_TIMEOUTR_TIMEOUTB7		(1 << 23)
#define I2C_TIMEOUTR_TIMEOUTB6		(1 << 22)
#define I2C_TIMEOUTR_TIMEOUTB5		(1 << 21)
#define I2C_TIMEOUTR_TIMEOUTB4		(1 << 20)
#define I2C_TIMEOUTR_TIMEOUTB3		(1 << 19)
#define I2C_TIMEOUTR_TIMEOUTB2		(1 << 18)
#define I2C_TIMEOUTR_TIMEOUTB1		(1 << 17)
#define I2C_TIMEOUTR_TIMEOUTB0		(1 << 16)
#define I2C_TIMEOUTR_TIMOUTEN		(1 << 15)
#define I2C_TIMEOUTR_TIDLE		(1 << 12)
#define I2C_TIMEOUTR_TIMEOUTA11		(1 << 11)
#define I2C_TIMEOUTR_TIMEOUTA10		(1 << 10)
#define I2C_TIMEOUTR_TIMEOUTA9		(1 << 9)
#define I2C_TIMEOUTR_TIMEOUTA8		(1 << 8)
#define I2C_TIMEOUTR_TIMEOUTA7		(1 << 7)
#define I2C_TIMEOUTR_TIMEOUTA6		(1 << 6)
#define I2C_TIMEOUTR_TIMEOUTA5		(1 << 5)
#define I2C_TIMEOUTR_TIMEOUTA4		(1 << 4)
#define I2C_TIMEOUTR_TIMEOUTA3		(1 << 3)
#define I2C_TIMEOUTR_TIMEOUTA2		(1 << 2)
#define I2C_TIMEOUTR_TIMEOUTA1		(1 << 1)
#define I2C_TIMEOUTR_TIMEOUTA0		(1 << 0)

/* --- I2C_ISR values ------------------------------------------------------ */

#define I2C_ISR_ADDCODE6		(1 << 23)
#define I2C_ISR_ADDCODE5		(1 << 22)
#define I2C_ISR_ADDCODE4		(1 << 21)
#define I2C_ISR_ADDCODE3		(1 << 20)
#define I2C_ISR_ADDCODE2		(1 << 19)
#define I2C_ISR_ADDCODE1		(1 << 18)
#define I2C_ISR_ADDCODE0		(1 << 17)
#define I2C_ISR_DIR			(1 << 16)
#define I2C_ISR_BUSY			(1 << 15)
#define I2C_ISR_ALERT			(1 << 13)
#define I2C_ISR_TIMEOUT			(1 << 12)
#define I2C_ISR_PECERR			(1 << 11)
#define I2C_ISR_OVR			(1 << 10)
#define I2C_ISR_ARLO			(1 << 9)
#define I2C_ISR_BERR			(1 << 8)
#define I2C_ISR_TCR			(1 << 7)
#define I2C_ISR_TC			(1 << 6)
#define I2C_ISR_STOPF			(1 << 5)
#define I2C_ISR_NACKF			(1 << 4)
#define I2C_ISR_ADDR			(1 << 3)
#define I2C_ISR_RXNE			(1 << 2)
#define I2C_ISR_TXIS			(1 << 1)
#define I2C_ISR_TXE			(1 << 0)

/* --- I2C_ICR values ------------------------------------------------------ */

#define I2C_ICR_ALERTCF			(1 << 13)
#define I2C_ICR_TIMOUTCF		(1 << 12)
#define I2C_ICR_PECCF			(1 << 11)
#define I2C_ICR_OVRCF			(1 << 10)
#define I2C_ICR_ARLOCF			(1 << 9)
#define I2C_ICR_BERRCF			(1 << 8)
#define I2C_ICR_STOPCF			(1 << 5)
#define I2C_ICR_NACKCF			(1 << 4)
#define I2C_ICR_ADDRCF			(1 << 3)

/* --- I2C_PECR values ----------------------------------------------------- */

/* I2C_PECR[7:0]: PEC[7:0]: Packet error checking register */

/* --- I2C_RXDR values ----------------------------------------------------- */

/* I2C_RXDR[7:0]: RXDATA[7:0]: 8-bit receive data */

/* --- I2C_TXDR values ----------------------------------------------------- */

/* I2C_TXDR[7:0]: TXDATA[7:0]: 8-bit transmit data */

/* --- Function prototypes ------------------------------------------------- */

/* Device number */
enum i2c {
	I2C1,
	I2C2,
	I2C3
};

/* Configuration */
enum {
	I2C_ENABLE = (1 << 0),
	I2C_ANFOFF = (1 << 12),

	/* slave mode */
	I2C_SBC = (1 << 16),
	I2C_NOSTRECH = (1 << 17),
	I2C_WUPEN = (1 << 18),
	I2C_GCEN = (1 << 19),

	/* SMBus */
	I2C_SMBHEN = (1 << 20),
	I2C_SMBDEN = (1 << 21),
	I2C_ALERTEN = (1 << 22),
	I2C_PECEN = (1 << 23)
};

/* DMA request */
enum i2c_dma {
	I2C_DMA_TX = (1 << 14),
	I2C_DMA_RX = (2 << 14),
	I2C_DMA_TX_RX = (3 << 14)
};

/* SADD and NBYTES */
enum {
	I2C_READ = (1 << 10),
	I2C_WRITE = 0,
	I2C_ADD10 = (1 << 11),
	I2C_HEAD10R = (1 << 12),

	I2C_RELOAD = (1 << 24),
	I2C_AUTOEND = (1 << 25)
};

/* Own address */
enum {
	/* OA1 */
	I2C_OA10 = (1 << 10),

	/* OA2 */
	I2C_MASK_1 = (1 << 8),
	I2C_MASK_2_1 = (2 << 8),
	I2C_MASK_3_1 = (3 << 8),
	I2C_MASK_4_1 = (4 << 8),
	I2C_MASK_5_1 = (5 << 8),
	I2C_MASK_6_1 = (6 << 8),
	I2C_MASK_7_1 = (7 << 8),

	I2C_OA_ENABLE = (1 << 15)
};

/* Timeout */
enum {
	/* TIMEOUTA */
	I2C_TIDLE = (1 << 12),

	I2C_TIMEOUT_ENABLE = (1 << 15)
};

/* Interrupt and status */
enum {
	I2C_TXE = (1 << 0),
	I2C_TXIS = (1 << 1),
	I2C_RXNE = (1 << 2),
	I2C_NACKF = (1 << 4),
	I2C_STOPF = (1 << 5),
	I2C_TCR = (1 << 7),
	I2C_BERR = (1 << 8),
	I2C_ARLO = (1 << 9),

	I2C_BUSY = (1 << 15),

	/* master mode */
	I2C_TC = (1 << 6),

	/* slave mode */
	I2C_ADDR = (1 << 3),
	I2C_OVR = (1 << 10),
	I2C_DIR = (1 << 16),
	I2C_ADDCODE = (0x7f << 17),

	/* SMBus */
	I2C_PECERR = (1 << 11),
	I2C_TIMEOUT = (1 << 12),
	I2C_ALERT = (1 << 13)
};

void i2c_set_digital_noise_filter(enum i2c i2c, int dnf);
void i2c_set_delay(enum i2c i2c, int sdadel, int scldel);
void i2c_init_master(enum i2c i2c, int prescaler, int scl_hi, int scl_lo,
		     int config);
void i2c_enable(enum i2c i2c);
void i2c_disable(enum i2c i2c);
void i2c_enable_dma(enum i2c i2c, enum i2c_dma request);
void i2c_disable_dma(enum i2c i2c, enum i2c_dma request);
void i2c_start(enum i2c i2c, int sadd, int nbytes);
void i2c_stop(enum i2c i2c);
void i2c_reload(enum i2c i2c, int nbytes);
void i2c_pecbyte(enum i2c i2c);
void i2c_init_slave(enum i2c i2c, int oa1, int oa2, int config);
void i2c_nack(enum i2c i2c);
void i2c_enable_wakeup(enum i2c i2c);
void i2c_disable_wakeup(enum i2c i2c);
void i2c_set_timeout(enum i2c i2c, int timeouta, int timeoutb);
void i2c_enable_interrupt(enum i2c i2c, int interrupt);
void i2c_disable_interrupt(enum i2c i2c, int interrupt);
int i2c_get_interrupt_mask(enum i2c i2c, int interrupt);
int i2c_get_interrupt_status(enum i2c i2c, int interrupt);
void i2c_clear_interrupt(enum i2c i2c, int interrupt);
void i2c_generate_txis(enum i2c i2c);
void i2c_flush_txdr(enum i2c i2c);
int i2c_get_pec(enum i2c i2c);
void i2c_send(enum i2c i2c, int data);
int i2c_recv(enum i2c i2c);
void i2c_send_blocking(enum i2c i2c, int data);
int i2c_recv_blocking(enum i2c i2c);
