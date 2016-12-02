/*
 * stdlib.c
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

int strtol(const char *nptr, char **endptr, int base)
{
	int s;
	int n;

	if (base != 10)
		return 0;
	
	while (*nptr == ' ' || *nptr == '\t')
		nptr++;
	if (*nptr == '-') {
		s = -1;
		nptr++;
	} else {
		s = 1;
		if (*nptr == '+')
			nptr++;
	}
	n = 0;
	while (*nptr >= '0' && *nptr <= '9')
		n = n * 10 + *nptr++ - '0';
	*endptr = (char *)nptr;
	return n * s;
}
