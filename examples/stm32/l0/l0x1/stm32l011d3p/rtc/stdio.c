/*
 * stdio.c
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of rtc.
 *
 * rtc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rtc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rtc.  If not, see <http://www.gnu.org/licenses/>.
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

int puts(const char *s)
{
	if (s) {
		while (*s)
			putchar(*s++);
	}
	putchar('\n');
	return 0;
}

static int print_u(unsigned int u, int width, bool zero)
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
	for (i = 0; i < width - n; i++) {
		if (zero)
			putchar('0');
		else
			putchar(' ');
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

static int print_s(char *s, int width)
{
	int i;

	if (width == 0)
		width = 0x7fffffff;
	for (i = 0; i < width; i++) {
		if (*s)
			putchar(*s++);
		else
			break;
	}
	return i;
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
	bool zero;
	int width;

	va_start(argp, fmt);
	n = 0;
	if (!fmt)
		return 0;
	
	while (*fmt) {
		if (*fmt != '%') {
			putchar(*fmt++);
			n++;
		} else {
			fmt++;
			zero = false;
			if (*fmt == '0') {
				zero = true;
				fmt++;
			}
			width = 0;
			while (isdigit(*fmt)) {
				width = width * 10 + (*fmt - '0');
				fmt++;
			}
			switch (*fmt) {
			case 'u':
				n += print_u(va_arg(argp, unsigned int),
					     width, zero);
				fmt++;
				break;
			case 's':
				n += print_s(va_arg(argp, char *), width);
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
