/*
 * WWDG functions
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

#include <mmio.h>
#include <memorymap.h>
#include <wwdg.h>

void wwdg_set_window(int prescaler, int window)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (prescaler == 1 << i)
			break;
	}
	if (i >= 4)
		return;
	MMIO32(WWDG_CFR) = i << 7 | 0x40 | (window & 0x3f);
}

void wwdg_reload(int count)
{
	MMIO32(WWDG_CR) = WWDG_CR_WDGA | ((0x40 + count - 1) & 0x7f);
}

void wwdg_enable_interrupt(int interrupt)
{
	if (interrupt & WWDG_EARLY_WAKEUP)
		MMIO32(WWDG_CFR) |= WWDG_CFR_EWI;
}

int wwdg_get_interrupt_mask(int interrupt)
{
	int r = 0;

	if (interrupt & WWDG_EARLY_WAKEUP) {
		if (MMIO32(WWDG_CFR) & WWDG_CFR_EWI)
			r |= WWDG_EARLY_WAKEUP;
	}
	return r;
}

int wwdg_get_interrupt_status(int interrupt)
{
	return MMIO32(WWDG_SR) & interrupt;
}

void wwdg_clear_interrupt(int interrupt)
{
	MMIO32(WWDG_SR) &= ~(interrupt & WWDG_SR_EWIF);
}
