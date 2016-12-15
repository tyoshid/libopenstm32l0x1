/*
 * Memory mapping
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
 * (14-Nov-2016 Rev 7)
 *
 * 2  System and memory overview
 * 3  Flash program memory and data EEPROM (FLASH)
 */

/* --- STM32L0x1 memory map ------------------------------------------------ */

#define FLASH_MEMORY_BASE		0x08000000
#define EEPROM_BASE			0x08080000
#define SYSTEM_MEMORY_BASE		0x1ff00000
#define OPTION_BYTE_BASE		0x1ff80000
#define SRAM_BASE			0x20000000
#define PERIPH_BASE			0x40000000

/* --- Option bytes -------------------------------------------------------- */

#define USER_OPTION_BASE		(OPTION_BYTE_BASE + 0x00)
#define FACTORY_OPTION_BASE		(OPTION_BYTE_BASE + 0x20)

/* --- Peripherals --------------------------------------------------------- */

/* Memory map for all busses */
#define PERIPH_BASE_APB1		(PERIPH_BASE + 0x00000000)
#define PERIPH_BASE_APB2		(PERIPH_BASE + 0x00010000)
#define PERIPH_BASE_AHB			(PERIPH_BASE + 0x00020000)
#define PERIPH_BASE_IOPORT		(PERIPH_BASE + 0x10000000)

/* Register boundary addresses */

/* APB1 */
#define TIM2_BASE			(PERIPH_BASE_APB1 + 0x0000)
#define TIM3_BASE			(PERIPH_BASE_APB1 + 0x0400)

#define TIM6_BASE			(PERIPH_BASE_APB1 + 0x1000)
#define TIM7_BASE			(PERIPH_BASE_APB1 + 0x1400)

#define RTC_BASE			(PERIPH_BASE_APB1 + 0x2800)
#define WWDG_BASE			(PERIPH_BASE_APB1 + 0x2c00)
#define IWDG_BASE			(PERIPH_BASE_APB1 + 0x3000)

#define SPI2_BASE			(PERIPH_BASE_APB1 + 0x3800)

#define USART2_BASE			(PERIPH_BASE_APB1 + 0x4400)
#define LPUART1_BASE			(PERIPH_BASE_APB1 + 0x4800)
#define USART4_BASE			(PERIPH_BASE_APB1 + 0x4c00)
#define USART5_BASE			(PERIPH_BASE_APB1 + 0x5000)
#define I2C1_BASE			(PERIPH_BASE_APB1 + 0x5400)
#define I2C2_BASE			(PERIPH_BASE_APB1 + 0x5800)

#define PWR_BASE			(PERIPH_BASE_APB1 + 0x7000)

#define I2C3_BASE			(PERIPH_BASE_APB1 + 0x7800)
#define LPTIM1_BASE			(PERIPH_BASE_APB1 + 0x7c00)

/* APB2 */
#define SYSCFG_BASE			(PERIPH_BASE_APB2 + 0x0000)
#define EXTI_BASE			(PERIPH_BASE_APB2 + 0x0400)
#define TIM21_BASE			(PERIPH_BASE_APB2 + 0x0800)

#define TIM22_BASE			(PERIPH_BASE_APB2 + 0x1400)

#define FIREWALL_BASE			(PERIPH_BASE_APB2 + 0x1c00)

#define ADC1_BASE			(PERIPH_BASE_APB2 + 0x2400)

#define SPI1_BASE			(PERIPH_BASE_APB2 + 0x3000)

#define USART1_BASE			(PERIPH_BASE_APB2 + 0x3800)

#define DBG_BASE			(PERIPH_BASE_APB2 + 0x5800)

/* AHB */
#define DMA1_BASE			(PERIPH_BASE_AHB + 0x0000)

#define RCC_BASE			(PERIPH_BASE_AHB + 0x1000)

#define FLASH_INTERFACE_BASE		(PERIPH_BASE_AHB + 0x2000)

#define CRC_BASE			(PERIPH_BASE_AHB + 0x3000)

#define AES_BASE			(PERIPH_BASE_AHB + 0x6000)

/* IOPORT */
#define GPIOA_BASE			(PERIPH_BASE_IOPORT + 0x0000)
#define GPIOB_BASE			(PERIPH_BASE_IOPORT + 0x0400)
#define GPIOC_BASE			(PERIPH_BASE_IOPORT + 0x0800)
#define GPIOD_BASE			(PERIPH_BASE_IOPORT + 0x0c00)
#define GPIOE_BASE			(PERIPH_BASE_IOPORT + 0x1000)

#define GPIOH_BASE			(PERIPH_BASE_IOPORT + 0x1c00)
