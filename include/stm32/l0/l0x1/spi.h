/*
 * SPI
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
 * 26  Serial peripheral interface / inter-IC sound (SPI/I2S)
 */

/* --- SPI registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		SPI_CR1		SPI control register 1
 * 0x04		SPI_CR2		SPI control register 2
 * 0x08		SPI_SR		SPI status register
 * 0x0c		SPI_DR		SPI data register
 * 0x10		SPI_CRCPR	SPI CRC polynomial register
 * 0x14		SPI_RXCRCR	SPI RX CRC register
 * 0x18		SPI_TXCRCR	SPI TX CRC register
 * 0x1c		SPI_I2SCFGR	SPI I2S configuration register
 * 0x20		SPI_I2SPR	SPI I2S prescaler register
 */

#define SPI_CR1(base)			((base) + 0x00)
#define SPI1_CR1			SPI_CR1(SPI1_BASE)
#define SPI2_CR1			SPI_CR1(SPI2_BASE)

#define SPI_CR2(base)			((base) + 0x04)
#define SPI1_CR2			SPI_CR2(SPI1_BASE)
#define SPI2_CR2			SPI_CR2(SPI2_BASE)

#define SPI_SR(base)			((base) + 0x08)
#define SPI1_SR				SPI_SR(SPI1_BASE)
#define SPI2_SR				SPI_SR(SPI2_BASE)

#define SPI_DR(base)			((base) + 0x0c)
#define SPI1_DR				SPI_DR(SPI1_BASE)
#define SPI2_DR				SPI_DR(SPI2_BASE)

#define SPI_CRCPR(base)			((base) + 0x10)
#define SPI1_CRCPR			SPI_CRCPR(SPI1_BASE)
#define SPI2_CRCPR			SPI_CRCPR(SPI2_BASE)

#define SPI_RXCRCR(base)		((base) + 0x14)
#define SPI1_RXCRCR			SPI_RXCRCR(SPI1_BASE)
#define SPI2_RXCRCR			SPI_RXCRCR(SPI2_BASE)

#define SPI_TXCRCR(base)		((base) + 0x18)
#define SPI1_TXCRCR			SPI_TXCRCR(SPI1_BASE)
#define SPI2_TXCRCR			SPI_TXCRCR(SPI2_BASE)

#define SPI_I2SCFGR(base)		((base) + 0x1c)
#define SPI1_I2SCFGR			SPI_I2SCFGR(SPI1_BASE)
#define SPI2_I2SCFGR			SPI_I2SCFGR(SPI2_BASE)

#define SPI_I2SPR(base)			((base) + 0x20)
#define SPI1_I2SPR			SPI_I2SPR(SPI1_BASE)
#define SPI2_I2SPR			SPI_I2SPR(SPI2_BASE)

/* --- SPI_CR1 values ------------------------------------------------------ */

#define SPI_CR1_BIDIMODE		(1 << 15)
#define SPI_CR1_BIDIOE			(1 << 14)
#define SPI_CR1_CRCEN			(1 << 13)
#define SPI_CR1_CRCNEXT			(1 << 12)
#define SPI_CR1_DFF			(1 << 11)
#define SPI_CR1_RXONLY			(1 << 10)
#define SPI_CR1_SSM			(1 << 9)
#define SPI_CR1_SSI			(1 << 8)
#define SPI_CR1_LSBFIRST		(1 << 7)
#define SPI_CR1_SPE			(1 << 6)
#define SPI_CR1_BR2			(1 << 5)
#define SPI_CR1_BR1			(1 << 4)
#define SPI_CR1_BR0			(1 << 3)
#define SPI_CR1_MSTR			(1 << 2)
#define SPI_CR1_CPOL			(1 << 1)
#define SPI_CR1_CPHA			(1 << 0)

/* Baud rate control */
#define SPI_CR1_BR_2			(0 << 3)
#define SPI_CR1_BR_4			(1 << 3)
#define SPI_CR1_BR_8			(2 << 3)
#define SPI_CR1_BR_16			(3 << 3)
#define SPI_CR1_BR_32			(4 << 3)
#define SPI_CR1_BR_64			(5 << 3)
#define SPI_CR1_BR_128			(6 << 3)
#define SPI_CR1_BR_256			(7 << 3)

