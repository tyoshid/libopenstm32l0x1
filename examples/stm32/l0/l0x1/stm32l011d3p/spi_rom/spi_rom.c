/*
 * spi_rom - Write/read a serial EEPROM.
 *
 * spi_rom.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of spi_rom.
 *
 * spi_rom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * spi_rom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with spi_rom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <tim.h>
#include <spi.h>

#include "spi_rom.h"

#define TIMX_CLK_APB1	32000000 /* TIM2 clock frequency */
#define BUFSIZE		1024

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
 * PA0: output		LED1
 * PA1: output		LED2
 * PA4: output		25LC640A /CS
 * PA7: SPI1_MOSI	25LC640A SI
 * PA13: SPI1_SCK	25LC640A SCK
 * PA14: SPI1_MISO	25LC640A SO
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(0, 1));
	gpio_set(GPIO_PA(0, 1));
	gpio_set(GPIO_PA4);
	gpio_config(GPIO_OUTPUT, GPIO_10MHZ, GPIO_PA4);
	gpio_config(GPIO_AF0, GPIO_10MHZ, GPIO_PA7);
	gpio_config(GPIO_AF5, GPIO_10MHZ, GPIO_PA13);
	gpio_config(GPIO_AF5, GPIO_PULLUP, GPIO_PA14);
}

/* TIM2: CK_CNT = 2 kHz, one-pulse mode */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM2);
	tim_enable_one_pulse_mode(TIM2);
	tim_disable_update_interrupt_on_any(TIM2);
	tim_load_prescaler(TIM2, TIMX_CLK_APB1 / 2000);
}

/* SPI1: SCK: 32 MHz / 8 = 4 MHz (25LC640A Max. 5 MHz) */
static void spi_setup(void)
{
	rcc_enable_clock(RCC_SPI1);
	spi_init_master(SPI1, 8, 8, SPI_NSS_OUTPUT | SPI_ENABLE);
}

/* Delay: 1 - 32768 ms */
void delay_ms(int ms)
{
	tim_set_autoreload(TIM2, ms << 1);
	tim_enable_counter(TIM2);
	while (!tim_get_interrupt_status(TIM2, TIM_UPDATE))
		;
	tim_clear_interrupt(TIM2, TIM_UPDATE);
}

int main(void)
{
	char data0;
	int addr;
	char data;
	int i;
	int j;
	static char buf[BUFSIZE];
	int n;
	int m;

	clock_setup();
	gpio_setup();
	tim_setup();
	spi_setup();
	
	rom_read(0, &data0, 1);
	data0++;
	addr = 0;
	data = data0;
	for (i = 0; i < PAGE_SIZE; i++)
		rom_write_byte(addr++, data++);

	for (j = 0; j < ROM_SIZE / PAGE_SIZE - 1; j++) {
		for (i = 0; i < PAGE_SIZE; i++)
			buf[i] = data++;
		rom_write_page(addr, buf);
		addr += PAGE_SIZE;
	}

	while (1) {
		for (n = 1; n <= BUFSIZE; n++) {
			gpio_toggle(GPIO_PA0);
			addr = 0;
			data = data0;
			for (j = 0; j < ROM_SIZE / n; j++) {
				rom_read(addr, buf, n);
				for (i = 0; i < n; i++) {
					if (buf[i] != data)
						goto data_error;
					data++;
				}
				addr += n;
			}

			m = ROM_SIZE % n;
			if (m) {
				rom_read(addr, buf, m);
				for (i = 0; i < m; i++) {
					if (buf[i] != data)
						goto data_error;
					data++;
				}
			}
		}
	}

data_error:
	while (1) {
		gpio_toggle(GPIO_PA1);
		delay_ms(500);
	}

	return 0;
}
