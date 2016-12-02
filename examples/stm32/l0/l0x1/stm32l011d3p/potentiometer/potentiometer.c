/*
 * potentiometer - Use a potentiometer to fade two LEDs.
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
#include <adc.h>
#include <dma.h>
#include <memorymap.h>

#define TIMX_CLK_APB1	32000000 /* TIM2 clock frequency */

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
 * PA0: TIM2_CH1	LED1
 * PA1: TIM2_CH2	LED2
 * (PA7: analog		ADC_IN7)
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_AF2, 0, GPIO_PA(0, 1));
}

/*
 * TIM
 * TIM2: CK_CNT = 204.8 kHz, count = 4096, TRGO: Update
 *   OC1: PWM mode 1
 *   OC2: PWM mode 2
 */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM2);
	tim_setup_counter(TIM2, TIMX_CLK_APB1 / 204800, 4096);
	tim_set_master_mode(TIM2, TIM_TRGO_UPDATE);
	tim_set_capture_compare_mode(TIM2_CC1, TIM_OC_PRELOAD | TIM_OC_PWM1 |
				     TIM_CC_ENABLE);
	tim_set_capture_compare_mode(TIM2_CC2, TIM_OC_PRELOAD | TIM_OC_PWM2 |
				     TIM_CC_ENABLE);
}

/* ADC: Channel: PA7, Trigger: TIM2_TRGO, DMA */
static void adc_setup(void)
{
	rcc_enable_clock(RCC_ADC);
	adc_calibration();

	adc_enable();
	adc_init(ADC_IN_PA7, ADC_160_5CLK, ADC_SINGLE, ADC_EXT_RISING,
		 ADC_TIM2_TRGO, ADC_DMA_CIRCULAR | ADC_DMA_ENABLE);
	adc_start();
}

/* DMA CH1: ADC, ADC_DR -> TIM2_CCR1, CCR2 */
static void dma_setup(void)
{
	rcc_enable_clock(RCC_DMA);
	dma_setup_channel(DMA_CH1, TIM2_CCR1, ADC_DR, 2,
			  DMA_M_32BIT | DMA_P_32BIT | DMA_M_INC |
			  DMA_CIRCULAR | DMA_ENABLE);
}

int main(void)
{
	clock_setup();
	gpio_setup();
	tim_setup();
	adc_setup();
	dma_setup();

	tim_enable_counter(TIM2);

	while (1)
		;

	return 0;
}
