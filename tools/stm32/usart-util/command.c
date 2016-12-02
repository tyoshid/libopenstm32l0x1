/*
 * command.c - STM32 USART bootloader interface
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

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#include "command.h"

extern bool debug;

/* Synchronization */
int bootloader_init(int fd, int retry)
{
	int i;
	uint8_t d;
	int r;

	for (i = 0; i < retry; i++) {
		r = tcflush(fd, TCIOFLUSH);
		if (r < 0) {
			perror("tcflush() failed");
			return -1;
		}
		d = 0x7f;
		r = write(fd, &d, 1);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
		r = read(fd, &d, 1);
		if (r < 0) {
			perror("read() failed");
			return -1;
		}
		if (r == 1 && d == ACK)
			return 0;
		if (debug)
			printf("%d 0x%02x\n", r, d);
	}
	fprintf(stderr, "No response\n");
	return -1;
}

/* Get command */
int get_command(int fd, uint8_t *data)
{
	uint8_t buf[2];
	int r;
	int n;
	int i;

	buf[0] = COM_GET;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Get command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1) {
		fprintf(stderr, "Can't get the number of data\n");
		return -1;
	}
	n = buf[0] + 1;
	if (n > MAX_COM + 1) {
		fprintf(stderr, "Invalid number of data (%d)\n", n);
		return -1;
	}
	for (i = 0; i < n; i++) {
		r = read(fd, buf, 1);
		if (r < 0) {
			perror("read() failed");
			return -1;
		}
		if (r != 1) {
			fprintf(stderr, "Can't get a data\n");
			if (debug)
				fprintf(stderr, "%d %d\n", n, i);
			return -1;
		}
		*data++ = buf[0];
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "No ACK\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return n;
}

/* Get Version & Read Protection Status command */
int get_version(int fd, uint8_t *data)
{
	uint8_t buf[2];
	int r;
	int i;

	buf[0] = COM_GET_VERSION_AND_READ_PROTECTION_STATUS;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Get Version command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	for (i = 0; i < 3; i++) {
		r = read(fd, buf, 1);
		if (r < 0) {
			perror("read() failed");
			return -1;
		}
		if (r != 1) {
			fprintf(stderr, "Can't get a data\n");
			if (debug)
				fprintf(stderr, "%d\n", i);
			return -1;
		}
		*data++ = buf[0];
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "No ACK\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return 3;
}
	
/* Get ID command */
int get_id(int fd, uint8_t *data)
{
	uint8_t buf[2];
	int r;
	int n;
	int i;

	buf[0] = COM_GET_ID;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Get ID command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1) {
		fprintf(stderr, "Can't get the number of data\n");
		return -1;
	}
	n = buf[0] + 1;
	if (n != 2) {
		fprintf(stderr, "Invalid number of data (%d)\n", n);
		return -1;
	}
	for (i = 0; i < n; i++) {
		r = read(fd, buf, 1);
		if (r < 0) {
			perror("read() failed");
			return -1;
		}
		if (r != 1) {
			fprintf(stderr, "Can't get a data\n");
			if (debug)
				fprintf(stderr, "%d %d\n", n, i);
			return -1;
		}
		*data++ = buf[0];
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "No ACK\n");
		if (debug)
			fprintf(stderr, "%d 0x%x\n", r, buf[0]);
		return -1;
	}
	return n;
}

/* Read Memory command */
int read_memory(int fd, uint32_t address, int bytes, uint8_t *data)
{
	uint8_t buf[5];
	int r;
	int n;
	int i;

	buf[0] = COM_READ_MEMORY;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Read Memory command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	buf[0] = address >> 24;
	buf[1] = (address >> 16) & 0xff;
	buf[2] = (address >> 8) & 0xff;
	buf[3] = address & 0xff;
	buf[4] = buf[0] ^ buf[1] ^ buf[2] ^ buf[3];
	r = write(fd, buf, 5);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't set the start address (0x%08x)\n",
			address);
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	buf[0] = bytes - 1;
	n = ((bytes - 1) & 0xff) + 1;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't set the number of bytes (%d)\n", n);
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	for (i = 0; i < n; i++) {
		r = read(fd, buf, 1);
		if (r < 0) {
			perror("read() failed");
			return -1;
		}
		if (r != 1) {
			fprintf(stderr, "Can't get a data\n");
			if (debug)
				fprintf(stderr, "%d %d\n", n, i);
			return -1;
		}
		*data++ = buf[0];
	}
	return n;
}

/* Go command */
int go_command(int fd, uint32_t address)
{
	uint8_t buf[5];
	int r;

	buf[0] = COM_GO;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Go command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	buf[0] = address >> 24;
	buf[1] = (address >> 16) & 0xff;
	buf[2] = (address >> 8) & 0xff;
	buf[3] = address & 0xff;
	buf[4] = buf[0] ^ buf[1] ^ buf[2] ^ buf[3];
	r = write(fd, buf, 5);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't set the start address (0x%08x)\n",
			address);
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't start\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return 0;
}

