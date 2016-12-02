/*
 * lptim - Blink an LED.
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

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <nvic.h>
#include <vector.h>
#include <lptim.h>

/*
 * Clock
 * PLL: 16 MHz * 4 / 2 = 32 MHz
 * SYSCLK	32 MHz
 * HCLK		32 MHz (AHB)
 * PCLK1	32 MHz (APB1)
 * PCLK2	32 MHz (APB2)
 */
static void clock_setup(void)
{
	rcc_enable_clock(RCC_PWR);
	pwr_set_vos(PWR_1_8V);

	rcc_enable_osc(RCC_HSI16);
	rcc_setup_pll(RCC_HSI16, 4, 2);
	rcc_enable_osc(RCC_PLL);
	flash_config_access(1, FLASH_PREFETCH | FLASH_PREREAD);
	rcc_set_sysclk_source(RCC_PLL);
	rcc_disable_osc(RCC_MSI);
}

/*
 * GPIO
 * PA0: output	LED
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA0);
}

/* LPTIM1: clock = 125 kHz, count = 62500, continuous mode */
static void lptim_setup(void)
{
	rcc_set_lptim1_clock(RCC_HSI16);
	rcc_enable_clock(RCC_LPTIM1);
	nvic_enable_irq(NVIC_LPTIM1);
	lptim_enable_interrupt(LPTIM1, LPTIM_ARRM);
	lptim_set_prescaler(LPTIM1, 128);
	lptim_enable_timer(LPTIM1);
	lptim_set_autoreload(LPTIM1, 62500);
	lptim_start_continuous(LPTIM1);
}

/* LPTIM1 interrupt: frequency = 2 Hz */
void lptim1_isr(void)
{
	if (lptim_get_interrupt_status(LPTIM1, LPTIM_ARRM)) {
		gpio_toggle(GPIO_PA0);
		lptim_clear_interrupt(LPTIM1, LPTIM_ARRM);
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	lptim_setup();

	while (1)
		;

	return 0;
}
