/*
 * comp - Control an LED with a potentiometer.
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
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
#include <syscfg.h>
#include <comp.h>
#include <nvic.h>
#include <vector.h>
#include <exti.h>

#include <stdint.h>
#include <memorymap.h>
#include <mmio.h>

#define TIMX_CLK_APB2	32000000 /* TIM21 clock frequency */
#define T_SETTLING	4	 /* COMP2 td_fast.max = 4 us */

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
 * PA0: COM1_OUT	LED1
 * PA1: output		LED2
 * (PA7: analog		COMP2_INP)
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_AF7, 0, GPIO_PA0);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA1);
}

/* TIM21: CK_CNT = 2 MHz */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM21);
	tim_enable_one_pulse_mode(TIM21);
	tim_disable_update_interrupt_on_any(TIM21);
	tim_load_prescaler(TIM21, TIMX_CLK_APB2 / 2000000);
}

/* Delay: 1 - 32768 us */
static void delay_us(int us)
{
	tim_set_autoreload(TIM21, us << 1);
	tim_enable_counter(TIM21);
	while (!tim_get_interrupt_status(TIM21, TIM_UPDATE))
		;
	tim_clear_interrupt(TIM21, TIM_UPDATE);
}

/*
 * COMP
 * COMP1: input+: COMP2+, input-: VREFINT, output: LED1
 * COMP2: input+: PA7, input-: VREFINT, output: EXTI22
 */
static void comp_setup(void)
{
	rcc_enable_clock(RCC_SYSCFG);
	syscfg_enable_vrefint(SYSCFG_VREFINT_COMP2 | SYSCFG_EN_VREFINT);
	comp_init(COMP1, COMP_COMP2, COMP_VREFINT, COMP_ENABLE);
	comp_init(COMP2, COMP_PA7, COMP_VREFINT, COMP_FAST | COMP_ENABLE);
	delay_us(COMP2_T_START_FAST);
}

static void exti_setup(void)
{
	nvic_enable_irq(NVIC_ADC_COMP);
	exti_set_trigger(EXTI_COMP2_OUTPUT, EXTI_BOTH);
	exti_enable_interrupt(EXTI_COMP2_OUTPUT);
}

/* COMP2 interrupt: blink LED2. */
void adc_comp_isr()
{
	static const int vrefint[4] = {COMP_3_4_VREFINT, COMP_1_2_VREFINT,
				       COMP_1_4_VREFINT, COMP_VREFINT};
	static int count;
	
	if (exti_get_interrupt_status(EXTI_COMP2_OUTPUT)) {
		comp_init(COMP2, COMP_PA7, vrefint[count++],
			  COMP_FAST | COMP_ENABLE);
		if (count >= 4)
			count = 0;
		gpio_toggle(GPIO_PA1);
		delay_us(T_SETTLING);
		exti_clear_interrupt(EXTI_COMP2_OUTPUT);
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	tim_setup();
	comp_setup();
	exti_setup();
	
	while (1)
		;

	return 0;
}
