/*
 * RTC functions
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

#include <stdint.h>
#include <stdbool.h>

#include <mmio.h>
#include <memorymap.h>
#include <rtc.h>

void rtc_unlock(void)
{
	MMIO32(RTC_WPR) = 0xca;
	MMIO32(RTC_WPR) = 0x53;
}

void rtc_lock(void)
{
	MMIO32(RTC_WPR) = 0xfe;
	MMIO32(RTC_WPR) = 0x64;
}

void rtc_init(int prediv_a, int prediv_s, int date, int time, bool fmt,
	      bool refck)
{
	int r;

	MMIO32(RTC_ISR) |= RTC_ISR_INIT;
	while (!(MMIO32(RTC_ISR) & RTC_ISR_INITF))
		;
	MMIO32(RTC_PRER) = (prediv_a & 0x7f) << 16 | (prediv_s & 0x7fff);
	MMIO32(RTC_TR) = time & 0x7f7f7f;
	MMIO32(RTC_DR) = date & 0xffff3f;
	r = MMIO32(RTC_CR);
	if (fmt)
		r |= RTC_CR_FMT;
	else
		r &= ~RTC_CR_FMT;
	if (refck)
		r |= RTC_CR_REFCKON;
	else
		r &= ~RTC_CR_REFCKON;
	MMIO32(RTC_CR) = r;
	MMIO32(RTC_ISR) &= ~RTC_ISR_INIT;
	while (MMIO32(RTC_ISR) & RTC_ISR_INITF)
		;
}

void rtc_disable_shadow_register(void)
{
	MMIO32(RTC_CR) |= RTC_CR_BYPSHAD;
}

void rtc_enable_shadow_register(void)
{
	MMIO32(RTC_CR) &= ~RTC_CR_BYPSHAD;
}

void rtc_enable_daylight_saving_time(void)
{
	MMIO32(RTC_CR) |= RTC_CR_ADD1H | RTC_CR_BKP;
}

void rtc_disable_daylight_saving_time(void)
{
	int r;

	r = MMIO32(RTC_CR);
	r &= ~RTC_CR_BKP;
	MMIO32(RTC_CR) = r | RTC_CR_SUB1H;
}

void rtc_enable_alarm_a(int time, int ss)
{
	while (!(MMIO32(RTC_ISR) & RTC_ISR_ALRAWF))
		;
	MMIO32(RTC_ALRMAR) = time;
	MMIO32(RTC_ALRMASSR) = ss & 0x0f007fff;
	MMIO32(RTC_CR) |= RTC_CR_ALRAE;
}

void rtc_disable_alarm_a(void)
{
	MMIO32(RTC_CR) &= ~RTC_CR_ALRAE;
}

void rtc_enable_alarm_b(int time, int ss)
{
	while (!(MMIO32(RTC_ISR) & RTC_ISR_ALRBWF))
		;
	MMIO32(RTC_ALRMBR) = time;
	MMIO32(RTC_ALRMBSSR) = ss & 0x0f007fff;
	MMIO32(RTC_CR) |= RTC_CR_ALRBE;
}

void rtc_disable_alarm_b(void)
{
	MMIO32(RTC_CR) &= ~RTC_CR_ALRBE;
}

void rtc_enable_wakeup_timer(enum rtc_wakeup_clock wucksel, int autoreload)
{
	int r;

	while (!(MMIO32(RTC_ISR) & RTC_ISR_WUTWF))
		;
	MMIO32(RTC_WUTR) = autoreload & 0xffff;
	r = MMIO32(RTC_CR);
	r &= ~(RTC_CR_WUCKSEL2 | RTC_CR_WUCKSEL1 | RTC_CR_WUCKSEL0);
	MMIO32(RTC_CR) = r | wucksel | RTC_CR_WUTE;
}

void rtc_disable_wakeup_timer(void)
{
	MMIO32(RTC_CR) &= ~RTC_CR_WUTE;
}

void rtc_get_calendar(int *date, int *time, int *ss)
{
	while (!(MMIO32(RTC_ISR) & RTC_ISR_RSF))
		;
	*ss = MMIO32(RTC_SSR);
	*time = MMIO32(RTC_TR);
	*date = MMIO32(RTC_DR);
}

void rtc_get_calendar_read_twice(int *date, int *time, int *ss)
{
	int ss1;
	int time1;
	int date1;
	int ss2;
	int time2;
	int date2;

	do {
		ss1 = MMIO32(RTC_SSR);
		time1 = MMIO32(RTC_TR);
		date1 = MMIO32(RTC_DR);
		ss2 = MMIO32(RTC_SSR);
		time2 = MMIO32(RTC_TR);
		date2 = MMIO32(RTC_DR);
	} while (ss1 != ss2 || time1 != time2 || date1 != date2);
	*ss = ss1;
	*time = time1;
	*date = date1;
}

void rtc_synchronize(int add, int sub)
{
	while (MMIO32(RTC_ISR) & RTC_ISR_SHPF)
		;
	MMIO32(RTC_SHIFTR) = (add ? RTC_SHIFTR_ADD1S : 0) | (sub & 0x7fff);
}

void rtc_set_smooth_digital_calibration(int calp, int calm,
					enum rtc_cal_period calw)
{
	while (MMIO32(RTC_ISR) & RTC_ISR_RECALPF)
		;
	MMIO32(RTC_CALR) = (calp ? RTC_CALR_CALP : 0) | calw | (calm & 0x1ff);
}

void rtc_get_timestamp(int *date, int *time, int *ss)
{
	*ss = MMIO32(RTC_TSSSR);
	*time = MMIO32(RTC_TSTR);
	*date = MMIO32(RTC_TSDR);
}

void rtc_enable_interrupt(int interrupt)
{
	int cr = 0;
	int tampcr = 0;

	if (interrupt & RTC_ALARM_A)
		cr |= RTC_CR_ALRAIE;
	if (interrupt & RTC_ALARM_B)
		cr |= RTC_CR_ALRBIE;
	if (interrupt & RTC_WAKEUP)
		cr |= RTC_CR_WUTIE;
	if (interrupt & RTC_TIMESTAMP)
		cr |= RTC_CR_TSIE;
	if (interrupt & RTC_TAMPER1)
		tampcr |= RTC_TAMPCR_TAMP1IE;
	if (interrupt & RTC_TAMPER2)
		tampcr |= RTC_TAMPCR_TAMP2IE;
	if (interrupt & RTC_TAMPER3)
		tampcr |= RTC_TAMPCR_TAMP3IE;
	if (cr)
		MMIO32(RTC_CR) |= cr;
	if (tampcr)
		MMIO32(RTC_TAMPCR) |= tampcr;
}

void rtc_disable_interrupt(int interrupt)
{
	int cr = 0;
	int tampcr = 0;

	if (interrupt & RTC_ALARM_A)
		cr |= RTC_CR_ALRAIE;
	if (interrupt & RTC_ALARM_B)
		cr |= RTC_CR_ALRBIE;
	if (interrupt & RTC_WAKEUP)
		cr |= RTC_CR_WUTIE;
	if (interrupt & RTC_TIMESTAMP)
		cr |= RTC_CR_TSIE;
	if (interrupt & RTC_TAMPER1)
		tampcr |= RTC_TAMPCR_TAMP1IE;
	if (interrupt & RTC_TAMPER2)
		tampcr |= RTC_TAMPCR_TAMP2IE;
	if (interrupt & RTC_TAMPER3)
		tampcr |= RTC_TAMPCR_TAMP3IE;
	if (cr)
		MMIO32(RTC_CR) &= ~cr;
	if (tampcr)
		MMIO32(RTC_TAMPCR) &= ~tampcr;
}

int rtc_get_interrupt_mask(int interrupt)
{
	int r;
	int m = 0;

	if (interrupt & (RTC_ALARM_A | RTC_ALARM_B | RTC_WAKEUP |
			 RTC_TIMESTAMP)) {
		r = MMIO32(RTC_CR);
		if ((interrupt & RTC_ALARM_A) && (r & RTC_CR_ALRAIE))
			m |= RTC_ALARM_A;
		if ((interrupt & RTC_ALARM_B) && (r & RTC_CR_ALRBIE))
			m |= RTC_ALARM_B;
		if ((interrupt & RTC_WAKEUP) && (r & RTC_CR_WUTIE))
			m |= RTC_WAKEUP;
		if ((interrupt & RTC_TIMESTAMP) && (r & RTC_CR_TSIE))
			m |= RTC_TIMESTAMP;
	}
	if (interrupt & (RTC_TAMPER1 | RTC_TAMPER2 | RTC_TAMPER3)) {
		r = MMIO32(RTC_TAMPCR);
		if ((interrupt & RTC_TAMPER1) && (r & RTC_TAMPCR_TAMP1IE))
			m |= RTC_TAMPER1;
		if ((interrupt & RTC_TAMPER2) && (r & RTC_TAMPCR_TAMP2IE))
			m |= RTC_TAMPER2;
		if ((interrupt & RTC_TAMPER3) && (r & RTC_TAMPCR_TAMP3IE))
			m |= RTC_TAMPER3;
	}
	return m;
}

int rtc_get_interrupt_status(int interrupt)
{
	return MMIO32(RTC_ISR) & interrupt;
}

void rtc_clear_interrupt(int interrupt)
{
	MMIO32(RTC_ISR) &= ~interrupt;
}

void rtc_set_rtc_calib(enum rtc_cal_output cosel)
{
	int r;

	r = MMIO32(RTC_CR);
	r &= ~(RTC_CR_COE | RTC_CR_COSEL);
	MMIO32(RTC_CR) = r | cosel;
}

void rtc_set_rtc_alarm(enum rtc_alarm_output osel, bool low_level)
{
	int r;

	r = MMIO32(RTC_CR);
	if (low_level) {
		r &= ~(RTC_CR_OSEL1 | RTC_CR_OSEL0);
		MMIO32(RTC_CR) = r | osel | RTC_CR_POL;
	} else {
		r &= ~(RTC_CR_OSEL1 | RTC_CR_OSEL0 | RTC_CR_POL);
		MMIO32(RTC_CR) = r | osel;
	}
}

void rtc_remap_rtc_out(bool pb14, bool push_pull)
{
	int r;

	r = MMIO32(RTC_OR);
	if (pb14)
		r |= RTC_OR_RTC_OUT_RMP;
	else
		r &= ~RTC_OR_RTC_OUT_RMP;
	if (push_pull)
		MMIO32(RTC_OR) = r | RTC_OR_RTC_ALARM_TYPE;
	else
		MMIO32(RTC_OR) = r & ~RTC_OR_RTC_ALARM_TYPE;
}

void rtc_enable_timestamp(bool falling)
{
	int r;

	r = MMIO32(RTC_CR);
	if (falling)
		r |= RTC_CR_TSEDGE;
	else
		r &= ~RTC_CR_TSEDGE;
	MMIO32(RTC_CR) = r | RTC_CR_TSE;
}

void rtc_disable_timestamp(void)
{
	MMIO32(RTC_CR) &= ~RTC_CR_TSE;
}

void rtc_setup_tamper(int precharge, int sample_div, int filter_count,
		      bool timestamp)
{
	int i;
	int tamp;
	int r;

	if (precharge) {
		for (i = 0; i < 4; i++) {
			if (precharge == 1 << i)
				break;
		}
		if (i >= 4)
			return;
		tamp = i << 13; /* TAMPPRCH */
	} else {
		tamp = 1 << 15; /* TAMPPUDIS */
	}
	if (filter_count || sample_div) {
		for (i = 0; i < 8; i++) {
			if (sample_div == 32768 / (1 << i))
				break;
		}
		if (i >= 8)
			return;
		tamp |= i << 8;		/* TAMPFREQ */
	}
	if (filter_count) {
		for (i = 1; i < 4; i++) {
			if (filter_count == 1 << i)
				break;
		}
		if (i >= 4)
			return;
		tamp |= i << 11;	/* TAMPFLT */
	}
	if (timestamp)
		tamp |= RTC_TAMPCR_TAMPTS;
	r = MMIO32(RTC_TAMPCR);
	r &= ~(RTC_TAMPCR_TAMPPUDIS | RTC_TAMPCR_TAMPPRCH1 |
	       RTC_TAMPCR_TAMPPRCH0 | RTC_TAMPCR_TAMPFLT1 |
	       RTC_TAMPCR_TAMPFLT0 | RTC_TAMPCR_TAMPFREQ2 |
	       RTC_TAMPCR_TAMPFREQ1 | RTC_TAMPCR_TAMPFREQ0 |
	       RTC_TAMPCR_TAMPTS);
	MMIO32(RTC_TAMPCR) = r | tamp;
}

