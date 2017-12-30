/*
 * RCC functions
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

#include <stdint.h>

#include <mmio.h>
#include <memorymap.h>
#include <rcc.h>

struct regbit  {
	int reg;
	int bit;
};

static const struct regbit rstr[] = {
	{RCC_IOPRSTR, RCC_IOPRSTR_IOPARST},	 /* RCC_GPIOA */
	{RCC_IOPRSTR, RCC_IOPRSTR_IOPBRST},	 /* RCC_GPIOB */
	{RCC_IOPRSTR, RCC_IOPRSTR_IOPCRST},	 /* RCC_GPIOC */
	{RCC_IOPRSTR, RCC_IOPRSTR_IOPDRST},	 /* RCC_GPIOD */
	{RCC_IOPRSTR, RCC_IOPRSTR_IOPERST},	 /* RCC_GPIOE */
	{RCC_IOPRSTR, RCC_IOPRSTR_IOPHRST},	 /* RCC_GPIOH */
	{RCC_AHBRSTR, RCC_AHBRSTR_DMARST},	 /* RCC_DMA */
	{RCC_AHBRSTR, RCC_AHBRSTR_MIFRST},	 /* RCC_MIF */
	{0, 0},					 /* RCC_SRAM */
	{RCC_AHBRSTR, RCC_AHBRSTR_CRCRST},	 /* RCC_CRC */
	{RCC_AHBRSTR, RCC_AHBRSTR_CRYPTRST},	 /* RCC_AES */
	{RCC_APB2RSTR, RCC_APB2RSTR_SYSCFGRST},	 /* RCC_SYSCFG */
	{RCC_APB2RSTR, RCC_APB2RSTR_TIM21RST},	 /* RCC_TIM21 */
	{RCC_APB2RSTR, RCC_APB2RSTR_TIM22RST},	 /* RCC_TIM22 */
	{0, 0},					 /* RCC_FW */
	{RCC_APB2RSTR, RCC_APB2RSTR_ADCRST},	 /* RCC_ADC */
	{RCC_APB2RSTR, RCC_APB2RSTR_SPI1RST},	 /* RCC_SPI1 */
	{RCC_APB2RSTR, RCC_APB2RSTR_USART1RST},	 /* RCC_USART1 */
	{RCC_APB2RSTR, RCC_APB2RSTR_DBGRST},	 /* RCC_DBG */
	{RCC_APB1RSTR, RCC_APB1RSTR_TIM2RST},	 /* RCC_TIM2 */
	{RCC_APB1RSTR, RCC_APB1RSTR_TIM3RST},	 /* RCC_TIM3 */
	{RCC_APB1RSTR, RCC_APB1RSTR_TIM6RST},	 /* RCC_TIM6 */
	{RCC_APB1RSTR, RCC_APB1RSTR_TIM7RST},	 /* RCC_TIM7 */
	{RCC_APB1RSTR, RCC_APB1RSTR_WWDGRST},	 /* RCC_WWDG */
	{RCC_APB1RSTR, RCC_APB1RSTR_SPI2RST},	 /* RCC_SPI2 */
	{RCC_APB1RSTR, RCC_APB1RSTR_USART2RST},	 /* RCC_USART2 */
	{RCC_APB1RSTR, RCC_APB1RSTR_LPUART1RST}, /* RCC_LPUART1 */
	{RCC_APB1RSTR, RCC_APB1RSTR_USART4RST},	 /* RCC_USART4 */
	{RCC_APB1RSTR, RCC_APB1RSTR_USART5RST},	 /* RCC_USART5 */
	{RCC_APB1RSTR, RCC_APB1RSTR_I2C1RST},	 /* RCC_I2C1 */
	{RCC_APB1RSTR, RCC_APB1RSTR_I2C2RST},	 /* RCC_I2C2 */
	{RCC_APB1RSTR, RCC_APB1RSTR_PWRRST},	 /* RCC_PWR */
	{RCC_APB1RSTR, RCC_APB1RSTR_I2C3RST},	 /* RCC_I2C3 */
	{RCC_APB1RSTR, RCC_APB1RSTR_LPTIM1RST},	 /* RCC_LPTIM1 */
	{RCC_CSR, RCC_CSR_RTCRST}		 /* RCC_RTC */
};
static const struct regbit enr[] = {
	{RCC_IOPENR, RCC_IOPENR_IOPAEN},      /* RCC_GPIOA */
	{RCC_IOPENR, RCC_IOPENR_IOPBEN},      /* RCC_GPIOB */
	{RCC_IOPENR, RCC_IOPENR_IOPCEN},      /* RCC_GPIOC */
	{RCC_IOPENR, RCC_IOPENR_IOPDEN},      /* RCC_GPIOD */
	{RCC_IOPENR, RCC_IOPENR_IOPEEN},      /* RCC_GPIOE */
	{RCC_IOPENR, RCC_IOPENR_IOPHEN},      /* RCC_GPIOH */
	{RCC_AHBENR, RCC_AHBENR_DMAEN},	      /* RCC_DMA */
	{RCC_AHBENR, RCC_AHBENR_MIFEN},	      /* RCC_MIF */
	{0, 0},				      /* RCC_SRAM */
	{RCC_AHBENR, RCC_AHBENR_CRCEN},	      /* RCC_CRC */
	{RCC_AHBENR, RCC_AHBENR_CRYPTEN},     /* RCC_AES */
	{RCC_APB2ENR, RCC_APB2ENR_SYSCFGEN},  /* RCC_SYSCFG */
	{RCC_APB2ENR, RCC_APB2ENR_TIM21EN},   /* RCC_TIM21 */
	{RCC_APB2ENR, RCC_APB2ENR_TIM22EN},   /* RCC_TIM22 */
	{RCC_APB2ENR, RCC_APB2ENR_FWEN},      /* RCC_FW */
	{RCC_APB2ENR, RCC_APB2ENR_ADCEN},     /* RCC_ADC */
	{RCC_APB2ENR, RCC_APB2ENR_SPI1EN},    /* RCC_SPI1 */
	{RCC_APB2ENR, RCC_APB2ENR_USART1EN},  /* RCC_USART1 */
	{RCC_APB2ENR, RCC_APB2ENR_DBGEN},     /* RCC_DBG */
	{RCC_APB1ENR, RCC_APB1ENR_TIM2EN},    /* RCC_TIM2 */
	{RCC_APB1ENR, RCC_APB1ENR_TIM3EN},    /* RCC_TIM3 */
	{RCC_APB1ENR, RCC_APB1ENR_TIM6EN},    /* RCC_TIM6 */
	{RCC_APB1ENR, RCC_APB1ENR_TIM7EN},    /* RCC_TIM7 */
	{RCC_APB1ENR, RCC_APB1ENR_WWDGEN},    /* RCC_WWDG */
	{RCC_APB1ENR, RCC_APB1ENR_SPI2EN},    /* RCC_SPI2 */
	{RCC_APB1ENR, RCC_APB1ENR_USART2EN},  /* RCC_USART2 */
	{RCC_APB1ENR, RCC_APB1ENR_LPUART1EN}, /* RCC_LPUART1 */
	{RCC_APB1ENR, RCC_APB1ENR_USART4EN},  /* RCC_USART4 */
	{RCC_APB1ENR, RCC_APB1ENR_USART5EN},  /* RCC_USART5 */
	{RCC_APB1ENR, RCC_APB1ENR_I2C1EN},    /* RCC_I2C1 */
	{RCC_APB1ENR, RCC_APB1ENR_I2C2EN},    /* RCC_I2C2 */
	{RCC_APB1ENR, RCC_APB1ENR_PWREN},     /* RCC_PWR */
	{RCC_APB1ENR, RCC_APB1ENR_I2C3EN},    /* RCC_I2C3 */
	{RCC_APB1ENR, RCC_APB1ENR_LPTIM1EN},  /* RCC_LPTIM1 */
	{RCC_CSR, RCC_CSR_RTCEN}	      /* RCC_RTC */
};
static const struct regbit smenr[] = {
	{RCC_IOPSMENR, RCC_IOPSMENR_IOPASMEN},      /* RCC_GPIOA */
	{RCC_IOPSMENR, RCC_IOPSMENR_IOPBSMEN},      /* RCC_GPIOB */
	{RCC_IOPSMENR, RCC_IOPSMENR_IOPCSMEN},      /* RCC_GPIOC */
	{RCC_IOPSMENR, RCC_IOPSMENR_IOPDSMEN},      /* RCC_GPIOD */
	{RCC_IOPSMENR, RCC_IOPSMENR_IOPESMEN},      /* RCC_GPIOE */
	{RCC_IOPSMENR, RCC_IOPSMENR_IOPHSMEN},      /* RCC_GPIOH */
	{RCC_AHBSMENR, RCC_AHBSMENR_DMASMEN},	    /* RCC_DMA */
	{RCC_AHBSMENR, RCC_AHBSMENR_MIFSMEN},	    /* RCC_MIF */
	{RCC_AHBSMENR, RCC_AHBSMENR_SRAMSMEN},	    /* RCC_SRAM */
	{RCC_AHBSMENR, RCC_AHBSMENR_CRCSMEN},	    /* RCC_CRC */
	{RCC_AHBSMENR, RCC_AHBSMENR_CRYPTSMEN},     /* RCC_AES */
	{RCC_APB2SMENR, RCC_APB2SMENR_SYSCFGSMEN},  /* RCC_SYSCFG */
	{RCC_APB2SMENR, RCC_APB2SMENR_TIM21SMEN},   /* RCC_TIM21 */
	{RCC_APB2SMENR, RCC_APB2SMENR_TIM22SMEN},   /* RCC_TIM22 */
	{0, 0},					    /* RCC_FW */
	{RCC_APB2SMENR, RCC_APB2SMENR_ADCSMEN},     /* RCC_ADC */
	{RCC_APB2SMENR, RCC_APB2SMENR_SPI1SMEN},    /* RCC_SPI1 */
	{RCC_APB2SMENR, RCC_APB2SMENR_USART1SMEN},  /* RCC_USART1 */
	{RCC_APB2SMENR, RCC_APB2SMENR_DBGSMEN},     /* RCC_DBG */
	{RCC_APB1SMENR, RCC_APB1SMENR_TIM2SMEN},    /* RCC_TIM2 */
	{RCC_APB1SMENR, RCC_APB1SMENR_TIM3SMEN},    /* RCC_TIM3 */
	{RCC_APB1SMENR, RCC_APB1SMENR_TIM6SMEN},    /* RCC_TIM6 */
	{RCC_APB1SMENR, RCC_APB1SMENR_TIM7SMEN},    /* RCC_TIM7 */
	{RCC_APB1SMENR, RCC_APB1SMENR_WWDGSMEN},    /* RCC_WWDG */
	{RCC_APB1SMENR, RCC_APB1SMENR_SPI2SMEN},    /* RCC_SPI2 */
	{RCC_APB1SMENR, RCC_APB1SMENR_USART2SMEN},  /* RCC_USART2 */
	{RCC_APB1SMENR, RCC_APB1SMENR_LPUART1SMEN}, /* RCC_LPUART1 */
	{RCC_APB1SMENR, RCC_APB1SMENR_USART4SMEN},  /* RCC_USART4 */
	{RCC_APB1SMENR, RCC_APB1SMENR_USART5SMEN},  /* RCC_USART5 */
	{RCC_APB1SMENR, RCC_APB1SMENR_I2C1SMEN},    /* RCC_I2C1 */
	{RCC_APB1SMENR, RCC_APB1SMENR_I2C2SMEN},    /* RCC_I2C2 */
	{RCC_APB1SMENR, RCC_APB1SMENR_PWRSMEN},     /* RCC_PWR */
	{RCC_APB1SMENR, RCC_APB1SMENR_I2C3SMEN},    /* RCC_I2C3 */
	{RCC_APB1SMENR, RCC_APB1SMENR_LPTIM1SMEN},  /* RCC_LPTIM1 */
	{0, 0}					    /* RCC_RTC */
};

