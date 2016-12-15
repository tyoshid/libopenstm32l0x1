/*
 * LPTIM
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
 * 19  Low-power timer (LPTIM)
 */

/* --- LPTIM registers ----------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		LPTIMx_ISR	LPTIM Interrupt and Status Register
 * 0x04		LPTIMx_ICR	LPTIM Interrupt Clear Register
 * 0x08		LPTIMx_IER	LPTIM Interrupt Enable Register
 * 0x0c		LPTIMx_CFGR	LPTIM Configuration Register
 * 0x10		LPTIMx_CR	LPTIM Control Register
 * 0x14		LPTIMx_CMP	LPTIM Compare Register
 * 0x18		LPTIMx_ARR	LPTIM Autoreload Register
 * 0x1c		LPTIMx_CNT	LPTIM Counter Register
 */

#define LPTIM_ISR(base)			((base) + 0x00)
#define LPTIM1_ISR			LPTIM_ISR(LPTIM1_BASE)

#define LPTIM_ICR(base)			((base) + 0x04)
#define LPTIM1_ICR			LPTIM_ICR(LPTIM1_BASE)

#define LPTIM_IER(base)			((base) + 0x08)
#define LPTIM1_IER			LPTIM_IER(LPTIM1_BASE)

#define LPTIM_CFGR(base)		((base) + 0x0c)
#define LPTIM1_CFGR			LPTIM_CFGR(LPTIM1_BASE)

#define LPTIM_CR(base)			((base) + 0x10)
#define LPTIM1_CR			LPTIM_CR(LPTIM1_BASE)

#define LPTIM_CMP(base)			((base) + 0x14)
#define LPTIM1_CMP			LPTIM_CMP(LPTIM1_BASE)

#define LPTIM_ARR(base)			((base) + 0x18)
#define LPTIM1_ARR			LPTIM_ARR(LPTIM1_BASE)

#define LPTIM_CNT(base)			((base) + 0x1c)
#define LPTIM1_CNT			LPTIM_CNT(LPTIM1_BASE)

/* --- LPTIMx_ISR values --------------------------------------------------- */

#define LPTIM_ISR_DOWN			(1 << 6)
#define LPTIM_ISR_UP			(1 << 5)
#define LPTIM_ISR_ARROK			(1 << 4)
#define LPTIM_ISR_CMPOK			(1 << 3)
#define LPTIM_ISR_EXTTRIG		(1 << 2)
#define LPTIM_ISR_ARRM			(1 << 1)
#define LPTIM_ISR_CMPM			(1 << 0)

/* --- LPTIMx_ICR values --------------------------------------------------- */

#define LPTIM_ICR_DOWNCF		(1 << 6)
#define LPTIM_ICR_UPCF			(1 << 5)
#define LPTIM_ICR_ARROKCF		(1 << 4)
#define LPTIM_ICR_CMPOKCF		(1 << 3)
#define LPTIM_ICR_EXTTRIGCF		(1 << 2)
#define LPTIM_ICR_ARRMCF		(1 << 1)
#define LPTIM_ICR_CMPMCF		(1 << 0)

/* --- LPTIMx_IER values --------------------------------------------------- */

#define LPTIM_IER_DOWNIE		(1 << 6)
#define LPTIM_IER_UPIE			(1 << 5)
#define LPTIM_IER_ARROKIE		(1 << 4)
#define LPTIM_IER_CMPOKIE		(1 << 3)
#define LPTIM_IER_EXTTRIGIE		(1 << 2)
#define LPTIM_IER_ARRMIE		(1 << 1)
#define LPTIM_IER_CMPMIE		(1 << 0)

/* --- LPTIMx_CFGR values -------------------------------------------------- */

