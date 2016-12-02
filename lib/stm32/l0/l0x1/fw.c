/*
 * FW functions
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
#include <fw.h>

void fw_init(int cssa, int csl, int nvdssa, int nvdsl, int vdssa, int vdsl,
	     int option)
{
	MMIO32(FW_CSSA) = cssa & 0x00ffff00;
	MMIO32(FW_CSL) = csl & 0x003fff00;
	MMIO32(FW_NVDSSA) = nvdssa & 0x00ffff00;
	MMIO32(FW_NVDSL) = nvdsl & 0x003fff00;
	MMIO32(FW_VDSSA) = vdssa & 0x0000ffc0;
	MMIO32(FW_VDSL) = vdsl & 0x000ffc0;
	MMIO32(FW_CR) = option & (FW_CR_VDE | FW_CR_VDS | FW_CR_FPA);
}

void fw_enable_fpa(void)
{
	MMIO32(FW_CR) |= FW_CR_FPA;
}

void fw_disable_fpa(void)
{
	MMIO32(FW_CR) &= ~FW_CR_FPA;
}