void rcc_enable_osc(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		MMIO32(RCC_CR) |= RCC_CR_PLLON;
		while (!(MMIO32(RCC_CR) & RCC_CR_PLLRDY))
			;
		break;
	case RCC_HSE:
		MMIO32(RCC_CR) |= RCC_CR_HSEON;
		while (!(MMIO32(RCC_CR) & RCC_CR_HSERDY))
			;
		break;
	case RCC_MSI:
		MMIO32(RCC_CR) |= RCC_CR_MSION;
		while (!(MMIO32(RCC_CR) & RCC_CR_MSIRDY))
			;
		break;
	case RCC_HSI16:
		MMIO32(RCC_CR) |= RCC_CR_HSI16ON;
		while (!(MMIO32(RCC_CR) & RCC_CR_HSI16RDY))
			;
		break;
	case RCC_LSE:
		MMIO32(RCC_CSR) |= RCC_CSR_LSEON;
		while (!(MMIO32(RCC_CSR) & RCC_CSR_LSERDY))
			;
		break;
	case RCC_LSI:
		MMIO32(RCC_CSR) |= RCC_CSR_LSION;
		while (!(MMIO32(RCC_CSR) & RCC_CSR_LSIRDY))
			;
		break;
	default:
		break;
	}
}

void rcc_disable_osc(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		MMIO32(RCC_CR) &= ~RCC_CR_PLLON;
		while (MMIO32(RCC_CR) & RCC_CR_PLLRDY)
			;
		break;
	case RCC_HSE:
		MMIO32(RCC_CR) &= ~RCC_CR_HSEON;
		while (MMIO32(RCC_CR) & RCC_CR_HSERDY)
			;
		break;
	case RCC_MSI:
		MMIO32(RCC_CR) &= ~RCC_CR_MSION;
		while (MMIO32(RCC_CR) & RCC_CR_MSIRDY)
			;
		break;
	case RCC_HSI16:
		MMIO32(RCC_CR) &= ~RCC_CR_HSI16ON;
		while (MMIO32(RCC_CR) & RCC_CR_HSI16RDY)
			;
		break;
	case RCC_LSE:
		MMIO32(RCC_CSR) &= ~RCC_CSR_LSEON;
		while (MMIO32(RCC_CSR) & RCC_CSR_LSERDY)
			;
		break;
	case RCC_LSI:
		MMIO32(RCC_CSR) &= ~RCC_CSR_LSION;
		while (MMIO32(RCC_CSR) & RCC_CSR_LSIRDY)
			;
		break;
	default:
		break;
	}
}

