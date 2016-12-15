/*
 * SYSCFG functions
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
#include <syscfg.h>

enum syscfg_mem syscfg_get_boot_mode(void)
{
	return (MMIO32(SYSCFG_CFGR1) & (SYSCFG_CFGR1_BOOT_MODE1 |
					SYSCFG_CFGR1_BOOT_MODE0)) >> 8;
}

enum syscfg_mem syscfg_get_memory_mapping(void)
{
	return (MMIO32(SYSCFG_CFGR1) & (SYSCFG_CFGR1_MEM_MODE1 |
					SYSCFG_CFGR1_MEM_MODE0));
}

void syscfg_set_memory_mapping(enum syscfg_mem mem)
{
	int r;

	r = MMIO32(SYSCFG_CFGR1);
	r &= ~(SYSCFG_CFGR1_MEM_MODE1 | SYSCFG_CFGR1_MEM_MODE0);
	MMIO32(SYSCFG_CFGR1) = r | mem;
}

void syscfg_enable_i2c_fmp(int i2c)
{
	MMIO32(SYSCFG_CFGR2) |= i2c & (SYSCFG_CFGR2_I2C3_FMP |
				       SYSCFG_CFGR2_I2C2_FMP |
				       SYSCFG_CFGR2_I2C1_FMP |
				       SYSCFG_CFGR2_I2C_PB9_FMP |
				       SYSCFG_CFGR2_I2C_PB8_FMP |
				       SYSCFG_CFGR2_I2C_PB7_FMP |
				       SYSCFG_CFGR2_I2C_PB6_FMP);
}

void syscfg_disable_i2c_fmp(int i2c)
{
	MMIO32(SYSCFG_CFGR2) &= ~(i2c & (SYSCFG_CFGR2_I2C3_FMP |
					 SYSCFG_CFGR2_I2C2_FMP |
					 SYSCFG_CFGR2_I2C1_FMP |
					 SYSCFG_CFGR2_I2C_PB9_FMP |
					 SYSCFG_CFGR2_I2C_PB8_FMP |
					 SYSCFG_CFGR2_I2C_PB7_FMP |
					 SYSCFG_CFGR2_I2C_PB6_FMP));
}

void syscfg_enable_firewall(void)
{
	MMIO32(SYSCFG_CFGR2) &= ~SYSCFG_CFGR2_FWDIS;
}

void syscfg_set_exti_source(int exti, enum syscfg_exti src)
{
	int r[4];
	int i;

	if (exti & 0xf)
		r[0] = MMIO32(SYSCFG_EXTICR1);
	if (exti & 0xf0)
		r[1] = MMIO32(SYSCFG_EXTICR2);
	if (exti & 0xf00)
		r[2] = MMIO32(SYSCFG_EXTICR3);
	if (exti & 0xf000)
		r[3] = MMIO32(SYSCFG_EXTICR4);
	for (i = 0; i < 16; i++) {
		if (exti & 1 << i) {
			if (src == SYSCFG_PH && i != 0 && i != 1 && i != 9 &&
			    i != 10)
				continue;
			r[i / 4] &= ~(0xf << (i & 3) * 4);
			r[i / 4] |= src << (i & 3) * 4;
		}
	}
	if (exti & 0xf)
		MMIO32(SYSCFG_EXTICR1) = r[0];
	if (exti & 0xf0)
		MMIO32(SYSCFG_EXTICR2) = r[1];
	if (exti & 0xf00)
		MMIO32(SYSCFG_EXTICR3) = r[2];
	if (exti & 0xf000)
		MMIO32(SYSCFG_EXTICR4) = r[3];
}

void syscfg_enable_vrefint(int control)
{
	MMIO32(SYSCFG_CFGR3) |= control & (SYSCFG_CFGR3_ENBUF_VREFINT_COMP2 |
					   SYSCFG_CFGR3_ENBUF_SENSOR_ADC |
					   SYSCFG_CFGR3_ENBUF_VREFINT_ADC |
					   SYSCFG_CFGR3_EN_VREFINT);
}

void syscfg_disable_vrefint(int control)
{
	MMIO32(SYSCFG_CFGR3) &= ~(control & (SYSCFG_CFGR3_ENBUF_VREFINT_COMP2 |
					     SYSCFG_CFGR3_ENBUF_SENSOR_ADC |
					     SYSCFG_CFGR3_ENBUF_VREFINT_ADC |
					     SYSCFG_CFGR3_EN_VREFINT));
}

int syscfg_get_vrefint_status(void)
{
	return MMIO32(SYSCFG_CFGR3) & SYSCFG_CFGR3_VREFINT_RDYF;
}

void syscfg_set_vrefint_adc_out(enum syscfg_vrefint_out pin)
{
	int r;
	
	r = MMIO32(SYSCFG_CFGR3);
	r &= ~(SYSCFG_CFGR3_SEL_VREF_OUT1 | SYSCFG_CFGR3_SEL_VREF_OUT0);
	MMIO32(SYSCFG_CFGR3) = r | pin;
}

void syscfg_lock_vrefint(void)
{
	MMIO32(SYSCFG_CFGR3) |= SYSCFG_CFGR3_REF_LOCK;
}

void syscfg_set_bank_map(int bank)
{
	if (bank == 1)
		MMIO32(SYSCFG_CFGR1) &= ~SYSCFG_CFGR1_UFB;
	else if (bank == 2)
		MMIO32(SYSCFG_CFGR1) |= SYSCFG_CFGR1_UFB;
}
