/*
 * MPU functions
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
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
#include <mpu.h>

int mpu_get_type(void)
{
	return MMIO32(MPU_TYPE);
}

void mpu_enable_default_memory_map(void)
{
	MMIO32(MPU_CTRL) |= MPU_CTRL_PRIVDEFENA;
}

void mpu_disable_default_memory_map(void)
{
	MMIO32(MPU_CTRL) &= ~MPU_CTRL_PRIVDEFENA;
}

void mpu_enable_hardfault_nmi(void)
{
	MMIO32(MPU_CTRL) |= MPU_CTRL_HFNMIENA;
}

void mpu_disable_hardfault_nmi(void)
{
	MMIO32(MPU_CTRL) &= ~MPU_CTRL_HFNMIENA;
}

void mpu_enable(void)
{
	MMIO32(MPU_CTRL) |= MPU_CTRL_ENABLE;
}

void mpu_disable(void)
{
	MMIO32(MPU_CTRL) &= ~MPU_CTRL_ENABLE;
}

void mpu_set_region(int region, int addr, int n, int attr)
{
	if (n < 8 || n > 32)
		return;
	MMIO32(MPU_RNR) = region & 0xff;
	MMIO32(MPU_RBAR) = addr & ~0x1f;
	MMIO32(MPU_RASR) = (n - 1) << 1 |
		(attr & (MPU_RASR_XN | MPU_RASR_AP2 | MPU_RASR_AP1 |
			 MPU_RASR_AP0 | MPU_RASR_S | MPU_RASR_C | MPU_RASR_B |
			 MPU_RASR_SRD7 | MPU_RASR_SRD6 | MPU_RASR_SRD5 |
			 MPU_RASR_SRD4 | MPU_RASR_SRD3 | MPU_RASR_SRD2 |
			 MPU_RASR_SRD1 | MPU_RASR_SRD0 | MPU_RASR_ENABLE));
}

void mpu_enable_region(int region)
{
	MMIO32(MPU_RNR) = region & 0xff;
	MMIO32(MPU_RASR) |= MPU_RASR_ENABLE;
}

void mpu_disable_region(int region)
{
	MMIO32(MPU_RNR) = region & 0xff;
	MMIO32(MPU_RASR) &= ~MPU_RASR_ENABLE;
}