void rcc_enable_css(enum rcc_osc osc)
{
	if (osc == RCC_HSE)
		MMIO32(RCC_CR) |= RCC_CR_CSSHSEON;
	else if (osc == RCC_LSE)
		MMIO32(RCC_CSR) |= RCC_CSR_CSSLSEON;
}

void rcc_disable_css(enum rcc_osc osc)
{
	if (osc == RCC_HSE)
		MMIO32(RCC_CR) &= ~RCC_CR_CSSHSEON;
	else if (osc == RCC_LSE)
		MMIO32(RCC_CSR) &= ~RCC_CSR_CSSLSEON;
}

int rcc_get_csson(enum rcc_osc osc)
{
	if (osc == RCC_HSE)
		return MMIO32(RCC_CR) & RCC_CR_CSSHSEON;
	else if (osc == RCC_LSE)
		return MMIO32(RCC_CSR) & RCC_CSR_CSSLSEON;
	return 0;
}

void rcc_enable_osc_bypass(enum rcc_osc osc)
{
	if (osc == RCC_HSE)
		MMIO32(RCC_CR) |= RCC_CR_HSEBYP;
	else if (osc == RCC_LSE)
		MMIO32(RCC_CSR) |= RCC_CSR_LSEBYP;
}

void rcc_disable_osc_bypass(enum rcc_osc osc)
{
	if (osc == RCC_HSE)
		MMIO32(RCC_CR) &= ~RCC_CR_HSEBYP;
	else if (osc == RCC_LSE)
		MMIO32(RCC_CSR) &= ~RCC_CSR_LSEBYP;
}

