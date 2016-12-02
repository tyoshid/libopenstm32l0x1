/*
 * NVIC
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
 * 4.2  Nested Vectored Interrupt Controller
 */

/* --- NVIC registers ------------------------------------------------------ */
/*
 * Offset	Register
 * 0x000	NVIC_ISER	Interrupt Set-enable Register
 * 0x080	NVIC_ICER	Interrupt Clear-enable Register
 * 0x100	NVIC_ISPR	Interrupt Set-pending Register
 * 0x180	NVIC_ICPR	Interrupt Clear-pending Register
 * 0x300	NVIC_IPR0	Interrupt Priority Register
 *   |
 * 0x31c	NVIC_IPR7
 */

#define NVIC_ISER			(NVIC_BASE + 0x000)
#define NVIC_ICER			(NVIC_BASE + 0x080)
#define NVIC_ISPR			(NVIC_BASE + 0x100)
#define NVIC_ICPR			(NVIC_BASE + 0x180)

#define NVIC_IPR(x)			(NVIC_BASE + 0x300 + (x) * 4)
#define NVIC_IPR0			NVIC_IPR(0)
#define NVIC_IPR1			NVIC_IPR(1)
#define NVIC_IPR2			NVIC_IPR(2)
#define NVIC_IPR3			NVIC_IPR(3)
#define NVIC_IPR4			NVIC_IPR(4)
#define NVIC_IPR5			NVIC_IPR(5)
#define NVIC_IPR6			NVIC_IPR(6)
#define NVIC_IPR7			NVIC_IPR(7)

/* --- NVIC_ISER values ---------------------------------------------------- */

/* NVIC_ISER[31:0]: SETENA[31:0]: Interrupt set-enable bits. */

/* --- NVIC_ICER values ---------------------------------------------------- */

/* NVIC_ICER[31:0]: CLRENA[31:0]: Interrupt clear-enable bits. */

/* --- NVIC_ISPR values ---------------------------------------------------- */

/* NVIC_ISPR[31:0]: SETPEND[31:0]: Interrupt set-pending bits. */

/* --- NVIC_ICPR values ---------------------------------------------------- */

/* NVIC_ICPR[31:0]: CLRPEND[31:0]: Interrupt clear-pending bits. */

/* --- NVIC_IPRx values ---------------------------------------------------- */

/* NVIC_IPRx[31:24]: IP[4x + 3]: Priority, byte offset 3 */
/* NVIC_IPRx[23:16]: IP[4x + 2]: Priority, byte offset 2 */
/* NVIC_IPRx[15:8]:  IP[4x + 1]: Priority, byte offset 1 */
/* NVIC_IPRx[7:0]:   IP[4x]:     Priority, byte offset 0 */

/* --- Function prototypes ------------------------------------------------- */

int nvic_get_enabled_irq(int interrupt);
void nvic_enable_irq(int interrupt);
void nvic_disable_irq(int interrupt);
int nvic_get_pending_irq(int interrupt);
void nvic_set_pending_irq(int interrupt);
void nvic_clear_pending_irq(int interrupt);
void nvic_set_priority(int irqn, int priority);
int nvic_get_priority(int irqn);
