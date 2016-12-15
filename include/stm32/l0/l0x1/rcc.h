/*
 * RCC
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
 * 7  Reset and clock control (RCC)
 */

/* --- RCC registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		RCC_CR		Clock control register
 * 0x04		RCC_ICSCR	Internal clock sources calibration register
 * 0x0c		RCC_CFGR	Clock configuration register
 * 0x10		RCC_CIER	Clock interrupt enable register
 * 0x14		RCC_CIFR	Clock interrupt flag register
 * 0x18		RCC_CICR	Clock interrupt clear register
 * 0x1c		RCC_IOPRSTR	GPIO reset register
 * 0x20		RCC_AHBRSTR	AHB peripheral reset register
 * 0x24		RCC_APB2RSTR	APB2 peripheral reset register
 * 0x28		RCC_APB1RSTR	APB1 peripheral reset register
 * 0x2c		RCC_IOPENR	GPIO clock enable register
 * 0x30		RCC_AHBENR	AHB peripheral clock enable register
 * 0x34		RCC_APB2ENR	APB2 peripheral clock enable register
 * 0x38		RCC_APB1ENR	APB1 peripheral clock enable register
 * 0x3c		RCC_IOPSMENR	GPIO clock enable in sleep mode register
 * 0x40		RCC_AHBSMENR	AHB peripheral clock enable in sleep mode
 *				register
 * 0x44		RCC_APB2SMENR	APB2 peripheral clock enable in sleep mode
 *				register
 * 0x48		RCC_APB1SMENR	APB1 peripheral clock enable in sleep mode
 *				register
 * 0x4c		RCC_CCIPR	Clock configuration register
 * 0x50		RCC_CSR		Control/status register
 */

#define RCC_CR				(RCC_BASE + 0x00)
#define RCC_ICSCR			(RCC_BASE + 0x04)
#define RCC_CFGR			(RCC_BASE + 0x0c)
#define RCC_CIER			(RCC_BASE + 0x10)
#define RCC_CIFR			(RCC_BASE + 0x14)
#define RCC_CICR			(RCC_BASE + 0x18)
#define RCC_IOPRSTR			(RCC_BASE + 0x1c)
#define RCC_AHBRSTR			(RCC_BASE + 0x20)
#define RCC_APB2RSTR			(RCC_BASE + 0x24)
#define RCC_APB1RSTR			(RCC_BASE + 0x28)
#define RCC_IOPENR			(RCC_BASE + 0x2c)
#define RCC_AHBENR			(RCC_BASE + 0x30)
#define RCC_APB2ENR			(RCC_BASE + 0x34)
#define RCC_APB1ENR			(RCC_BASE + 0x38)
#define RCC_IOPSMENR			(RCC_BASE + 0x3c)
#define RCC_AHBSMENR			(RCC_BASE + 0x40)
#define RCC_APB2SMENR			(RCC_BASE + 0x44)
#define RCC_APB1SMENR			(RCC_BASE + 0x48)
#define RCC_CCIPR			(RCC_BASE + 0x4c)
#define RCC_CSR				(RCC_BASE + 0x50)

/* --- RCC_CR values ------------------------------------------------------- */

#define RCC_CR_PLLRDY			(1 << 25)
#define RCC_CR_PLLON			(1 << 24)
#define RCC_CR_RTCPRE1			(1 << 21)
#define RCC_CR_RTCPRE0			(1 << 20)
#define RCC_CR_CSSHSEON			(1 << 19)
#define RCC_CR_HSEBYP			(1 << 18)
#define RCC_CR_HSERDY			(1 << 17)
#define RCC_CR_HSEON			(1 << 16)
#define RCC_CR_MSIRDY			(1 << 9)
#define RCC_CR_MSION			(1 << 8)
#define RCC_CR_HSI16OUTEN		(1 << 5)
#define RCC_CR_HSI16DIVF		(1 << 4)
#define RCC_CR_HSI16DIVEN		(1 << 3)
#define RCC_CR_HSI16RDY			(1 << 2)
#define RCC_CR_HSI16KERON		(1 << 1)
#define RCC_CR_HSI16ON			(1 << 0)

