/*
 * command.h
 *
 * Copyright 2014 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of usart-util.
 *
 * usart-util is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * usart-util is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with usart-util.  If not, see <http://www.gnu.org/licenses/>.
 */

/* USART bootloader commands */
#define COM_GET						0x00
#define COM_GET_VERSION_AND_READ_PROTECTION_STATUS	0x01
#define COM_GET_ID					0x02
#define COM_READ_MEMORY					0x11
#define COM_GO						0x21
#define COM_WRITE_MEMORY				0x31
#define COM_ERASE					0x43
#define COM_EXTENDED_ERASE				0x44
#define COM_WRITE_PROTECT				0x63
#define COM_WRITE_UNPROTECT				0x73
#define COM_READOUT_PROTECT				0x82
#define COM_READOUT_UNPROTECT				0x92

#define MAX_COM						12

#define ACK						0x79
#define NACK						0x1f

int bootloader_init(int fd, int retry);
int get_command(int fd, uint8_t *data);
int get_version(int fd, uint8_t *data);
int get_id(int fd, uint8_t *data);
int read_memory(int fd, uint32_t address, int bytes, uint8_t *data);
int go_command(int fd, uint32_t address);
int write_memory(int fd, uint32_t address, int bytes, uint8_t *data);
int erase_memory(int fd, int pages, uint8_t *data);
int extended_erase_memory(int fd, int pages, uint16_t *data);
int write_protect(int fd, int sectors, uint8_t *data);
int write_unprotect(int fd);
int readout_protect(int fd);
int readout_unprotect(int fd);
