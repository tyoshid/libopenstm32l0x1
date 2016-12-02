/*
 * usart_irq - Receive and transmit (echo back) characters.
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
#include <nvic.h>
#include <vector.h>
#include <usart.h>

#define FCK		32000000 /* USART clock frequency */
#define BUFSIZE		8	 /* power of 2 */

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
 * PA1: output		LED1
 * PA4: output		LED2
 * PA14: USART2_TX
 * PA0: USART2_RX
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(1, 4));
	gpio_config(GPIO_AF4, 0, GPIO_PA14);
	gpio_config(GPIO_AF0, 0, GPIO_PA0);
}

/* USART2: 115200 8N1 */
static void usart_setup(void)
{
	rcc_enable_clock(RCC_USART2);
	nvic_enable_irq(NVIC_USART2);
	usart_enable_interrupt(USART2, USART_RXNE);
	usart_init(USART2, FCK, 115200, 8, USART_STOP_1, USART_PARITY_NONE,
		   USART_FLOW_NONE, USART_TX_RX);
}

void usart2_isr(void)
{
	int m;
	int s;
	static int buf[BUFSIZE];
	static int rp;
	static int wp;
	static int len;

	m = usart_get_interrupt_mask(USART2, USART_RXNE | USART_TXE);
	s = usart_get_interrupt_status(USART2, USART_RXNE | USART_TXE);
	if (m & s & USART_RXNE) {
		if (len < BUFSIZE) {
			gpio_toggle(GPIO_PA1);

			buf[wp++] = usart_recv(USART2);
			wp &= BUFSIZE - 1;
			len++;

			if (!(m & USART_TXE))
				usart_enable_interrupt(USART2, USART_TXE);
		} else {
			usart_flush_receive_data(USART2);
		}

	}

	if (m & s & USART_TXE) {
		if (len) {
			gpio_toggle(GPIO_PA4);

			usart_send(USART2, buf[rp++]);
			rp &= BUFSIZE - 1;
			len--;
		} else {
			usart_disable_interrupt(USART2, USART_TXE);
		}
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	usart_setup();

	while (1)
		;

	return 0;
}