/* RTC prescaler */
#define RCC_CR_RTCPRE_HSE_2		(0 << 20)
#define RCC_CR_RTCPRE_HSE_4		(1 << 20)
#define RCC_CR_RTCPRE_HSE_8		(2 << 20)
#define RCC_CR_RTCPRE_HSE_16		(3 << 20)

/* --- RCC_ICSCR values ---------------------------------------------------- */

#define RCC_ICSCR_MSITRIM7		(1 << 31)
#define RCC_ICSCR_MSITRIM6		(1 << 30)
#define RCC_ICSCR_MSITRIM5		(1 << 29)
#define RCC_ICSCR_MSITRIM4		(1 << 28)
#define RCC_ICSCR_MSITRIM3		(1 << 27)
#define RCC_ICSCR_MSITRIM2		(1 << 26)
#define RCC_ICSCR_MSITRIM1		(1 << 25)
#define RCC_ICSCR_MSITRIM0		(1 << 24)
#define RCC_ICSCR_MSICAL7		(1 << 23)
#define RCC_ICSCR_MSICAL6		(1 << 22)
#define RCC_ICSCR_MSICAL5		(1 << 21)
#define RCC_ICSCR_MSICAL4		(1 << 20)
#define RCC_ICSCR_MSICAL3		(1 << 19)
#define RCC_ICSCR_MSICAL2		(1 << 18)
#define RCC_ICSCR_MSICAL1		(1 << 17)
#define RCC_ICSCR_MSICAL0		(1 << 16)
#define RCC_ICSCR_MSIRANGE2		(1 << 15)
#define RCC_ICSCR_MSIRANGE1		(1 << 14)
#define RCC_ICSCR_MSIRANGE0		(1 << 13)
#define RCC_ICSCR_HSI16TRIM4		(1 << 12)
#define RCC_ICSCR_HSI16TRIM3		(1 << 11)
#define RCC_ICSCR_HSI16TRIM2		(1 << 10)
#define RCC_ICSCR_HSI16TRIM1		(1 << 9)
#define RCC_ICSCR_HSI16TRIM0		(1 << 8)
#define RCC_ICSCR_HSI16CAL7		(1 << 7)
#define RCC_ICSCR_HSI16CAL6		(1 << 6)
#define RCC_ICSCR_HSI16CAL5		(1 << 5)
#define RCC_ICSCR_HSI16CAL4		(1 << 4)
#define RCC_ICSCR_HSI16CAL3		(1 << 3)
#define RCC_ICSCR_HSI16CAL2		(1 << 2)
#define RCC_ICSCR_HSI16CAL1		(1 << 1)
#define RCC_ICSCR_HSI16CAL0		(1 << 0)

/* MSI clock ranges */
#define RCC_ICSCR_MSIRANGE_65_536KHZ	(0 << 13)
#define RCC_ICSCR_MSIRANGE_131_072KHZ	(1 << 13)
#define RCC_ICSCR_MSIRANGE_262_144KHZ	(2 << 13)
#define RCC_ICSCR_MSIRANGE_524_288KHZ	(3 << 13)
#define RCC_ICSCR_MSIRANGE_1_048MHZ	(4 << 13)
#define RCC_ICSCR_MSIRANGE_2_097MHZ	(5 << 13)
#define RCC_ICSCR_MSIRANGE_4_194MHZ	(6 << 13)

/* --- RCC_CFGR values ----------------------------------------------------- */

#define RCC_CFGR_MCOPRE2		(1 << 30)
#define RCC_CFGR_MCOPRE1		(1 << 29)
#define RCC_CFGR_MCOPRE0		(1 << 28)
#define RCC_CFGR_MCOSEL3		(1 << 27)
#define RCC_CFGR_MCOSEL2		(1 << 26)
#define RCC_CFGR_MCOSEL1		(1 << 25)
#define RCC_CFGR_MCOSEL0		(1 << 24)
#define RCC_CFGR_PLLDIV1		(1 << 23)
#define RCC_CFGR_PLLDIV0		(1 << 22)
#define RCC_CFGR_PLLMUL3		(1 << 21)
#define RCC_CFGR_PLLMUL2		(1 << 20)
#define RCC_CFGR_PLLMUL1		(1 << 19)
#define RCC_CFGR_PLLMUL0		(1 << 18)
#define RCC_CFGR_PLLSRC			(1 << 16)
#define RCC_CFGR_STOPWUCK		(1 << 15)
#define RCC_CFGR_PPRE22			(1 << 13)
#define RCC_CFGR_PPRE21			(1 << 12)
#define RCC_CFGR_PPRE20			(1 << 11)
#define RCC_CFGR_PPRE12			(1 << 10)
#define RCC_CFGR_PPRE11			(1 << 9)
#define RCC_CFGR_PPRE10			(1 << 8)
#define RCC_CFGR_HPRE3			(1 << 7)
#define RCC_CFGR_HPRE2			(1 << 6)
#define RCC_CFGR_HPRE1			(1 << 5)
#define RCC_CFGR_HPRE0			(1 << 4)
#define RCC_CFGR_SWS1			(1 << 3)
#define RCC_CFGR_SWS0			(1 << 2)
#define RCC_CFGR_SW1			(1 << 1)
#define RCC_CFGR_SW0			(1 << 0)

