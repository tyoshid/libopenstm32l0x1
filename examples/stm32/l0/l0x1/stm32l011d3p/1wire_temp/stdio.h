/*
 * stdio.h
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This file is part of 1wire_temp.
 *
 * 1wire_temp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 1wire_temp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 1wire_temp.  If not, see <http://www.gnu.org/licenses/>.
 */

#define fprintf(stream, ...) printf(__VA_ARGS__)

int puts(const char *s);
int printf(const char *fmt, ...);

