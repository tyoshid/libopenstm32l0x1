/*
 * stdio.c
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
#include <stdarg.h>

#include <usart.h>

static int putchar(int c)
{
	if (c == '\n')
		usart_send_blocking(USART2, '\r');
	usart_send_blocking(USART2, c);
	return c;
}

int puts(const char *s)
{
	while (*s)
		putchar(*s++);
	putchar('\n');
	return 0;
}

static int print_x(unsigned int x)
{
	int i;
	int h;
	
	for (i = 0; i < 8; i++) {
		h = (x >> ((7 - i) * 4)) & 0xf;
		if (h > 9)
			putchar(h - 10 + 'a');
		else
			putchar(h + '0');
	}
	return 8;
}

static int isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int printf(const char *fmt, ...)
{
	va_list argp;
	int n;

	va_start(argp, fmt);
	n = 0;
	while (*fmt) {
		if (*fmt != '%') {
			putchar(*fmt++);
			n++;
		} else {
			while (isdigit(*++fmt))
				;
			if (*fmt == 'x') {
				n += print_x(va_arg(argp, unsigned int));
				fmt++;
			} else {
				if (*fmt)
					fmt++;
			}
		}
	}
	return n;
}
