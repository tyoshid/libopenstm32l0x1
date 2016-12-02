/*
 * SCB
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
 * 4.3  System Control Block
 */

/* --- SCB registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		SCB_CPUID	CPUID Register
 * 0x04		SCB_ICSR	Interrupt Control and State Register
 * 0x08		SCB_VTOR	Vector Table Offset Register
 * 0x0c		SCB_AIRCR	Application Interrupt and Reset Control
 *				Register
 * 0x10		SCB_SCR		System Control Register
 * 0x14		SCB_CCR		Configuration and Control Register
 * 0x1c		SCB_SHPR2	System Handler Priority Register 2
 * 0x20		SCB_SHPR3	System Handler Priority Register 3
 */

#define SCB_CPUID			(SCB_BASE + 0x00)
#define SCB_ICSR			(SCB_BASE + 0x04)
#define SCB_VTOR			(SCB_BASE + 0x08)
#define SCB_AIRCR			(SCB_BASE + 0x0c)
#define SCB_SCR				(SCB_BASE + 0x10)
#define SCB_CCR				(SCB_BASE + 0x14)
#define SCB_SHPR2			(SCB_BASE + 0x1c)
#define SCB_SHPR3			(SCB_BASE + 0x20)

/* --- SCB_CPUID values ---------------------------------------------------- */

/* SCB_CPUID[31:24]: Implementer: Implementer code */
/* SCB_CPUID[23:20]: Variant: Major revision number */
/* SCB_CPUID[19:16]: Architecture: Constant */
/* SCB_CPUID[15:4]: PartNo: Part number of the processor */
/* SCB_CPUID[3:0]: Revision: Minor revision number */

/* --- SCB_ICSR values ----------------------------------------------------- */

#define SCB_ICSR_NMIPENDSET		(1 << 31)
#define SCB_ICSR_PENDSVSET		(1 << 28)
#define SCB_ICSR_PENDSVCLR		(1 << 27)
#define SCB_ICSR_PENDSTSET		(1 << 26)
#define SCB_ICSR_PENDSTCLR		(1 << 25)
#define SCB_ICSR_ISRPENDING		(1 << 22)
#define SCB_ICSR_VECTPENDING6		(1 << 18)
#define SCB_ICSR_VECTPENDING5		(1 << 17)
#define SCB_ICSR_VECTPENDING4		(1 << 16)
#define SCB_ICSR_VECTPENDING3		(1 << 15)
#define SCB_ICSR_VECTPENDING2		(1 << 14)
#define SCB_ICSR_VECTPENDING1		(1 << 13)
#define SCB_ICSR_VECTPENDING0		(1 << 12)
#define SCB_ICSR_RETOBASE		(1 << 11)
#define SCB_ICSR_VECTACTIVE8		(1 << 8)
#define SCB_ICSR_VECTACTIVE7		(1 << 7)
#define SCB_ICSR_VECTACTIVE6		(1 << 6)
#define SCB_ICSR_VECTACTIVE5		(1 << 5)
#define SCB_ICSR_VECTACTIVE4		(1 << 4)
#define SCB_ICSR_VECTACTIVE3		(1 << 3)
#define SCB_ICSR_VECTACTIVE2		(1 << 2)
#define SCB_ICSR_VECTACTIVE1		(1 << 1)
#define SCB_ICSR_VECTACTIVE0		(1 << 0)

/* --- SCB_VTOR values ----------------------------------------------------- */

/* SCB_VTOR[31:7]: TBLOFF: Vector table base offset field */

/* --- SCB_AIRCR values ---------------------------------------------------- */

/* SCB_AIRCR[31:16]: VECTKEY: Register key */
#define SCB_AIRCR_ENDIANESS		(1 << 15)
#define SCB_AIRCR_SYSRESETREQ		(1 << 2)
#define SCB_AIRCR_VECTCLRACTIVE		(1 << 1)

/* Register key */
#define SCB_AIRCR_VECTKEY		(0x05fa << 16)

/* --- SCB_SCR values ------------------------------------------------------ */

#define SCB_SCR_SEVEONPEND		(1 << 4)
#define SCB_SCR_SLEEPDEEP		(1 << 2)
#define SCB_SCR_SLEEPONEXIT		(1 << 1)

/* --- SCB_CCR values ------------------------------------------------------ */

#define SCB_CCR_STKALIGN		(1 << 9)
#define SCB_CCR_BFHFNMIGN		(1 << 8)
#define SCB_CCR_DIV_0_TRP		(1 << 4)
#define SCB_CCR_UNALIGN_TRP		(1 << 3)
#define SCB_CCR_USERSETMPEND		(1 << 1)
#define SCB_CCR_NONBASETHRDENA		(1 << 0)

/* --- SCB_SHPR2 values ---------------------------------------------------- */

/* SCB_SHPR2[31:24]: PRI_11[7:0]: Priority of system handler 11, SVCall */

/* --- SCB_SHPR3 values ---------------------------------------------------- */

/*
 * SCB_SHPR3[31:24]: PRI_15[7:0]: Priority of system handler 15,
 *				  SysTick exception
 */
/* SCB_SHPR3[23:16]: PRI_14[7:0]: Priority of system handler 14, PendSV */

/* --- Function prototypes ------------------------------------------------- */

/* Sleep */
enum {
	SCB_SLEEP_ON_EXIT = (1 << 1),
	SCB_SLEEP_DEEP = (1 << 2)
};

void scb_set_vector_table_offset(int tbloff);
void scb_reset_system(void);
void scb_set_sleep(int sleep);
int scb_get_sleep(void);