/* Microcontroller clock output prescaler */
#define RCC_CFGR_MCOPRE_NODIV		(0 << 28)
#define RCC_CFGR_MCOPRE_DIV2		(1 << 28)
#define RCC_CFGR_MCOPRE_DIV4		(2 << 28)
#define RCC_CFGR_MCOPRE_DIV8		(3 << 28)
#define RCC_CFGR_MCOPRE_DIV16		(4 << 28)

/* Microcontroller clock output selection */
#define RCC_CFGR_MCOSEL_NOCLK		(0 << 24)
#define RCC_CFGR_MCOSEL_SYSCLK		(1 << 24)
#define RCC_CFGR_MCOSEL_HSI16		(2 << 24)
#define RCC_CFGR_MCOSEL_MSI		(3 << 24)
#define RCC_CFGR_MCOSEL_HSE		(4 << 24)
#define RCC_CFGR_MCOSEL_PLL		(5 << 24)
#define RCC_CFGR_MCOSEL_LSI		(6 << 24)
#define RCC_CFGR_MCOSEL_LSE		(7 << 24)

/* PLL output division */
#define RCC_CFGR_PLLDIV_DIV2		(1 << 22)
#define RCC_CFGR_PLLDIV_DIV3		(2 << 22)
#define RCC_CFGR_PLLDIV_DIV4		(3 << 22)

/* PLL multiplication factor */
#define RCC_CFGR_PLLMUL_MUL3		(0 << 18)
#define RCC_CFGR_PLLMUL_MUL4		(1 << 18)
#define RCC_CFGR_PLLMUL_MUL6		(2 << 18)
#define RCC_CFGR_PLLMUL_MUL8		(3 << 18)
#define RCC_CFGR_PLLMUL_MUL12		(4 << 18)
#define RCC_CFGR_PLLMUL_MUL16		(5 << 18)
#define RCC_CFGR_PLLMUL_MUL24		(6 << 18)
#define RCC_CFGR_PLLMUL_MUL32		(7 << 18)
#define RCC_CFGR_PLLMUL_MUL48		(8 << 18)

/* APB high-speed prescaler (APB2) */
#define RCC_CFGR_PPRE2_HCLK_NODIV	(0 << 11)
#define RCC_CFGR_PPRE2_HCLK_DIV2	(4 << 11)
#define RCC_CFGR_PPRE2_HCLK_DIV4	(5 << 11)
#define RCC_CFGR_PPRE2_HCLK_DIV8	(6 << 11)
#define RCC_CFGR_PPRE2_HCLK_DIV16	(7 << 11)

/* APB low-speed prescaler (APB1) */
#define RCC_CFGR_PPRE1_HCLK_NODIV	(0 << 8)
#define RCC_CFGR_PPRE1_HCLK_DIV2	(4 << 8)
#define RCC_CFGR_PPRE1_HCLK_DIV4	(5 << 8)
#define RCC_CFGR_PPRE1_HCLK_DIV8	(6 << 8)
#define RCC_CFGR_PPRE1_HCLK_DIV16	(7 << 8)

/* AHB prescaler */
#define RCC_CFGR_HPRE_SYSCLK_NODIV	(0 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV2	(8 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV4	(9 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV8	(10 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV16	(11 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV64	(12 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV128	(13 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV256	(14 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV512	(15 << 4)

