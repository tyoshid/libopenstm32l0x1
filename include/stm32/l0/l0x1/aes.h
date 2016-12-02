/*
 * AES
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
 * 15  Advanced encryption standard hardware accelerator (AES)
 */

/* --- AES registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		AES_CR		AES control register
 * 0x04		AES_SR		AES status register
 * 0x08		AES_DINR	AES data input register
 * 0x0c		AES_DOUTR	AES data output register
 * 0x10		AES_KEYR0	AES key register 0
 * 0x14		AES_KEYR1	AES key register 1
 * 0x18		AES_KEYR2	AES key register 2
 * 0x1c		AES_KEYR3	AES key register 3
 * 0x20		AES_IVR0	AES initialization vector register 0
 * 0x24		AES_IVR1	AES initialization vector register 1
 * 0x28		AES_IVR2	AES initialization vector register 2
 * 0x2c		AES_IVR3	AES initialization vector register 3
 */

#define AES_CR				(AES_BASE + 0x00)
#define AES_SR				(AES_BASE + 0x04)
#define AES_DINR			(AES_BASE + 0x08)
#define AES_DOUTR			(AES_BASE + 0x0c)

#define AES_KEY(n)			(AES_BASE + 0x10 + (n) * 4)
#define AES_KEY0			AES_KEY(0)
#define AES_KEY1			AES_KEY(1)
#define AES_KEY2			AES_KEY(2)
#define AES_KEY3			AES_KEY(3)

#define AES_IVR(n)			(AES_BASE + 0x20 + (n) * 4)
#define AES_IVR0			AES_IVR(0)
#define AES_IVR1			AES_IVR(1)
#define AES_IVR2			AES_IVR(2)
#define AES_IVR3			AES_IVR(3)

/* --- AES_CR values ------------------------------------------------------- */

#define AES_CR_DMAOUTEN			(1 << 12)
#define AES_CR_DMAINEN			(1 << 11)
#define AES_CR_ERRIE			(1 << 10)
#define AES_CR_CCFIE			(1 << 9)
#define AES_CR_ERRC			(1 << 8)
#define AES_CR_CCFC			(1 << 7)
#define AES_CR_CHMOD1			(1 << 6)
#define AES_CR_CHMOD0			(1 << 5)
#define AES_CR_MODE1			(1 << 4)
#define AES_CR_MODE0			(1 << 3)
#define AES_CR_DATATYPE1		(1 << 2)
#define AES_CR_DATATYPE0		(1 << 1)
#define AES_CR_EN			(1 << 0)

/* AES chaining mode */
#define AES_CR_CHMOD_EBC		(0 << 5)
#define AES_CR_CHMOD_CBC		(1 << 5)
#define AES_CR_CHMOD_CTR		(2 << 5)

/* AES operating mode */
#define AES_CR_MODE_ENCRYPTION		(0 << 3)
#define AES_CR_MODE_KEY_DERIVATION	(1 << 3)
#define AES_CR_MODE_DECRYPTION		(2 << 3)
#define AES_CR_MODE_KEY_PLUS_DECRYPT	(3 << 3)

/* Data type selection */
#define AES_CR_DATATYPE_32BIT		(0 << 1)
#define AES_CR_DATATYPE_16BIT		(1 << 1)
#define AES_CR_DATATYPE_8BIT		(2 << 1)
#define AES_CR_DATATYPE_1BIT		(3 << 1)

/* --- AES_SR values ------------------------------------------------------- */

#define AES_SR_WRERR			(1 << 2)
#define AES_SR_RDERR			(1 << 1)
#define AES_SR_CCF			(1 << 0)

/* --- AES_DINR values ----------------------------------------------------- */

/* AES_DINR[31:0]: DINR[31:0]: Data input register */

/* --- AES_DOUTR values ---------------------------------------------------- */

/* AES_DOUTR[31:0]: DOUTR[31:0]: Data output register */

/* --- AES_KEYR0 values ---------------------------------------------------- */

/* AES_KEYR0[31:0]: KEYR0[31:0]: AES key register (LSB key[31:0]) */

/* --- AES_KEYR1 values ---------------------------------------------------- */

/* AES_KEYR1[31:0]: KEYR1[31:0]: AES key register (key[63:32]) */

/* --- AES_KEYR2 values ---------------------------------------------------- */

/* AES_KEYR2[31:0]: KEYR2[31:0]: AES key register (key[95:64]) */

/* --- AES_KEYR3 values ---------------------------------------------------- */

/* AES_KEYR3[31:0]: KEYR3[31:0]: AES key register (MSB key[127:96]) */

/* --- AES_IVR0 values ----------------------------------------------------- */

/* AES_IVR0[31:0]: IVR0[31:0]: Initialization vector register (LSB IVR[31:0]) */

/* --- AES_IVR1 values ----------------------------------------------------- */

/* AES_IVR1[31:0]: IVR1[31:0]: Initialization vector register (IVR[63:32]) */

/* --- AES_IVR2 values ----------------------------------------------------- */

/* AES_IVR2[31:0]: IVR2[31:0]: Initialization vector register (IVR[95:64]) */

/* --- AES_IVR3 values ----------------------------------------------------- */

/* AES_IVR3[31:0]: IVR3[31:0]: Initialization vector register */
/* (MSB IVR[127:96]) */

/* --- Function prototypes ------------------------------------------------- */

/* AES operating mode */
enum aes_mode {
	AES_MODE1 = 0,
	AES_MODE2 = 1,
	AES_MODE3 = 2,
	AES_MODE4 = 3,

	AES_ENCRYPTION = 0,
	AES_KEY_DERIVATION = 1,
	AES_DECRYPTION = 2,
	AES_KEY_DERIVATION_DECRYPTION = 3
};

/* AES chaining mode */
enum aes_chaining_mode {
	AES_ECB,
	AES_CBC,
	AES_CTR
};

/* Data type */
enum aes_data_type {
	AES_32BIT,
	AES_16BIT,
	AES_8BIT,
	AES_1BIT
};

/* DMA */
enum {
	AES_DMA_IN = (1 << 11),
	AES_DMA_OUT = (1 << 12)
};

/* Interrupt */
enum {
	AES_COMPLETE = (1 << 0),
	AES_RDERR = (1 << 1),
	AES_WRERR = (1 << 2)
};

void aes_init(enum aes_mode mode, enum aes_chaining_mode chaining,
	      enum aes_data_type type);
void aes_set_key(int *key);
void aes_get_key(int *key);
void aes_set_init_vector(int *vec);
void aes_enable(void);
void aes_disable(void);
void aes_set_data(int data);
int aes_get_data(void);
void aes_enable_dma(int dma);
void aes_disable_dma(int dma);
void aes_enable_interrupt(int interrupt);
void aes_disable_interrupt(int interrupt);
int aes_get_interrupt_mask(int interrupt);
int aes_get_interrupt_status(int interrupt);
void aes_clear_interrupt(int interrupt);
