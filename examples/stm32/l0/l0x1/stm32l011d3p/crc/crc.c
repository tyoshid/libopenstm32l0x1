/*
 * crc - Calculate CRCs.
 *
 * crc.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of crc.
 *
 * crc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * crc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with crc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <gpio.h>
#include <usart.h>
#include <crc.h>

#include "crc.h"
#include "stdio.h"

#define FCK	32000000	/* USART clock frequency */

extern const char test_data[];

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
 * PA9: USART2_TX
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_config(GPIO_OUTPUT, 0, GPIO_PA(0, 1));
	gpio_set(GPIO_PA(0, 1));
	gpio_config(GPIO_AF4, 0, GPIO_PA9);
}

/* USART2: 115200 8N1 */
static void usart_setup(void)
{
	rcc_enable_clock(RCC_USART2);
	usart_init(USART2, FCK, 115200, 8, USART_STOP_1, USART_PARITY_NONE,
		   USART_FLOW_NONE, USART_TX);
}

static void crc_setup(void)
{
	rcc_enable_clock(RCC_CRC);
}

static int test_crc32_be(void)
{
	int i;
	int r;
	bool error_flag;
	extern const struct test_result crc32_be_result[];
	
	puts("CRC-32(BE)");
	crc_set_mode(0x04c11db7, CRC_POLYSIZE_32);
	error_flag = false;
	for (i = 0; i < TESTLEN; i++) {
		r = crc_calc(crc32_be_result[i].init,
			     (char *)test_data + crc32_be_result[i].offset,
			     crc32_be_result[i].length);
		if (r != crc32_be_result[i].result) {
			printf("CRC-32(BE) failed: 0x%08x (0x%08x)\n",
			       r, crc32_be_result[i].result);
			error_flag = true;
			gpio_clear(GPIO_PA1);
		}
	}
	if (error_flag)
		return -1;
	puts("Passed");
	return 0;
}

static int bitreverse32(int data)
{
	int i;
	int r;

	r = 0;
	for (i = 0; i < 32; i++) {
		if (data & (1 << i))
			r |= 1 << (31 - i);
	}
	return r;
}

static int test_crc32_le(void)
{
	int i;
	int r;
	bool error_flag;
	extern const struct test_result crc32_le_result[];
	
	puts("CRC-32(LE)");
	crc_set_mode(0x04c11db7, CRC_POLYSIZE_32 | CRC_REV_IN_BYTE |
		     CRC_REV_OUT);
	error_flag = false;
	for (i = 0; i < TESTLEN; i++) {
		r = crc_calc(bitreverse32(crc32_le_result[i].init),
			     (char *)test_data + crc32_le_result[i].offset,
			     crc32_le_result[i].length);
		if (r != crc32_le_result[i].result) {
			printf("CRC-32(LE) failed: 0x%08x (0x%08x)\n",
			       r, crc32_le_result[i].result);
			error_flag = true;
			gpio_clear(GPIO_PA1);
		}
	}
	if (error_flag)
		return -1;
	puts("Passed");
	return 0;
}

static int bitreverse16(int data)
{
	int i;
	int r;

	r = 0;
	for (i = 0; i < 16; i++) {
		if (data & (1 << i))
			r |= 1 << (15 - i);
	}
	return r;
}

static int test_crc16(void)
{
	int i;
	int r;
	bool error_flag;
	extern const struct test_result crc16_result[];

	puts("CRC-16");
	crc_set_mode(0x8005, CRC_POLYSIZE_16 | CRC_REV_IN_BYTE | CRC_REV_OUT);
	error_flag = false;
	for (i = 0; i < TESTLEN; i++) {
		r = crc_calc(bitreverse16(crc16_result[i].init),
			     (char *)test_data + crc16_result[i].offset,
			     crc16_result[i].length);
		if (r != crc16_result[i].result) {
			printf("CRC-16 failed: 0x%08x (0x%08x)\n",
			       r, crc16_result[i].result);
			error_flag = true;
			gpio_clear(GPIO_PA1);
		}
	}
	if (error_flag)
		return -1;
	puts("Passed");
	return 0;
}

static int test_crc_ccitt(void)
{
	int i;
	int r;
	bool error_flag;
	extern const struct test_result crc_ccitt_result[];

	puts("CRC-CCITT");
	crc_set_mode(0x1021, CRC_POLYSIZE_16 | CRC_REV_IN_BYTE | CRC_REV_OUT);
	error_flag = false;
	for (i = 0; i < TESTLEN; i++) {
		r = crc_calc(bitreverse16(crc_ccitt_result[i].init),
			     (char *)test_data + crc_ccitt_result[i].offset,
			     crc_ccitt_result[i].length);
		if (r != crc_ccitt_result[i].result) {
			printf("CRC-CCITT failed: 0x%08x (0x%08x)\n",
			       r, crc_ccitt_result[i].result);
			error_flag = true;
			gpio_clear(GPIO_PA1);
		}
	}
	if (error_flag)
		return -1;
	puts("Passed");
	return 0;
}

static int bitreverse8(int data)
{
	int i;
	int r;

	r = 0;
	for (i = 0; i < 8; i++) {
		if (data & (1 << i))
			r |= 1 << (7 - i);
	}
	return r;
}

static int test_crc8(void)
{
	int i;
	int r;
	bool error_flag;
	extern const struct test_result crc8_result[];

	puts("CRC-8 Dallas/Maxim");
	crc_set_mode(0x31, CRC_POLYSIZE_8 | CRC_REV_IN_BYTE | CRC_REV_OUT);
	error_flag = false;
	for (i = 0; i < TESTLEN; i++) {
		r = crc_calc(bitreverse8(crc8_result[i].init),
			     (char *)test_data + crc8_result[i].offset,
			     crc8_result[i].length);
		if (r != crc8_result[i].result) {
			printf("CRC-8 failed: 0x%08x (0x%08x)\n",
			       r, crc8_result[i].result);
			error_flag = true;
			gpio_clear(GPIO_PA1);
		}
	}
	if (error_flag)
		return -1;
	puts("Passed");
	return 0;
}

static int test_crc7(void)
{
	int i;
	int r;
	bool error_flag;
	extern const struct test_result crc7_result[];

	puts("CRC-7");
	crc_set_mode(0x09, CRC_POLYSIZE_7);
	error_flag = false;
	for (i = 0; i < TESTLEN; i++) {
		r = crc_calc(crc7_result[i].init,
			     (char *)test_data + crc7_result[i].offset,
			     crc7_result[i].length);
		if (r != crc7_result[i].result) {
			printf("CRC-7 failed: 0x%08x (0x%08x)\n",
			       r, crc7_result[i].result);
			error_flag = true;
			gpio_clear(GPIO_PA1);
		}
	}
	if (error_flag)
		return -1;
	puts("Passed");
	return 0;
}

int main(void)
{
	clock_setup();
	gpio_setup();
	usart_setup();
	crc_setup();

	puts("CRC");
	while (1) {
		gpio_toggle(GPIO_PA0);
		test_crc32_be();
		test_crc32_le();
		test_crc16();
		test_crc_ccitt();
		test_crc8();
		test_crc7();
	}

	return 0;
}