void rcc_enable_hsi16_divider(void)
{
	MMIO32(RCC_CR) |= RCC_CR_HSI16DIVEN;
	while (!(MMIO32(RCC_CR) & RCC_CR_HSI16DIVF))
		;
}

void rcc_disable_hsi16_divider(void)
{
	MMIO32(RCC_CR) &= ~RCC_CR_HSI16DIVEN;
	while (MMIO32(RCC_CR) & RCC_CR_HSI16DIVF)
		;
}

void rcc_enable_hsi16_force(void)
{
	MMIO32(RCC_CR) |= RCC_CR_HSI16KERON;
}

void rcc_disable_hsi16_force(void)
{
	MMIO32(RCC_CR) &= ~RCC_CR_HSI16KERON;
}

int rcc_get_cal(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_MSI:
		return (MMIO32(RCC_ICSCR) >> 16) & 0xff;
	case RCC_HSI16:
		return MMIO32(RCC_ICSCR) & 0xff;
	default:
		break;
	}
	return 0;
}

void rcc_set_trim(enum rcc_osc osc, int trim)
{
	int r;

	if (osc == RCC_MSI) {
		r = MMIO32(RCC_ICSCR);
		r &= ~(0xff << 24);
		MMIO32(RCC_ICSCR) = r | (trim << 24);
	} else if (osc == RCC_HSI16) {
		r = MMIO32(RCC_ICSCR);
		r &= ~(0x1f << 8);
		MMIO32(RCC_ICSCR) = r | ((trim & 0x1f) << 8);
	}
}

