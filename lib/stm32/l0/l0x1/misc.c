/*
 * Miscellaneous functions
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
#include <misc.h>

int misc_get_flash_size(void)
{
	return MMIO16(MISC_F_SIZE);
}

void misc_get_unique_id(int *u_id)
{
	*u_id++ = MMIO32(MISC_U_ID0);
	*u_id++ = MMIO32(MISC_U_ID1);
	*u_id = MMIO32(MISC_U_ID2);
}

int misc_get_vrefint_cal(void)
{
	return MMIO16(MISC_VREFINT_CAL);
}

int misc_get_ts_cal1(void)
{
	return MMIO16(MISC_TS_CAL1);
}

int misc_get_ts_cal2(void)
{
	return MMIO16(MISC_TS_CAL2);
}
