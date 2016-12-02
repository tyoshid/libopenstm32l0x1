/*
 * 1wire_temp - Read a temperature sensor.
 *
 * 1wire_temp.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of 1wire_temp.
 *
 * 1wire_temp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 1wire_temp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 1wire_temp.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <usart.h>
#include <tim.h>
#include <crc.h>

#include "1wire_temp.h"
#include "stdio.h"

#define FCK			32000000 /* USART clock frequency */
#define TIMX_CLK_APB1		32000000 /* TIM2 clock frequency */
#define TIMX_CLK_APB2		32000000 /* TIM21 clock frequency */

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
 * PA0: output			LED1
 * PA1: output			LED2
 * PA7: output, open-drain	DS18B20 DQ
 * PA9: USART2_TX
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_set(GPIO_PA(0, 1));
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(0, 1));
	gpio_set(GPIO_PA7);
	gpio_config(GPIO_OUTPUT, GPIO_OPENDRAIN, GPIO_PA7);
	gpio_config(GPIO_AF4, 0, GPIO_PA9);
}

/* USART2: 115200 8N1 */
static void usart_setup(void)
{
	rcc_enable_clock(RCC_USART2);
	usart_init(USART2, FCK, 115200, 8, USART_STOP_1, USART_PARITY_NONE,
		   USART_FLOW_NONE, USART_TX);
}

/*
 * TIM
 * TIM2: CK_CNT = 2 MHz
 * TIM21: CK_CNT = 2 kHz
 */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM2);
	rcc_enable_clock(RCC_TIM21);
	tim_enable_one_pulse_mode(TIM2);
	tim_enable_one_pulse_mode(TIM21);
	tim_disable_update_interrupt_on_any(TIM2);
	tim_disable_update_interrupt_on_any(TIM21);
	tim_load_prescaler(TIM2, TIMX_CLK_APB1 / 2000000);
	tim_load_prescaler(TIM21, TIMX_CLK_APB2 / 2000);
}

/* CRC: CRC-8 */
static void crc_setup(void)
{
	rcc_enable_clock(RCC_CRC);
	crc_set_mode(0x31, CRC_POLYSIZE_8 | CRC_REV_IN_BYTE | CRC_REV_OUT);
}

/* Delay: 1 - 32768 us */
void delay_us(int us)
{
	tim_set_autoreload(TIM2, us << 1);
	tim_enable_counter(TIM2);
	while (!tim_get_interrupt_status(TIM2, TIM_UPDATE))
		;
	tim_clear_interrupt(TIM2, TIM_UPDATE);
}

/* Delay: 1 - 32768 ms */
void delay_ms(int ms)
{
	tim_set_autoreload(TIM21, ms << 1);
	tim_enable_counter(TIM21);
	while (!tim_get_interrupt_status(TIM21, TIM_UPDATE))
		;
	tim_clear_interrupt(TIM21, TIM_UPDATE);
}

int main(void)
{
	char buf[9];
	int t;
	static const int frac[16] = {0, 1, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7,
				     8, 8, 9, 9};
	
	clock_setup();
	gpio_setup();
	usart_setup();
	tim_setup();
	crc_setup();

	puts("1wire_temp");
	if (ds_read_rom(buf))
		goto onewire_error;
	printf("DS18B20 serial number: %02x%02x%02x%02x%02x%02x\n",
	       (unsigned char)buf[6], (unsigned char)buf[5],
	       (unsigned char)buf[4], (unsigned char)buf[3],
	       (unsigned char)buf[2], (unsigned char)buf[1]);
	
	while (1) {
		gpio_toggle(GPIO_PA0);
		if (ds_read_data(buf))
			goto onewire_error;
		t = buf[1] << 8 | (buf[0] & 0xff);
		if (t >= 0)
			printf(" %2u.%1u degrees Celsius\n", t >> 4,
			       frac[t & 0xf]);
		else
			printf("-%2u.%1u degrees Celsius\n", -t >> 4,
			       frac[-t & 0xf]);
	}

onewire_error:
	while (1) {
		gpio_toggle(GPIO_PA1);
		delay_ms(500);
	}
	
	return 0;
}