/* System clock switch status */
#define RCC_CFGR_SWS_MSI		(0 << 2)
#define RCC_CFGR_SWS_HSI16		(1 << 2)
#define RCC_CFGR_SWS_HSE		(2 << 2)
#define RCC_CFGR_SWS_PLL		(3 << 2)

/* System clock switch */
#define RCC_CFGR_SW_MSI			(0 << 0)
#define RCC_CFGR_SW_HSI16		(1 << 0)
#define RCC_CFGR_SW_HSE			(2 << 0)
#define RCC_CFGR_SW_PLL			(3 << 0)

/* --- RCC_CIER values ----------------------------------------------------- */

#define RCC_CIER_CSSLSE			(1 << 7)
#define RCC_CIER_MSIRDYIE		(1 << 5)
#define RCC_CIER_PLLRDYIE		(1 << 4)
#define RCC_CIER_HSERDYIE		(1 << 3)
#define RCC_CIER_HSI16RDYIE		(1 << 2)
#define RCC_CIER_LSERDYIE		(1 << 1)
#define RCC_CIER_LSIRDYIE		(1 << 0)

/* --- RCC_CIFR values ----------------------------------------------------- */

#define RCC_CIFR_CSSHSEF		(1 << 8)
#define RCC_CIFR_CSSLSEF		(1 << 7)
#define RCC_CIFR_MSIRDYF		(1 << 5)
#define RCC_CIFR_PLLRDYF		(1 << 4)
#define RCC_CIFR_HSERDYF		(1 << 3)
#define RCC_CIFR_HSI16RDYF		(1 << 2)
#define RCC_CIFR_LSERDYF		(1 << 1)
#define RCC_CIFR_LSIRDYF		(1 << 0)

/* --- RCC_CICR values ----------------------------------------------------- */

#define RCC_CICR_CSSHSEC		(1 << 8)
#define RCC_CICR_CSSLSEC		(1 << 7)
#define RCC_CICR_MSIRDYC		(1 << 5)
#define RCC_CICR_PLLRDYC		(1 << 4)
#define RCC_CICR_HSERDYC		(1 << 3)
#define RCC_CICR_HSI16RDYC		(1 << 2)
#define RCC_CICR_LSERDYC		(1 << 1)
#define RCC_CICR_LSIRDYC		(1 << 0)

/* --- RCC_IOPRSTR values -------------------------------------------------- */

#define RCC_IOPRSTR_IOPHRST		(1 << 7)
#define RCC_IOPRSTR_IOPERST		(1 << 4)
#define RCC_IOPRSTR_IOPDRST		(1 << 3)
#define RCC_IOPRSTR_IOPCRST		(1 << 2)
#define RCC_IOPRSTR_IOPBRST		(1 << 1)
#define RCC_IOPRSTR_IOPARST		(1 << 0)

/* --- RCC_AHBRSTR values -------------------------------------------------- */

#define RCC_AHBRSTR_CRYPTRST		(1 << 24)
#define RCC_AHBRSTR_CRCRST		(1 << 12)
#define RCC_AHBRSTR_MIFRST		(1 << 8)
#define RCC_AHBRSTR_DMARST		(1 << 0)

/* --- RCC_APB2RSTR values ------------------------------------------------- */

#define RCC_APB2RSTR_DBGRST		(1 << 22)
#define RCC_APB2RSTR_USART1RST		(1 << 14)
#define RCC_APB2RSTR_SPI1RST		(1 << 12)
#define RCC_APB2RSTR_ADCRST		(1 << 9)
#define RCC_APB2RSTR_TIM22RST		(1 << 5)
#define RCC_APB2RSTR_TIM21RST		(1 << 2)
#define RCC_APB2RSTR_SYSCFGRST		(1 << 0)

/* --- RCC_APB1RSTR values ------------------------------------------------- */