int rcc_get_trim(enum rcc_osc osc)
{
	if (osc == RCC_MSI)
		return MMIO32(RCC_ICSCR) >> 24;
	else if (osc == RCC_HSI16)
		return (MMIO32(RCC_ICSCR) >> 8) & 0x1f;
	return 0;
}

void rcc_set_msi_range(enum rcc_msi_range range)
{
	int r;

	r = MMIO32(RCC_ICSCR);
	r &= ~(RCC_ICSCR_MSIRANGE2 | RCC_ICSCR_MSIRANGE1 |
	       RCC_ICSCR_MSIRANGE0);
	MMIO32(RCC_ICSCR) = r | range;
	while ((int)(MMIO32(RCC_ICSCR) & (RCC_ICSCR_MSIRANGE2 |
					  RCC_ICSCR_MSIRANGE1 |
					  RCC_ICSCR_MSIRANGE0)) != range)
		;
}

void rcc_setup_mco(enum rcc_osc src, int div)
{
	int mcosel;
	int i;
	int mcopre;
	int r;

	switch (src) {
	case RCC_NOCLK:
		mcosel = RCC_CFGR_MCOSEL_NOCLK;
		break;
	case RCC_SYSCLK:
		mcosel = RCC_CFGR_MCOSEL_SYSCLK;
		break;
	case RCC_HSI16:
		mcosel = RCC_CFGR_MCOSEL_HSI16;
		break;
	case RCC_MSI:
		mcosel = RCC_CFGR_MCOSEL_MSI;
		break;
	case RCC_HSE:
		mcosel = RCC_CFGR_MCOSEL_HSE;
		break;
	case RCC_PLL:
		mcosel = RCC_CFGR_MCOSEL_PLL;
		break;
	case RCC_LSI:
		mcosel = RCC_CFGR_MCOSEL_LSI;
		break;
	case RCC_LSE:
		mcosel = RCC_CFGR_MCOSEL_LSE;
		break;
	default:
		return;
	}
	for (i = 0; i < 5; i++) {
		if (div == 1 << i)
			break;
	}
	if (i >= 5)
		return;
	mcopre = i << 28;
	r = MMIO32(RCC_CFGR);
	r &= ~(RCC_CFGR_MCOPRE2 | RCC_CFGR_MCOPRE1 | RCC_CFGR_MCOPRE0 |
	       RCC_CFGR_MCOSEL3 | RCC_CFGR_MCOSEL2 | RCC_CFGR_MCOSEL1 |
	       RCC_CFGR_MCOSEL0);
	MMIO32(RCC_CFGR) = r | mcopre | mcosel;
}

void rcc_setup_pll(enum rcc_osc src, int mul, int div)
{
	int i;
	static const int m[9] = {3, 4, 6, 8, 12, 16, 24, 32, 48};
	int r;

	if (src != RCC_HSI16 && src != RCC_HSE)
		return;
	if (div < 2 || div > 4)
		return;
	for (i = 0; i < 9 && mul != m[i]; i++)
		;
	if (i >= 9)
		return;
	r = MMIO32(RCC_CFGR);
	r &= ~(RCC_CFGR_PLLDIV1 | RCC_CFGR_PLLDIV0 |
	       RCC_CFGR_PLLMUL3 | RCC_CFGR_PLLMUL2 | RCC_CFGR_PLLMUL1 |
	       RCC_CFGR_PLLMUL0 |
	       RCC_CFGR_PLLSRC);
	if (src == RCC_HSE)
		r |= RCC_CFGR_PLLSRC;
	MMIO32(RCC_CFGR) = r | (div - 1) << 22 | i << 18;
}

