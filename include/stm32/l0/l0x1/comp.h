/*
 * COMP
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
 * 14  Comparator (COMP)
 */

/* --- COMP registers ------------------------------------------------------ */
/*
 * Offset	Register
 * 0x18		COMP1_CSR	Comparator 1 control and status register
 * 0x1c		COMP2_CSR	Comparator 2 control and status register
 */

#define COMP1_CSR			(SYSCFG_BASE + 0x18)
#define COMP2_CSR			(SYSCFG_BASE + 0x1c)

/* --- COMP1_CSR values ---------------------------------------------------- */

#define COMP1_CSR_COMP1LOCK		(1 << 31)
#define COMP1_CSR_COMP1VALUE		(1 << 30)
#define COMP1_CSR_COMP1POLARITY		(1 << 15)
#define COMP1_CSR_COMP1LPTIMIN1		(1 << 12)
#define COMP1_CSR_COMP1WM		(1 << 8)
#define COMP1_CSR_COMP1INNSEL1		(1 << 5)
#define COMP1_CSR_COMP1INNSEL0		(1 << 4)
#define COMP1_CSR_COMP1EN		(1 << 0)

/* Comparator 1 Input Minus connection configuration bit */
#define COMP1_CSR_COMP1INNSEL_VREFINT	(0 << 4)
#define COMP1_CSR_COMP1INNSEL_PA0	(1 << 4)
#define COMP1_CSR_COMP1INNSEL_PA4	(2 << 4)
#define COMP1_CSR_COMP1INNSEL_PA5	(3 << 4)

/* --- COMP2_CSR values ---------------------------------------------------- */

#define COMP2_CSR_COMP2LOCK		(1 << 31)
#define COMP2_CSR_COMP2VALUE		(1 << 30)
#define COMP2_CSR_COMP2POLARITY		(1 << 15)
#define COMP2_CSR_COMP2LPTIMIN1		(1 << 13)
#define COMP2_CSR_COMP2LPTIMIN2		(1 << 12)
#define COMP2_CSR_COMP2INPSEL2		(1 << 10)
#define COMP2_CSR_COMP2INPSEL1		(1 << 9)
#define COMP2_CSR_COMP2INPSEL0		(1 << 8)
#define COMP2_CSR_COMP2INNSEL2		(1 << 6)
#define COMP2_CSR_COMP2INNSEL1		(1 << 5)
#define COMP2_CSR_COMP2INNSEL0		(1 << 4)
#define COMP2_CSR_COMP2SPEED		(1 << 3)
#define COMP2_CSR_COMP2EN		(1 << 0)

/* Comparator 2 Input Plus connection configuration bit */
#define COMP2_CSR_COMP2INPSEL_PA3	(0 << 8)
#define COMP2_CSR_COMP2INPSEL_PB4	(1 << 8)
#define COMP2_CSR_COMP2INPSEL_PB5	(2 << 8)
#define COMP2_CSR_COMP2INPSEL_PB6	(3 << 8)
#define COMP2_CSR_COMP2INPSEL_PB7	(4 << 8)
#define COMP2_CSR_COMP2INPSEL_PA7	(5 << 8)

/* Comparator 2 Input Minus connection configuration bit */
#define COMP2_CSR_COMP2INNSEL_VREFINT	(0 << 4)
#define COMP2_CSR_COMP2INNSEL_PA2	(1 << 4)
#define COMP2_CSR_COMP2INNSEL_PA4	(2 << 4)
#define COMP2_CSR_COMP2INNSEL_PA5	(3 << 4)
#define COMP2_CSR_COMP2INNSEL_1_4_VREFINT	(4 << 4)
#define COMP2_CSR_COMP2INNSEL_1_2_VREFINT	(5 << 4)
#define COMP2_CSR_COMP2INNSEL_3_4_VREFINT	(6 << 4)
#define COMP2_CSR_COMP2INNSEL_PB3	(7 << 4)

/* --- Comparator startup time --------------------------------------------- */

#define COMP1_T_START			10	/* 10 us */
#define COMP2_T_START_FAST		20	/* 20 us */
#define COMP2_T_START_SLOW		25	/* 25 us */

/* --- Function prototypes ------------------------------------------------- */

/* Device number */
enum comp {
	COMP1,
	COMP2
};

/* Input */
enum comp_input {
	/* COMP1 - */
	COMP_VREFINT = (0 << 4),
	COMP_PA0 = (1 << 4),
	COMP_PA4 = (2 << 4),
	COMP_PA5 = (3 << 4),

	/* COMP1 + */
	COMP_PA1 = (0 << 8),
	COMP_COMP2 = (1 << 8),

	/* COMP2 - */
	/* VREFINT */
	COMP_PA2 = (1 << 4),
	/* PA4 */
	/* PA5 */
	COMP_1_4_VREFINT = (4 << 4),
	COMP_1_2_VREFINT = (5 << 4),
	COMP_3_4_VREFINT = (6 << 4),
	COMP_PB3 = (7 << 4),

	/* COMP2 + */
	COMP_PA3 = (0 << 8),
	COMP_PB4 = (1 << 8),
	COMP_PB5 = (2 << 8),
	COMP_PB6 = (3 << 8),
	COMP_PB7 = (4 << 8),
	COMP_PA7 = (5 << 8)
};

/* Function */
enum {
	COMP_ENABLE = (1 << 0),
	COMP_SLOW = 0,
	COMP_FAST = (1 << 3),
	COMP_INVERT = (1 << 15)
};

/* LPTIM1 remap */
enum comp_lptim1_remap {
	COMP_LPTIM1_NONE,
	COMP_LPTIM1_IN1,
	COMP_LPTIM1_IN2
};

void comp_init(enum comp comp, enum comp_input plus, enum comp_input minus,
	       int func);
void comp_enable(enum comp comp);
void comp_disable(enum comp comp);
void comp_lock(enum comp comp);
int comp_get_status(enum comp comp);
void comp_remap_lptim1_input(enum comp comp, enum comp_lptim1_remap remap);
