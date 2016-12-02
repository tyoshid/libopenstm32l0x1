/*
 * transfer.c - Download or upload file.
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
#include <stdint.h>
#include <stdbool.h>

#include "command.h"
#include "transfer.h"

#define BUFSIZE 256

extern bool debug;
extern bool extended_erase;

int upload(int fd, FILE *stream, int bytes)
{
	uint32_t a;
	int i;
	int n;
	int r;
	uint8_t buf[BUFSIZE];

	a = FLASH_ADDRESS;
	i = 0;
	while (i < bytes) {
		n = (bytes - i) > BUFSIZE ? BUFSIZE : bytes - i;
		r = read_memory(fd, a, n, buf);
		if (r < 0)
			return -1;
		r = fwrite(buf, 1, n, stream);
		if (r != n) {
			fprintf(stderr, "fwrite() failed\n");
			return -1;
		}
		if (debug)
			printf("%08x\n", a);
		a += n;
		i += n;
	}
	printf("read %d bytes\n", bytes);
	return bytes;
}

static bool erase_zero_error(uint8_t *p, int size, bool silent)
{
	int i;

	for (i = 0; i < size; i++) {
		if (*p) {
			if (!silent)
				fprintf(stderr, "%02x %02x\n", i, *p);
			return true;
		}
		p++;
	}
	return false;
}

static bool erase_error(uint8_t *p, int size, bool silent)
{
	int i;

	for (i = 0; i < size; i++) {
		if (*p != 0xff) {
			if (!silent)
				fprintf(stderr, "%02x %02x\n", i, *p);
			return true;
		}
		p++;
	}
	return false;
}

static bool verify_error(uint8_t *p1, uint8_t *p2, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		if (*p1 != *p2) {
			fprintf(stderr, "%02x %02x %02x\n", i, *p1, *p2);
			return true;
		}
		p1++;
		p2++;
	}
	return false;
}

int download_stm32l1(int fd, FILE *stream, int page_size)
{
	uint32_t a;
	int len;
	int r;
	uint8_t buf[BUFSIZE];
	int n;
	int i;
	uint8_t flash[BUFSIZE];
	uint16_t page = 0;

	a = FLASH_ADDRESS;
	len = 0;
	while (!feof(stream)) {
		r = fread(buf, 1, page_size, stream);
		n = (r + 4 - 1) & ~(4 - 1);
		if (r < page_size) {
			if (ferror(stream)) {
				fprintf(stderr, "File read error\n");
				return -1;
			}
			if (r == 0)
				break;
			for (i = 0; i < n - r; i++)
				buf[r + i] = 0;
			if (debug)
				printf("%02x ", r);
		}
		if (debug)
			printf("%d ", page);

		if (extended_erase)
			r = extended_erase_memory(fd, 1, &page);
		else
			r = erase_memory(fd, 1, (uint8_t *)&page);
		if (r < 0)
			return -1;
		r = read_memory(fd, a, n, flash);
		if (r < 0)
			return -1;
		if (erase_zero_error(flash, n, false)) {
			fprintf(stderr, "Erase error %08x\n", a);
			return -1;
		}
		if (debug)
			printf("E ");

		r = write_memory(fd, a, n, buf);
		if (r < 0)
			return -1;
		if (debug)
			printf("W ");

		r = read_memory(fd, a, n, flash);
		if (r < 0)
			return -1;
		if (verify_error(buf, flash, n)) {
			fprintf(stderr, "Verify error %08x\n", a);
			return -1;
		}
		if (debug)
			printf("V\n");
		a += n;
		len += n;
		page++;
	}
	printf("wrote %d bytes\n", len);
	return len;
}

int download(int fd, FILE *stream)
{
	uint32_t a;
	int r;
	uint8_t buf[BUFSIZE];
	int n;
	uint8_t flash[BUFSIZE];
	bool mass_erase = false;
	int len;
	int i;

	a = FLASH_ADDRESS;
	while (!feof(stream)) {
		r = fread(buf, 1, BUFSIZE, stream);
		n = (r + 4 - 1) & ~(4 - 1);
		if (r < BUFSIZE) {
			if (ferror(stream)) {
				fprintf(stderr, "File read error\n");
				return -1;
			}
			if (r == 0)
				break;
		}
		r = read_memory(fd, a, n, flash);
		if (r < 0)
			return -1;
		if (erase_error(flash, n, true)) {
			mass_erase = true;
			break;
		}
		a += n;
	}

	if (mass_erase) {
		if (extended_erase)
			r = extended_erase_memory(fd, 0x10000, NULL);
		else
			r = erase_memory(fd, 256, NULL);
		if (r < 0)
			return -1;
	}
	clearerr(stream);
	rewind(stream);
	a = FLASH_ADDRESS;
	len = 0;
	while (!feof(stream)) {
		r = fread(buf, 1, BUFSIZE, stream);
		n = (r + 4 - 1) & ~(4 - 1);
		if (r < BUFSIZE) {
			if (ferror(stream)) {
				fprintf(stderr, "File read error\n");
				return -1;
			}
			if (r == 0)
				break;
			for (i = 0; i < n - r; i++)
				buf[r + i] = 0xff;
			if (debug)
				printf("%02x ", r);
		}
		if (debug)
			printf("%08x ", a);
		if (mass_erase) {
			r = read_memory(fd, a, n, flash);
			if (r < 0)
				return -1;
			if (erase_error(flash, n, false)) {
				fprintf(stderr, "Erase error %08x\n", a);
				return -1;
			}
			if (debug)
				printf("E ");
		}

		r = write_memory(fd, a, n, buf);
		if (r < 0)
			return -1;
		if (debug)
			printf("W ");

		r = read_memory(fd, a, n, flash);
		if (r < 0)
			return -1;
		if (verify_error(buf, flash, n)) {
			fprintf(stderr, "Verify error %08x\n", a);
			return -1;
		}
		if (debug)
			printf("V\n");
		a += n;
		len += n;
	}
	printf("wrote %d bytes\n", len);
	return len;
}