#define LPTIM_CFGR_ENC			(1 << 24)
#define LPTIM_CFGR_COUNTMODE		(1 << 23)
#define LPTIM_CFGR_PRELOAD		(1 << 22)
#define LPTIM_CFGR_WAVPOL		(1 << 21)
#define LPTIM_CFGR_WAVE			(1 << 20)
#define LPTIM_CFGR_TIMEOUT		(1 << 19)
#define LPTIM_CFGR_TRIGEN1		(1 << 18)
#define LPTIM_CFGR_TRIGEN0		(1 << 17)
#define LPTIM_CFGR_TRIGSEL2		(1 << 15)
#define LPTIM_CFGR_TRIGSEL1		(1 << 14)
#define LPTIM_CFGR_TRIGSEL0		(1 << 13)
#define LPTIM_CFGR_PRESC2		(1 << 11)
#define LPTIM_CFGR_PRESC1		(1 << 10)
#define LPTIM_CFGR_PRESC0		(1 << 9)
#define LPTIM_CFGR_TRGFLT1		(1 << 7)
#define LPTIM_CFGR_TRGFLT0		(1 << 6)
#define LPTIM_CFGR_CKFLT1		(1 << 4)
#define LPTIM_CFGR_CKFLT0		(1 << 3)
#define LPTIM_CFGR_CKPOL1		(1 << 2)
#define LPTIM_CFGR_CKPOL0		(1 << 1)
#define LPTIM_CFGR_CKSEL		(1 << 0)

/* Trigger enable and polarity */
#define LPTIM_CFGR_TRIGEN_SOFTWARE	(0 << 17)
#define LPTIM_CFGR_TRIGEN_RISING	(1 << 17)
#define LPTIM_CFGR_TRIGEN_FALLING	(2 << 17)
#define LPTIM_CFGR_TRIGEN_BOTH		(3 << 17)

/* Trigger selector */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG0	(0 << 13) /* PA4,PA6,PA13,PB6,PC3 */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG1	(1 << 13) /* RTC alarm A */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG2	(2 << 13) /* RTC alarm B */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG3	(3 << 13) /* RTC_TAMP1 */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG4	(4 << 13) /* RTC_TAMP2 */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG5	(5 << 13) /* RTC_TAMP3 */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG6	(6 << 13) /* COMP1_OUT */
#define LPTIM_CFGR_TRIGSEL_EXT_TRIG7	(7 << 13) /* COMP2_OUT */

/* Clock prescaler */
#define LPTIM_CFGR_PRESC_1		(0 << 9)
#define LPTIM_CFGR_PRESC_2		(1 << 9)
#define LPTIM_CFGR_PRESC_4		(2 << 9)
#define LPTIM_CFGR_PRESC_8		(3 << 9)
#define LPTIM_CFGR_PRESC_16		(4 << 9)
#define LPTIM_CFGR_PRESC_32		(5 << 9)
#define LPTIM_CFGR_PRESC_64		(6 << 9)
#define LPTIM_CFGR_PRESC_128		(7 << 9)

/* Configurable digital filter for trigger */
#define LPTIM_CFGR_TRGFLT_NONE		(0 << 6)
#define LPTIM_CFGR_TRGFLT_2_CLOCK	(1 << 6)
#define LPTIM_CFGR_TRGFLT_4_CLOCK	(2 << 6)
#define LPTIM_CFGR_TRGFLT_8_CLOCK	(3 << 6)

/* Configurable digital filter for external clock */
#define LPTIM_CFGR_CKFLT_NONE		(0 << 3)
#define LPTIM_CFGR_CKFLT_2_CLOCK	(1 << 3)
#define LPTIM_CFGR_CKFLT_4_CLOCK	(2 << 3)
#define LPTIM_CFGR_CKFLT_8_CLOCK	(3 << 3)

/* Clock Polarity */
#define LPTIM_CFGR_CKPOL_RISING		(0 << 1)
#define LPTIM_CFGR_CKPOL_FALLING	(1 << 1)
#define LPTIM_CFGR_CKPOL_BOTH		(2 << 1)

#define LPTIM_CFGR_ENCODER_MODE1	(0 << 1)
#define LPTIM_CFGR_ENCODER_MODE2	(1 << 1)
#define LPTIM_CFGR_ENCODER_MODE3	(2 << 1)

