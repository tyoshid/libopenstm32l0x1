/*
 * COMP functions
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
#include <comp.h>

void comp_init(enum comp comp, enum comp_input plus, enum comp_input minus,
	       int func)
{
	if (comp == COMP1) {
		MMIO32(COMP1_CSR) = (plus & COMP1_CSR_COMP1WM) |
			(minus & (COMP1_CSR_COMP1INNSEL1 |
				  COMP1_CSR_COMP1INNSEL0)) |
			(func & (COMP1_CSR_COMP1POLARITY | COMP1_CSR_COMP1EN));
	} else if (comp == COMP2) {
		MMIO32(COMP2_CSR) = plus | minus |
			(func & (COMP2_CSR_COMP2POLARITY |
				 COMP2_CSR_COMP2SPEED | COMP2_CSR_COMP2EN));
	}
}

void comp_enable(enum comp comp)
{
	if (comp == COMP1)
		MMIO32(COMP1_CSR) |= COMP1_CSR_COMP1EN;
	else if (comp == COMP2)
		MMIO32(COMP2_CSR) |= COMP2_CSR_COMP2EN;
}

void comp_disable(enum comp comp)
{
	if (comp == COMP1)
		MMIO32(COMP1_CSR) &= ~COMP1_CSR_COMP1EN;
	else if (comp == COMP2)
		MMIO32(COMP2_CSR) &= ~COMP2_CSR_COMP2EN;
}

void comp_lock(enum comp comp)
{
	if (comp == COMP1)
		MMIO32(COMP1_CSR) |= COMP1_CSR_COMP1LOCK;
	else if (comp == COMP2)
		MMIO32(COMP2_CSR) |= COMP2_CSR_COMP2LOCK;
}

int comp_get_status(enum comp comp)
{
	if (comp == COMP1)
		return MMIO32(COMP1_CSR) & COMP1_CSR_COMP1VALUE;
	else if (comp == COMP2)
		return MMIO32(COMP2_CSR) & COMP2_CSR_COMP2VALUE;
	return 0;
}

void comp_remap_lptim1_input(enum comp comp, enum comp_lptim1_remap remap)
{
	int r;
	
	if (comp == COMP1) {
		if (remap == COMP_LPTIM1_IN1)
			MMIO32(COMP1_CSR) |= COMP1_CSR_COMP1LPTIMIN1;
		else
			MMIO32(COMP1_CSR) &= ~COMP1_CSR_COMP1LPTIMIN1;
	} else if (comp == COMP2) {
		r = MMIO32(COMP2_CSR);
		if (remap == COMP_LPTIM1_IN1) {
			r &= ~COMP2_CSR_COMP2LPTIMIN2;
			MMIO32(COMP2_CSR) = r | COMP2_CSR_COMP2LPTIMIN1;
		} else if (remap == COMP_LPTIM1_IN2) {
			r &= ~COMP2_CSR_COMP2LPTIMIN1;
			MMIO32(COMP2_CSR) = r | COMP2_CSR_COMP2LPTIMIN2;
		} else {
			MMIO32(COMP2_CSR) = r & ~(COMP2_CSR_COMP2LPTIMIN1 |
						  COMP2_CSR_COMP2LPTIMIN2);
		}
	}
}