#define RCC_APB1RSTR_LPTIM1RST		(1 << 31)
#define RCC_APB1RSTR_I2C3RST		(1 << 30)
#define RCC_APB1RSTR_PWRRST		(1 << 28)
#define RCC_APB1RSTR_I2C2RST		(1 << 22)
#define RCC_APB1RSTR_I2C1RST		(1 << 21)
#define RCC_APB1RSTR_USART5RST		(1 << 20)
#define RCC_APB1RSTR_USART4RST		(1 << 19)
#define RCC_APB1RSTR_LPUART1RST		(1 << 18)
#define RCC_APB1RSTR_USART2RST		(1 << 17)
#define RCC_APB1RSTR_SPI2RST		(1 << 14)
#define RCC_APB1RSTR_WWDGRST		(1 << 11)
#define RCC_APB1RSTR_TIM7RST		(1 << 5)
#define RCC_APB1RSTR_TIM6RST		(1 << 4)
#define RCC_APB1RSTR_TIM3RST		(1 << 1)
#define RCC_APB1RSTR_TIM2RST		(1 << 0)

/* --- RCC_IOPENR values --------------------------------------------------- */

#define RCC_IOPENR_IOPHEN		(1 << 7)
#define RCC_IOPENR_IOPEEN		(1 << 4)
#define RCC_IOPENR_IOPDEN		(1 << 3)
#define RCC_IOPENR_IOPCEN		(1 << 2)
#define RCC_IOPENR_IOPBEN		(1 << 1)
#define RCC_IOPENR_IOPAEN		(1 << 0)

/* --- RCC_AHBENR values --------------------------------------------------- */

#define RCC_AHBENR_CRYPTEN		(1 << 24)
#define RCC_AHBENR_CRCEN		(1 << 12)
#define RCC_AHBENR_MIFEN		(1 << 8)
#define RCC_AHBENR_DMAEN		(1 << 0)

/* --- RCC_APB2ENR values -------------------------------------------------- */

#define RCC_APB2ENR_DBGEN		(1 << 22)
#define RCC_APB2ENR_USART1EN		(1 << 14)
#define RCC_APB2ENR_SPI1EN		(1 << 12)
#define RCC_APB2ENR_ADCEN		(1 << 9)
#define RCC_APB2ENR_FWEN		(1 << 7)
#define RCC_APB2ENR_TIM22EN		(1 << 5)
#define RCC_APB2ENR_TIM21EN		(1 << 2)
#define RCC_APB2ENR_SYSCFGEN		(1 << 0)

/* --- RCC_APB1ENR values -------------------------------------------------- */

#define RCC_APB1ENR_LPTIM1EN		(1 << 31)
#define RCC_APB1ENR_I2C3EN		(1 << 30)
#define RCC_APB1ENR_PWREN		(1 << 28)
#define RCC_APB1ENR_I2C2EN		(1 << 22)
#define RCC_APB1ENR_I2C1EN		(1 << 21)
#define RCC_APB1ENR_USART5EN		(1 << 20)
#define RCC_APB1ENR_USART4EN		(1 << 19)
#define RCC_APB1ENR_LPUART1EN		(1 << 18)
#define RCC_APB1ENR_USART2EN		(1 << 17)
#define RCC_APB1ENR_SPI2EN		(1 << 14)
#define RCC_APB1ENR_WWDGEN		(1 << 11)
#define RCC_APB1ENR_TIM7EN		(1 << 5)
#define RCC_APB1ENR_TIM6EN		(1 << 4)
#define RCC_APB1ENR_TIM3EN		(1 << 1)
#define RCC_APB1ENR_TIM2EN		(1 << 0)

/* --- RCC_IOPSMENR values ------------------------------------------------- */

#define RCC_IOPSMENR_IOPHSMEN		(1 << 7)
#define RCC_IOPSMENR_IOPESMEN		(1 << 4)
#define RCC_IOPSMENR_IOPDSMEN		(1 << 3)
#define RCC_IOPSMENR_IOPCSMEN		(1 << 2)
#define RCC_IOPSMENR_IOPBSMEN		(1 << 1)
#define RCC_IOPSMENR_IOPASMEN		(1 << 0)

/* --- RCC_AHBSMENR values ------------------------------------------------- */

#define RCC_AHBSMENR_CRYPTSMEN		(1 << 24)
#define RCC_AHBSMENR_CRCSMEN		(1 << 12)
#define RCC_AHBSMENR_SRAMSMEN		(1 << 9)
#define RCC_AHBSMENR_MIFSMEN		(1 << 8)
#define RCC_AHBSMENR_DMASMEN		(1 << 0)

/* --- RCC_APB2SMENR values ------------------------------------------------ */

