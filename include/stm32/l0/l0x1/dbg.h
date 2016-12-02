/*
 * DBG
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
 * 27  Debug support (DBG)
 */

/* --- DBG registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		DBG_IDCODE	MCU device ID code
 * 0x04		DBG_CR		Debug MCU configuration register
 * 0x08		DBG_APB1_FZ	Debug MCU APB1 freeze register
 * 0x0c		DBG_APB2_FZ	Debug MCU APB2 freeze register
 */

#define DBG_IDCODE			(DBG_BASE + 0x00)
#define DBG_CR				(DBG_BASE + 0x04)
#define DBG_APB1_FZ			(DBG_BASE + 0x08)
#define DBG_APB2_FZ			(DBG_BASE + 0x0c)

/* --- DBG_IDCODE values --------------------------------------------------- */

#define DBG_IDCODE_REV_ID_MASK		0xffff0000
#define DBG_IDCODE_DEV_ID_MASK		0x00000fff

/* Revision identifier */
#define DBG_IDCODE_REV_ID_A		0x10000000
/* Cat.1 devices */
#define DBG_IDCODE_REV_ID_Z		0x10080000
/* Cat.2 devices */
#define DBG_IDCODE_REV_ID_B		0x20000000
#define DBG_IDCODE_REV_ID_Y_CAT2	0x20080000
#define DBG_IDCODE_REV_ID_X_CAT2	0x20180000
/* Cat.3 devices */
#define DBG_IDCODE_REV_ID_Y		0x10180000
#define DBG_IDCODE_REV_ID_X		0x10380000
/* Cat.5 devices */
#define DBG_IDCODE_REV_ID_Z_CAT5	0x20080000

/* Device identifier */
#define DBG_IDCODE_DEV_ID_CAT1		0x457
#define DBG_IDCODE_DEV_ID_CAT2		0x425
#define DBG_IDCODE_DEV_ID_CAT3		0x417
#define DBG_IDCODE_DEV_ID_CAT5		0x447

/* --- DBG_CR values ------------------------------------------------------- */

#define DBG_CR_DBG_STANDBY		(1 << 2)
#define DBG_CR_DBG_STOP			(1 << 1)
#define DBG_CR_DBG_SLEEP		(1 << 0)

/* --- DBG_APB1_FZ values -------------------------------------------------- */

#define DBG_APB1_FZ_DBG_LPTIMER_STOP	(1 << 31)
#define DBG_APB1_FZ_DBG_I2C3_STOP	(1 << 30)
#define DBG_APB1_FZ_DBG_I2C1_STOP	(1 << 21)
#define DBG_APB1_FZ_DBG_IWDG_STOP	(1 << 12)
#define DBG_APB1_FZ_DBG_WWDG_STOP	(1 << 11)
#define DBG_APB1_FZ_DBG_RTC_STOP	(1 << 10)
#define DBG_APB1_FZ_DBG_TIM7_STOP	(1 << 5)
#define DBG_APB1_FZ_DBG_TIM6_STOP	(1 << 4)
#define DBG_APB1_FZ_DBG_TIM3_STOP	(1 << 1)
#define DBG_APB1_FZ_DBG_TIM2_STOP	(1 << 0)

/* --- DBG_APB2_FZ values -------------------------------------------------- */

#define DBG_APB2_FZ_DBG_TIM22_STOP	(1 << 5)
#define DBG_APB2_FZ_DBG_TIM21_STOP	(1 << 2)

/* --- Function prototypes ------------------------------------------------- */

int dbg_get_mcu_id(void);
