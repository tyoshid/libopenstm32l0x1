/*
 * ds18b20.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of 1wire_temp.
 *
 * 1wire_temp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 1wire_temp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 1wire_temp.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <gpio.h>
#include <crc.h>

#include "1wire_temp.h"
#include "stdio.h"

/*
 * Maxim DS18B20
 * Programmable Resolution
 * 1-Wire Digital Thermometer
 *
 * DQ - PA3
 */
/* ROM Commands */
#define DS_SEARCH_ROM		0xf0
#define DS_READ_ROM		0x33
#define DS_MATCH_ROM		0x55
#define DS_SKIP_ROM		0xcc
#define DS_ALARM_SEARCH		0xec
/* Function Commands */
#define DS_CONVERT_T		0x44
#define DS_WRITE_SCRATCHPAD	0x4e
#define DS_READ_SCRATCHPAD	0xbe
#define DS_COPY_SCRATCHPAD	0x48
#define DS_RECALL_E2		0xb8
#define DS_READ_POWER_SUPPLY	0xb4

#define DS_FAMILY_CODE		0x28

/* 1-Wire Master Timing (us) */
#define OWI_A			6
#define OWI_B			64
#define OWI_C			60
#define OWI_D			10
#define OWI_E			9
#define OWI_F			55
#define OWI_G			0
#define OWI_H			480
#define OWI_I			70
#define OWI_J			410

/* 1-Wire Operations */

/* Write bit */
/*
 * write 1    ---------+       +---------------------------
 *                     |       |
 *                     +-------+
 *                      <- A -> <-        B              ->
 *
 * write 0    ---------+                           +-------
 *                     |                           |
 *                     +---------------------------+
 *                      <-         C             -> <- D ->
 */
static void owi_write_bit(bool bit)
{
	gpio_clear(GPIO_PA7);
	delay_us(bit ? OWI_A : OWI_C);
	gpio_set(GPIO_PA7);
	delay_us(bit ? OWI_B : OWI_D);
}

/* Read bit */
/*
 * read       ---------+       +---------------------------
 *                     |       |       * Master Sample
 *                     +-------+...........................
 *                      <- A -> <- E -> <-    F          ->
 */
static bool owi_read_bit(void)
{
	bool r;

	gpio_clear(GPIO_PA7);
	delay_us(OWI_A);
	gpio_set(GPIO_PA7);
	delay_us(OWI_E);
	r = gpio_get(GPIO_PA7);
	delay_us(OWI_F);
	return r;
}

/* Reset */
/*
 * reset      ---------+            +-----+      +---------
 *                     |            |     : * Master Sample
 *                     +------------+     +......+
 *              <- G -> <-   H    -> <- I -> <-    J     ->
 */
static bool owi_reset(void)
{
	bool r;

	gpio_clear(GPIO_PA7);
	delay_us(OWI_H);
	gpio_set(GPIO_PA7);
	delay_us(OWI_I);
	r = gpio_get(GPIO_PA7);
	delay_us(OWI_J);
	return r;
}

/* Write byte */
static void owi_write(int data)
{
	int i;

	for (i = 0; i < 8; i++)
		owi_write_bit(data & (1 << i));
}

/* Read byte */
static int owi_read(void)
{
	int i;
	int r;

	r = 0;
	for (i = 0; i < 8; i++) {
		if (owi_read_bit())
			r |= (1 << i);
	}
	return r;
}

/* read 64-bit lasered ROM code (single slave) */
int ds_read_rom(char *buf)
{
	int i;

	if (owi_reset()) {
		fprintf(stderr, "no presence\n");
		return -1;
	}
	owi_write(DS_READ_ROM);
	for (i = 0; i < 8; i++)
		buf[i] = owi_read();
	if (crc_calc(0, buf, 8)) {
		fprintf(stderr, "CRC error\n");
		return -1;
	}
	if (buf[0] != DS_FAMILY_CODE) {
		fprintf(stderr, "family code=%02x?\n", buf[0]);
		return -1;
	}
	return 0;
}

/* read thermal data (single slave) */
int ds_read_data(char *buf)
{
	int i;

	if (owi_reset()) {
		fprintf(stderr, "no presence\n");
		return -1;
	}
	owi_write(DS_SKIP_ROM);
	owi_write(DS_CONVERT_T);
	delay_ms(1000);
	if (owi_reset()) {
		fprintf(stderr, "no presence\n");
		return -1;
	}
	owi_write(DS_SKIP_ROM);
	owi_write(DS_READ_SCRATCHPAD);
	for (i = 0; i < 9; i++)
		buf[i] = owi_read();
	if (crc_calc(0, buf, 9)) {
		fprintf(stderr, "CRC error\n");
		return -1;
	}
	return 0;
}