#define RCC_APB2SMENR_DBGSMEN		(1 << 22)
#define RCC_APB2SMENR_USART1SMEN	(1 << 14)
#define RCC_APB2SMENR_SPI1SMEN		(1 << 12)
#define RCC_APB2SMENR_ADCSMEN		(1 << 9)
#define RCC_APB2SMENR_TIM22SMEN		(1 << 5)
#define RCC_APB2SMENR_TIM21SMEN		(1 << 2)
#define RCC_APB2SMENR_SYSCFGSMEN	(1 << 0)

/* --- RCC_APB1SMENR values ------------------------------------------------ */

#define RCC_APB1SMENR_LPTIM1SMEN	(1 << 31)
#define RCC_APB1SMENR_I2C3SMEN		(1 << 30)
#define RCC_APB1SMENR_PWRSMEN		(1 << 28)
#define RCC_APB1SMENR_I2C2SMEN		(1 << 22)
#define RCC_APB1SMENR_I2C1SMEN		(1 << 21)
#define RCC_APB1SMENR_USART5SMEN	(1 << 20)
#define RCC_APB1SMENR_USART4SMEN	(1 << 19)
#define RCC_APB1SMENR_LPUART1SMEN	(1 << 18)
#define RCC_APB1SMENR_USART2SMEN	(1 << 17)
#define RCC_APB1SMENR_SPI2SMEN		(1 << 14)
#define RCC_APB1SMENR_WWDGSMEN		(1 << 11)
#define RCC_APB1SMENR_TIM7SMEN		(1 << 5)
#define RCC_APB1SMENR_TIM6SMEN		(1 << 4)
#define RCC_APB1SMENR_TIM3SMEN		(1 << 1)
#define RCC_APB1SMENR_TIM2SMEN		(1 << 0)

/* --- RCC_CCIPR values ---------------------------------------------------- */

#define RCC_CCIPR_LPTIM1SEL1		(1 << 19)
#define RCC_CCIPR_LPTIM1SEL0		(1 << 18)
#define RCC_CCIPR_I2C3SEL1		(1 << 17)
#define RCC_CCIPR_I2C3SEL0		(1 << 16)
#define RCC_CCIPR_I2C1SEL1		(1 << 13)
#define RCC_CCIPR_I2C1SEL0		(1 << 12)
#define RCC_CCIPR_LPUART1SEL1		(1 << 11)
#define RCC_CCIPR_LPUART1SEL0		(1 << 10)
#define RCC_CCIPR_USART2SEL1		(1 << 3)
#define RCC_CCIPR_USART2SEL0		(1 << 2)
#define RCC_CCIPR_USART1SEL1		(1 << 1)
#define RCC_CCIPR_USART1SEL0		(1 << 0)

/* Low Power Timer clock source selection bits */
#define RCC_CCIPR_LPTIM1SEL_APB		(0 << 18)
#define RCC_CCIPR_LPTIM1SEL_LSI		(1 << 18)
#define RCC_CCIPR_LPTIM1SEL_HSI16	(2 << 18)
#define RCC_CCIPR_LPTIM1SEL_LSE		(3 << 18)

/* I2C3 clock source selection bits */
#define RCC_CCIPR_I2C3SEL_APB		(0 << 16)
#define RCC_CCIPR_I2C3SEL_SYSTEM	(1 << 16)
#define RCC_CCIPR_I2C3SEL_HSI16		(2 << 16)

/* I2C1 clock source selection bits */
#define RCC_CCIPR_I2C1SEL_APB		(0 << 12)
#define RCC_CCIPR_I2C1SEL_SYSTEM	(1 << 12)
#define RCC_CCIPR_I2C1SEL_HSI16		(2 << 12)

/* LPUART1 clock source selection bits */
#define RCC_CCIPR_LPUART1SEL_APB	(0 << 10)
#define RCC_CCIPR_LPUART1SEL_SYSTEM	(1 << 10)
#define RCC_CCIPR_LPUART1SEL_HSI16	(2 << 10)
#define RCC_CCIPR_LPUART1SEL_LSE	(3 << 10)

/* USART2 clock source selection bits */
#define RCC_CCIPR_USART2SEL_APB		(0 << 2)
#define RCC_CCIPR_USART2SEL_SYSTEM	(1 << 2)
#define RCC_CCIPR_USART2SEL_HSI16	(2 << 2)
#define RCC_CCIPR_USART2SEL_LSE		(3 << 2)

