/*
 * FW
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
 * 5  Firewall (FW)
 */

/* --- FW registers -------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		FW_CSSA		Code segment start address
 * 0x04		FW_CSL		Code segment length
 * 0x08		FW_NVDSSA	Non-volatile data segment start address
 * 0x0c		FW_NVDSL	Non-volatile data segment length
 * 0x10		FW_VDSSA	Volatile data segment start address
 * 0x14		FW_VDSL		Volatile data segment length
 * 0x20		FW_CR		Configuration register
 */

#define FW_CSSA				(FIREWALL_BASE + 0x00)
#define FW_CSL				(FIREWALL_BASE + 0x04)
#define FW_NVDSSA			(FIREWALL_BASE + 0x08)
#define FW_NVDSL			(FIREWALL_BASE + 0x0c)
#define FW_VDSSA			(FIREWALL_BASE + 0x10)
#define FW_VDSL				(FIREWALL_BASE + 0x14)
#define FW_CR				(FIREWALL_BASE + 0x20)

/* --- FW_CSSA values ------------------------------------------------------ */

/* FW_CSSA[23:8]: ADD[23:8]: code segment start address */

/* --- FW_CSL values ------------------------------------------------------- */

/* FW_CSL[21:8]: LENG[21:8]: code segment length */

/* --- FW_NVDSSA values ---------------------------------------------------- */

/* FW_NVDSSA[23:8]: ADD[23:8]: Non-volatile data segment start address */

/* --- FW_NVDSL values ----------------------------------------------------- */

/* FW_NVDSL[21:8]: LENG[21:8]: Non-volatile data segment length */

/* --- FW_VDSSA values ----------------------------------------------------- */

/* FW_VDSSA[15:6]: ADD[15:6]: Volatile data segment start address */

/* --- FW_VDSL values ------------------------------------------------------ */

/* FW_VDSL[15:6]: LENG[15:6]: Volatile data segment length */

/* --- FW_CR values -------------------------------------------------------- */

#define FW_CR_VDE			(1 << 2)
#define FW_CR_VDS			(1 << 1)
#define FW_CR_FPA			(1 << 0)

/* --- Function prototypes ------------------------------------------------- */

/* Option */
enum {
	FW_FPA = (1 << 0),	/* Firewall pre arm */
	FW_VDS = (1 << 1),	/* Volatile data shared */
	FW_VDE = (1 << 2)	/* Volatile data execution */
};

void fw_init(int cssa, int csl, int nvdssa, int nvdsl, int vdssa, int vdsl,
	     int option);
void fw_enable_fpa(void);
void fw_disable_fpa(void);
