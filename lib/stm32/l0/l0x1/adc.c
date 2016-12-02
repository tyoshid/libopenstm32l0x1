/*
 * ADC functions
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
#include <adc.h>

int adc_calibration(void)
{
	MMIO32(ADC_CR) |= ADC_CR_ADCAL;
	while (MMIO32(ADC_CR) & ADC_CR_ADCAL)
		;
	return MMIO32(ADC_DR) & 0x7f;
}

void adc_set_calfact(int calfact)
{
	MMIO32(ADC_CALFACT) = calfact & 0x7f;
}

void adc_set_clock(enum adc_clock clock, int presc, bool low_freq)
{
	int i;
	int r;
	
	if (presc == 1) {
		i = 0;
	} else if (presc <= 12) {
		for (i = 1; i < 7; i++) {
			if (presc == i * 2)
				break;
		}
		if (i >= 7) {
			if (clock == ADC_ADCCLK)
				return;
			else
				i = 0;
		}
	} else {
		for (i = 7; i < 12; i++) {
			if (presc == 1 << (i - 3))
				break;
		}
		if (i >= 12) {
			if (clock == ADC_ADCCLK)
				return;
			else
				i = 0;
		}
	}
	r = MMIO32(ADC_CFGR2);
	r &= ~(ADC_CFGR2_CKMODE1 | ADC_CFGR2_CKMODE0);
	MMIO32(ADC_CFGR2) = r | clock;
	r = MMIO32(ADC_CCR);
	if (low_freq)
		r |= ADC_CCR_LFMEN;
	else
		r &= ~ADC_CCR_LFMEN;
	r &= ~(ADC_CCR_PRESC3 | ADC_CCR_PRESC2 | ADC_CCR_PRESC1 |
	       ADC_CCR_PRESC0);
	MMIO32(ADC_CCR) = r | i << 18;
}

void adc_set_resolution(enum adc_resolution res)
{
	int r;

	r = MMIO32(ADC_CFGR1);
	r &= ~(ADC_CFGR1_RES1 | ADC_CFGR1_RES0);
	MMIO32(ADC_CFGR1) = r | res;
}

void adc_enable(void)
{
	if (MMIO32(ADC_ISR) & ADC_ISR_ADRDY)
		MMIO32(ADC_ISR) = ADC_ISR_ADRDY;
	MMIO32(ADC_CR) |= ADC_CR_ADEN;
	while (!(MMIO32(ADC_ISR) & ADC_ISR_ADRDY))
		;
	MMIO32(ADC_ISR) = ADC_ISR_ADRDY;
}

void adc_disable(void)
{
	if (MMIO32(ADC_CR) & ADC_CR_ADSTART) {
		MMIO32(ADC_CR) |= ADC_CR_ADSTP;
		while (MMIO32(ADC_CR) & ADC_CR_ADSTP)
			;
	}
	MMIO32(ADC_CR) |= ADC_CR_ADDIS;
	while (MMIO32(ADC_CR) & ADC_CR_ADEN)
		;
}

void adc_enable_voltage_regulator(void)
{
	MMIO32(ADC_CR) = ADC_CR_ADVREGEN;
}

void adc_disable_voltage_regulator(void)
{
	MMIO32(ADC_CR) = 0;
}

void adc_set_channel(int channel, bool backward)
{
	MMIO32(ADC_CHSELR) = channel & 0x7ffff;
	if (backward)
		MMIO32(ADC_CFGR1) |= ADC_CFGR1_SCANDIR;
	else
		MMIO32(ADC_CFGR1) &= ~ADC_CFGR1_SCANDIR;
}

void adc_set_sampling_time(enum adc_sampling_time smp)
{
	MMIO32(ADC_SMPR) = smp;
}

void adc_set_conversion_mode(enum adc_conversion_mode mode)
{
	int r;

	switch (mode) {
	case ADC_SINGLE:
		MMIO32(ADC_CFGR1) &= ~(ADC_CFGR1_CONT | ADC_CFGR1_DISCEN);
		break;
	case ADC_CONTINUOUS:
		r = MMIO32(ADC_CFGR1);
		r &= ~ADC_CFGR1_DISCEN;
		MMIO32(ADC_CFGR1) = r | ADC_CFGR1_CONT;
		break;
	case ADC_DISCONTINUOUS:
		r = MMIO32(ADC_CFGR1);
		r &= ~ADC_CFGR1_CONT;
		MMIO32(ADC_CFGR1) = r | ADC_CFGR1_DISCEN;
		break;
	default:
		break;
	}
}

void adc_start(void)
{
	MMIO32(ADC_CR) |= ADC_CR_ADSTART;
}

void adc_stop(void)
{
	MMIO32(ADC_CR) |= ADC_CR_ADSTP;
	while (MMIO32(ADC_CR) & ADC_CR_ADSTP)
		;
}

void adc_set_trigger(enum adc_trigger trigger, enum adc_trigger_source source)
{
	int r;

	r = MMIO32(ADC_CFGR1);
	r &= ~(ADC_CFGR1_EXTEN1 | ADC_CFGR1_EXTEN0 |
	       ADC_CFGR1_EXTSEL2 | ADC_CFGR1_EXTSEL1 | ADC_CFGR1_EXTSEL0);
	MMIO32(ADC_CFGR1) = r | trigger | source;
}

int adc_get_data(void)
{
	return MMIO32(ADC_DR) & 0xffff;
}

void adc_set_alignment(bool left_align)
{
	if (left_align)
		MMIO32(ADC_CFGR1) |= ADC_CFGR1_ALIGN;
	else
		MMIO32(ADC_CFGR1) &= ~ADC_CFGR1_ALIGN;
}

void adc_set_overrun_mode(bool overwrite)
{
	if (overwrite)
		MMIO32(ADC_CFGR1) |= ADC_CFGR1_OVRMOD;
	else
		MMIO32(ADC_CFGR1) &= ~ADC_CFGR1_OVRMOD;
}

void adc_enable_dma(bool circular)
{
	int r;

	r = MMIO32(ADC_CFGR1);
	if (circular)
		r |= ADC_CFGR1_DMACFG;
	else
		r &= ~ADC_CFGR1_DMACFG;
	MMIO32(ADC_CFGR1) = r | ADC_CFGR1_DMAEN;
}

void adc_disable_dma(void)
{
	MMIO32(ADC_CFGR1) &= ~ADC_CFGR1_DMAEN;
}

void adc_enable_wait_mode(void)
{
	MMIO32(ADC_CFGR1) |= ADC_CFGR1_WAIT;
}

void adc_disable_wait_mode(void)
{
	MMIO32(ADC_CFGR1) &= ~ADC_CFGR1_WAIT;
}

void adc_enable_auto_off(void)
{
	MMIO32(ADC_CFGR1) |= ADC_CFGR1_AUTOFF;
}

void adc_disable_auto_off(void)
{
	MMIO32(ADC_CFGR1) &= ~ADC_CFGR1_AUTOFF;
}

void adc_init(int channel, enum adc_sampling_time smp,
	      enum adc_conversion_mode mode,
	      enum adc_trigger trigger, enum adc_trigger_source source,
	      int function)
{
	int r;

	r = MMIO32(ADC_CFGR1);
	r &= ~0x1ffff;
	MMIO32(ADC_CHSELR) = channel & 0x7ffff;
	MMIO32(ADC_SMPR) = smp;
	switch (mode) {
	case ADC_CONTINUOUS:
		r |= ADC_CFGR1_CONT;
		break;
	case ADC_DISCONTINUOUS:
		r |= ADC_CFGR1_DISCEN;
		break;
	case ADC_SINGLE:
	default:
		break;
	}
	r |= trigger | source;
	MMIO32(ADC_CFGR1) = r | (function & (ADC_CFGR1_AUTOFF |
					     ADC_CFGR1_WAIT |
					     ADC_CFGR1_OVRMOD |
					     ADC_CFGR1_ALIGN |
					     ADC_CFGR1_SCANDIR |
					     ADC_CFGR1_DMACFG |
					     ADC_CFGR1_DMAEN));
}

void adc_init_analog_window_watchdog(int channel, int ht, int lt)
{
	int n;
	int i;
	int awdch;
	int r;

	n = 0;
	for (i = 0; i < 19; i++) {
		if (channel & 1 << i) {
			awdch = i;
			n++;
		}
	}
	if (n == 0) {
		MMIO32(ADC_CFGR1) &= ~ADC_CFGR1_AWDEN;
	} else if (n == 1) {
		MMIO32(ADC_TR) = (ht & 0xfff) << 16 | (lt & 0xfff);
		MMIO32(ADC_CHSELR) |= channel & 0x7ffff;
		r = MMIO32(ADC_CFGR1);
		r &= ~(ADC_CFGR1_AWDCH4 | ADC_CFGR1_AWDCH3 |
		       ADC_CFGR1_AWDCH2 | ADC_CFGR1_AWDCH1 |
		       ADC_CFGR1_AWDCH0);
		MMIO32(ADC_CFGR1) = r | awdch << 26 | ADC_CFGR1_AWDSGL |
			ADC_CFGR1_AWDEN;
	} else {
		MMIO32(ADC_TR) = (ht & 0xfff) << 16 | (lt & 0xfff);
		MMIO32(ADC_CHSELR) = channel & 0x7ffff;
		r = MMIO32(ADC_CFGR1);
		r &= ~ADC_CFGR1_AWDSGL;
		MMIO32(ADC_CFGR1) = r | ADC_CFGR1_AWDEN;
	}
}

void adc_enable_oversampler(int n, bool trigger)
{
	int i;
	int r;
	
	for (i = 0; i < 8; i++) {
		if (n == 1 << (i + 1))
			break;
	}
	if (i >= 8)
		return;
	r = MMIO32(ADC_CFGR2);
	r &= ~(ADC_CFGR2_OVSS3 | ADC_CFGR2_OVSS2 | ADC_CFGR2_OVSS1 |
	       ADC_CFGR2_OVSS0 | ADC_CFGR2_OVSR2 | ADC_CFGR2_OVSR1 |
	       ADC_CFGR2_OVSR0);
	if (trigger)
		r |= ADC_CFGR2_TOVS;
	else
		r &= ~ADC_CFGR2_TOVS;
	MMIO32(ADC_CFGR2) = r | ((i + 1) << 5) | (i << 2) | ADC_CFGR2_OVSE;
}

void adc_disable_oversampler(void)
{
	MMIO32(ADC_CFGR2) &= ~ADC_CFGR2_OVSE;
}

void adc_set_oversampling_shift(int bit)
{
	int r;
	
	if (bit < 0 || bit > 8)
		return;
	r = MMIO32(ADC_CFGR2);
	r &= ~(ADC_CFGR2_OVSS3 | ADC_CFGR2_OVSS2 | ADC_CFGR2_OVSS1 |
	       ADC_CFGR2_OVSS0);
	MMIO32(ADC_CFGR2) = r | bit << 5;
}

void adc_enable_temperature_sensor(void)
{
	MMIO32(ADC_CCR) |= ADC_CCR_TSEN;
}

void adc_disable_temperature_sensor(void)
{
	MMIO32(ADC_CCR) &= ~ADC_CCR_TSEN;
}

void adc_enable_vrefint(void)
{
	MMIO32(ADC_CCR) |= ADC_CCR_VREFEN;
}

void adc_disable_vrefint(void)
{
	MMIO32(ADC_CCR) &= ~ADC_CCR_VREFEN;
}

void adc_enable_interrupt(int interrupt)
{
	MMIO32(ADC_IER) |= interrupt & (ADC_IER_EOCALIE | ADC_IER_AWDIE |
					ADC_IER_OVRIE | ADC_IER_EOSEQIE |
					ADC_IER_EOCIE | ADC_IER_EOSMPIE |
					ADC_IER_ADRDYIE);
}

void adc_disable_interrupt(int interrupt)
{
	MMIO32(ADC_IER) &= ~(interrupt & (ADC_IER_EOCALIE | ADC_IER_AWDIE |
					  ADC_IER_OVRIE | ADC_IER_EOSEQIE |
					  ADC_IER_EOCIE | ADC_IER_EOSMPIE |
					  ADC_IER_ADRDYIE));
}

int adc_get_interrupt_mask(int interrupt)
{
	return MMIO32(ADC_IER) & interrupt;
}

int adc_get_interrupt_status(int interrupt)
{
	return MMIO32(ADC_ISR) & interrupt;
}

void adc_clear_interrupt(int interrupt)
{
	MMIO32(ADC_ISR) = interrupt & (ADC_ISR_EOCAL | ADC_ISR_AWD |
				       ADC_ISR_OVR | ADC_ISR_EOSEQ |
				       ADC_ISR_EOC | ADC_ISR_EOSMP |
				       ADC_ISR_ADRDY);
}
