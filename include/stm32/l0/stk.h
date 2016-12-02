/*
 * STK
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
 * PM0223: Programming manual
 * STM32L0 Series Cortex-M0+ programming manual
 * (15-Apr-2014 Rev 1)
 *
 * 4.4  SysTick timer (STK)
 */

/* --- STK registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		STK_CSR		SysTick Control and Status Register
 * 0x04		STK_RVR		SysTick Reload Value Register
 * 0x08		STK_CVR		SysTick Current Value Register
 * 0x0c		STK_CALIB	SysTick Calibration Value Register
 */

#define STK_CSR				(STK_BASE + 0x00)
#define STK_RVR				(STK_BASE + 0x04)
#define STK_CVR				(STK_BASE + 0x08)
#define STK_CALIB			(STK_BASE + 0x0c)

/* --- STK_CSR values ------------------------------------------------------ */

#define STK_CSR_COUNTFLAG		(1 << 16)
#define STK_CSR_CLKSOURCE		(1 << 2)
#define STK_CSR_TICKINT			(1 << 1)
#define STK_CSR_ENABLE			(1 << 0)

/* --- STK_RVR values ------------------------------------------------------ */

/* STK_RVR[23:0]: RELOAD[23:0]: value to load into the STK_CVR */

/* --- STK_CVR values ------------------------------------------------------ */

/* STK_CVR[23:0]: CURRENT[23:0]: the current value of the SysTick counter */

/* --- STK_CALIB values ---------------------------------------------------- */

#define STK_CALIB_NOREF			(1 << 31)
#define STK_CALIB_SKEW			(1 << 30)
/* STK_CALIB[23:0]: TENMS[23:0]: the calibration value */

/* --- Function prototypes ------------------------------------------------- */

/* Control */
enum {
	STK_HCLK_8 = 0,
	STK_ENABLE = 1,
	STK_INT = 2,
	STK_HCLK = 4	/* clock source */
};

void stk_init(int count, int control);
void stk_set_reload(int count);
int stk_get_counter(void);
void stk_enable_interrupt(void);
void stk_disable_interrupt(void);
void stk_enable_counter(void);
void stk_disable_counter(void);
bool stk_countflag(void);
int stk_get_calib(void);
