/*
 * PWR functions
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
#include <stdbool.h>

#include <mmio.h>
#include <memorymap.h>
#include <pwr.h>

void pwr_set_vos(enum pwr_vos vos)
{
	int r;

	while (MMIO32(PWR_CSR) & PWR_CSR_VOSF)
		;
	r = MMIO32(PWR_CR);
	if ((r & (PWR_CR_VOS1 | PWR_CR_VOS0)) == vos)
		return;
	r &= ~(PWR_CR_VOS1 | PWR_CR_VOS0);
	MMIO32(PWR_CR) = r | vos;
	while (MMIO32(PWR_CSR) & PWR_CSR_VOSF)
		;
}

int pwr_get_vos(void)
{
	return MMIO32(PWR_CR) & (PWR_CR_VOS1 | PWR_CR_VOS0);
}

void pwr_set_mode(enum pwr_mode mode)
{
	int r;
	
	r = MMIO32(PWR_CR);
	switch (mode) {
	case PWR_RUN:
	case PWR_SLEEP:
		r &= ~PWR_CR_LPRUN;
		MMIO32(PWR_CR) = r;
		MMIO32(PWR_CR) = r & ~(PWR_CR_PDDS | PWR_CR_LPSDSR);
		break;
	case PWR_LOW_POWER_RUN:
		r &= ~PWR_CR_PDDS;
		r |= PWR_CR_LPSDSR;
		MMIO32(PWR_CR) = r;
		MMIO32(PWR_CR) = r | PWR_CR_LPRUN;
		break;
	case PWR_LOW_POWER_SLEEP:
		r &= ~(PWR_CR_LPRUN | PWR_CR_PDDS);
		MMIO32(PWR_CR) = r;
		MMIO32(PWR_CR) = r | PWR_CR_LPSDSR;
		break;
	case PWR_STOP:
		r &= ~(PWR_CR_LPRUN | PWR_CR_PDDS);
		MMIO32(PWR_CR) = r;
		r &= ~PWR_CR_LPSDSR;
		MMIO32(PWR_CR) = r | PWR_CR_CWUF;
		break;
	case PWR_LOW_POWER_STOP:
		r &= ~(PWR_CR_LPRUN | PWR_CR_PDDS);
		MMIO32(PWR_CR) = r;
		MMIO32(PWR_CR) = r | PWR_CR_CWUF | PWR_CR_LPSDSR;
		break;
	case PWR_STANDBY:
		r &= ~PWR_CR_LPRUN;
		MMIO32(PWR_CR) = r;
		r &= ~PWR_CR_LPSDSR;
		MMIO32(PWR_CR) = r | PWR_CR_CWUF | PWR_CR_PDDS;
		break;
	default:
		break;
	}
}

void pwr_enable_ultra_low_power_mode(bool fast_wakeup)
{
	int r;

	r = MMIO32(PWR_CR);
	if (fast_wakeup)
		r |= PWR_CR_FWU;
	else
		r &= ~PWR_CR_FWU;
	MMIO32(PWR_CR) = r | PWR_CR_ULP;
}

void pwr_disable_ultra_low_power_mode(void)
{
	MMIO32(PWR_CR) &= ~PWR_CR_ULP;
}

void pwr_disable_backup_write_protection(void)
{
	MMIO32(PWR_CR) |= PWR_CR_DBP;
}

void pwr_enable_backup_write_protection(void)
{
	MMIO32(PWR_CR) &= ~PWR_CR_DBP;
}

void pwr_set_pvd_level(enum pwr_pvd level)
{
	int r;

	r = MMIO32(PWR_CR);
	r &= ~(PWR_CR_PLS2 | PWR_CR_PLS1 | PWR_CR_PLS0);
	MMIO32(PWR_CR) = r | level;
}

void pwr_enable_pvd(void)
{
	MMIO32(PWR_CR) |= PWR_CR_PVDE;
}

void pwr_disable_pvd(void)
{
	MMIO32(PWR_CR) &= ~PWR_CR_PVDE;
}

void pwr_enable_wkup_pin(int ewup)
{
	MMIO32(PWR_CSR) |= ewup & (PWR_CSR_EWUP3 | PWR_CSR_EWUP2 |
				   PWR_CSR_EWUP1);
}

void pwr_disable_wkup_pin(int ewup)
{
	MMIO32(PWR_CSR) &= ~(ewup & (PWR_CSR_EWUP3 | PWR_CSR_EWUP2 |
				     PWR_CSR_EWUP1));
}

int pwr_get_flag(int flag)
{
	return MMIO32(PWR_CSR) & flag;
}

void pwr_clear_flag(int flag)
{
	int c;

	c = 0;
	if (flag & PWR_STANDBY)
		c |= PWR_CR_CSBF;
	if (flag & PWR_WAKEUP)
		c |= PWR_CR_CWUF;
	if (c)
		MMIO32(PWR_CR) |= c;
}

void pwr_enable_flash_keep_off(void)
{
	MMIO32(PWR_CR) |= PWR_CR_DS_EE_KOFF;
}

void pwr_disable_flash_keep_off(void)
{
	MMIO32(PWR_CR) &= ~PWR_CR_DS_EE_KOFF;
}

void pwr_enable_low_power_deepsleep(void)
{
	MMIO32(PWR_CR) |= PWR_CR_LPDS;
}

void pwr_disable_low_power_deepsleep(void)
{
	MMIO32(PWR_CR) &= ~PWR_CR_LPDS;
}
