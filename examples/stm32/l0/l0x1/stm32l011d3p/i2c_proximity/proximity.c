/*
 * proximity.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of i2c_proximity.
 *
 * i2c_proximity is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * i2c_proximity is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with i2c_proximity.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <i2c.h>

#include "i2c_proximity.h"

/*
 * Vishay VCNL4000
 * Fully Integrated Proximity and Ambient Light Sensor with Infrared Emitter
 * and I2C Interface
 *
 * VCNL4000 Infrared Proximity Breakout
 * BOB-10901
 * SparkFun Electronics
 */
#define PROX_THRESH	25

extern volatile int sndbuflen;
extern volatile int *sndbuf;
extern volatile int rcvbuflen;
extern volatile int *rcvbuf;
extern volatile bool busy;
extern volatile int status;

/* Write command */
static int vcnl_write_command(int addr, int data)
{
	int buf[2];

	buf[0] = addr;
	buf[1] = data;
	sndbuf = buf;
	sndbuflen = 2;
	rcvbuflen = 0;
	busy = true;
	status = 0;
	i2c_start(I2C1, I2C_AUTOEND | VCNL4000_SLA, 2);
	while (busy)
		;
	if ((status & (I2C_BERR | I2C_ARLO)) || sndbuflen)
		return -1;
	return 0;
}

/* Read word */
static int vcnl_read_word(int addr, int *data)
{
	int h;

	sndbuf = &addr;
	sndbuflen = 1;
	rcvbuf = &h;
	rcvbuflen = 1;
	busy = true;
	status = 0;
	i2c_start(I2C1, VCNL4000_SLA, 1);
	while (busy)
		;
	if ((status & (I2C_BERR | I2C_ARLO)) || sndbuflen || rcvbuflen)
		return -1;

	sndbuflen = 0;
	rcvbuf = data;
	rcvbuflen = 1;
	busy = true;
	status = 0;
	i2c_start(I2C1, I2C_AUTOEND | I2C_READ | VCNL4000_SLA, 1);
	while (busy)
		;
	if ((status & (I2C_BERR | I2C_ARLO)) || rcvbuflen)
		return -1;
	*data |= h << 8;
	return 0;
}

/*
 * IR LED current = 100mA
 * proximity IR test signal frequency = 781.25 kHz
 * Modulation delay time = 4, Modulation dead time = 1
 */
static int vcnl_init(void)
{
	delay_us(400);
	if (vcnl_write_command(0x83, 10))
		return -1;
	if (vcnl_write_command(0x89, 2))
		return -1;
	if (vcnl_write_command(0x8a, 129))
		return -1;
	return 0;
}

static int calib(void)
{
	int i;
	int d;
	int prox_min;
	int prox_max;
	int total;
	int prox_off;

	for (i = 0; i < 5; i++) {
		if (vcnl_write_command(0x80, 8))
			return -1;
		delay_us(i == 0 ? 600 : 200);
		if (vcnl_read_word(0x87, &d))
			return -1;
		if (i == 0) {
			prox_min = d;
			prox_max = d;
			total = d;
		} else {
			if (d < prox_min)
				prox_min = d;
			if (d > prox_max)
				prox_max = d;
			total += d;
		}
		delay_ms(10);
	}
	prox_off = total / 5;
	/*
	printf("proximity offset = %u (%u - %u)\n",
	       prox_off, prox_min, prox_max);
	*/
	return prox_off;
}

int proximity_init(void)
{
	if (vcnl_init())
		return -1;
	return calib();
}
	
int proximity_get_ambient_light(void)
{
	int d;
	
	if (vcnl_write_command(0x80, 0x10))
		return -1;
	delay_ms(400);
	if (vcnl_read_word(0x85, &d))
		return -1;
	return d / 4;
}

int proximity_measure(int prox_off)
{
	int n;
	int x;
	int p;
	int d;
	
	n = 0;
	x = 0;
	p = 0;
	while (n < 9 && x < 10) {
		if (vcnl_write_command(0x80, 8))
			return -1;
		delay_us(200);
		if (vcnl_read_word(0x87, &d))
			return -1;
		if (d > prox_off + PROX_THRESH) {
			p += d;
			x++;
		} else {
			n++;
		}
		delay_ms(10);
	}
	if (x >= 10)
		return p / 10;
	return 0;
}
