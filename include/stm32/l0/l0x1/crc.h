/*
 * CRC
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
 * 4  Cyclic redundancy check calculation unit (CRC)
 */

/* --- CRC registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		CRC_DR		Data register
 * 0x04		CRC_IDR		Independent data register
 * 0x08		CRC_CR		Control register
 * 0x10		CRC_INIT	Initial CRC value
 * 0x14		CRC_POL		CRC polynomial
 */

#define CRC_DR				(CRC_BASE + 0x00)
#define CRC_IDR				(CRC_BASE + 0x04)
#define CRC_CR				(CRC_BASE + 0x08)
#define CRC_INIT			(CRC_BASE + 0x10)
#define CRC_POL				(CRC_BASE + 0x14)

/* --- CRC_DR values ------------------------------------------------------- */

/* CRC_DR[31:0]: DR[31:0]: Data register bits */

/* --- CRC_IDR values ------------------------------------------------------ */

/* CRC_IDR[7:0]: IDR[7:0]: General-purpose 8-bit data register bits */

/* --- CRC_CR values ------------------------------------------------------- */

#define CRC_CR_REV_OUT			(1 << 7)
#define CRC_CR_REV_IN1			(1 << 6)
#define CRC_CR_REV_IN0			(1 << 5)
#define CRC_CR_POLYSIZE1		(1 << 4)
#define CRC_CR_POLYSIZE0		(1 << 3)
#define CRC_CR_RESET			(1 << 0)

/* Reverse input data */
#define CRC_CR_REV_IN_BYTE		(1 << 5)
#define CRC_CR_REV_IN_HALFWORD		(2 << 5)
#define CRC_CR_REV_IN_WORD		(3 << 5)

/* Polynomial size */
#define CRC_CR_POLYSIZE_32		(0 << 3)
#define CRC_CR_POLYSIZE_16		(1 << 3)
#define CRC_CR_POLYSIZE_8		(2 << 3)
#define CRC_CR_POLYSIZE_7		(3 << 3)

/* --- CRC_INIT values ----------------------------------------------------- */

/* CRC_INIT[31:0]: CRC_INIT: Programmable initial CRC value */

/* --- CRC_POL values ------------------------------------------------------ */

/* CRC_POL[31:0]: POL[31:0]: Programmable polynomial */

/* --- Function prototypes ------------------------------------------------- */

/* Mode */
enum {
	CRC_POLYSIZE_32 = (0 << 3),
	CRC_POLYSIZE_16 = (1 << 3),
	CRC_POLYSIZE_8 = (2 << 3),
	CRC_POLYSIZE_7 = (3 << 3),
	CRC_REV_IN_BYTE = (1 << 5),
	CRC_REV_IN_HALFWORD = (2 << 5),
	CRC_REV_IN_WORD = (3 << 5),
	CRC_REV_OUT = (1 << 7)
};

void crc_set_mode(int pol, int mode);
int crc_calc(int crc, char *buffer, int len);
int crc_calc16(int crc, short *buffer, int len);
int crc_calc32(int crc, int *buffer, int len);