/* --- SPI_CR2 values ------------------------------------------------------ */

#define SPI_CR2_TXEIE			(1 << 7)
#define SPI_CR2_RXNEIE			(1 << 6)
#define SPI_CR2_ERRIE			(1 << 5)
#define SPI_CR2_FRF			(1 << 4)
#define SPI_CR2_SSOE			(1 << 2)
#define SPI_CR2_TXDMAEN			(1 << 1)
#define SPI_CR2_RXDMAEN			(1 << 0)

/* --- SPI_SR values ------------------------------------------------------- */

#define SPI_SR_FRE			(1 << 8)
#define SPI_SR_BSY			(1 << 7)
#define SPI_SR_OVR			(1 << 6)
#define SPI_SR_MODF			(1 << 5)
#define SPI_SR_CRCERR			(1 << 4)
#define SPI_SR_UDR			(1 << 3)
#define SPI_SR_CHSIDE			(1 << 2)
#define SPI_SR_TXE			(1 << 1)
#define SPI_SR_RXNE			(1 << 0)

/* --- SPI_DR values ------------------------------------------------------- */

/* SPI_DR[15:0]: DR[15:0]: Data register */

/* --- SPI_CRCPR values ---------------------------------------------------- */

/* SPI_CRCPR[15:0]: CRCPOLY[15:0]: CRC polynomial register */

/* --- SPI_RXCRCR values --------------------------------------------------- */

/* SPI_RXCRCR[15:0]: RXCRC[15:0]: Rx CRC register */

/* --- SPI_TXCRCR values --------------------------------------------------- */

/* SPI_TXCRCR[15:0]: TXCRC[15:0]: Tx CRC register */

/* --- SPI_I2SCFGR values -------------------------------------------------- */

#define SPI_I2SCFGR_I2SMOD		(1 << 11)
#define SPI_I2SCFGR_I2SE		(1 << 10)
#define SPI_I2SCFGR_I2SCFG1		(1 << 9)
#define SPI_I2SCFGR_I2SCFG0		(1 << 8)
#define SPI_I2SCFGR_PCMSYNC		(1 << 7)
#define SPI_I2SCFGR_I2SSTD1		(1 << 5)
#define SPI_I2SCFGR_I2SSTD0		(1 << 4)
#define SPI_I2SCFGR_CKPOL		(1 << 3)
#define SPI_I2SCFGR_DATLEN1		(1 << 2)
#define SPI_I2SCFGR_DATLEN0		(1 << 1)
#define SPI_I2SCFGR_CHLEN		(1 << 0)

/* I2S configuration mode */
#define SPI_I2SCFGR_I2SCFG_SLAVE_TX	(0 << 8)
#define SPI_I2SCFGR_I2SCFG_SLAVE_RX	(1 << 8)
#define SPI_I2SCFGR_I2SCFG_MASTER_TX	(2 << 8)
#define SPI_I2SCFGR_I2SCFG_MASTER_RX	(3 << 8)

/* I2S standard selection */
#define SPI_I2SCFGR_I2SSTD_I2S_PHILIPS	(0 << 4)
#define SPI_I2SCFGR_I2SSTD_LEFT_JUST	(1 << 4)
#define SPI_I2SCFGR_I2SSTD_RIGHT_JUST	(2 << 4)
#define SPI_I2SCFGR_I2SSTD_PCM_STANDARD	(3 << 4)

/* Data length to be transferred */
#define SPI_I2SCFGR_DATLEN_16		(0 << 1)
#define SPI_I2SCFGR_DATLEN_24		(1 << 1)
#define SPI_I2SCFGR_DATLEN_32		(2 << 1)

/* --- SPI_I2SPR values ---------------------------------------------------- */

