/*
 * i2c_proximity - Detect objects with a proximity sensor.
 *
 * i2c_proximity.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of i2c_proximity.
 *
 * i2c_proximity is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * i2c_proximity is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with i2c_proximity.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <usart.h>
#include <tim.h>
#include <nvic.h>
#include <vector.h>
#include <i2c.h>

#include "i2c_proximity.h"
#include "stdio.h"

#define FASTMODE
#define FCK		32000000 /* USART clock frequency */
#define TIMX_CLK_APB1	32000000 /* TIM2 clock frequency */
#define TIMX_CLK_APB2	32000000 /* TIM21 clock frequency */

volatile int sndbuflen;
volatile int *sndbuf;
volatile int rcvbuflen;
volatile int *rcvbuf;
volatile bool busy;
volatile int status;

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
 * PA9: USART2_TX
 * PA4: I2C1_SCL
 * PA13: I2C1_SDA
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(0, 1));
	gpio_set(GPIO_PA(0, 1));
	gpio_config(GPIO_AF4, 0, GPIO_PA9);
	gpio_config(GPIO_AF3, GPIO_OPENDRAIN | GPIO_2MHZ, GPIO_PA(4, 13));
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
 * TIM2: CK_CNT = 2 MHz, one-pulse mode
 * TIM21: CK_CNT = 2 kHz, one-pulse mode
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
	nvic_enable_irq(NVIC_I2C1);
#ifndef FASTMODE
	i2c_init_master(I2C1, 8, 20, 20, I2C_ANFOFF | I2C_ENABLE);
#else
	i2c_init_master(I2C1, 4, 8, 12, I2C_ENABLE);
#endif
	i2c_enable_interrupt(I2C1, I2C_TXIS | I2C_RXNE | I2C_NACKF |
			     I2C_STOPF | I2C_TC | I2C_BERR | I2C_ARLO);
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

void i2c1_isr(void)
{
	int s;
	int r;
	
	s = i2c_get_interrupt_status(I2C1, I2C_TXIS | I2C_RXNE | I2C_NACKF |
				     I2C_STOPF | I2C_TC | I2C_BERR | I2C_ARLO);
	if (s & I2C_TXIS) {
		if (sndbuflen) {
			i2c_send(I2C1, *sndbuf++);
			sndbuflen--;
		}
	}
	if (s & I2C_TC) {
		if (rcvbuflen)
			i2c_start(I2C1, I2C_AUTOEND | I2C_READ | VCNL4000_SLA,
				  rcvbuflen);
		else
			i2c_stop(I2C1);
	}
	if (s & I2C_RXNE) {
		r = i2c_recv(I2C1);
		if (rcvbuflen) {
			*rcvbuf++ = r;
			rcvbuflen--;
		}
	}
	if (s & (I2C_NACKF | I2C_BERR | I2C_ARLO))
		status |= s & (I2C_NACKF | I2C_BERR | I2C_ARLO);
	if (s & (I2C_STOPF | I2C_BERR | I2C_ARLO))
		busy = false;
	if (s & (I2C_NACKF | I2C_STOPF | I2C_BERR | I2C_ARLO))
		i2c_clear_interrupt(I2C1, s & (I2C_NACKF | I2C_STOPF |
					       I2C_BERR | I2C_ARLO));
}

int main(void)
{
	int offset;
	int a;
	int p;

	clock_setup();
	gpio_setup();
	usart_setup();
	tim_setup();
	i2c_setup();

	puts("i2c_proximity");
	offset = proximity_init();
	if (offset < 0)
		goto i2c_error;
	printf("proximity offset = %u\n", offset);

	a = proximity_get_ambient_light();
	if (a < 0)
		goto i2c_error;
	printf("Ambient Light = %u lx\n", a);

	while (1) {
		p = proximity_measure(offset);
		if (p < 0)
			goto i2c_error;
		if (p) {
			gpio_clear(GPIO_PA0);
			printf("Proximity detected %u\n", p);
		} else {
			gpio_set(GPIO_PA0);
		}
	}

i2c_error:
	printf("status = 0x%08x\n", status);
	printf("sndbuflen = %u\n", sndbuflen);
	printf("rcvbuflen = %u\n", rcvbuflen);
	while (1) {
		gpio_toggle(GPIO_PA1);
		delay_ms(250);
	}

	return 0;
}