void rcc_set_wakeup(enum rcc_osc osc)
{
	if (osc == RCC_MSI)
		MMIO32(RCC_CFGR) &= ~RCC_CFGR_STOPWUCK;
	else if (osc == RCC_HSI16)
		MMIO32(RCC_CFGR) |= RCC_CFGR_STOPWUCK;
}

void rcc_set_prescaler(int ahb, int apb1, int apb2)
{
	int x;
	int i;
	int hpre;
	int ppre1;
	int ppre2;
	int r;

	x = 7;
	for (i = 7; i < 16 && ahb != 1 << (i - x); i++) {
		if (i == 11)
			x = 6;
	}
	if (i >= 16)
		return;
	if (i == 7)
		i = 0;
	hpre = i << 4;
	for (i = 3; i < 8 && apb1 != 1 << (i - 3); i++)
		;
	if (i >= 8)
		return;
	if (i == 3)
		i = 0;
	ppre1 = i << 8;
	for (i = 3; i < 8 && apb2 != 1 << (i - 3); i++)
		;
	if (i >= 8)
		return;
	if (i == 3)
		i = 0;
	ppre2 = i << 11;
	r = MMIO32(RCC_CFGR);
	r &= ~(RCC_CFGR_PPRE22 | RCC_CFGR_PPRE21 | RCC_CFGR_PPRE20 |
	       RCC_CFGR_PPRE12 | RCC_CFGR_PPRE11 | RCC_CFGR_PPRE10 |
	       RCC_CFGR_HPRE3 | RCC_CFGR_HPRE2 | RCC_CFGR_HPRE1 |
	       RCC_CFGR_HPRE0);
	MMIO32(RCC_CFGR) = r | ppre2 | ppre1 | hpre;
	while ((int)(MMIO32(RCC_CFGR) & (RCC_CFGR_PPRE22 | RCC_CFGR_PPRE21 |
					 RCC_CFGR_PPRE20 |
					 RCC_CFGR_PPRE12 | RCC_CFGR_PPRE11 |
					 RCC_CFGR_PPRE10 |
					 RCC_CFGR_HPRE3 | RCC_CFGR_HPRE2 |
					 RCC_CFGR_HPRE1 | RCC_CFGR_HPRE0)) !=
	       (ppre2 | ppre1 | hpre))
		;
}

void rcc_set_sysclk_source(enum rcc_osc src)
{
	int clk;
	int r;

	switch (src) {
	case RCC_MSI:
		clk = RCC_CFGR_SW_MSI;
		break;
	case RCC_HSI16:
		clk = RCC_CFGR_SW_HSI16;
		break;
	case RCC_HSE:
		clk = RCC_CFGR_SW_HSE;
		break;
	case RCC_PLL:
		clk = RCC_CFGR_SW_PLL;
		break;
	default:
		return;
	}
	r = MMIO32(RCC_CFGR);
	r &= ~(RCC_CFGR_SW1 | RCC_CFGR_SW0);
	MMIO32(RCC_CFGR) = r | clk;
	while ((int)(MMIO32(RCC_CFGR) & (RCC_CFGR_SWS1 | RCC_CFGR_SWS0)) >> 2
	       != clk)
		;
}

enum rcc_osc rcc_get_sysclk_source(void)
{
	switch (MMIO32(RCC_CFGR) & (RCC_CFGR_SWS1 | RCC_CFGR_SWS0)) {
	case RCC_CFGR_SWS_MSI:
		return RCC_MSI;
	case RCC_CFGR_SWS_HSI16:
		return RCC_HSI16;
	case RCC_CFGR_SWS_HSE:
		return RCC_HSE;
	case RCC_CFGR_SWS_PLL:
		return RCC_PLL;
	default:
		break;
	}
	return RCC_MSI;
}

void rcc_enable_interrupt(int interrupt)
{
	MMIO32(RCC_CIER) |= interrupt & 0xff;
}

