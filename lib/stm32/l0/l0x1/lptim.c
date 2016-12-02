/*
 * LPTIM functions
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
#include <lptim.h>

static const int base[] = {
	LPTIM1_BASE
};

void lptim_enable_interrupt(enum lptim lptim, int interrupt)
{
	MMIO32(LPTIM_IER(base[lptim])) |= interrupt & (LPTIM_IER_DOWNIE |
						       LPTIM_IER_UPIE |
						       LPTIM_IER_ARROKIE |
						       LPTIM_IER_CMPOKIE |
						       LPTIM_IER_EXTTRIGIE |
						       LPTIM_IER_ARRMIE |
						       LPTIM_IER_CMPMIE);
}

void lptim_disable_interrupt(enum lptim lptim, int interrupt)
{
	MMIO32(LPTIM_IER(base[lptim])) &= ~(interrupt & (LPTIM_IER_DOWNIE |
							 LPTIM_IER_UPIE |
							 LPTIM_IER_ARROKIE |
							 LPTIM_IER_CMPOKIE |
							 LPTIM_IER_EXTTRIGIE |
							 LPTIM_IER_ARRMIE |
							 LPTIM_IER_CMPMIE));
}

int lptim_get_interrupt_mask(enum lptim lptim, int interrupt)
{
	return MMIO32(LPTIM_IER(base[lptim])) & interrupt;
}

int lptim_get_interrupt_status(enum lptim lptim, int interrupt)
{
	return MMIO32(LPTIM_ISR(base[lptim])) & interrupt;
}

void lptim_clear_interrupt(enum lptim lptim, int interrupt)
{
	MMIO32(LPTIM_ICR(base[lptim])) = interrupt & (LPTIM_ICR_DOWNCF |
						      LPTIM_ICR_UPCF |
						      LPTIM_ICR_ARROKCF |
						      LPTIM_ICR_CMPOKCF |
						      LPTIM_ICR_EXTTRIGCF |
						      LPTIM_ICR_ARRMCF |
						      LPTIM_ICR_CMPMCF);
}

void lptim_enable_external_clock(enum lptim lptim, enum lptim_pol pol,
				 enum lptim_flt flt)
{
	int r;

	r = MMIO32(LPTIM_CFGR(base[lptim]));
	r &= ~(LPTIM_CFGR_CKFLT1 | LPTIM_CFGR_CKFLT0 | LPTIM_CFGR_CKPOL1 |
	       LPTIM_CFGR_CKPOL0);
	MMIO32(LPTIM_CFGR(base[lptim])) = r | flt << 3 | pol << 1 |
		LPTIM_CFGR_CKSEL;
}

void lptim_disable_external_clock(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) &= ~LPTIM_CFGR_CKSEL;
}

void lptim_enable_external_event_count(enum lptim lptim, enum lptim_pol pol,
				       enum lptim_flt flt)
{
	int r;

	r = MMIO32(LPTIM_CFGR(base[lptim]));
	r &= ~(LPTIM_CFGR_CKFLT1 | LPTIM_CFGR_CKFLT0 | LPTIM_CFGR_CKPOL1 |
	       LPTIM_CFGR_CKPOL0);
	MMIO32(LPTIM_CFGR(base[lptim])) = r | LPTIM_CFGR_COUNTMODE | flt << 3 |
		pol << 1;
}

void lptim_disable_external_event_count(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) &= ~LPTIM_CFGR_COUNTMODE;
}

void lptim_set_prescaler(enum lptim lptim, int presc)
{
	int i;
	int r;

	for (i = 0; i < 8; i++) {
		if (presc == 1 << i)
			break;
	}
	if (i >= 8)
		return;
	r = MMIO32(LPTIM_CFGR(base[lptim]));
	r &= ~(LPTIM_CFGR_PRESC2 | LPTIM_CFGR_PRESC1 | LPTIM_CFGR_PRESC0);
	MMIO32(LPTIM_CFGR(base[lptim])) = r | i << 9;
}

void lptim_enable_external_trigger(enum lptim lptim, enum lptim_trig src,
				   enum lptim_pol pol, enum lptim_flt flt)
{
	int r;

	r = MMIO32(LPTIM_CFGR(base[lptim]));
	r &= ~(LPTIM_CFGR_TRIGEN1 | LPTIM_CFGR_TRIGEN0 |
	       LPTIM_CFGR_TRIGSEL2 | LPTIM_CFGR_TRIGSEL1 |
	       LPTIM_CFGR_TRIGSEL0 |
	       LPTIM_CFGR_TRGFLT1 | LPTIM_CFGR_TRGFLT0);
	MMIO32(LPTIM_CFGR(base[lptim])) = r | (pol + 1) << 17 | src | flt << 6;
}

void lptim_disable_external_trigger(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) &= ~(LPTIM_CFGR_TRIGEN1 |
					     LPTIM_CFGR_TRIGEN0);
}

void lptim_enable_timeout(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) |= LPTIM_CFGR_TIMEOUT;
}

void lptim_disable_timeout(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) &= ~LPTIM_CFGR_TIMEOUT;
}

void lptim_set_waveform(enum lptim lptim, bool set_once, bool pol)
{
	int r;

	r = MMIO32(LPTIM_CFGR(base[lptim]));
	if (set_once)
		r |= LPTIM_CFGR_WAVE;
	else
		r &= ~LPTIM_CFGR_WAVE;
	if (pol)
		r |= LPTIM_CFGR_WAVPOL;
	else
		r &= ~LPTIM_CFGR_WAVPOL;
	MMIO32(LPTIM_CFGR(base[lptim])) = r;
}

void lptim_enable_preload(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) |= LPTIM_CFGR_PRELOAD;
}

void lptim_disable_preload(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) &= ~LPTIM_CFGR_PRELOAD;
}

void lptim_enable_encoder_mode(enum lptim lptim, enum lptim_pol pol,
			       enum lptim_flt flt)
{
	int r;

	r = MMIO32(LPTIM_CFGR(base[lptim]));
	r &= ~(LPTIM_CFGR_CKFLT1 | LPTIM_CFGR_CKFLT0 | LPTIM_CFGR_CKPOL1 |
	       LPTIM_CFGR_CKPOL0);
	MMIO32(LPTIM_CFGR(base[lptim])) = r | LPTIM_CFGR_ENC | flt << 3 |
		pol << 1;
}

void lptim_disable_encoder_mode(enum lptim lptim)
{
	MMIO32(LPTIM_CFGR(base[lptim])) &= ~LPTIM_CFGR_ENC;
}

void lptim_enable_timer(enum lptim lptim)
{
	MMIO32(LPTIM_CR(base[lptim])) |= LPTIM_CR_ENABLE;
}

void lptim_disable_timer(enum lptim lptim)
{
	MMIO32(LPTIM_CR(base[lptim])) &= ~LPTIM_CR_ENABLE;
}

void lptim_start_continuous(enum lptim lptim)
{
	MMIO32(LPTIM_CR(base[lptim])) |= LPTIM_CR_CNTSTRT;
}

void lptim_start_single(enum lptim lptim)
{
	MMIO32(LPTIM_CR(base[lptim])) |= LPTIM_CR_SNGSTRT;
}

void lptim_set_compare(enum lptim lptim, int cmp)
{
	MMIO32(LPTIM_CMP(base[lptim])) = cmp & 0xffff;
}

void lptim_set_autoreload(enum lptim lptim, int count)
{
	MMIO32(LPTIM_ARR(base[lptim])) = (count - 1) & 0xffff;
}

int lptim_get_counter(enum lptim lptim)
{
	return MMIO32(LPTIM_CNT(base[lptim]));
}
