/*
 * rtc - A simple clock.
 *
 * rtc.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of rtc.
 *
 * rtc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rtc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rtc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <nvic.h>
#include <vector.h>
#include <usart.h>
#include <exti.h>
#include <rtc.h>

#include "rtc.h"

#define FCK		32000000 /* USART clock frequency */
#define TXBUFSIZE	32	 /* Tx buffer size (power of 2) */
#define RXBUFSIZE	32	 /* Rx buffer size (power of 2) */

/* Tx buffer */
static volatile int tx_buf[TXBUFSIZE];
static volatile int tx_len;
/* Rx buffer */
static volatile int rx_buf[RXBUFSIZE];
static volatile int rx_len;

/*
 * Clock
 * PLL: 16 MHz * 4 / 2 = 32 MHz
 * SYSCLK	32 MHz
 * HCLK		32 MHz (AHB)
 * PCLK1	32 MHz (APB1)
 * PCLK2	32 MHz (APB2)
 * LSE -> RTC
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

	pwr_disable_backup_write_protection();
	rcc_enable_osc(RCC_LSE);
}	

/*
 * GPIO
 * PA0: output		LED
 * PA9: USART2_TX
 * PA10: USART2_RX
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA0);
	gpio_config(GPIO_AF4, 0, GPIO_PA(9, 10));
}

/* USART2: 115200 8N1, interrupt */
static void usart_setup(void)
{
	rcc_enable_clock(RCC_USART2);
	nvic_enable_irq(NVIC_USART2);
	usart_enable_interrupt(USART2, USART_RXNE);
	usart_init(USART2, FCK, 115200, 8, USART_STOP_1, USART_PARITY_NONE,
		   USART_FLOW_NONE, USART_TX_RX);
}

/* EXTI20: RTC wakeup timer event */
static void exti_setup(void)
{
	nvic_enable_irq(NVIC_RTC);
	exti_set_trigger(EXTI_RTC_WAKEUP_TIMER, EXTI_RISING);
	exti_enable_interrupt(EXTI_RTC_WAKEUP_TIMER);
}

/* RTC: wakeup: 1 Hz */
static void rtc_setup(void)
{
	rcc_set_rtc_clock(RCC_LSE, 0);
	rcc_enable_clock(RCC_RTC);
	rtc_unlock();
	rtc_init(PREDIV_A, PREDIV_S, 0x00012101, 0x00000000, false, false);
	rtc_enable_interrupt(RTC_WAKEUP);
	rtc_enable_wakeup_timer(RTC_CK_SPRE, 1 - 1);
	rtc_lock();
}

void usart2_isr(void)
{
	int m;
	int s;
	static int rx_wp;
	static int tx_rp;

	m = usart_get_interrupt_mask(USART2, USART_RXNE | USART_TXE);
	s = usart_get_interrupt_status(USART2, USART_RXNE | USART_TXE);
	if (m & s & USART_RXNE) {
		if (rx_len < RXBUFSIZE) {
			rx_buf[rx_wp++] = usart_recv(USART2);
			rx_wp &= RXBUFSIZE - 1;
			rx_len++;
		} else {
			usart_flush_receive_data(USART2);
		}
	}
	if (m & s & USART_TXE) {
		if (tx_len) {
			usart_send(USART2, tx_buf[tx_rp++]);
			tx_rp &= TXBUFSIZE - 1;
			tx_len--;
	        } else {
			usart_disable_interrupt(USART2, USART_TXE);
		}
	}
}

void tx_write_blocking(int data)
{
	static int tx_wp;

	while (tx_len == TXBUFSIZE)
		;
	usart_disable_interrupt(USART2, USART_TXE);
	tx_buf[tx_wp++] = data;
	tx_wp &= TXBUFSIZE - 1;
	tx_len++;
	usart_enable_interrupt(USART2, USART_TXE);
}

int rx_read_blocking(void)
{
	int r;
	static int rx_rp;
	
	while (rx_len == 0)
		;
	usart_disable_interrupt(USART2, USART_RXNE);
	r = rx_buf[rx_rp++];
	rx_rp &= RXBUFSIZE - 1;
	rx_len--;
	usart_enable_interrupt(USART2, USART_RXNE);
	return r;
}

void rtc_isr(void)
{
	if (exti_get_interrupt_status(EXTI_RTC_WAKEUP_TIMER)) {
		if (rtc_get_interrupt_status(RTC_WAKEUP)) {
			gpio_toggle(GPIO_PA0);
			rtc_clear_interrupt(RTC_WAKEUP);
		}
		exti_clear_interrupt(EXTI_RTC_WAKEUP_TIMER);
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	usart_setup();
	exti_setup();
	rtc_setup();
	
	command();

	return 0;
}