/* USART1 clock source selection bits */
#define RCC_CCIPR_USART1SEL_APB		(0 << 0)
#define RCC_CCIPR_USART1SEL_SYSTEM	(1 << 0)
#define RCC_CCIPR_USART1SEL_HSI16	(2 << 0)
#define RCC_CCIPR_USART1SEL_LSE		(3 << 0)

/* --- RCC_CSR values ------------------------------------------------------ */

#define RCC_CSR_LPWRRSTF		(1 << 31)
#define RCC_CSR_WWDGRSTF		(1 << 30)
#define RCC_CSR_IWDGRSTF		(1 << 29)
#define RCC_CSR_SFTRSTF			(1 << 28)
#define RCC_CSR_PORRSTF			(1 << 27)
#define RCC_CSR_PINRSTF			(1 << 26)
#define RCC_CSR_OBLRSTF			(1 << 25)
#define RCC_CSR_FWRSTF			(1 << 24)
#define RCC_CSR_RMVF			(1 << 23)
#define RCC_CSR_RTCRST			(1 << 19)
#define RCC_CSR_RTCEN			(1 << 18)
#define RCC_CSR_RTCSEL1			(1 << 17)
#define RCC_CSR_RTCSEL0			(1 << 16)
#define RCC_CSR_CSSLSED			(1 << 14)
#define RCC_CSR_CSSLSEON		(1 << 13)
#define RCC_CSR_LSEDRV1			(1 << 12)
#define RCC_CSR_LSEDRV0			(1 << 11)
#define RCC_CSR_LSEBYP			(1 << 10)
#define RCC_CSR_LSERDY			(1 << 9)
#define RCC_CSR_LSEON			(1 << 8)
#define RCC_CSR_LSIRDY			(1 << 1)
#define RCC_CSR_LSION			(1 << 0)

/* RTC clock source selection bits */
#define RCC_CSR_RTCSEL_NONE		(0 << 16)
#define RCC_CSR_RTCSEL_LSE		(1 << 16)
#define RCC_CSR_RTCSEL_LSI		(2 << 16)
#define RCC_CSR_RTCSEL_HSE		(3 << 16)

/* LSE oscillator driving capability bits */
#define RCC_CSR_LSEDRV_LOW		(0 << 11)
#define RCC_CSR_LSEDRV_MEDIUM_LOW	(1 << 11)
#define RCC_CSR_LSEDRV_MEDIUM_HIGH	(2 << 11)
#define RCC_CSR_LSEDRV_HIGH		(3 << 11)

/* --- Function prototypes ------------------------------------------------- */

/* Oscillator (clock source) */
enum rcc_osc {
	RCC_HSE, RCC_HSI16, RCC_MSI,
	RCC_PLL,
	RCC_LSE, RCC_LSI,
	RCC_SYSCLK, RCC_HCLK, RCC_PCLK, RCC_NOCLK
};

/* MSI frequency range */
enum rcc_msi_range {
	RCC_MSI_65KHZ = (0 << 13),
	RCC_MSI_131KHZ = (1 << 13),
	RCC_MSI_262KHZ = (2 << 13),
	RCC_MSI_524KHZ = (3 << 13),
	RCC_MSI_1MHZ = (4 << 13),
	RCC_MSI_2MHZ = (5 << 13),
	RCC_MSI_4MHZ = (6 << 13),
	RCC_MSI_RANGE0 = (0 << 13),
	RCC_MSI_RANGE1 = (1 << 13),
	RCC_MSI_RANGE2 = (2 << 13),
	RCC_MSI_RANGE3 = (3 << 13),
	RCC_MSI_RANGE4 = (4 << 13),
	RCC_MSI_RANGE5 = (5 << 13),
	RCC_MSI_RANGE6 = (6 << 13)
};

/* Peripheral */
enum rcc_peripheral {
	RCC_GPIOA, RCC_GPIOB, RCC_GPIOC, RCC_GPIOD, RCC_GPIOE, RCC_GPIOH,
	RCC_DMA, RCC_MIF, RCC_SRAM, RCC_CRC, RCC_CRYPT,
	RCC_SYSCFG, RCC_TIM21, RCC_TIM22, RCC_FW, RCC_ADC, RCC_SPI1,
	RCC_USART1, RCC_DBG,
	RCC_TIM2, RCC_TIM3, RCC_TIM6, RCC_TIM7, RCC_WWDG, RCC_SPI2, RCC_USART2,
	RCC_LPUART1, RCC_USART4, RCC_USART5, RCC_I2C1, RCC_I2C2, RCC_PWR,
	RCC_I2C3, RCC_LPTIM1,
	RCC_RTC
};

