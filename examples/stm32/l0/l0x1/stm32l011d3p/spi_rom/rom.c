/*
 * rom.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of spi_rom.
 *
 * spi_rom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * spi_rom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with spi_rom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>

#include <gpio.h>
#include <spi.h>

#include "spi_rom.h"

/*
 * Microchip 25LC640A
 * 64Kbit SPI Serial EEPROM
 *
 * FCLKmax	5 MHz (Vcc = 3.3 V)
 *
 * /CS - PA4
 */
#define COMMAND_READ	0x03
#define COMMAND_WRITE	0x02
#define COMMAND_WRDI	0x04
#define COMMAND_WREN	0x06
#define COMMAND_RDSR	0x05
#define COMMAND_WRSR	0x01
#define TWC		5	/* Internal write cycle time: 5 ms */

/* Byte Write */
void rom_write_byte(int addr, char data)
{
	gpio_clear(GPIO_PA4);
	spi_send_blocking(SPI1, COMMAND_WREN);
	spi_recv_blocking(SPI1);
	gpio_set(GPIO_PA4);

	gpio_clear(GPIO_PA4);
	spi_send_blocking(SPI1, COMMAND_WRITE);
	spi_recv_blocking(SPI1);
	spi_send_blocking(SPI1, addr >> 8);
	spi_recv_blocking(SPI1);
	spi_send_blocking(SPI1, addr);
	spi_recv_blocking(SPI1);
	spi_send_blocking(SPI1, data);
	spi_recv_blocking(SPI1);
	gpio_set(GPIO_PA4);

	delay_ms(TWC);
}

/* Page Write */
void rom_write_page(int addr, char *data)
{
	int i;

	gpio_clear(GPIO_PA4);
	spi_send_blocking(SPI1, COMMAND_WREN);
	spi_recv_blocking(SPI1);
	gpio_set(GPIO_PA4);

	gpio_clear(GPIO_PA4);
	spi_send_blocking(SPI1, COMMAND_WRITE);
	spi_recv_blocking(SPI1);
	spi_send_blocking(SPI1, addr >> 8);
	spi_recv_blocking(SPI1);
	spi_send_blocking(SPI1, addr);
	spi_recv_blocking(SPI1);
	for (i = 0; i < PAGE_SIZE; i++) {
		spi_send_blocking(SPI1, *data++);
		spi_recv_blocking(SPI1);
	}
	gpio_set(GPIO_PA4);

	delay_ms(TWC);
}

/* Read */
void rom_read(int addr, char *data, int nbyte)
{
	int i;

	gpio_clear(GPIO_PA4);
	spi_send_blocking(SPI1, COMMAND_READ);
	spi_recv_blocking(SPI1);
	spi_send_blocking(SPI1, addr >> 8);
	spi_recv_blocking(SPI1);
	spi_send_blocking(SPI1, addr);
	spi_recv_blocking(SPI1);
	for (i = 0; i < nbyte; i++) {
		spi_send_blocking(SPI1, 0);
		*data++ = spi_recv_blocking(SPI1);
	}
	gpio_set(GPIO_PA4);
}
