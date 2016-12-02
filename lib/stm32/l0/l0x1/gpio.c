/*
 * GPIO functions
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
#include <gpio.h>

static const int base_addr[] = {
	GPIOA_BASE,
	GPIOB_BASE,
	GPIOC_BASE,
	GPIOD_BASE,
	GPIOE_BASE,
	0,
	0,
	GPIOH_BASE
};

#define BASE(port)			base_addr[GPIO_PORT(port) >> 16]

void gpio_set_mode(enum gpio_mode mode, int portbits)
{
	int base;
	int m;
	int i;
	int mask = 0;
	int value = 0;
	int r;

	base = BASE(portbits);
	switch (mode) {
	case GPIO_OUTPUT:
		m = GPIO_MODER_OUTPUT;
		break;
	case GPIO_INPUT:
		m = GPIO_MODER_INPUT;
		break;
	case GPIO_ANALOG:
		m = GPIO_MODER_ANALOG;
		break;
	default:
		m = GPIO_MODER_ALTFN;
		break;
	}
	for (i = 0; i < 16; i++) {
		if (portbits & (1 << i)) {
			mask |= 3 << (i * 2);
			value |= m << (i * 2);
		}
	}
	if (mask) {
		r = MMIO32(GPIO_MODER(base));
		MMIO32(GPIO_MODER(base)) = (r & ~mask) | value;
	}
}

void gpio_config(enum gpio_mode mode, int options, int portbits)
{
	int base;
	int m;
	int ot;
	int os;
	int pu;
	int i;
	int moder_mask = 0;
	int moder_value = 0;
	int otyper_mask = 0;
	int otyper_value = 0;
	int ospeedr_mask = 0;
	int ospeedr_value = 0;
	int pupdr_mask = 0;
	int pupdr_value = 0;
	int afrl_mask = 0;
	int afrl_value = 0;
	int afrh_mask = 0;
	int afrh_value = 0;
	int r;

	base = BASE(portbits);
	switch (mode) {
	case GPIO_OUTPUT:
		m = GPIO_MODER_OUTPUT;
		break;
	case GPIO_INPUT:
		m = GPIO_MODER_INPUT;
		break;
	case GPIO_ANALOG:
		m = GPIO_MODER_ANALOG;
		break;
	default:
		m = GPIO_MODER_ALTFN;
		break;
	}
	ot = options & 1;
	os = options >> 1 & 3;
	pu = options >> 3 & 3;
	for (i = 0; i < 16; i++) {
		if (!(portbits & (1 << i)))
			continue;
		moder_mask |= 3 << (i * 2);
		moder_value |= m << (i * 2);
		if (mode != GPIO_INPUT && mode != GPIO_ANALOG) {
			otyper_mask |= 1 << i;
			otyper_value |= ot << i;
			ospeedr_mask |= 3 << (i * 2);
			ospeedr_value |= os << (i * 2);
		}
		if (mode != GPIO_ANALOG) {
			pupdr_mask |= 3 << (i * 2);
			pupdr_value |= pu << (i * 2);
		}
		if (mode <= GPIO_AF7) {
			if (i < 8) {
				afrl_mask |= 0xf << (i * 4);
				afrl_value |= mode << (i * 4);
			} else {
				afrh_mask |= 0xf << ((i - 8) * 4);
				afrh_value |= mode << ((i - 8) * 4);
			}
		}
	}
	if (afrl_mask) {
		r = MMIO32(GPIO_AFRL(base));
		MMIO32(GPIO_AFRL(base)) = (r & ~afrl_mask) | afrl_value;
	}
	if (afrh_mask) {
		r = MMIO32(GPIO_AFRH(base));
		MMIO32(GPIO_AFRH(base)) = (r & ~afrh_mask) | afrh_value;
	}
	if (otyper_mask) {
		r = MMIO32(GPIO_OTYPER(base));
		MMIO32(GPIO_OTYPER(base)) = (r & ~otyper_mask) | otyper_value;
	}
	if (ospeedr_mask) {
		r = MMIO32(GPIO_OSPEEDR(base));
		MMIO32(GPIO_OSPEEDR(base)) = (r & ~ospeedr_mask) |
			ospeedr_value;
	}
	if (pupdr_mask) {
		r = MMIO32(GPIO_PUPDR(base));
		MMIO32(GPIO_PUPDR(base)) = (r & ~pupdr_mask) | pupdr_value;
	}
	if (moder_mask) {
		r = MMIO32(GPIO_MODER(base));
		MMIO32(GPIO_MODER(base)) = (r & ~moder_mask) | moder_value;
	}
}

void gpio_set(int portbits)
{
	MMIO32(GPIO_BSRR(BASE(portbits))) = GPIO_BITS(portbits);
}

void gpio_clear(int portbits)
{
	MMIO32(GPIO_BRR(BASE(portbits))) = GPIO_BITS(portbits);
}

int gpio_get(int portbits)
{
	return MMIO32(GPIO_IDR(BASE(portbits))) & portbits;
}

void gpio_toggle(int portbits)
{
	MMIO32(GPIO_ODR(BASE(portbits))) ^= (GPIO_BITS(portbits));
}

int gpio_read_port(int port)
{
	return MMIO32(GPIO_IDR(BASE(port)));
}

void gpio_write_port(int port, int data)
{
	MMIO32(GPIO_ODR(BASE(port))) = data;
}

int gpio_lock_config(int portbits)
{
	int base;
	int bits;

	base = BASE(portbits);
	bits = GPIO_BITS(portbits);
	MMIO32(GPIO_LCKR(base)) = GPIO_LCKK | bits;
	MMIO32(GPIO_LCKR(base)) = bits;
	MMIO32(GPIO_LCKR(base)) = GPIO_LCKK | bits;
	MMIO32(GPIO_LCKR(base));
	return MMIO32(GPIO_LCKR(base)) & GPIO_LCKK;
}
