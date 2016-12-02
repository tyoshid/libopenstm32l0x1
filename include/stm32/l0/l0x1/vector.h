/*
 * Vector table
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

/*
 * STMicroelectronics(www.st.com)
 *
 * RM0377: Reference manual
 * Ultra-low-power STM32L0x1 advanced ARM-based 32-bit MCUs
 * (30-Aug-2016 Rev 6)
 *
 * 11  Nested vectored interrupt controller (NVIC)
 */

/* --- IRQ channel numbers ------------------------------------------------- */

#define NVIC_NMI_IRQ			-14
#define NVIC_HARDFAULT_IRQ		-13
#define NVIC_SVCALL_IRQ			-5
#define NVIC_PENDSV_IRQ			-2
#define NVIC_SYSTICK_IRQ		-1

#define NVIC_WWDG_IRQ			0
#define NVIC_PVD_IRQ			1
#define NVIC_RTC_IRQ			2
#define NVIC_FLASH_IRQ			3
#define NVIC_RCC_IRQ			4
#define NVIC_EXTI0_1_IRQ		5
#define NVIC_EXTI2_3_IRQ		6
#define NVIC_EXTI4_15_IRQ		7
#define NVIC_DMA_CH1_IRQ		9
#define NVIC_DMA_CH2_3_IRQ		10
#define NVIC_DMA_CH4_7_IRQ		11
#define NVIC_ADC_COMP_IRQ		12
#define NVIC_LPTIM1_IRQ			13
#define NVIC_USART4_5_IRQ		14
#define NVIC_TIM2_IRQ			15
#define NVIC_TIM3_IRQ			16
#define NVIC_TIM6_IRQ			17
#define NVIC_TIM7_IRQ			18
#define NVIC_TIM21_IRQ			20
#define NVIC_I2C3_IRQ			21
#define NVIC_TIM22_IRQ			22
#define NVIC_I2C1_IRQ			23
#define NVIC_I2C2_IRQ			24
#define NVIC_SPI1_IRQ			25
#define NVIC_SPI2_IRQ			26
#define NVIC_USART1_IRQ			27
#define NVIC_USART2_IRQ			28
#define NVIC_LPUART1_AES_IRQ		29

/* --- Handler prototypes -------------------------------------------------- */

void nmi(void);
void hardfault(void);
void svcall(void);
void pendsv(void);
void systick_isr(void);

void wwdg_isr(void);
void pvd_isr(void);
void rtc_isr(void);
void flash_isr(void);
void rcc_isr(void);
void exti0_1_isr(void);
void exti2_3_isr(void);
void exti4_15_isr(void);
void dma_ch1_isr(void);
void dma_ch2_3_isr(void);
void dma_ch4_7_isr(void);
void adc_comp_isr(void);
void lptim1_isr(void);
void usart4_5_isr(void);
void tim2_isr(void);
void tim3_isr(void);
void tim6_isr(void);
void tim7_isr(void);
void tim21_isr(void);
void i2c3_isr(void);
void tim22_isr(void);
void i2c1_isr(void);
void i2c2_isr(void);
void spi1_isr(void);
void spi2_isr(void);
void usart1_isr(void);
void usart2_isr(void);
void lpuart1_aes_isr(void);

/* Interrupt */
enum {
	NVIC_WWDG = (1 << 0),
	NVIC_PVD = (1 << 1),
	NVIC_RTC = (1 << 2),
	NVIC_FLASH = (1 << 3),
	NVIC_RCC = (1 << 4),
	NVIC_EXTI0_1 = (1 << 5),
	NVIC_EXTI2_3 = (1 << 6),
	NVIC_EXTI4_15 = (1 << 7),
	NVIC_DMA_CH1 = (1 << 9),
	NVIC_DMA_CH2_3 = (1 << 10),
	NVIC_DMA_CH4_7 = (1 << 11),
	NVIC_ADC_COMP = (1 << 12),
	NVIC_LPTIM1 = (1 << 13),
	NVIC_USART4_5 = (1 << 14),
	NVIC_TIM2 = (1 << 15),
	NVIC_TIM3 = (1 << 16),
	NVIC_TIM6 = (1 << 17),
	NVIC_TIM7 = (1 << 18),
	NVIC_TIM21 = (1 << 20),
	NVIC_I2C3 = (1 << 21),
	NVIC_TIM22 = (1 << 22),
	NVIC_I2C1 = (1 << 23),
	NVIC_I2C2 = (1 << 24),
	NVIC_SPI1 = (1 << 25),
	NVIC_SPI2 = (1 << 26),
	NVIC_USART1 = (1 << 27),
	NVIC_USART2 = (1 << 28),
	NVIC_LPUART1_AES = (1 << 29),
};
