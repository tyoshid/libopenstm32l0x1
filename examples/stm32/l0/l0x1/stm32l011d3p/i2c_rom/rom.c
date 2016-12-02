/*
 * rom.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of i2c_rom.
 *
 * i2c_rom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * i2c_rom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with i2c_rom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <i2c.h>

#include "i2c_rom.h"

/* 24FC64 slave address */
#define ROM_SLA		0xa0	/* |1|0|1|0|A2|A1|A0|R/W| */

/*
 * Byte Write 
 *
 * |S|10100000|A|xxx.....|A|........|A|........|A|P|
 *    Slave      Address    Address    Data
 *    Address    High Byte  Low Byte
 */
int rom_write_byte(int addr, char data)
{
	int r;
	
	do {
		i2c_start(I2C1, I2C_AUTOEND | ROM_SLA, 3);
		i2c_send_blocking(I2C1, addr >> 8);
		r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR |
					     I2C_NACKF);
		if (r & (I2C_ARLO | I2C_BERR))
			return r;
		if (r & I2C_NACKF) {
			while (!i2c_get_interrupt_status(I2C1, I2C_STOPF))
				;
			i2c_clear_interrupt(I2C1, I2C_NACKF | I2C_STOPF);
		}
	} while (r & I2C_NACKF);
			  
	i2c_send_blocking(I2C1, addr);
	r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR | I2C_NACKF);
	if (r)
		return r;
	
	i2c_send_blocking(I2C1, data);
	r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR | I2C_NACKF);
	if (r)
		return r;

	while (!i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR |
					 I2C_NACKF | I2C_STOPF))
		;
	r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR | I2C_NACKF);
	if (r)
		return r;
	i2c_clear_interrupt(I2C1, I2C_STOPF);
	return 0;
}

/*
 * Page Write 
 *
 * |S|10100000|A|xxx.....|A|........|A|........|A|~|........|A|P|
 *    Slave      Address    Address    Data         Data
 *    Address    High Byte  Low Byte   Byte 0       Byte 31
 */
int rom_write_page(int addr, char *data)
{
	int r;
	int i;

	do {
		i2c_start(I2C1, I2C_AUTOEND | ROM_SLA, PAGE_SIZE + 2);
		i2c_send_blocking(I2C1, addr >> 8);
		r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR |
					     I2C_NACKF);
		if (r & (I2C_ARLO | I2C_BERR))
			return r;
		if (r & I2C_NACKF) {
			while (!i2c_get_interrupt_status(I2C1, I2C_STOPF))
				;
			i2c_clear_interrupt(I2C1, I2C_NACKF | I2C_STOPF);
		}
	} while (r & I2C_NACKF);

	i2c_send_blocking(I2C1, addr);
	r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR | I2C_NACKF);
	if (r)
		return r;

	for (i = 0; i < PAGE_SIZE; i++) {
		i2c_send_blocking(I2C1, *(data + i));
		r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR |
					     I2C_NACKF);
		if (r)
			return r;
	}

	while (!i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR |
					 I2C_NACKF | I2C_STOPF))
		;
	r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR | I2C_NACKF);
	if (r)
		return r;
	i2c_clear_interrupt(I2C1, I2C_STOPF);
	return 0;
}

/*
 * Random Read / Sequential Read
 *
 * |S|10100000|A|xxx.....|A|........|A|S|10100001|A|........|A|~|........|N|P|
 *    Slave      Address    Address      Slave      Data n       Data n + x
 *    Address    High Byte  Low Byte     Address
 */
int rom_read(int addr, char *data, int nbyte)
{
	int r;
	int j;
	int i;
	int n;

	do {
		i2c_start(I2C1, ROM_SLA, 2);
		i2c_send_blocking(I2C1, addr >> 8);
		r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR |
					     I2C_NACKF);
		if (r & (I2C_ARLO | I2C_BERR))
			return r;
		if (r & I2C_NACKF) {
			while (!i2c_get_interrupt_status(I2C1, I2C_STOPF))
				;
			i2c_clear_interrupt(I2C1, I2C_NACKF | I2C_STOPF);
		}
	} while (r & I2C_NACKF);

	i2c_send_blocking(I2C1, addr);
	r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR | I2C_NACKF);
	if (r)
		return r;

	while (!i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR |
					 I2C_NACKF | I2C_TC))
		;
	r = i2c_get_interrupt_status(I2C1, I2C_ARLO | I2C_BERR | I2C_NACKF);
	if (r)
		return r;

	if (nbyte <= 255) {
		n = nbyte;
		i2c_start(I2C1, I2C_AUTOEND | I2C_READ | ROM_SLA, n);
	} else {
		n = 255;
		i2c_start(I2C1, I2C_AUTOEND | I2C_RELOAD | I2C_READ | ROM_SLA,
			  n);
	}

	for (j = 0; j < nbyte; j += 255) {
		for (i = 0; i < n; i++) {
			*(data + j + i) = i2c_recv_blocking(I2C1);
			r = i2c_get_interrupt_status(I2C1, I2C_ARLO |
						     I2C_BERR | I2C_NACKF);
			if (r)
				return r;
		}

		if (nbyte - j > 255) {
			while (!i2c_get_interrupt_status(I2C1, I2C_BERR |
							 I2C_TCR))
				;
			r = i2c_get_interrupt_status(I2C1, I2C_BERR);
			if (r)
				return r;
			if (nbyte - j - 255 <= 255) {
				n = nbyte - j - 255;
				i2c_reload(I2C1, n);
			} else {
				n = 255;
				i2c_reload(I2C1, I2C_RELOAD | n);
			}
		}
	}

	while (!i2c_get_interrupt_status(I2C1, I2C_BERR | I2C_STOPF))
		;
	r = i2c_get_interrupt_status(I2C1, I2C_BERR);
	if (r)
		return r;
	i2c_clear_interrupt(I2C1, I2C_STOPF);
	return 0;
}
