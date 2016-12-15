/*
 * Miscellaneous registers (factory option bytes)
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
 * 28  Device electronic signature
 */

/* --- miscellaneous registers --------------------------------------------- */
/*
 * Offset	Register
 * 0x50		MISC_U_ID0		31:0 unique ID bits
 * 0x54		MISC_U_ID1		63:32 unique ID bits
 * 0x64		MISC_U_ID2		95:64 unique ID bits
 * 0x78		MISC_VREFINT_CAL	VREFINT measured value
 * 0x7a		MISC_TS_CAL1		TS calibration value (30 degrees)
 * 0x7c		MISC_F_SIZE		Flash size register
 * 0x7e		MISC_TS_CAL2		TS calibration value (130 degrees)
 */

#define MISC_U_ID0			(OPTION_BYTE_BASE + 0x50)
#define MISC_U_ID1			(OPTION_BYTE_BASE + 0x54)
#define MISC_U_ID2			(OPTION_BYTE_BASE + 0x64)
#define MISC_VREFINT_CAL		(OPTION_BYTE_BASE + 0x78)
#define MISC_TS_CAL1			(OPTION_BYTE_BASE + 0x7a)
#define MISC_F_SIZE			(OPTION_BYTE_BASE + 0x7c)
#define MISC_TS_CAL2			(OPTION_BYTE_BASE + 0x7e)

/* --- Function prototypes ------------------------------------------------- */

int misc_get_flash_size(void);
void misc_get_unique_id(int *u_id);
int misc_get_vrefint_cal(void);
int misc_get_ts_cal1(void);
int misc_get_ts_cal2(void);
