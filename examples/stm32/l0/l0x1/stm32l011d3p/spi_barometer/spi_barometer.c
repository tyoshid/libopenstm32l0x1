/*
 * spi_barometer - Read a barometer.
 *
 * spi_barometer.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of spi_barometer.
 *
 * spi_barometer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * spi_barometer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with spi_barometer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <usart.h>
#include <tim.h>
#include <dma.h>
#include <spi.h>

#include "spi_barometer.h"
#include "stdio.h"

#define FCK			32000000 /* USART clock frequency */
#define TIMX_CLK_APB1		32000000 /* TIM2 clock frequency */

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
 * PA9: USART2_TX
 * PA4: output		MPL115A1 /CS
 * PA7: SPI1_MOSI	MPL115A1 DIN
 * PA13: SPI1_SCK	MPL115A1 SCLK
 * PA14: SPI1_MISO	MPL115A1 DOUT
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA0);
	gpio_config(GPIO_AF4, 0, GPIO_PA9);
	gpio_set(GPIO_PA4);
	gpio_config(GPIO_OUTPUT, GPIO_10MHZ, GPIO_PA4);
	gpio_config(GPIO_AF0, GPIO_10MHZ, GPIO_PA7);
	gpio_config(GPIO_AF5, GPIO_10MHZ, GPIO_PA13);
	gpio_config(GPIO_AF5, GPIO_PULLUP, GPIO_PA14);
}

/* USART2: 115200 8N1 */
static void usart_setup(void)
{
	rcc_enable_clock(RCC_USART2);
	usart_init(USART2, FCK, 115200, 8, USART_STOP_1, USART_PARITY_NONE,
		   USART_FLOW_NONE, USART_TX);
}

/* TIM2: CK_CNT = 2 kHz, one-pulse mode */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM2);
	tim_enable_one_pulse_mode(TIM2);
	tim_disable_update_interrupt_on_any(TIM2);
	tim_load_prescaler(TIM2, TIMX_CLK_APB1 / 2000);
}

/*
 * DMA
 * CH2: SPI1_RX
 * CH3: SPI1_TX
 */
static void dma_setup(void)
{
	rcc_enable_clock(RCC_DMA);
	dma_set_request(DMA_CH2_SPI1_RX | DMA_CH3_SPI1_TX);
}

/* SPI1: SCK: 32 MHz / 4 = 8 MHz */
static void spi_setup(void)
{
	rcc_enable_clock(RCC_SPI1);
	spi_init_master(SPI1, 4, 8, SPI_NSS_OUTPUT | SPI_ENABLE);
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

static void print_pressure(int pressure)
{
	int f;
	int i;
	static const int frac[16] = {0, 1, 1, 2, 3, 3, 4, 4,
				     5, 6, 6, 7, 8, 8, 9, 9};

	f = pressure & 0xf;
	i = pressure >> 4;
	printf("%u.%u kPa\n", i, frac[f]);
}

int main(void)
{
	int pressure;

	clock_setup();
	gpio_setup();
	usart_setup();
	tim_setup();
	dma_setup();
	spi_setup();

	baro_init();

	puts("spi_barometer");
	
	while (1) {
		gpio_toggle(GPIO_PA0);
		pressure = baro_measure();
		print_pressure(pressure);
		delay_ms(1000);
	}

	return 0;
}
