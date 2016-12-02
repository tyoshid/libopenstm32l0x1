/*
 * lpuart_irq - Receive and transmit (echo back) characters.
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

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <nvic.h>
#include <vector.h>
#include <lpuart.h>

#define FCK		16000000 /* LPUART clock frequency */
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
 * PA0: LPUART1_RX
 * PA1: LPUART1_TX
 * PA4: output		LED1
 * PA7: output		LED2
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_AF6, 0, GPIO_PA(0, 1));
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(4, 7));
}

/* LPUART1: 115200 8N1 */
static void lpuart_setup(void)
{
	rcc_set_lpuart1_clock(RCC_HSI16);
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
	static int buf[BUFSIZE];
	static int rp;
	static int wp;
	static int len;

	m = lpuart_get_interrupt_mask(LPUART1, LPUART_RXNE | LPUART_TXE);
	s = lpuart_get_interrupt_status(LPUART1, LPUART_RXNE | LPUART_TXE);
	if (m & s & LPUART_RXNE) {
		if (len < BUFSIZE) {
			gpio_toggle(GPIO_PA4);

			buf[wp++] = lpuart_recv(LPUART1);
			wp &= BUFSIZE - 1;
			len++;

			if (!(m & LPUART_TXE))
				lpuart_enable_interrupt(LPUART1, LPUART_TXE);
		} else {
			lpuart_flush_receive_data(LPUART1);
		}

	}

	if (m & s & LPUART_TXE) {
		if (len) {
			gpio_toggle(GPIO_PA7);

			lpuart_send(LPUART1, buf[rp++]);
			rp &= BUFSIZE - 1;
			len--;
		} else {
			lpuart_disable_interrupt(LPUART1, LPUART_TXE);
		}
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	lpuart_setup();

	while (1)
		;

	return 0;
}
