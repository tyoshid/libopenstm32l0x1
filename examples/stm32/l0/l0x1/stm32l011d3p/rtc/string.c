/*
 * string.c
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

int strlen(const char *s)
{
	int n;

	n = 0;
	while (*s++)
		n++;
	return n;
}

int strcmp(const char *s1, const char *s2)
{
	int d;
	
	do {
		d = *s1 - *s2++;
	} while (d == 0 && *s1++);
	return d;
}

static int isdelim(int c, const char *delim)
{
	while (*delim) {
		if (c == *delim)
			break;
		delim++;
	}
	return *delim;
}

static char *strtok1(char *p, const char *delim, char **next)
{
	char *t;
	
	while (*p) {
		if (!isdelim(*p, delim))
			break;
		p++;
	}
	if (!*p)
		return 0;
	t = p;
	while (*p) {
		if (isdelim(*p, delim))
			break;
		p++;
	}
	if (*p)
		*p++ = '\0';
	*next = p;
	return t;
}

char *strtok(char *str, const char *delim)
{
	static char *next;

	return strtok1(str ? str : next, delim, &next);
}	
