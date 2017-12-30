/*
 * AES functions
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
#include <aes.h>

void aes_init(enum aes_mode mode, enum aes_chaining_mode chaining,
	      enum aes_data_type type)
{
	int r;
	
	r = MMIO32(AES_CR);
	r &= ~(AES_CR_CHMOD1 | AES_CR_CHMOD0 | AES_CR_MODE1 | AES_CR_MODE0 |
	       AES_CR_DATATYPE1 | AES_CR_DATATYPE0);
	MMIO32(AES_CR) = r | (mode << 3) | (chaining << 5) | (type << 1);
}

void aes_set_mode(enum aes_mode mode)
{
	int r;
	
	r = MMIO32(AES_CR);
	r &= ~(AES_CR_MODE1 | AES_CR_MODE0);
	MMIO32(AES_CR) = r | (mode << 3);
}

void aes_set_chaining_mode(enum aes_chaining_mode chaining)
{
	int r;
	
	r = MMIO32(AES_CR);
	r &= ~(AES_CR_CHMOD1 | AES_CR_CHMOD0);
	MMIO32(AES_CR) = r | (chaining << 5);
}

void aes_set_data_type(enum aes_data_type type)
{
	int r;
	
	r = MMIO32(AES_CR);
	r &= ~(AES_CR_DATATYPE1 | AES_CR_DATATYPE0);
	MMIO32(AES_CR) = r | (type << 1);
}

void aes_set_key(int *key)
{
	int i;
	
	for (i = 0; i < 4; i++)
		MMIO32(AES_KEY(i)) = *key++;
}

void aes_get_key(int *key)
{
	int i;
	
	for (i = 0; i < 4; i++)
		*key++ = MMIO32(AES_KEY(i));
}

void aes_set_init_vector(int *vec)
{
	int i;
	
	for (i = 0; i < 4; i++)
		MMIO32(AES_IVR(i)) = *vec++;
}

void aes_enable(void)
{
	MMIO32(AES_CR) |= AES_CR_EN;
}

void aes_disable(void)
{
	MMIO32(AES_CR) &= ~AES_CR_EN;
}

void aes_set_data(int data)
{
	MMIO32(AES_DINR) = data;
}

int aes_get_data(void)
{
	return MMIO32(AES_DOUTR);
}

void aes_enable_dma(int dma)
{
	MMIO32(AES_CR) |= dma & (AES_CR_DMAOUTEN | AES_CR_DMAINEN);
}

void aes_disable_dma(int dma)
{
	MMIO32(AES_CR) &= ~(dma & (AES_CR_DMAOUTEN | AES_CR_DMAINEN));
}

void aes_enable_interrupt(int interrupt)
{
	int r;

	r = MMIO32(AES_CR);
	if (interrupt & AES_COMPLETE)
		r |= AES_CR_CCFIE;
	if (interrupt & (AES_WRERR | AES_RDERR))
		r |= AES_CR_ERRIE;
	MMIO32(AES_CR) = r;
}

void aes_disable_interrupt(int interrupt)
{
	int r;

	r = MMIO32(AES_CR);
	if (interrupt & AES_COMPLETE)
		r &= ~AES_CR_CCFIE;
	if (interrupt & (AES_WRERR | AES_RDERR))
		r &= ~AES_CR_ERRIE;
	MMIO32(AES_CR) = r;
}

int aes_get_interrupt_mask(int interrupt)
{
	int r;
	int m;

	m = 0;
	r = MMIO32(AES_CR);
	if (r & AES_CR_CCFIE)
		m |= AES_COMPLETE;
	if (r & AES_CR_ERRIE)
		m |= (AES_WRERR | AES_RDERR);
	return m & interrupt;
}

int aes_get_interrupt_status(int interrupt)
{
	return MMIO32(AES_SR) & interrupt;
}

void aes_clear_interrupt(int interrupt)
{
	int r;

	r = MMIO32(AES_CR);
	if (interrupt & AES_COMPLETE)
		r |= AES_CR_CCFC;
	if (interrupt & (AES_WRERR | AES_RDERR))
		r |= AES_CR_ERRC;
	MMIO32(AES_CR) = r;
}
