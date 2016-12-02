/*
 * iwdg - Test IWDG.
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
#include <iwdg.h>

/*
 * ## Measurement ##
 *
 *    <-- t -->
 *    _________
 *  _|         |_
 * ^ ^         ^
 * a b         c
 *
 * a: iwdg_start()
 * b: gpio_set()
 * c: IWDG RESET
 *
 * prescaler	reload	t
 * 4		0	 543 us
 * 4		1	 650 us
 * 4		2	 755 us
 * 4		3	 860 us
 * 4		4	 967 us
 * 4		5	1073 us
 * 256		0	34.0 ms
 * 256		1	40.7 ms
 * 256		2	47.5 ms
 * 256		3	54.3 ms
 * 256		4	61.0 ms
 * 256		5	67.8 ms
 */
/*
 * ## My guess ##
 *
 * IWDG CLOCK                _   _   _   _   _   _     _   _   _
 * f = fLSI / prescaler    _| |_| |_| |_| |_| |_| ... | |_| |_|
 *
 * counter                                  |N-1| ... | 1 | 0 |
 *                                                             _
 * IWDG RESET                                                _|
 *                         ^ iwdg_reload()
 *                           <-- t_sync  -->  4-5 clocks
 */
/*
 * t_clk:				(1 / fLSI) * prescaler
 * t_sync:				t_clk * (4 or 5)
 * t_reset:	reload to RESET:	t_clk * N + t_sync
 * t_timeout:	max. reload interval:	t_clk * (N + ((-1) to 1))
 * t_win:	min. reload interval:	t_clk * (N - W - 1 + ((-1) to 1))
 */

#define FLSIMAX			56 /* 56 kHz */
#define FLSIMIN			26 /* 26 kHz */
#define TIMX_CLK_APB1		32000000 /* TIM2 clock frequency */
#define TIMX_CLK_APB2		32000000 /* TIM21 clock frequency */

extern char end;		/* The end of BSS segment */
char * const testnum = &end;	/* Test number */
char * const state = &end + 1;	/* Test state */

