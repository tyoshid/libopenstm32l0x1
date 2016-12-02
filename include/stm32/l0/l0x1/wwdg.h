/*
 * WWDG
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
 * 21  System window watchdog (WWDG)
 */

/* --- WWDG registers ------------------------------------------------------ */
/*
 * Offset	Register
 * 0x00		WWDG_CR		Control register
 * 0x04		WWDG_CFR	Configuration register
 * 0x08		WWDG_SR		Status register
 */

#define WWDG_CR				(WWDG_BASE + 0x00)
#define WWDG_CFR			(WWDG_BASE + 0x04)
#define WWDG_SR				(WWDG_BASE + 0x08)

/* --- WWDG_CR values ------------------------------------------------------ */

#define WWDG_CR_WDGA			(1 << 7)
#define WWDG_CR_T6			(1 << 6)
#define WWDG_CR_T5			(1 << 5)
#define WWDG_CR_T4			(1 << 4)
#define WWDG_CR_T3			(1 << 3)
#define WWDG_CR_T2			(1 << 2)
#define WWDG_CR_T1			(1 << 1)
#define WWDG_CR_T0			(1 << 0)

/* --- WWDG_CFR values ----------------------------------------------------- */

#define WWDG_CFR_EWI			(1 << 9)
#define WWDG_CFR_WDGTB1			(1 << 8)
#define WWDG_CFR_WDGTB0			(1 << 7)
#define WWDG_CFR_W6			(1 << 6)
#define WWDG_CFR_W5			(1 << 5)
#define WWDG_CFR_W4			(1 << 4)
#define WWDG_CFR_W3			(1 << 3)
#define WWDG_CFR_W2			(1 << 2)
#define WWDG_CFR_W1			(1 << 1)
#define WWDG_CFR_W0			(1 << 0)

/* Time base */
#define WWDG_CFR_WDGTB_CK_DIV1		(0 << 7)
#define WWDG_CFR_WDGTB_CK_DIV2		(1 << 7)
#define WWDG_CFR_WDGTB_CK_DIV4		(2 << 7)
#define WWDG_CFR_WDGTB_CK_DIV8		(3 << 7)

/* --- WWDG_SR values ------------------------------------------------------ */

#define WWDG_SR_EWIF			(1 << 0)

/* --- Function prototypes ------------------------------------------------- */

/* Interrupt */
enum {
	WWDG_EARLY_WAKEUP = (1 << 0)
};

void wwdg_set_window(int prescaler, int window);
void wwdg_reload(int count);
void wwdg_enable_interrupt(int interrupt);
int wwdg_get_interrupt_mask(int interrupt);
int wwdg_get_interrupt_status(int interrupt);
void wwdg_clear_interrupt(int interrupt);
