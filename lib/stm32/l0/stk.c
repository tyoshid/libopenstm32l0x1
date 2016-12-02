/*
 * STK functions
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
#include <ppb.h>
#include <stk.h>

void stk_init(int count, int control)
{
	MMIO32(STK_RVR) = (count - 1) & 0xffffff;
	MMIO32(STK_CVR) = 0;
	MMIO32(STK_CSR) = control & (STK_CSR_CLKSOURCE | STK_CSR_TICKINT |
				     STK_CSR_ENABLE);
}

void stk_set_reload(int count)
{
	MMIO32(STK_RVR) = (count - 1) & 0xffffff;
}

int stk_get_counter(void)
{
	return MMIO32(STK_CVR);
}

void stk_enable_interrupt(void)
{
	MMIO32(STK_CSR) |= STK_CSR_TICKINT;
}

void stk_disable_interrupt(void)
{
	MMIO32(STK_CSR) &= ~STK_CSR_TICKINT;
}

void stk_enable_counter(void)
{
	MMIO32(STK_CSR) |= STK_CSR_ENABLE;
}

void stk_disable_counter(void)
{
	MMIO32(STK_CSR) &= ~STK_CSR_ENABLE;
}

bool stk_countflag(void)
{
	return MMIO32(STK_CSR) & STK_CSR_COUNTFLAG;
}

int stk_get_calib(void)
{
	return MMIO32(STK_CALIB);
}
