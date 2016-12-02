/*
 * i2c_rom.h
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

/*
 * Microchip 24FC64
 * 64Kbit I2C Serial EEPROM
 */
#define ROM_SIZE	8192	/* 8 KByte */
#define PAGE_SIZE	32	/* 32 Byte */

int rom_read(int addr, char *data, int nbyte);
int rom_write_byte(int addr, char data);
int rom_write_page(int addr, char *data);