/* Write Memory command */
int write_memory(int fd, uint32_t address, int bytes, uint8_t *data)
{
	uint8_t buf[5];
	int r;
	uint8_t sum;
	int i;

	buf[0] = COM_WRITE_MEMORY;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Write Memory command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	buf[0] = address >> 24;
	buf[1] = (address >> 16) & 0xff;
	buf[2] = (address >> 8) & 0xff;
	buf[3] = address & 0xff;
	buf[4] = buf[0] ^ buf[1] ^ buf[2] ^ buf[3];
	r = write(fd, buf, 5);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't set the start address (0x%08x)\n",
			address);
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	if (bytes > 256) {
		fprintf(stderr, "Invalid argument (%d)\n", bytes);
		return -1;
	}
	buf[0] = bytes - 1;
	sum = buf[0];
	r = write(fd, buf, 1);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	for (i = 0; i < bytes; i++)
		sum ^= *(data + i);
	r = write(fd, data, bytes);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = write(fd, &sum, 1);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't write data\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return bytes;
}

/* Erase Memory command */
int erase_memory(int fd, int pages, uint8_t *data)
{
	uint8_t buf[2];
	int r;
	uint8_t sum;
	int i;

	buf[0] = COM_ERASE;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Erase Memory command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	if (pages > 256) {
		fprintf(stderr, "Invalid argument (%d)\n", pages);
		return -1;
	} else if (pages == 256) { /* Global Erase */
		buf[0] = 0xff;
		buf[1] = 0;
		r = write(fd, buf, 2);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
	} else {
		buf[0] = pages - 1;
		sum = buf[0];
		r = write(fd, buf, 1);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
		for (i = 0; i < pages; i++)
			sum ^= *(data + i);
		r = write(fd, data, pages);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
		r = write(fd, &sum, 1);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't erase memory\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return pages;
}

/* Extended Erase Memory command */
int extended_erase_memory(int fd, int pages, uint16_t *data)
{
	uint8_t buf[3];
	int r;
	uint8_t sum;
	int i;

	buf[0] = COM_EXTENDED_ERASE;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Extended Erase Memory command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	if (pages > 0xffff + 1) {
		fprintf(stderr, "Invalid argument (0x%08x)\n", pages);
		return -1;
	} else if (pages >= 0xfff0 + 1) { /* Send Special Erase command */
		buf[0] = (pages - 1) >> 8;
		buf[1] = (pages - 1) & 0xff;
		buf[2] = buf[0] ^ buf[1];
		r = write(fd, buf, 3);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
	} else {
		buf[0] = (pages - 1) >> 8;
		buf[1] = (pages - 1) & 0xff;
		sum = buf[0] ^ buf[1];
		r = write(fd, buf, 2);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
		for (i = 0; i < pages; i++) {
			buf[0] = *data >> 8;
			sum ^= buf[0];
			buf[1] = *data++ & 0xff;
			sum ^= buf[1];
			r = write(fd, buf, 2);
			if (r < 0) {
				perror("write() failed");
				return -1;
			}
		}
		r = write(fd, &sum, 1);
		if (r < 0) {
			perror("write() failed");
			return -1;
		}
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't erase memory\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return pages;
}

/* Write Protect command */
int write_protect(int fd, int sectors, uint8_t *data)
{
	uint8_t buf[2];
	int r;
	uint8_t sum;
	int i;

	buf[0] = COM_WRITE_PROTECT;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Write Protect command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	if (sectors > 256) {
		fprintf(stderr, "Invalid argument (%d)\n", sectors);
		return -1;
	}
	buf[0] = sectors - 1;
	sum = buf[0];
	r = write(fd, buf, 1);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	for (i = 0; i < sectors; i++)
		sum ^= *(data + i);
	r = write(fd, data, sectors);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = write(fd, &sum, 1);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't write-protect the sectors\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return sectors;
}

/* Write Unprotect command */
int write_unprotect(int fd)
{
	uint8_t buf[2];
	int r;

	buf[0] = COM_WRITE_UNPROTECT;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Write Unprotect command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't remove the protection\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return 0;
}

/* Readout Protect command */
int readout_protect(int fd)
{
	uint8_t buf[2];
	int r;

	buf[0] = COM_READOUT_PROTECT;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Readout Protect command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't activate read protection\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return 0;
}

/* Readout Unprotect command */
int readout_unprotect(int fd)
{
	uint8_t buf[2];
	int r;

	buf[0] = COM_READOUT_UNPROTECT;
	buf[1] = ~buf[0];
	r = write(fd, buf, 2);
	if (r < 0) {
		perror("write() failed");
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Readout Unprotect command failed\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	r = read(fd, buf, 1);
	if (r < 0) {
		perror("read() failed");
		return -1;
	}
	if (r != 1 || buf[0] != ACK) {
		fprintf(stderr, "Can't disable RDP\n");
		if (debug)
			fprintf(stderr, "%d 0x%02x\n", r, buf[0]);
		return -1;
	}
	return 0;
}