/*
 * Clock
 * PLL: 16 MHz * 4 / 2 = 32 MHz
 * SYSCLK	32 MHz
 * HCLK		32 MHz (AHB)
 * PCLK1	32 MHz (APB1)
 * PCLK2	32 MHz (APB2)
 * LSI -> IWDG
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

	rcc_enable_osc(RCC_LSI);
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
	tim_enable_one_pulse_mode(TIM2);
	tim_disable_update_interrupt_on_any(TIM2);
	tim_load_prescaler(TIM2, TIMX_CLK_APB1 / 2000000);

	rcc_enable_clock(RCC_TIM21);
	tim_enable_one_pulse_mode(TIM21);
	tim_disable_update_interrupt_on_any(TIM21);
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

static void blink_led(int n)
{
	int i;

	delay_ms(250);
	for (i = 0; i < n; i++) {
		gpio_clear(GPIO_PA0);
		delay_ms(250);
		gpio_set(GPIO_PA0);
		delay_ms(250);
	}
	delay_ms(250);
}

static void watchdog_test(int prescaler, int count)
{
	int ttimeout;
	int ttimeout_ms;
	int n;
	int treset;
	int treset_ms;
	int i;
	int m;

	ttimeout = prescaler * (count - 1) * 1000 / FLSIMAX * 9 / 10;
	ttimeout_ms = ttimeout / 1000;
	n = 1000000 / ttimeout;
	if (n == 0)
		n = 1;
	treset = prescaler * (count + 5) * 1000 / FLSIMIN * 11 / 10;
	treset_ms = (treset + 999) / 1000;
	*state = 0;
	gpio_clear(GPIO_PA1);
	iwdg_start(prescaler, count, 0);
	for (i = 0; i < n; i++) {
		if (ttimeout < 32768) {
			delay_us(ttimeout);
		} else if (ttimeout_ms < 1000) {
			delay_ms(ttimeout_ms);
		} else {
			for (m = ttimeout_ms; m > 1000; m -= 1000) {
				gpio_toggle(GPIO_PA0);
				delay_ms(1000);
			}
			gpio_set(GPIO_PA0);
			if (m)
				delay_ms(m);
		}
		iwdg_reload();
	}

	*state = 1;
	gpio_set(GPIO_PA1);
	if (treset < 32768) {
		delay_us(treset);
	} else if (treset_ms < 1000) {
		delay_ms(treset_ms);
	} else {
		for (m = treset_ms; m > 1000; m -= 1000) {
			gpio_toggle(GPIO_PA0);
			delay_ms(1000);
		}
		gpio_set(GPIO_PA0);
		if (m)
			delay_ms(m);
	}

	*state = 2;
	gpio_clear(GPIO_PA1);
}

static void window_test(int prescaler, int count, int window)
{
	int tsync;
	int tsync_ms;
	int twin;
	int twin_ms;
	int n;
	int i;
	int m;
	
	tsync = prescaler * 5 * 1000 * 11 / (FLSIMIN * 10);
	tsync_ms = (tsync + 999) / 1000;
	twin = prescaler * (count - window) * 1000 / FLSIMIN * 11 / 10;
	twin_ms = (twin + 999) / 1000;
	n = 1000000 / twin;
	if (n == 0)
		n = 1;
	*state = 0;
	gpio_clear(GPIO_PA1);
	iwdg_start(prescaler, count, window);
	for (i = 0; i < n; i++) {
		if (twin < 32768) {
			delay_us(twin);
		} else if (twin_ms < 1000) {
			delay_ms(twin_ms);
		} else {
			for (m = twin_ms; m > 1000; m -= 1000) {
				gpio_toggle(GPIO_PA0);
				delay_ms(1000);
			}
			gpio_set(GPIO_PA0);
			if (m)
				delay_ms(m);
		}
		iwdg_reload();
	}

	*state = 1;
	gpio_set(GPIO_PA1);
	if (tsync < 32768)
		delay_us(tsync);
	else
		delay_ms(tsync_ms);
	iwdg_reload();
	if (tsync < 32768)
		delay_us(tsync);
	else
		delay_ms(tsync_ms);

	*state = 2;
	gpio_clear(GPIO_PA1);
}

/*
 * TESTNUM: 5
 * prescaler = 4, count = 4096, window = 2560
 *
 *			min(us)		max(us)
 * t_clk		        71	       154
 * t_sync		       286	       769
 * t_reset		    292857	    630923
 * t_timeout		    292500	    630308
 * t_win		    109571	    236308
 *
 *
 * TESTNUM: 6
 * prescaler = 4, count = 64, window = 40
 *
 *			min(us)		max(us)
 * t_clk		        71	       154
 * t_sync		       286	       769
 * t_reset		      4857	     10615
 * t_timeout		      4500	     10000
 * t_win		      1571	      3692
 *
 *
 * TESTNUM: 7
 * prescaler = 256, count = 64, window = 40
 *
 *			min(us)		max(us)
 * t_clk		      4571	      9846
 * t_sync		     18286	     49231
 * t_reset		    310857	    679385
 * t_timeout		    288000	    640000
 * t_win		    100571	    236308
 *
 *
 * TESTNUM: 8
 * prescaler = 256, count = 4096, window = 2560
 *
 *			min(us)		max(us)
 * t_clk		      4571	      9846
 * t_sync		     18286	     49231
 * t_reset		  18742857	  40379077
 * t_timeout		  18720000	  40339692
 * t_win		   7012571	  15123692
 */
int main(void)
{
	int s;
	
	clock_setup();
	gpio_setup();
	tim_setup();

	s = rcc_get_reset_flag(RCC_POR_PDR | RCC_IWDG_RESET);
	rcc_clear_reset_flag();
	if (s & RCC_POR_PDR) {
		*testnum = 1;
	} else if (s & RCC_IWDG_RESET) {
		if (*state != 1)
			goto iwdg_error;
		(*testnum)++;
	} else {
		goto iwdg_error;
	}
	if (*testnum > 8)
		*testnum = 1;
	switch (*testnum) {
	case 1:
		blink_led(1);
		watchdog_test(4, 4096);
		break;
	case 2:
		blink_led(2);
		watchdog_test(4, 8);
		break;
	case 3:
		blink_led(3);
		watchdog_test(256, 8);
		break;
	case 4:
		blink_led(4);
		watchdog_test(256, 4096);
		break;
	case 5:
		blink_led(5);
		window_test(4, 4096, 2560);
		break;
	case 6:
		blink_led(6);
		window_test(4, 64, 40);
		break;
	case 7:
		blink_led(7);
		window_test(256, 64, 40);
		break;
	case 8:
		blink_led(8);
		window_test(256, 4096, 2560);
		break;
	default:
		break;
	}

iwdg_error:
	while (1) {
		gpio_toggle(GPIO_PA0);
		delay_ms(500);
	}

	return 0;
}
