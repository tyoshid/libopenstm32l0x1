/*
 * CRC functions
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
#include <crc.h>

void crc_set_mode(int pol, int mode)
{
	MMIO32(CRC_POL) = pol;
	MMIO32(CRC_CR) = mode & (CRC_CR_REV_OUT | CRC_CR_REV_IN1 |
				 CRC_CR_REV_IN0 | CRC_CR_POLYSIZE1 |
				 CRC_CR_POLYSIZE0);
}

int crc_calc(int crc, char *buffer, int len)
{
	int i;

	MMIO32(CRC_INIT) = crc;
	MMIO32(CRC_CR) |= CRC_CR_RESET;
	for (i = 0; i < len; i++)
		MMIO8(CRC_DR) = *buffer++;
	return MMIO32(CRC_DR);
}

int crc_calc16(int crc, short *buffer, int len)
{
	int i;

	MMIO32(CRC_INIT) = crc;
	MMIO32(CRC_CR) |= CRC_CR_RESET;
	for (i = 0; i < len; i++)
		MMIO16(CRC_DR) = *buffer++;
	return MMIO32(CRC_DR);
}

int crc_calc32(int crc, int *buffer, int len)
{
	int i;

	MMIO32(CRC_INIT) = crc;
	MMIO32(CRC_CR) |= CRC_CR_RESET;
	for (i = 0; i < len; i++)
		MMIO32(CRC_DR) = *buffer++;
	return MMIO32(CRC_DR);
}
