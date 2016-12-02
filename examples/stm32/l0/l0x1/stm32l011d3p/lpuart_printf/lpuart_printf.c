/*
 * lpuart_printf - Use newlib printf() function.
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

#include <stdio.h>
#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <lpuart.h>

#include <syscall.h>

#define FCK	32000000	/* LPUART clock frequency */

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
 * PA0: output		LED
 * PA14: LPUART1_TX
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA0);
	gpio_config(GPIO_AF6, 0, GPIO_PA14);
}

/* LPUART1: 115200 8N1 */
static void lpuart_setup(void)
{
	rcc_enable_clock(RCC_LPUART1);
	lpuart_init(LPUART1, FCK, 115200, 8, LPUART_STOP_1, LPUART_PARITY_NONE,
		    LPUART_FLOW_NONE, LPUART_TX);
}

int _write(int file, char *ptr, int len)
{
	int i;

	if (file == 1) {
		for (i = 0; i < len; i++) {
			if (ptr[i] == '\n')
				lpuart_send_blocking(LPUART1, '\r');
			lpuart_send_blocking(LPUART1, ptr[i]);
		}
		return i;
	}

	errno = EIO;
	return -1;
}

int main(void)
{
	int counter = 0;

	clock_setup();
	gpio_setup();
	lpuart_setup();

	while (1) {
		gpio_toggle(GPIO_PA0);
		printf("Hello World! %i\n", counter);
		counter++;
	}

	return 0;
}
