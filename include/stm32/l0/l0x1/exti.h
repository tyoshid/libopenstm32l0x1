/*
 * EXTI
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
 * 12  Extended interrupts and events controller (EXTI)
 */

/* --- EXTI registers ------------------------------------------------------ */
/*
 * Offset	Register
 * 0x00		EXTI_IMR	EXTI interrupt mask register
 * 0x04		EXTI_EMR	EXTI event mask register
 * 0x08		EXTI_RTSR	EXTI rising edge trigger selection register
 * 0x0c		EXTI_FTSR	Falling edge trigger selection register
 * 0x10		EXTI_SWIER	EXTI software interrupt event register
 * 0x14		EXTI_PR		EXTI pending register
 */

#define EXTI_IMR			(EXTI_BASE + 0x00)
#define EXTI_EMR			(EXTI_BASE + 0x04)
#define EXTI_RTSR			(EXTI_BASE + 0x08)
#define EXTI_FTSR			(EXTI_BASE + 0x0c)
#define EXTI_SWIER			(EXTI_BASE + 0x10)
#define EXTI_PR				(EXTI_BASE + 0x14)

/* --- EXTI_IMR values ----------------------------------------------------- */

/* EXTI_IMR[29:28,26:0]: MRx: Interrupt mask on line x */

#define EXTI_IMR_MASK			0x37ffffff

/* --- EXTI_EMR values ----------------------------------------------------- */

/* EXTI_EMR[29:28,26:0]: MRx: Event mask on line x */

#define EXTI_EMR_MASK			0x37ffffff

/* --- EXTI_RTSR values ---------------------------------------------------- */
/*
 * EXTI_RTSR[22:19,17:0]: TRx: Rising edge trigger event configuration bit of
 *                       line x
 */

#define EXTI_RTSR_MASK			0x007bffff

/* --- EXTI_FTSR values ---------------------------------------------------- */
/*
 * EXTI_FTSR[22:19,17:0]: TRx: Falling edge trigger event configuration bit of
 *                       line x
 */

#define EXTI_FTSR_MASK			0x007bffff

/* --- EXTI_SWIER values --------------------------------------------------- */

/* EXTI_SWIER[22:19,17:0]: SWIERx: Software interrupt on line x */

#define EXTI_SWIER_MASK			0x007bffff

/* --- EXTI_PR values ------------------------------------------------------ */

/* EXTI_PR[22:19,17:0]: PRx: Pending bit */

#define EXTI_PR_MASK			0x007bffff

/* --- Function prototypes ------------------------------------------------- */

/* Line number */
enum {
	EXTI0 = (1 << 0),
	EXTI1 = (1 << 1),
	EXTI2 = (1 << 2),
	EXTI3 = (1 << 3),
	EXTI4 = (1 << 4),
	EXTI5 = (1 << 5),
	EXTI6 = (1 << 6),
	EXTI7 = (1 << 7),
	EXTI8 = (1 << 8),
	EXTI9 = (1 << 9),
	EXTI10 = (1 << 10),
	EXTI11 = (1 << 11),
	EXTI12 = (1 << 12),
	EXTI13 = (1 << 13),
	EXTI14 = (1 << 14),
	EXTI15 = (1 << 15),

	EXTI16 = (1 << 16),
	EXTI17 = (1 << 17),
	EXTI19 = (1 << 19),
	EXTI20 = (1 << 20),
	EXTI21 = (1 << 21),
	EXTI22 = (1 << 22),
	EXTI23 = (1 << 23),
	EXTI24 = (1 << 24),
	EXTI25 = (1 << 25),
	EXTI26 = (1 << 26),
	EXTI28 = (1 << 28),
	EXTI29 = (1 << 29),

	EXTI_PVD = (1 << 16),
	EXTI_RTC_ALARM = (1 << 17),
	EXTI_RTC_TAMPER_TIMESTAMP = (1 << 19),
	EXTI_CSS_LSE = (1 << 19),
	EXTI_RTC_WAKEUP_TIMER = (1 << 20),
	EXTI_COMP1_OUTPUT = (1 << 21),
	EXTI_COMP2_OUTPUT = (1 << 22),
	EXTI_I2C1_WAKEUP = (1 << 23),
	EXTI_I2C3_WAKEUP = (1 << 24),
	EXTI_USART1_WAKEUP = (1 << 25),
	EXTI_USART2_WAKEUP = (1 << 26),
	EXTI_LPUART1_WAKEUP = (1 << 28),
	EXTI_LPTIM1_WAKEUP = (1 << 29)
};

/* Trigger type */
enum exti_trigger {
	EXTI_TRIGGER_NONE,
	EXTI_RISING,
	EXTI_FALLING,
	EXTI_BOTH,
	EXTI_TRIGGER_UNKNOWN
};

void exti_set_trigger(int extis, enum exti_trigger type);
enum exti_trigger exti_get_trigger(int extis);
void exti_enable_interrupt(int extis);
void exti_disable_interrupt(int extis);
int exti_get_interrupt_mask(int extis);
int exti_get_interrupt_status(int extis);
void exti_clear_interrupt(int extis);
void exti_enable_event(int extis);
void exti_disable_event(int extis);
int exti_get_event_mask(int extis);
void exti_set_software_interrupt(int extis);
