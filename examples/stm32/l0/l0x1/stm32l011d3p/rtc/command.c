/*
 * command.c
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

#include <gpio.h>
#include <tim.h>
#include <nvic.h>
#include <vector.h>
#include <rtc.h>

#include "rtc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "strings.h"

#define MAXTOKEN		10
#define BUFSIZE			64
#define DELIMITER		" /.,;:"
#define PROMPT			"rtc> "

/* Day of week */
const char week_day_name[8][4] = {
	"???",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
	"Sun"
};

/* Month */
const char month_name[13][4] = {
	"???",
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

static void print_date(int date, int time, int ss)
{
	unsigned int u;

	printf("%s ", week_day_name[(date >> 13) & 7]);
	u = ((date >> 12) & 1) * 10 + ((date >> 8) & 15);
	if (u <= 12)
		printf("%s ", month_name[u]);
	u = ((date >> 4) & 3) * 10 + (date & 15);
	printf("%2u ", u);
	u = ((time >> 20) & 3) * 10 + ((time >> 16) & 15);
	printf("%02u:", u);
	u = ((time >> 12) & 7) * 10 + ((time >> 8) & 15);
	printf("%02u:", u);
	u = ((time >> 4) & 7) * 10 + (time & 15);
	printf("%02u", u);
	if (ss < 0) {
		printf(" ");
	} else if (ss > PREDIV_S) {
		printf(".?????? ");
	} else {
		u = ((PREDIV_S - ss) * 1000000 + (PREDIV_S + 1) / 2) /
			(PREDIV_S + 1);
		printf(".%06u ", u);
	}
	u = ((date >> 20) & 15) * 10 + ((date >> 16) & 15);
	printf("20%02u\n", u);
}

static int str_date(char **p, int *date, int *time)
{
	int i;
	int d;
	int t;
	char *endp;
	
	for (i = 1; i <= 7; i++) {
		if (strncasecmp(p[1], week_day_name[i], 3) == 0)
			break;
	}
	if (i > 7)
		return 1;
	d = i << 13;
	for (i = 1; i <= 12; i++) {
		if (strncasecmp(p[2], month_name[i], 3) == 0)
			break;
	}
	if (i > 12)
		return 2;
	d |= (i / 10) << 12;
	d |= (i % 10) << 8;
	i = strtol(p[3], &endp, 10);
	if (*endp)
		return 3;
	if (i <= 0 || i > 31)
		return 3;
	d |= (i / 10) << 4;
	d |= i % 10;
	i = strtol(p[4], &endp, 10);
	if (*endp)
		return 4;
	if (i < 0 || i >= 24)
		return 4;
	t = (i / 10) << 20;
	t |= (i % 10) << 16;
	i = strtol(p[5], &endp, 10);
	if (*endp)
		return 5;
	if (i < 0 || i >= 60)
		return 5;
	t |= (i / 10) << 12;
	t |= (i % 10) << 8;
	i = strtol(p[6], &endp, 10);
	if (*endp)
		return 6;
	if (i < 0 || i >= 60)
		return 6;
	t |= (i / 10) << 4;
	t |= i % 10;
	i = strtol(p[8], &endp, 10);
	if (*endp)
		return 8;
	if (i < 2000 || i > 2099)
		return 8;
	d |= (i / 10 % 10) << 20;
	d |= (i % 10) << 16;
	*date = d;
	*time = t;
	return 0;
}

static void date(int n, char **p)
{
	int date;
	int time;
	int ss;
	int r;

	if (n != 1 && n != 9) {
		puts("Invalid argument: date [<day_of_week> <month> dd \\");
		puts("                        hh:mm:ss <not_used> 20yy]");
		return;
	}
	if (n == 9 && (r = str_date(p, &date, &time))) {
		printf("Invalid value: %s ", p[r]);
		switch (r) {
		case 1:
			puts("(Mon - Sun)");
			break;
		case 2:
			puts("(Jan - Dec)");
			break;
		case 3:
			puts("(1 - 31)");
			break;
		case 4:
			puts("(0 - 23)");
			break;
		case 5:
			puts("(0 - 59)");
			break;
		case 6:
			puts("(0 - 59)");
			break;
		case 8:
			puts("(2000 - 2099)");
			break;
		default:
			break;
		}
		return;
	}
	
	nvic_disable_irq(NVIC_RTC);
	if (n == 9) {
		rtc_unlock();
		rtc_init(PREDIV_A, PREDIV_S, date, time, false, false);
		rtc_lock();
	}
	rtc_get_calendar(&date, &time, &ss);
	nvic_enable_irq(NVIC_RTC);
	print_date(date, time, ss);
}

static void help(void)
{
	puts("Usage:");
	puts("  date                             Print date and time");
	puts("  date <day_of_week> <month> dd \\");
	puts("        hh:mm:ss <not_used> 20yy   Set date and time");
	puts("  help                             Print this message");
}

static int isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return 1;
	return 0;
}

static void get_line(char buf[])
{
	int i;
	int c;

	i = 0;
	do {
		c = getchar();
		if (isprint(c)) {
			putchar(c);
			if (i < BUFSIZE - 1)
				buf[i++] = c;
		} else {
			switch (c) {
			case '\b':
				if (i > 0) {
					putchar('\b');
					putchar(' ');
					putchar('\b');
					--i;
				}
				break;
			case '\n':
				putchar('\n');
				buf[i] = '\0';
				break;
			default:
				break;
			}
		}
	} while (c != '\n');
}

void command(void)
{
	static char buf[BUFSIZE];
	int i;
	static char *p[MAXTOKEN];

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	while (1) {
		printf(PROMPT);
		get_line(buf);
		for (i = 0; i < MAXTOKEN; i++) {
			p[i] = strtok(i ? NULL : buf, DELIMITER);
			if (p[i] == NULL)
				break;
		}
		if (i == 0)
			continue;
		if (strncasecmp(p[0], "date", strlen(p[0])) == 0)
			date(i, p);

		else if (strncasecmp(p[0], "help", strlen(p[0])) == 0 ||
			 strcmp(p[0], "?") == 0)
			help();
		else
			puts("unknown command");
	}
}
