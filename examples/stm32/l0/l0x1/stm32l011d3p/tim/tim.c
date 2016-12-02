/*
 * tim - Blink two LEDs.
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
 * TIM2: CK_CNT = 2 kHz, count = 1000
 * TIM21: CK_CNT = 2 kHz, count = 1000
 */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM2);
	nvic_enable_irq(NVIC_TIM2);
	tim_setup_counter(TIM2, TIMX_CLK_APB1 / 2000, 1000);
	tim_clear_interrupt(TIM2, TIM_UPDATE);
	tim_enable_interrupt(TIM2, TIM_UPDATE);

	rcc_enable_clock(RCC_TIM21);
	nvic_enable_irq(NVIC_TIM21);
	tim_setup_counter(TIM21, TIMX_CLK_APB2 / 2000, 1000);
	tim_clear_interrupt(TIM21, TIM_UPDATE);
	tim_enable_interrupt(TIM21, TIM_UPDATE);

	tim_enable_counter(TIM2);
}

/* TIM2 interrupt: blink LED1 five times, frequency = 2 Hz */
void tim2_isr(void)
{
	static int count;

	if (tim_get_interrupt_status(TIM2, TIM_UPDATE)) {
		gpio_toggle(GPIO_PA0);

		if (++count >= 10) {
			tim_disable_counter(TIM2);
			count = 0;
			tim_enable_counter(TIM21);
		}

		tim_clear_interrupt(TIM2, TIM_UPDATE);
	}
}

/* TIM21 interrupt: blink LED2 five times, frequency = 2 Hz */
void tim21_isr(void)
{
	static int count;

	if (tim_get_interrupt_status(TIM21, TIM_UPDATE)) {
		gpio_toggle(GPIO_PA1);

		if (++count >= 10) {
			tim_disable_counter(TIM21);
			count = 0;
			tim_enable_counter(TIM2);
		}

		tim_clear_interrupt(TIM21, TIM_UPDATE);
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	tim_setup();

	while (1)
		;

	return 0;
}