void rtc_enable_tamp1(enum rtc_tamp_trigger trigger, bool mask, bool no_erase)
{
	int r;

	r = MMIO32(RTC_TAMPCR);
	if (trigger)
		r |= RTC_TAMPCR_TAMP1TRG;
	else
		r &= ~RTC_TAMPCR_TAMP1TRG;
	if (mask)
		r |= RTC_TAMPCR_TAMP1MF;
	else
		r &= ~RTC_TAMPCR_TAMP1MF;
	if (no_erase)
		r |= RTC_TAMPCR_TAMP1NOERASE;
	else
		r &= ~RTC_TAMPCR_TAMP1NOERASE;
	MMIO32(RTC_TAMPCR) = r | RTC_TAMPCR_TAMP1E;
}

void rtc_disable_tamp1(void)
{
	MMIO32(RTC_TAMPCR) &= ~RTC_TAMPCR_TAMP1E;
}

void rtc_enable_tamp2(enum rtc_tamp_trigger trigger, bool mask, bool no_erase)
{
	int r;

	r = MMIO32(RTC_TAMPCR);
	if (trigger)
		r |= RTC_TAMPCR_TAMP2TRG;
	else
		r &= ~RTC_TAMPCR_TAMP2TRG;
	if (mask)
		r |= RTC_TAMPCR_TAMP2MF;
	else
		r &= ~RTC_TAMPCR_TAMP2MF;
	if (no_erase)
		r |= RTC_TAMPCR_TAMP2NOERASE;
	else
		r &= ~RTC_TAMPCR_TAMP2NOERASE;
	MMIO32(RTC_TAMPCR) = r | RTC_TAMPCR_TAMP2E;
}

void rtc_disable_tamp2(void)
{
	MMIO32(RTC_TAMPCR) &= ~RTC_TAMPCR_TAMP2E;
}

void rtc_enable_tamp3(enum rtc_tamp_trigger trigger, bool mask, bool no_erase)
{
	int r;

	r = MMIO32(RTC_TAMPCR);
	if (trigger)
		r |= RTC_TAMPCR_TAMP3TRG;
	else
		r &= ~RTC_TAMPCR_TAMP3TRG;
	if (mask)
		r |= RTC_TAMPCR_TAMP3MF;
	else
		r &= ~RTC_TAMPCR_TAMP3MF;
	if (no_erase)
		r |= RTC_TAMPCR_TAMP3NOERASE;
	else
		r &= ~RTC_TAMPCR_TAMP3NOERASE;
	MMIO32(RTC_TAMPCR) = r | RTC_TAMPCR_TAMP3E;
}

void rtc_disable_tamp3(void)
{
	MMIO32(RTC_TAMPCR) &= ~RTC_TAMPCR_TAMP3E;
}
