/*
 * tim_delay - Blink two LEDs.
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
#include <tim.h>

#define TIMX_CLK_APB1	32000000 /* TIM2 clock frequency */
#define TIMX_CLK_APB2	32000000 /* TIM21 clock frequency */

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
 * PA0: output	LED1
 * PA1: output	LED2
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(0, 1));
	gpio_set(GPIO_PA(0, 1));
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

/* Delay: 1 - 32768 us */
static void delay_us(int us)
{
	tim_set_autoreload(TIM2, us << 1);
	tim_enable_counter(TIM2);
	while (!tim_get_interrupt_status(TIM2, TIM_UPDATE))
		;
	tim_clear_interrupt(TIM2, TIM_UPDATE);
}

/* Delay: 1 - 32768 ms */
static void delay_ms(int ms)
{
	tim_set_autoreload(TIM21, ms << 1);
	tim_enable_counter(TIM21);
	while (!tim_get_interrupt_status(TIM21, TIM_UPDATE))
		;
	tim_clear_interrupt(TIM21, TIM_UPDATE);
}

/* Blink LED1 five times and then LED2 five times. */
int main(void)
{
	int i;
	int j;

	clock_setup();
	gpio_setup();
	tim_setup();

	while (1) {
		for (i = 0; i < 10; i++) {
			gpio_toggle(GPIO_PA0);
			delay_ms(1000);
		}
		for (i = 0; i < 10; i++) {
			gpio_toggle(GPIO_PA1);
			for (j = 0; j < 100; j++)
				delay_us(10000);
		}
	}

	return 0;
}