void rcc_disable_interrupt(int interrupt)
{
	MMIO32(RCC_CIER) &= ~(interrupt & 0xff);
}

int rcc_get_interrupt_mask(int interrupt)
{
	return MMIO32(RCC_CIER) & interrupt;
}

int rcc_get_interrupt_status(int interrupt)
{
	return MMIO32(RCC_CIFR) & interrupt;
}

void rcc_clear_interrupt(int interrupt)
{
	MMIO32(RCC_CICR) |= interrupt & 0x1ff;
}

void rcc_enable_reset(enum rcc_peripheral peripheral)
{
	if (rstr[peripheral].bit)
		MMIO32(rstr[peripheral].reg) |= rstr[peripheral].bit;
}

void rcc_disable_reset(enum rcc_peripheral peripheral)
{
	if (rstr[peripheral].bit)
		MMIO32(rstr[peripheral].reg) &= ~rstr[peripheral].bit;
}

void rcc_enable_clock(enum rcc_peripheral peripheral)
{
	if (enr[peripheral].bit)
		MMIO32(enr[peripheral].reg) |= enr[peripheral].bit;
}

void rcc_disable_clock(enum rcc_peripheral peripheral)
{
	if (enr[peripheral].bit)
		MMIO32(enr[peripheral].reg) &= ~enr[peripheral].bit;
}

void rcc_enable_sleep_mode_clock(enum rcc_peripheral peripheral)
{
	if (smenr[peripheral].bit)
		MMIO32(smenr[peripheral].reg) |= smenr[peripheral].bit;
}

void rcc_disable_sleep_mode_clock(enum rcc_peripheral peripheral)
{
	if (smenr[peripheral].bit)
		MMIO32(smenr[peripheral].reg) &= ~smenr[peripheral].bit;
}

void rcc_set_usart1_clock(enum rcc_osc src)
{
	int clk;
	int r;

	switch (src) {
	case RCC_PCLK:
		clk = RCC_CCIPR_USART1SEL_APB;
		break;
	case RCC_SYSCLK:
		clk = RCC_CCIPR_USART1SEL_SYSTEM;
		break;
	case RCC_HSI16:
		clk = RCC_CCIPR_USART1SEL_HSI16;
		break;
	case RCC_LSE:
		clk = RCC_CCIPR_USART1SEL_LSE;
		break;
	default:
		return;
	}
	r = MMIO32(RCC_CCIPR);
	r &= ~(RCC_CCIPR_USART1SEL1 | RCC_CCIPR_USART1SEL0);
	MMIO32(RCC_CCIPR) = r | clk;
}

void rcc_set_usart2_clock(enum rcc_osc src)
{
	int clk;
	int r;

	switch (src) {
	case RCC_PCLK:
		clk = RCC_CCIPR_USART2SEL_APB;
		break;
	case RCC_SYSCLK:
		clk = RCC_CCIPR_USART2SEL_SYSTEM;
		break;
	case RCC_HSI16:
		clk = RCC_CCIPR_USART2SEL_HSI16;
		break;
	case RCC_LSE:
		clk = RCC_CCIPR_USART2SEL_LSE;
		break;
	default:
		return;
	}
	r = MMIO32(RCC_CCIPR);
	r &= ~(RCC_CCIPR_USART2SEL1 | RCC_CCIPR_USART2SEL0);
	MMIO32(RCC_CCIPR) = r | clk;
}

void rcc_set_lpuart1_clock(enum rcc_osc src)
{
	int clk;
	int r;

	switch (src) {
	case RCC_PCLK:
		clk = RCC_CCIPR_LPUART1SEL_APB;
		break;
	case RCC_SYSCLK:
		clk = RCC_CCIPR_LPUART1SEL_SYSTEM;
		break;
	case RCC_HSI16:
		clk = RCC_CCIPR_LPUART1SEL_HSI16;
		break;
	case RCC_LSE:
		clk = RCC_CCIPR_LPUART1SEL_LSE;
		break;
	default:
		return;
	}
	r = MMIO32(RCC_CCIPR);
	r &= ~(RCC_CCIPR_LPUART1SEL1 | RCC_CCIPR_LPUART1SEL0);
	MMIO32(RCC_CCIPR) = r | clk;
}

