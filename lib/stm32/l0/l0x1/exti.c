/*
 * EXTI functions
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
#include <exti.h>

void exti_set_trigger(int extis, enum exti_trigger type)
{
	switch (type) {
	case EXTI_TRIGGER_NONE:
		MMIO32(EXTI_RTSR) &= ~(extis & EXTI_RTSR_MASK);
		MMIO32(EXTI_FTSR) &= ~(extis & EXTI_FTSR_MASK);
		break;
	case EXTI_RISING:
		MMIO32(EXTI_RTSR) |= extis & EXTI_RTSR_MASK;
		MMIO32(EXTI_FTSR) &= ~(extis & EXTI_FTSR_MASK);
		break;
	case EXTI_FALLING:
		MMIO32(EXTI_RTSR) &= ~(extis & EXTI_RTSR_MASK);
		MMIO32(EXTI_FTSR) |= extis & EXTI_FTSR_MASK;
		break;
	case EXTI_BOTH:
		MMIO32(EXTI_RTSR) |= extis & EXTI_RTSR_MASK;
		MMIO32(EXTI_FTSR) |= extis & EXTI_FTSR_MASK;
		break;
	default:
		break;
	}
}

enum exti_trigger exti_get_trigger(int extis)
{
	int r;
	int f;

	r = MMIO32(EXTI_RTSR) & extis;
	f = MMIO32(EXTI_FTSR) & extis;
	if (r == 0 && f == 0)
		return EXTI_TRIGGER_NONE;
	else if (r == extis && f == 0)
		return EXTI_RISING;
	else if (r == 0 && f == extis)
		return EXTI_FALLING;
	else if (r == extis && f == extis)
		return EXTI_BOTH;
	else
		return EXTI_TRIGGER_UNKNOWN;
}

void exti_enable_interrupt(int extis)
{
	MMIO32(EXTI_IMR) |= extis & EXTI_IMR_MASK;
}

void exti_disable_interrupt(int extis)
{
	MMIO32(EXTI_IMR) &= ~(extis & EXTI_IMR_MASK);
}

int exti_get_interrupt_mask(int extis)
{
	return MMIO32(EXTI_IMR) & extis;
}

int exti_get_interrupt_status(int extis)
{
	return MMIO32(EXTI_PR) & extis;
}

void exti_clear_interrupt(int extis)
{
	int r;

	r = MMIO32(EXTI_PR);
	r &= ~EXTI_PR_MASK;
	MMIO32(EXTI_PR) = r | (extis & EXTI_PR_MASK);
}

void exti_enable_event(int extis)
{
	MMIO32(EXTI_EMR) |= extis & EXTI_EMR_MASK;
}

void exti_disable_event(int extis)
{
	MMIO32(EXTI_EMR) &= ~(extis & EXTI_EMR_MASK);
}

int exti_get_event_mask(int extis)
{
	return MMIO32(EXTI_EMR) & extis;
}

void exti_set_software_interrupt(int extis)
{
	MMIO32(EXTI_SWIER) |= extis & EXTI_SWIER_MASK;
}