#define SPI_I2SPR_MCKOE			(1 << 9)
#define SPI_I2SPR_ODD			(1 << 8)
#define SPI_I2SPR_I2SDIV7		(1 << 7)
#define SPI_I2SPR_I2SDIV6		(1 << 6)
#define SPI_I2SPR_I2SDIV5		(1 << 5)
#define SPI_I2SPR_I2SDIV4		(1 << 4)
#define SPI_I2SPR_I2SDIV3		(1 << 3)
#define SPI_I2SPR_I2SDIV2		(1 << 2)
#define SPI_I2SPR_I2SDIV1		(1 << 1)
#define SPI_I2SPR_I2SDIV0		(1 << 0)

/* --- Function prototypes ------------------------------------------------- */

/* Device number */
enum spi {
	SPI1,
	SPI2
};

/* Configuration */
enum {
	/* SPI mode */
	SPI_CPOL = (1 << 1),
	SPI_CPHA = (1 << 0),
	SPI_LSBFIRST = (1 << 7),
	SPI_RXONLY = (1 << 10),

	SPI_NSS_HIGH = (3 << 8),
	SPI_NSS_LOW = (2 << 8),
	SPI_NSS_OUTPUT = (1 << 18),

	SPI_CRCEN = (1 << 13),

	SPI_BIDIRECTIONAL = (1 << 15),
	SPI_BIDI_OUT = (1 << 14),
	SPI_BIDI_IN = 0,

	SPI_TI_MODE = (1 << 20),

	SPI_ENABLE = (1 << 6),

	/* I2S mode */
	SPI_I2S_MODE = (1 << 11),

	SPI_I2S_TX = (0 << 8),
	SPI_I2S_RX = (1 << 8),

	SPI_I2S_PHILIPS = (0 << 4),
	SPI_I2S_LEFT_JUSTIFIED = (1 << 4),
	SPI_I2S_RIGHT_JUSTIFIED = (2 << 4),
	SPI_I2S_PCM_STANDARD = (3 << 4),
	SPI_I2S_PCMSYNC = (1 << 7),

	SPI_I2S_CKPOL = (1 << 3),

	SPI_I2S_MCKOE = (1 << 25),

	SPI_I2S_ODD = (1 << 24),

	SPI_I2S_ENABLE = (1 << 10)
};

/* interrupt and status */
enum {
	SPI_RXNE = (1 << 0),
	SPI_TXE = (1 << 1),

	SPI_ERROR = (1 << 16),

	SPI_UDR = (1 << 3),
	SPI_CRCERR = (1 << 4),
	SPI_MODF = (1 << 5),
	SPI_OVR = (1 << 6),
	SPI_FRE = (1 << 8),

	SPI_CHSIDE = (1 << 2),
	SPI_BSY = (1 << 7)
};

/* DMA request */
enum spi_dma {
	SPI_DMA_TX = (2 << 16),
	SPI_DMA_RX = (1 << 16),
	SPI_DMA_TX_RX = (3 << 16)
};

void spi_init_master(enum spi spi, int prescaler, int bits, int config);
void spi_init_slave(enum spi spi, int bits, int config);
void spi_set_spi_mode(enum spi spi);
void spi_set_i2s_mode(enum spi spi);
void spi_enable(enum spi spi);
void spi_disable(enum spi spi);
void spi_i2s_enable(enum spi spi);
void spi_i2s_disable(enum spi spi);
void spi_set_ss(enum spi spi, bool value);
void spi_set_bidi_output(enum spi spi);
void spi_set_bidi_input(enum spi spi);
void spi_enable_interrupt(enum spi spi, int interrupt);
void spi_disable_interrupt(enum spi spi, int interrupt);
int spi_get_interrupt_mask(enum spi spi, int interrupt);
int spi_get_interrupt_status(enum spi spi, int interrupt);
void spi_clear_interrupt(enum spi spi, int interrupt);
void spi_enable_dma(enum spi spi, enum spi_dma request);
void spi_disable_dma(enum spi spi, enum spi_dma request);
void spi_set_crc_polynomial(enum spi spi, int polynomial);
void spi_enable_crc_phase(enum spi spi);
void spi_disable_crc_phase(enum spi spi);
int spi_get_rx_crc(enum spi spi);
int spi_get_tx_crc(enum spi spi);
void spi_send(enum spi spi, int data);
int spi_recv(enum spi spi);
void spi_send_blocking(enum spi spi, int data);
int spi_recv_blocking(enum spi spi);