/* --- LPTIMx_CR values ---------------------------------------------------- */

#define LPTIM_CR_CNTSTRT		(1 << 2)
#define LPTIM_CR_SNGSTRT		(1 << 1)
#define LPTIM_CR_ENABLE			(1 << 0)

/* --- LPTIMx_CMP values --------------------------------------------------- */

/* LPTIM_CMP[15:0]: CMP: Compare value */

/* --- LPTIMx_ARR values --------------------------------------------------- */

/* LPTIM_ARR[15:0]: ARR: Auto reload value */

/* --- LPTIMx_CNT values --------------------------------------------------- */

/* LPTIM_CNT[15:0]: CNT: Counter value */

/* --- Function prototypes ------------------------------------------------- */

/* Device number */
enum lptim {
	LPTIM1
};

/* Interrupt */
enum {
	LPTIM_CMPM = (1 << 0),
	LPTIM_ARRM = (1 << 1),
	LPTIM_EXTTRIG = (1 << 2),
	LPTIM_CMPOK = (1 << 3),
	LPTIM_ARROK = (1 << 4),
	LPTIM_UP = (1 << 5),
	LPTIM_DOWN = (1 << 6)
};

/* Polarity */
enum lptim_pol {
	LPTIM_RISING,
	LPTIM_FALLING,
	LPTIM_BOTH
};

/* Digital filter */
enum lptim_flt {
	LPTIM_FLT_NONE,
	LPTIM_2_CLOCK,
	LPTIM_4_CLOCK,
	LPTIM_8_CLOCK
};

/* External trigger source */
enum lptim_trig {
	LPTIM_GPIO = (0 << 13),
	LPTIM_RTC_ALARM_A = (1 << 13),
	LPTIM_RTC_ALARM_B = (2 << 13),
	LPTIM_RTC_TAMP1 = (3 << 13),
	LPTIM_RTC_TAMP2 = (4 << 13),
	LPTIM_RTC_TAMP3 = (5 << 13),
	LPTIM_COMP1_OUT = (6 << 13),
	LPTIM_COMP2_OUT = (7 << 13)
};

void lptim_enable_interrupt(enum lptim lptim, int interrupt);
void lptim_disable_interrupt(enum lptim lptim, int interrupt);
int lptim_get_interrupt_mask(enum lptim lptim, int interrupt);
int lptim_get_interrupt_status(enum lptim lptim, int interrupt);
void lptim_clear_interrupt(enum lptim lptim, int interrupt);
void lptim_enable_external_clock(enum lptim lptim, enum lptim_pol pol,
				 enum lptim_flt flt);
void lptim_disable_external_clock(enum lptim lptim);
void lptim_enable_external_event_count(enum lptim lptim, enum lptim_pol pol,
				       enum lptim_flt flt);
void lptim_disable_external_event_count(enum lptim lptim);
void lptim_set_prescaler(enum lptim lptim, int presc);
void lptim_enable_external_trigger(enum lptim lptim, enum lptim_trig src,
				enum lptim_pol pol, enum lptim_flt flt);
void lptim_disable_external_trigger(enum lptim lptim);
void lptim_enable_timeout(enum lptim lptim);
void lptim_disable_timeout(enum lptim lptim);
void lptim_set_waveform(enum lptim lptim, bool set_once, bool pol);
void lptim_enable_preload(enum lptim lptim);
void lptim_disable_preload(enum lptim lptim);
void lptim_enable_encoder_mode(enum lptim lptim, enum lptim_pol pol,
			       enum lptim_flt flt);
void lptim_disable_encoder_mode(enum lptim lptim);
void lptim_enable_timer(enum lptim lptim);
void lptim_disable_timer(enum lptim lptim);
void lptim_start_continuous(enum lptim lptim);
void lptim_start_single(enum lptim lptim);
void lptim_set_compare(enum lptim lptim, int cmp);
void lptim_set_autoreload(enum lptim lptim, int count);
int lptim_get_counter(enum lptim lptim);
