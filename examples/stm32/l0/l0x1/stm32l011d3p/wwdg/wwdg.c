/*
 * wwdg - Test WWDG.
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
#include <nvic.h>
#include <vector.h>
#include <wwdg.h>

#define PCLK1		32000000 /* PCLK1 frequency */
#define CK250MS		(PCLK1 / 1000 * 250 / 4096) /* 250 ms */
#define CK500MS		(PCLK1 / 1000 * 500 / 4096) /* 500 ms */

extern char end;		/* The end of BSS segment */
char * const testnum = &end;	/* Test number */
char * const state = &end + 1;	/* Test state */
volatile int isr_reload;	/* reload value */


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

/* TIM2: CK_CNT = PCLK1 / (4096 / 2) */
static void tim_setup(void)
{
	rcc_enable_clock(RCC_TIM2);
	tim_enable_one_pulse_mode(TIM2);
	tim_disable_update_interrupt_on_any(TIM2);
	tim_load_prescaler(TIM2, 4096 / 2);
}

static void wwdg_setup(void)
{
	rcc_enable_clock(RCC_WWDG);
	nvic_enable_irq(NVIC_WWDG);
}

/* Delay: 1 - 32768 (PCLK1 / 4096) */
static void delay_ck(int ck)
{
	tim_set_autoreload(TIM2, ck << 1);
	tim_enable_counter(TIM2);
	while (!tim_get_interrupt_status(TIM2, TIM_UPDATE))
		;
	tim_clear_interrupt(TIM2, TIM_UPDATE);
}

void wwdg_isr(void)
{
	if (wwdg_get_interrupt_mask(WWDG_EARLY_WAKEUP) &&
	    wwdg_get_interrupt_status(WWDG_EARLY_WAKEUP)) {
		if (isr_reload)
			wwdg_reload(isr_reload);
		wwdg_clear_interrupt(WWDG_EARLY_WAKEUP);
	}
}

static void blink_led(int n)
{
	int i;

	delay_ck(CK250MS);
	for (i = 0; i < n; i++) {
		gpio_clear(GPIO_PA0);
		delay_ck(CK250MS);
		gpio_set(GPIO_PA0);
		delay_ck(CK250MS);
	}
	delay_ck(CK250MS);
}

static void watchdog_test(int prescaler, int count)
{
	int n;
	int i;

	n = PCLK1 / (4096 * prescaler * (count - 2));
	*state = 0;
	gpio_clear(GPIO_PA1);
	wwdg_set_window(prescaler, 63);
	wwdg_reload(count);
	for (i = 0; i < n; i++) {
		delay_ck((count - 2) * prescaler);
		wwdg_reload(count);
	}
	*state = 1;
	gpio_set(GPIO_PA1);
	delay_ck((count + 1) * prescaler);
	*state = 2;
	gpio_clear(GPIO_PA1);
}

static void window_test(int prescaler, int count, int window)
{
	int n;
	int i;

	n = PCLK1 / (4096 * prescaler * (count - window - 1));
	*state = 0;
	gpio_clear(GPIO_PA1);
	wwdg_set_window(prescaler, window);
	wwdg_reload(count);
	for (i = 0; i < n; i++) {
		delay_ck((count - window - 1) * prescaler);
		wwdg_reload(count);
	}
	*state = 1;
	gpio_set(GPIO_PA1);
	delay_ck((count - window - 3) * prescaler);
	wwdg_reload(count);
	delay_ck(1);
	*state = 2;
	gpio_clear(GPIO_PA1);
}

static void ewi_test(int prescaler, int count)
{
	int n;
	int i;

	n = PCLK1 / (4096 * prescaler * (count - 2));
	*state = 0;
	gpio_clear(GPIO_PA1);
	wwdg_set_window(prescaler, 63);
	isr_reload = count;
	wwdg_enable_interrupt(WWDG_EARLY_WAKEUP);
	wwdg_reload(count);
	for (i = 0; i < n; i++)
		__asm__ ("wfi");
	*state = 1;
	gpio_set(GPIO_PA1);
	isr_reload = 0;
	delay_ck((count + 1) * prescaler);
	*state = 2;
	gpio_clear(GPIO_PA1);
}

int main(void)
{
	int s;
	
	clock_setup();
	gpio_setup();
	tim_setup();
	wwdg_setup();

	s = rcc_get_reset_flag(RCC_POR_PDR | RCC_WWDG_RESET);
	rcc_clear_reset_flag();
	if (s & RCC_POR_PDR) {
		*testnum = 1;
	} else if (s & RCC_WWDG_RESET) {
		if (*state != 1)
			goto wwdg_error;
		(*testnum)++;
	} else {
		goto wwdg_error;
	}
	if (*testnum > 8)
		*testnum = 1;
	switch (*testnum) {
	case 1:
		blink_led(1);
		watchdog_test(1, 64);
		break;
	case 2:
		blink_led(2);
		watchdog_test(1, 4);
		break;
	case 3:
		blink_led(3);
		watchdog_test(8, 64);
		break;
	case 4:
		blink_led(4);
		watchdog_test(8, 4);
		break;
	case 5:
		blink_led(5);
		window_test(1, 64, 60);
		break;
	case 6:
		blink_led(6);
		window_test(1, 64, 4);
		break;
	case 7:
		blink_led(7);
		window_test(8, 8, 4);
		break;
	case 8:
		blink_led(8);
		ewi_test(1, 64);
		break;
	default:
		break;
	}

wwdg_error:
	while (1) {
		gpio_toggle(GPIO_PA0);
		delay_ck(CK500MS);
	}

	return 0;
}
