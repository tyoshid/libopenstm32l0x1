/*
 * i2c_rom - Write/read a serial EEPROM.
 *
 * i2c_rom.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of i2c_rom.
 *
 * i2c_rom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * i2c_rom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with i2c_rom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <tim.h>
#include <i2c.h>

#include "i2c_rom.h"

#define FASTMODE
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
 * PA4: I2C1_SCL
 * PA13: I2C1_SDA
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(0, 1));
	gpio_set(GPIO_PA(0, 1));
	gpio_config(GPIO_AF3, GPIO_OPENDRAIN | GPIO_2MHZ, GPIO_PA(4, 13));
}

/* TIM2: CK_CNT = 2 kHz */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM2);
	tim_enable_one_pulse_mode(TIM2);
	tim_disable_update_interrupt_on_any(TIM2);
	tim_load_prescaler(TIM2, TIMX_CLK_APB1 / 2000);
}

/*
 * I2C
 * Standard-mode
 * tPRESC = 32 MHz / 8 = 4 MHz = 250 ns
 * scl_hi = (tHIGH - tSYNC2(min)) / tPRESC
 *          (5 us - 2 * tI2CCLK) / 250 ns = 20
 * scl_lo = (tLOW - tSYNC1(min)) / tPRESC
 *          (5 us - 2 * tI2CCLK) / 250 ns = 20
 *
 * Fast-mode
 * tPRESC = 32 MHz / 4 = 8 MHz = 125 ns
 * scl_hi = (tHIGH - tSYNC2(min)) / tPRESC
 *          (1 us - tAF(min) - 2 * tI2CCLK) / 125 ns = 8
 * scl_lo = (tLOW - tSYNC1(min)) / tPRESC
 *          (1.5 us - tAF(min) - 2 * tI2CCLK) / 125 ns = 12
 */
static void i2c_setup(void)
{
	rcc_enable_clock(RCC_I2C1);
#ifndef FASTMODE
	i2c_init_master(I2C1, 8, 20, 20, I2C_ANFOFF | I2C_ENABLE);
#else
	i2c_init_master(I2C1, 4, 8, 12, I2C_ENABLE);
#endif
}

/* Delay: 1 - 32768 ms */
static void delay_ms(int ms)
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
	i2c_setup();
	
	if (rom_read(0, &data0, 1))
		goto i2c_error;
	data0++;
	addr = 0;
	data = data0;
	for (i = 0; i < PAGE_SIZE; i++) {
		if (rom_write_byte(addr++, data++))
			goto i2c_error;
	}
	for (j = 0; j < ROM_SIZE / PAGE_SIZE - 1; j++) {
		for (i = 0; i < PAGE_SIZE; i++)
			buf[i] = data++;
		if (rom_write_page(addr, buf))
			goto i2c_error;
		addr += PAGE_SIZE;
	}

	while (1) {
		for (n = 1; n <= BUFSIZE; n++) {
			gpio_toggle(GPIO_PA0);

			addr = 0;
			data = data0;
			for (j = 0; j < ROM_SIZE / n; j++) {
				if (rom_read(addr, buf, n))
					goto i2c_error;
				for (i = 0; i < n; i++) {
					if (buf[i] != data)
						goto data_error;
					data++;
				}
				addr += n;
			}

			m = ROM_SIZE % n;
			if (m) {
				if (rom_read(addr, buf, m))
					goto i2c_error;
				for (i = 0; i < m; i++) {
					if (buf[i] != data)
						goto data_error;
					data++;
				}
			}
		}
	}

i2c_error:
	while (1) {
		gpio_toggle(GPIO_PA1);
		delay_ms(250);
	}
data_error:
	while (1) {
		gpio_toggle(GPIO_PA1);
		delay_ms(500);
	}

	return 0;
}