void rcc_set_i2c1_clock(enum rcc_osc src)
{
	int clk;
	int r;

	switch (src) {
	case RCC_PCLK:
		clk = RCC_CCIPR_I2C1SEL_APB;
		break;
	case RCC_SYSCLK:
		clk = RCC_CCIPR_I2C1SEL_SYSTEM;
		break;
	case RCC_HSI16:
		clk = RCC_CCIPR_I2C1SEL_HSI16;
		break;
	default:
		return;
	}
	r = MMIO32(RCC_CCIPR);
	r &= ~(RCC_CCIPR_I2C1SEL1 | RCC_CCIPR_I2C1SEL0);
	MMIO32(RCC_CCIPR) = r | clk;
}

void rcc_set_lptim1_clock(enum rcc_osc src)
{
	int clk;
	int r;

	switch (src) {
	case RCC_PCLK:
		clk = RCC_CCIPR_LPTIM1SEL_APB;
		break;
	case RCC_LSI:
		clk = RCC_CCIPR_LPTIM1SEL_LSI;
		break;
	case RCC_HSI16:
		clk = RCC_CCIPR_LPTIM1SEL_HSI16;
		break;
	case RCC_LSE:
		clk = RCC_CCIPR_LPTIM1SEL_LSE;
		break;
	default:
		return;
	}
	r = MMIO32(RCC_CCIPR);
	r &= ~(RCC_CCIPR_LPTIM1SEL1 | RCC_CCIPR_LPTIM1SEL0);
	MMIO32(RCC_CCIPR) = r | clk;
}

void rcc_set_rtc_clock(enum rcc_osc src, int pre)
{
	int clk;
	int i;
	int r;

	switch (src) {
	case RCC_NOCLK:
		clk = RCC_CSR_RTCSEL_NONE;
		break;
	case RCC_LSE:
		clk = RCC_CSR_RTCSEL_LSE;
		break;
	case RCC_LSI:
		clk = RCC_CSR_RTCSEL_LSI;
		break;
	case RCC_HSE:
		clk = RCC_CSR_RTCSEL_HSE;
		break;
	default:
		return;
	}
	if (src == RCC_HSE) {
		for (i = 0; i < 4 && pre != 1 << (i + 1); i++)
			;
		if (i >= 4)
			return;
		r = MMIO32(RCC_CR);
		r &= ~(RCC_CR_RTCPRE1 | RCC_CR_RTCPRE0);
		MMIO32(RCC_CR) = r | i << 20;
	}
	r = MMIO32(RCC_CSR);
	r &= ~(RCC_CSR_RTCSEL1 | RCC_CSR_RTCSEL0);
	MMIO32(RCC_CSR) = r | clk;
}

void rcc_set_lse_drive(enum rcc_drive drive)
{
	int r;

	r = MMIO32(RCC_CSR);
	r &= ~(RCC_CSR_LSEDRV1 | RCC_CSR_LSEDRV0);
	MMIO32(RCC_CSR) = r | drive;
}

int rcc_get_reset_flag(int flag)
{
	return MMIO32(RCC_CSR) & flag;
}

void rcc_clear_reset_flag(void)
{
	MMIO32(RCC_CSR) |= RCC_CSR_RMVF;
}

void rcc_set_i2c3_clock(enum rcc_osc src)
{
	int clk;
	int r;

	switch (src) {
	case RCC_PCLK:
		clk = RCC_CCIPR_I2C3SEL_APB;
		break;
	case RCC_SYSCLK:
		clk = RCC_CCIPR_I2C3SEL_SYSTEM;
		break;
	case RCC_HSI16:
		clk = RCC_CCIPR_I2C3SEL_HSI16;
		break;
	default:
		return;
	}
	r = MMIO32(RCC_CCIPR);
	r &= ~(RCC_CCIPR_I2C3SEL1 | RCC_CCIPR_I2C3SEL0);
	MMIO32(RCC_CCIPR) = r | clk;
}

void rcc_enable_hsi16_tim2_etr(void)
{
	MMIO32(RCC_CR) |= RCC_CR_HSI16OUTEN;
}

void rcc_disable_hsi16_tim2_etr(void)
{
	MMIO32(RCC_CR) &= ~RCC_CR_HSI16OUTEN;
}
