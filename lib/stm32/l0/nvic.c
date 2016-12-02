/*
 * NVIC functions
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
#include <ppb.h>
#include <nvic.h>

int nvic_get_enabled_irq(int interrupt)
{
	return MMIO32(NVIC_ISER) & interrupt;
}

void nvic_enable_irq(int interrupt)
{
	MMIO32(NVIC_ISER) = interrupt;
}

void nvic_disable_irq(int interrupt)
{
	MMIO32(NVIC_ICER) = interrupt;
}

int nvic_get_pending_irq(int interrupt)
{
	return MMIO32(NVIC_ISPR) & interrupt;
}

void nvic_set_pending_irq(int interrupt)
{
	MMIO32(NVIC_ISPR) = interrupt;
}

void nvic_clear_pending_irq(int interrupt)
{
	MMIO32(NVIC_ICPR) = interrupt;
}

void nvic_set_priority(int irqn, int priority)
{
	int r;

	if (irqn < 0 || irqn > 31)
		return;
	r = MMIO32(NVIC_IPR(irqn / 4));
	r &= ~(0xff << (irqn % 4 * 8));
	MMIO32(NVIC_IPR(irqn / 4)) = r | priority << (irqn % 4 * 8);
}

int nvic_get_priority(int irqn)
{

	int r;

	if (irqn < 0 || irqn > 31)
		return 0;
	r = MMIO32(NVIC_IPR(irqn / 4));
	return (r >> (irqn % 4 * 8)) & 0xff;
}