/* Interrupt and status */
enum {
	RCC_LSIRDY = (1 << 0),
	RCC_LSERDY = (1 << 1),
	RCC_HSI16RDY = (1 << 2),
	RCC_HSERDY = (1 << 3),
	RCC_PLLRDY = (1 << 4),
	RCC_MSIRDY = (1 << 5),
	RCC_CSSLSE = (1 << 7),
	RCC_CSSHSE = (1 << 8)
};

/* Oscillator drive capability */
enum rcc_drive {
	RCC_LOW = (0 << 11),
	RCC_MEDIUM_LOW = (1 << 11),
	RCC_MEDIUM_HIGH = (2 << 11),
	RCC_HIGH = (3 << 11)
};

/* Reset flag */
enum {
	RCC_FIREWALL = (1 << 24),
	RCC_OPTION_BYTE = (1 << 25),
	RCC_EXTERNAL = (1 << 26),
	RCC_POR_PDR = (1 << 27),
	RCC_SOFTWARE = (1 << 28),
	RCC_IWDG_RESET = (1 << 29),
	RCC_WWDG_RESET = (1 << 30),
	RCC_LOW_POWER = (1 << 31)
};

void rcc_enable_osc(enum rcc_osc osc);
void rcc_disable_osc(enum rcc_osc osc);
void rcc_enable_css(enum rcc_osc osc);
void rcc_disable_css(enum rcc_osc osc);
int rcc_get_csson(enum rcc_osc osc);
void rcc_enable_osc_bypass(enum rcc_osc osc);
void rcc_disable_osc_bypass(enum rcc_osc osc);
void rcc_enable_hsi16_divider(void);
void rcc_disable_hsi16_divider(void);
void rcc_enable_hsi16_force(void);
void rcc_disable_hsi16_force(void);
int rcc_get_cal(enum rcc_osc osc);
void rcc_set_trim(enum rcc_osc osc, int trim);
int rcc_get_trim(enum rcc_osc osc);
void rcc_set_msi_range(enum rcc_msi_range range);
void rcc_setup_mco(enum rcc_osc src, int div);
void rcc_setup_pll(enum rcc_osc src, int mul, int div);
void rcc_set_wakeup(enum rcc_osc osc);
void rcc_set_prescaler(int ahb, int apb1, int apb2);
void rcc_set_sysclk_source(enum rcc_osc src);
enum rcc_osc rcc_get_sysclk_source(void);
void rcc_enable_interrupt(int interrupt);
void rcc_disable_interrupt(int interrupt);
int rcc_get_interrupt_mask(int interrupt);
int rcc_get_interrupt_status(int interrupt);
void rcc_clear_interrupt(int interrupt);
void rcc_enable_reset(enum rcc_peripheral peripheral);
void rcc_disable_reset(enum rcc_peripheral peripheral);
void rcc_enable_clock(enum rcc_peripheral peripheral);
void rcc_disable_clock(enum rcc_peripheral peripheral);
void rcc_enable_sleep_mode_clock(enum rcc_peripheral peripheral);
void rcc_disable_sleep_mode_clock(enum rcc_peripheral peripheral);
void rcc_set_usart1_clock(enum rcc_osc src);
void rcc_set_usart2_clock(enum rcc_osc src);
void rcc_set_lpuart1_clock(enum rcc_osc src);
void rcc_set_i2c1_clock(enum rcc_osc src);
void rcc_set_lptim1_clock(enum rcc_osc src);
void rcc_set_rtc_clock(enum rcc_osc src, int pre);
void rcc_set_lse_drive(enum rcc_drive drive);
int rcc_get_reset_flag(int flag);
void rcc_clear_reset_flag(void);
void rcc_set_i2c3_clock(enum rcc_osc src);
void rcc_enable_hsi16_tim2_etr(void);
void rcc_disable_hsi16_tim2_etr(void);
