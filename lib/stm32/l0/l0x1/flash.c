/*
 * Flash interface functions
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
#include <flash.h>

void flash_config_access(int wait, int option)
{
	int r;
	
	option &= (FLASH_ACR_PRE_READ | FLASH_ACR_DISAB_BUF |
		   FLASH_ACR_PRFTEN);
	if (wait)
		option |= FLASH_ACR_LATENCY;
	r = MMIO32(FLASH_ACR);
	r &= ~(FLASH_ACR_PRE_READ | FLASH_ACR_DISAB_BUF | FLASH_ACR_PRFTEN |
	       FLASH_ACR_LATENCY);
	MMIO32(FLASH_ACR) = r | option;
	while ((int)(MMIO32(FLASH_ACR) & (FLASH_ACR_PRE_READ |
					  FLASH_ACR_DISAB_BUF |
					  FLASH_ACR_PRFTEN |
					  FLASH_ACR_LATENCY)) != option)
		;
}

void flash_enable_power_down(int mode)
{
	MMIO32(FLASH_ACR) |= mode & (FLASH_ACR_RUN_PD | FLASH_ACR_SLEEP_PD);
}

void flash_disable_power_down(int mode)
{
	MMIO32(FLASH_ACR) &= ~(mode & (FLASH_ACR_RUN_PD | FLASH_ACR_SLEEP_PD));
}

void flash_unlock(enum flash_lock lock)
{
	switch (lock) {
	case FLASH_LOCK_POWER_DOWN:
		MMIO32(FLASH_PDKEYR) = FLASH_PDKEYR_KEY1;
		MMIO32(FLASH_PDKEYR) = FLASH_PDKEYR_KEY2;
		break;
	case FLASH_LOCK_PECR:
		MMIO32(FLASH_PEKEYR) = FLASH_PEKEYR_KEY1;
		MMIO32(FLASH_PEKEYR) = FLASH_PEKEYR_KEY2;
		break;
	case FLASH_LOCK_PROGRAM_ERASE:
		MMIO32(FLASH_PRGKEYR) = FLASH_PRGKEYR_KEY1;
		MMIO32(FLASH_PRGKEYR) = FLASH_PRGKEYR_KEY2;
		break;
	case FLASH_LOCK_OPTION_BYTES:
		MMIO32(FLASH_OPTKEYR) = FLASH_OPTKEYR_KEY1;
		MMIO32(FLASH_OPTKEYR) = FLASH_OPTKEYR_KEY2;
		break;
	default:
		break;
	}
}

void flash_lock(enum flash_lock lock)
{
	switch (lock) {
	case FLASH_LOCK_PECR:
		MMIO32(FLASH_PECR) |= FLASH_PECR_PELOCK;
		break;
	case FLASH_LOCK_PROGRAM_ERASE:
		MMIO32(FLASH_PECR) |= FLASH_PECR_PRGLOCK;
		break;
	case FLASH_LOCK_OPTION_BYTES:
		MMIO32(FLASH_PECR) |= FLASH_PECR_OPTLOCK;
		break;
	default:
		break;
	}
}

void flash_enable_fixed_time_data_write(void)
{
	MMIO32(FLASH_PECR) |= FLASH_PECR_FIX;
}

void flash_enable_erase(enum flash_obj obj)
{
	int r;
	
	r = MMIO32(FLASH_PECR);
	if (obj == FLASH_PROGRAM_MEMORY) {
		r &= ~FLASH_PECR_DATA;
		MMIO32(FLASH_PECR) = r | FLASH_PECR_ERASE | FLASH_PECR_PROG;
	} else if (obj == FLASH_DATA_EEPROM) {
		r &= ~FLASH_PECR_PROG;
		MMIO32(FLASH_PECR) = r | FLASH_PECR_ERASE | FLASH_PECR_DATA;
	} else {
		r &= ~(FLASH_PECR_PROG | FLASH_PECR_DATA);
		MMIO32(FLASH_PECR) = r | FLASH_PECR_ERASE;
	}
}

void flash_enable_half_page_write(void)
{
	MMIO32(FLASH_PECR) |= FLASH_PECR_FPRG;
}

void flash_launch_option_byte_loading(void)
{
	MMIO32(FLASH_PECR) |= FLASH_PECR_OBL_LAUNCH;
}

void flash_enable_interrupt(int interrupt)
{
	MMIO32(FLASH_PECR) |= interrupt & (FLASH_PECR_ERRIE |
					   FLASH_PECR_EOPIE);
}

void flash_disable_interrupt(int interrupt)
{
	MMIO32(FLASH_PECR) &= ~(interrupt & (FLASH_PECR_ERRIE |
					     FLASH_PECR_EOPIE));
}

int flash_get_interrupt_mask(int interrupt)
{
	return MMIO32(FLASH_PECR) & interrupt;
}

int flash_get_status(int status)
{
	return MMIO32(FLASH_SR) & status;
}

void flash_clear_status(int status)
{
	MMIO32(FLASH_SR) = status & (FLASH_SR_FWWERR | FLASH_SR_NOTZEROERR |
				     FLASH_SR_RDERR | FLASH_SR_OPTVERR |
				     FLASH_SR_SIZERR | FLASH_SR_PGAERR |
				     FLASH_SR_WRPERR | FLASH_SR_EOP);
}

int flash_get_option_byte_info(int info)
{
	return MMIO32(FLASH_OPTR) & info;
}

int flash_get_write_protection1(void)
{
	return MMIO32(FLASH_WRPROT1);
}

int flash_get_write_protection2(void)
{
	return MMIO32(FLASH_WRPROT2);
}

void flash_enable_parallel_bank(void)
{
	MMIO32(FLASH_PECR) |= FLASH_PECR_PARALLELBANK;
}

void flash_disable_parallel_bank(void)
{
	MMIO32(FLASH_PECR) &= ~FLASH_PECR_PARALLELBANK;
}

void flash_disable_non_zero_check(void)
{
	MMIO32(FLASH_PECR) |= FLASH_PECR_NZDISABLE;
}

void flash_enable_non_zero_check(void)
{
	MMIO32(FLASH_PECR) &= ~FLASH_PECR_NZDISABLE;
}
