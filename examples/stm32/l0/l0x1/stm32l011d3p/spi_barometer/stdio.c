/*
 * stdio.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of spi_barometer.
 *
 * spi_barometer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * spi_barometer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with spi_barometer.  If not, see <http://www.gnu.org/licenses/>.
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
	
	for (i = 0; i < 2; i++) {
		h = (x >> ((1 - i) * 4)) & 0xf;
		if (h > 9)
			putchar(h - 10 + 'a');
		else
			putchar(h + '0');
	}
	return 8;
}

static int print_u(unsigned int u)
{
	unsigned int tmp;
	int n;
	int i;
	unsigned int x;
	int j;

	tmp = u;
	n = 1;
	while (tmp >= 10) {
		tmp /= 10;
		n++;
	}
	for (i = 0; i < n; i++) {
		tmp = u;
		x = 1;
		for (j = 0; j < n - i - 1; j++) {
			tmp /= 10;
			x *= 10;
		}
		putchar(tmp + '0');
		u -= tmp * x;
	}
	return n;
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
			} else if (*fmt == 'u') {
				n += print_u(va_arg(argp, unsigned int));
				fmt++;
			} else {
				if (*fmt)
					fmt++;
			}
		}
	}
	return n;
}
