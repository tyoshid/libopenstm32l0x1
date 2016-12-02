/*
 * exti - Count the number of button pushes.
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
#include <syscfg.h>
#include <exti.h>

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
 * PA1: input	SW
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA0);
	gpio_set(GPIO_PA0);
	gpio_config(GPIO_INPUT, 0, GPIO_PA1);
}

/* EXTI1: falling edge trigger */
static void exti_setup(void)
{
	rcc_enable_clock(RCC_SYSCFG);
	syscfg_set_exti_source(1, SYSCFG_PA);
	nvic_enable_irq(NVIC_EXTI0_1);
	exti_set_trigger(EXTI1, EXTI_FALLING);
	exti_enable_interrupt(EXTI1);
}

/*
 * EXTI1 interrupt
 *
 * Change the interrupt mode when the button is pushed and released 3 times.
 * 1) falling edge
 * 2) rising edge
 * 3) both edge
 */
void exti0_1_isr(void)
{
	static int count;

	if (exti_get_interrupt_status(EXTI1)) {
		switch (exti_get_trigger(EXTI1)) {
		case EXTI_FALLING:
			gpio_toggle(GPIO_PA0);
			if (++count >= 3) {
				count = -1;
				exti_set_trigger(EXTI1, EXTI_RISING);
			}
			break;
		case EXTI_RISING:
			if (count >= 0) 
				gpio_toggle(GPIO_PA0);
			if (++count >= 3) {
				count = 0;
				exti_set_trigger(EXTI1, EXTI_BOTH);
			}
			break;
		case EXTI_BOTH:
			gpio_toggle(GPIO_PA0);
			if (++count >= 6) {
				count = 0;
				exti_set_trigger(EXTI1, EXTI_FALLING);
			}
			break;
		default:
			break;
		}

		exti_clear_interrupt(EXTI1);
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	exti_setup();

	while (1)
		;

	return 0;
}
