/*
 * lpuart_getchar - Use newlib functions.
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
#include <ctype.h>
#include <string.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <nvic.h>
#include <vector.h>
#include <lpuart.h>

#include "stdio.h"

#define FCK		32000000 /* LPUART clock frequency */
#define BUFSIZE		32	 /* Line buffer size */
#define TXBUFSIZE	32	 /* power of 2 */
#define RXBUFSIZE	32	 /* power of 2 */
#define DELIMITER	" /.,;:-" /* Separator characters */

volatile int tx_buf[TXBUFSIZE];
volatile int tx_len;
volatile int rx_buf[RXBUFSIZE];
volatile int rx_len;

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
 * PA0: output		LED1
 * PA1: output		LED2
 * PA13: LPUART1_RX
 * PA14: LPUART1_TX
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(0, 1));
	gpio_config(GPIO_AF6, 0, GPIO_PA(13, 14));
}

/* LPUART1: 115200 8N1, interrupt */
static void lpuart_setup(void)
{
	rcc_enable_clock(RCC_LPUART1);
	nvic_enable_irq(NVIC_LPUART1_AES);
	lpuart_enable_interrupt(LPUART1, LPUART_RXNE);
	lpuart_init(LPUART1, FCK, 115200, 8, LPUART_STOP_1, LPUART_PARITY_NONE,
		    LPUART_FLOW_NONE, LPUART_TX_RX);
}

void lpuart1_aes_isr(void)
{
	int m;
	int s;
	static int rx_wp;
	static int tx_rp;

	m = lpuart_get_interrupt_mask(LPUART1, LPUART_RXNE | LPUART_TXE);
	s = lpuart_get_interrupt_status(LPUART1, LPUART_RXNE | LPUART_TXE);

	if (m & s & LPUART_RXNE) {
		if (rx_len < RXBUFSIZE) {
			gpio_toggle(GPIO_PA0);

			rx_buf[rx_wp++] = lpuart_recv(LPUART1);
			rx_wp &= RXBUFSIZE - 1;
			rx_len++;
		} else {
			lpuart_flush_receive_data(LPUART1);
		}

	}

	if (m & s & LPUART_TXE) {
		if (tx_len) {
			gpio_toggle(GPIO_PA1);

			lpuart_send(LPUART1, tx_buf[tx_rp++]);
			tx_rp &= TXBUFSIZE - 1;
			tx_len--;
		} else {
			lpuart_disable_interrupt(LPUART1, LPUART_TXE);
		}
	}
}

void tx_write_blocking(int data)
{
	static int tx_wp;

	while (tx_len == TXBUFSIZE)
		;
	lpuart_disable_interrupt(LPUART1, LPUART_TXE);
	tx_buf[tx_wp++] = data;
	tx_wp &= TXBUFSIZE - 1;
	tx_len++;
	lpuart_enable_interrupt(LPUART1, LPUART_TXE);
}

int rx_read_blocking(void)
{
	int r;
	static int rx_rp;
	
	while (rx_len == 0)
		;
	lpuart_disable_interrupt(LPUART1, LPUART_RXNE);
	r = rx_buf[rx_rp++];
	rx_rp &= RXBUFSIZE - 1;
	rx_len--;
	lpuart_enable_interrupt(LPUART1, LPUART_RXNE);
	return r;
}

static void get_line(char buf[])
{
	int c;
	int i;

	i = 0;
	do {
		c = getchar();
		if (isprint(c)) {
			putchar(c);
			if (i < BUFSIZE - 1)
				buf[i++] = c;
		} else {
			switch (c) {
			case '\b':
				if (i > 0) {
					putchar('\b');
					putchar(' ');
					putchar('\b');
					i--;
				}
				break;
			case '\n':
				putchar('\n');
				buf[i] = '\0';
				break;
			default:
				break;
			}
		}
	} while (c != '\n');
}

int main(void)
{
	static char buf[BUFSIZE];
	char *p;
	int i;

	clock_setup();
	gpio_setup();
	lpuart_setup();

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	while (1) {
		printf("lpuart_getchar> ");
		get_line(buf);
		p = strtok(buf, DELIMITER);
		i = 1;
		while (p) {
			printf("token %u: %s\n", i++, p);
			p = strtok(NULL, DELIMITER);
		}
		printf("%u tokens found.\n", i - 1);
	}

	return 0;
}
