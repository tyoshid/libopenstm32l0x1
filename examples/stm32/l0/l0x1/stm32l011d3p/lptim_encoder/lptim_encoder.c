/*
 * lptim_encoder - Use an encoder to blink two LEDs.
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

#define MAXCOUNT	(24 * 4) /* Pulses per rotation */

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
 * PA0: LPTIM1_IN1	encoder
 * PA1: LPTIM1_IN2	encoder
 * PA4: output		LED1
 * PA7: output		LED2
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_AF1, 0, GPIO_PA(0, 1));
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(4, 7));
	gpio_set(GPIO_PA(4, 7));
}

/* LPTIM1: encoder mode, both edges */
static void lptim_setup(void)
{
	rcc_set_lptim1_clock(RCC_HSI16);
	rcc_enable_clock(RCC_LPTIM1);
	lptim_enable_encoder_mode(LPTIM1, LPTIM_BOTH, LPTIM_FLT_NONE);
	lptim_enable_timer(LPTIM1);
	lptim_set_autoreload(LPTIM1, MAXCOUNT);
	lptim_start_continuous(LPTIM1);
}

/* Blink LED1 or LED2 depending on the direction. */
int main(void)
{
	int c;
	int prev;
	int u;
	int d;
	
	clock_setup();
	gpio_setup();
	lptim_setup();

	prev = 0;
	while (1) {
		c = lptim_get_counter(LPTIM1);
		u = 0;
		d = 0;
		if (c > prev) {
			if (c - prev < MAXCOUNT / 2)
				u = c - prev;
			else
				d = MAXCOUNT - (c - prev);
		} else if (c < prev) {
			if (prev - c < MAXCOUNT / 2)
				d = prev - c;
			else
				u = MAXCOUNT - (prev - c);
		}

		if (u >= 4) {
			gpio_toggle(GPIO_PA4);
			prev = c;
		} else if (d >= 4) {
			gpio_toggle(GPIO_PA7);
			prev = c;
		}
	}

	return 0;
}
