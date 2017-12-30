/*
 * stdio.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of lpuart_getchar.
 *
 * lpuart_getchar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lpuart_getchar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lpuart_getchar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdarg.h>

void tx_write_blocking(int data);
int rx_read_blocking(void);

int getchar(void)
{
	int r;

	r = rx_read_blocking();
	if (r == '\r')
		r = '\n';
	return r;
}

int putchar(int c)
{
	if (c == '\n')
		tx_write_blocking('\r');
	tx_write_blocking(c);
	return c;
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

static int print_s(char *s)
{
	int n;
	
	n = 0;
	while (*s) {
		putchar(*s++);
		n++;
	}
	return n;
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
			fmt++;
			switch (*fmt) {
			case 'u':
				n += print_u(va_arg(argp, unsigned int));
				fmt++;
				break;
			case 's':
				n += print_s(va_arg(argp, char *));
				fmt++;
				break;
			default:
				if (*fmt)
					fmt++;
				break;
			}
		}
	}
	return n;
}
