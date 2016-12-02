/*
 * lptim_delay - Blink an LED.
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

/* LPTIM1: clock = 2 MHz */
static void lptim_setup(void)
{
	rcc_enable_clock(RCC_LPTIM1);
	lptim_set_prescaler(LPTIM1, 16);
	lptim_enable_timer(LPTIM1);
}

/* Delay: 1 - 32768 us */
static void delay_us(int us)
{
	lptim_set_autoreload(LPTIM1, us << 1);
	lptim_start_single(LPTIM1);
	while (!lptim_get_interrupt_status(LPTIM1, LPTIM_ARRM))
		;
	lptim_clear_interrupt(LPTIM1, LPTIM_ARRM);
}

/* Blink the LED at 1 Hz. */
int main(void)
{
	int i;
	int j;

	clock_setup();
	gpio_setup();
	lptim_setup();

	while (1) {
		for (i = 0; i < 10; i++) {
			gpio_toggle(GPIO_PA0);
			for (j = 0; j < 50; j++)
				delay_us(10000);
		}
	}

	return 0;
}
