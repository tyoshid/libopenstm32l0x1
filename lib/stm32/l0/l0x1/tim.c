/*
 * TIM functions
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
#include <tim.h>

struct reg_shift {
	int addr;
	int shift;
};

static const int base[] = {
	TIM2_BASE,
	TIM3_BASE,
	TIM21_BASE,
	TIM22_BASE,
	TIM6_BASE,
	TIM7_BASE
};
static const int ccr[] = {
	TIM2_CCR1,
	TIM2_CCR2,
	TIM2_CCR3,
	TIM2_CCR4,
	TIM3_CCR1,
	TIM3_CCR2,
	TIM3_CCR3,
	TIM3_CCR4,
	TIM21_CCR1,
	TIM21_CCR2,
	TIM22_CCR1,
	TIM22_CCR2,
};

void tim_set_prescaler(enum tim tim, int pcount)
{
	MMIO32(TIM_PSC(base[tim])) = (pcount - 1) & 0xffff;
}

void tim_load_prescaler(enum tim tim, int pcount)
{
	MMIO32(TIM_PSC(base[tim])) = (pcount - 1) & 0xffff;
	MMIO32(TIM_EGR(base[tim])) = TIM_EGR_UG;
}

void tim_set_autoreload(enum tim tim, int count)
{
	MMIO32(TIM_ARR(base[tim])) = (count - 1) & 0xffff;
}

void tim_setup_counter(enum tim tim, int pcount, int count)
{
	MMIO32(TIM_ARR(base[tim])) = (count - 1) & 0xffff;
	MMIO32(TIM_PSC(base[tim])) = (pcount - 1) & 0xffff;
	MMIO32(TIM_EGR(base[tim])) = TIM_EGR_UG;
}

void tim_set_counter(enum tim tim, int cnt)
{
	MMIO32(TIM_CNT(base[tim])) = cnt & 0xffff;
}

int tim_get_counter(enum tim tim)
{
	return MMIO32(TIM_CNT(base[tim]));
}

void tim_enable_counter(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) |= TIM_CR1_CEN;
}

void tim_disable_counter(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) &= ~TIM_CR1_CEN;
}

void tim_set_dts_division(enum tim tim, int div)
{
	int i;
	int r;

	for (i = 0; i < 3; i++) {
		if (div == 1 << i)
			break;
	}
	if (i >= 3)
		return;
	r = MMIO32(TIM_CR1(base[tim]));
	r &= ~(TIM_CR1_CKD1 | TIM_CR1_CKD0);
	MMIO32(TIM_CR1(base[tim])) = r | i << 8;
}

void tim_enable_autoreload_preload(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) |= TIM_CR1_ARPE;
}

void tim_disable_autoreload_preload(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) &= ~TIM_CR1_ARPE;
}

void tim_set_center_aligned_mode(enum tim tim,
				 enum tim_center_aligned_mode mode)
{
	int r;

	r = MMIO32(TIM_CR1(base[tim]));
	r &= ~(TIM_CR1_CMS1 | TIM_CR1_CMS0);
	MMIO32(TIM_CR1(base[tim])) = r | mode;
}

void tim_set_downcounter(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) |= TIM_CR1_DIR;
}

void tim_set_upcounter(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) &= ~TIM_CR1_DIR;
}

bool tim_downcounter(enum tim tim)
{
	return MMIO32(TIM_CR1(base[tim])) & TIM_CR1_DIR;
}

void tim_enable_one_pulse_mode(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) |= TIM_CR1_OPM;
}

void tim_disable_one_pulse_mode(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) &= ~TIM_CR1_OPM;
}

void tim_disable_update_interrupt_on_any(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) |= TIM_CR1_URS;
}

void tim_enable_update_interrupt_on_any(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) &= ~TIM_CR1_URS;
}

void tim_disable_update_event(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) |= TIM_CR1_UDIS;
}

void tim_enable_update_event(enum tim tim)
{
	MMIO32(TIM_CR1(base[tim])) &= ~TIM_CR1_UDIS;
}

void tim_enable_ti1_ch123_xor(enum tim tim)
{
	MMIO32(TIM_CR2(base[tim])) |= TIM_CR2_TI1S;
}

void tim_disable_ti1_ch123_xor(enum tim tim)
{
	MMIO32(TIM_CR2(base[tim])) &= ~TIM_CR2_TI1S;
}

void tim_set_master_mode(enum tim tim, enum tim_master_mode mode)
{
	int r;

	r = MMIO32(TIM_CR2(base[tim]));
	r &= ~(TIM_CR2_MMS2 | TIM_CR2_MMS1 | TIM_CR2_MMS0);
	MMIO32(TIM_CR2(base[tim])) = r | mode;
}

void tim_enable_ccx_dma_on_update_event(enum tim tim)
{
	MMIO32(TIM_CR2(base[tim])) |= TIM_CR2_CCDS;
}

void tim_disable_ccx_dma_on_update_event(enum tim tim)
{
	MMIO32(TIM_CR2(base[tim])) &= ~TIM_CR2_CCDS;
}

void tim_set_slave_mode(enum tim tim, int mode)
{
	MMIO32(TIM_SMCR(base[tim])) = mode & 0xfff7;
}

void tim_enable_interrupt(enum tim tim, int interrupt)
{
	MMIO32(TIM_DIER(base[tim])) |= interrupt & (TIM_DIER_TIE |
						    TIM_DIER_CC4IE |
						    TIM_DIER_CC3IE |
						    TIM_DIER_CC2IE |
						    TIM_DIER_CC1IE |
						    TIM_DIER_UIE);
}

void tim_disable_interrupt(enum tim tim, int interrupt)
{
	MMIO32(TIM_DIER(base[tim])) &= ~(interrupt & (TIM_DIER_TIE |
						      TIM_DIER_CC4IE |
						      TIM_DIER_CC3IE |
						      TIM_DIER_CC2IE |
						      TIM_DIER_CC1IE |
						      TIM_DIER_UIE));
}

int tim_get_interrupt_mask(enum tim tim, int interrupt)
{
	return MMIO32(TIM_DIER(base[tim])) & interrupt;
}

int tim_get_interrupt_status(enum tim tim, int interrupt)
{
	return MMIO32(TIM_SR(base[tim])) & interrupt;
}

void tim_clear_interrupt(enum tim tim, int interrupt)
{
	MMIO32(TIM_SR(base[tim])) &= ~interrupt;
}

void tim_enable_dma(enum tim tim, int request)
{
	MMIO32(TIM_DIER(base[tim])) |= request & (TIM_DIER_TDE |
						  TIM_DIER_CC4DE |
						  TIM_DIER_CC3DE |
						  TIM_DIER_CC2DE |
						  TIM_DIER_CC1DE |
						  TIM_DIER_UDE);
}

void tim_disable_dma(enum tim tim, int request)
{
	MMIO32(TIM_DIER(base[tim])) &= ~(request & (TIM_DIER_TDE |
						    TIM_DIER_CC4DE |
						    TIM_DIER_CC3DE |
						    TIM_DIER_CC2DE |
						    TIM_DIER_CC1DE |
						    TIM_DIER_UDE));
}

void tim_generate_event(enum tim tim, int event)
{
	MMIO32(TIM_EGR(base[tim])) |= event & (TIM_EGR_TG |
					       TIM_EGR_CC4G |
					       TIM_EGR_CC3G |
					       TIM_EGR_CC2G |
					       TIM_EGR_CC1G |
					       TIM_EGR_UG);
}

void tim_set_capture_compare_mode(enum tim_cc tim_cc, int mode)
{
	static const struct reg_shift ccmr[] = {
		{TIM2_CCMR1, 0},
		{TIM2_CCMR1, 8},
		{TIM2_CCMR2, 0},
		{TIM2_CCMR2, 8},
		{TIM3_CCMR1, 0},
		{TIM3_CCMR1, 8},
		{TIM3_CCMR2, 0},
		{TIM3_CCMR2, 8},
		{TIM21_CCMR1, 0},
		{TIM21_CCMR1, 8},
		{TIM22_CCMR1, 0},
		{TIM22_CCMR1, 8}
	};
	static const struct reg_shift ccer[] = {
		{TIM2_CCER, 0},
		{TIM2_CCER, 4},
		{TIM2_CCER, 8},
		{TIM2_CCER, 12},
		{TIM3_CCER, 0},
		{TIM3_CCER, 4},
		{TIM3_CCER, 8},
		{TIM3_CCER, 12},
		{TIM21_CCER, 0},
		{TIM21_CCER, 4},
		{TIM22_CCER, 0},
		{TIM22_CCER, 4}
	};
	int r;

	r = MMIO32(ccmr[tim_cc].addr);
	r &= ~(0xff << ccmr[tim_cc].shift);
	MMIO32(ccmr[tim_cc].addr) = r | (mode & 0xff) << ccmr[tim_cc].shift;
	r = MMIO32(ccer[tim_cc].addr);
	r &= ~(0xf << ccer[tim_cc].shift);
	if (ccer[tim_cc].shift <= 8)
		MMIO32(ccer[tim_cc].addr) = r |
			(mode & 0xf00) >> (8 - ccer[tim_cc].shift);
	else
		MMIO32(ccer[tim_cc].addr) = r |
			(mode & 0xf00) << (ccer[tim_cc].shift - 8);
}

void tim_set_capture_compare_value(enum tim_cc tim_cc, int value)
{
	MMIO32(ccr[tim_cc]) = value & 0xffff;
}

int tim_get_capture_compare_value(enum tim_cc tim_cc)
{
	return MMIO32(ccr[tim_cc]);
}

void tim_setup_dma(enum tim tim, int dba, int dbl)
{
	MMIO32(TIM_DCR(base[tim])) = (dbl & 0x1f) << 8 | (dba & 0x1f);
}

void tim_tim2_remap(enum tim_tim2_ti4 tim2_ti4, enum tim_tim2_etr tim2_etr)
{
	MMIO32(TIM2_OR) = tim2_ti4 | tim2_etr;
}

void tim_tim3_remap(int remap)
{
	MMIO32(TIM3_OR) = remap & 0x1f;
}

void tim_tim21_remap(enum tim_tim21_ti2 tim21_ti2,
		     enum tim_tim21_ti1 tim21_ti1,
		     enum tim_tim21_etr tim21_etr)
{
	MMIO32(TIM21_OR) = tim21_ti2 | tim21_ti1 | tim21_etr;
}

void tim_tim22_remap(enum tim_tim22_ti1 tim22_ti1,
		     enum tim_tim22_etr tim22_etr)
{
	MMIO32(TIM22_OR) = tim22_ti1 | tim22_etr;
}
