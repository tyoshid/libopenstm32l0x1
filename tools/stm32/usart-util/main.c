/*
 * main.c
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

/*
 * STMicroelectronics(www.st.com)
 *
 * AN2606: STM32 microcontroller system memory boot mode
 * (21-Apr-2016 Rev 27)
 *
 *
 * AN3155: USART protocol used in the STM32 bootloader
 * (20-Jun-2014 Rev 6)
 */
/*
 * STM32 USART bootloader
 *
 * System memory boot mode:
 *   BOOT0 - High
 *   BOOT1 - Low
 *
 * auto baud rate, 8 bits, even parity and 1 Stop bit
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <strings.h>

#include "command.h"
#include "transfer.h"

#define RETRY	4
#define TIMEOUT	15		/* 1500 ms */

struct {
	char *name;
	speed_t speed;
} baud_table[] = {
	{"1200", B1200},
	{"1800", B1800},
	{"2400", B2400},
	{"4800", B4800},
	{"9600", B9600},
	{"19200", B19200},
	{"38400", B38400},
	{"57600", B57600},
	{"115200", B115200},
	{0, 0}
};
		
bool debug;
bool extended_erase = true;

static void usage(char *prog)
{
	printf("Usage: %s [options]\n", prog);
	printf("  -h\t\tPrint this message\n");
	printf("  -v\t\tPrint verbose debug statements\n");
	printf("  -d <dev>\tSpecify USART device (default: /dev/ttyUSB0)\n");
	printf("  -b <baud>\tSpecify baud rate (default: 115200)\n");
	printf("  -t <bytes>\tSpecify the number of upload transfer bytes\n");
	printf("  -U <file>\tRead firmware from device into file\n");
	printf("  -D <file>\tWrite firmware from file into device\n");
}

int main(int argc, char *argv[])
{
	int opt;
	int i;
	speed_t baudrate = B115200;
	bool download_flag = false;
	char *fname = NULL;
	char *usart = "/dev/ttyUSB0";
	int size = 256;
	bool upload_flag = false;
	FILE *stream;
	int fd;
	struct termios oldtio;
	struct termios newtio;
	int r;
	uint8_t buf[256];
	uint8_t version;
	int num_command;
	uint8_t command[MAX_COM];
	int pid;

	while ((opt = getopt(argc, argv, "b:D:d:ht:U:v")) != -1) {
		switch (opt) {
		case 'b':
			for (i = 0; baud_table[i].name; i++) {
				if (strcmp(optarg, baud_table[i].name) == 0) {
					baudrate = baud_table[i].speed;
					break;
				}
			}
			if (!baud_table[i].name) {
				fprintf(stderr, "Invalid baud rate (%s).\n",
					optarg);
				return 1;
			}
			break;
		case 'D':
			download_flag = true;
			fname = optarg;
			break;
		case 'd':
			usart = optarg;
			break;
		case 'h':
			usage(argv[0]);
			return 0;
		case 't':
			size = atoi(optarg);
			break;
		case 'U':
			upload_flag = true;
			fname = optarg;
			break;
		case 'v':
			debug = true;
			break;
		default:
			usage(argv[0]);
			return 1;
		}
	}

	if ((download_flag && upload_flag) ||
	    (!download_flag && !upload_flag)) {
		fprintf(stderr, "You need to specify one of -D or -U\n");
		return 1;
	}
	if (download_flag)
		stream = fopen(fname, "r");
	else
		stream = fopen(fname, "w");
	if (stream == NULL) {
		perror(fname);
		return 1;
	}

	fd = open(usart, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		perror(usart);
		fclose(stream);
		return 1;
	}
	if (tcgetattr(fd, &oldtio)) {
		perror("tcgetattr() failed");
		close(fd);
		fclose(stream);
		return 1;
	}
	bzero(&newtio, sizeof(newtio));
        if (cfsetospeed(&newtio, baudrate)) {
                perror("cfsetospeed() failed");
                close(fd);
                fclose(stream);
                return 1;
        }
        if (cfsetispeed(&newtio, baudrate)) {
                perror("cfsetispeed() failed");
                close(fd);
                fclose(stream);
                return 1;
        }
        newtio.c_cflag |= CS8 | CLOCAL | CREAD | PARENB;
	newtio.c_cc[VTIME] = TIMEOUT;
	newtio.c_cc[VMIN] = 0;
	if (tcflush(fd, TCIFLUSH)) {
		perror("tcflush() failed");
		close(fd);
		fclose(stream);
		return 1;
	}
	if (tcsetattr(fd, TCSANOW, &newtio)) {
		perror("tcsetattr() failed");
		close(fd);
		fclose(stream);
		return 1;
	}

	r = bootloader_init(fd, RETRY);
	if (r < 0)
		goto ioerror;
	r = get_command(fd, buf);
	if (r < 0)
		goto ioerror;
	if (r == 0) {
		fprintf(stderr, "Can't get the version number.\n");
		goto ioerror;
	}
	version = buf[0];
	printf("Bootloader version %d.%d\n", version >> 4, version & 0xf);
	if (r <= 1 || r > MAX_COM) {
		fprintf(stderr, "Invalid command number (%d).\n", r);
		goto ioerror;
	}
	num_command = r - 1;
	for (i = 1; i < r; i++)
		command[i - 1] = buf[i];
	if (debug) {
		printf("Supported commands\n");
		for (i = 0; i < num_command; i++)
			printf("0x%02x\n", command[i]);
	}
	for (i = 0; i < num_command; i++) {
		if (command[i] == COM_EXTENDED_ERASE)
			break;
	}
	if (i >= num_command)
		extended_erase = false;
	r = get_id(fd, buf);
	if (r < 0)
		goto ioerror;
	if (r != 2) {
		fprintf(stderr, "Invalid data number (%d).\n", r);
		goto ioerror;
	}
	pid = (buf[0] << 8) | buf[1];
	printf("PID 0x%x  ", pid);
	switch (pid) {
		/* STM32F0 */
	case 0x440:
		printf("STM32F05xxx/030x8\n");
		break;
	case 0x444:
		printf("STM32F03xx4/6\n");
		break;
	case 0x442:
		printf("STM32F030xC/09xxx\n");
		break;
	case 0x445:
		printf("STM32F04xxx/070x6\n");
		break;
	case 0x448:
		printf("STM32F070xB/071xx/072xx\n");
		break;

		/* STM32F1 */
	case 0x412:
		printf("STM32F10xxx Low-density\n");
		break;
	case 0x410:
		printf("STM32F10xxx Medium-density\n");
		break;
	case 0x414:
		printf("STM32F10xxx High-density\n");
		break;
	case 0x420:
		printf("STM32F10xxx Medium-density value line\n");
		break;
	case 0x428:
		printf("STM32F10xxx High-density value line\n");
		break;
	case 0x418:
		printf("STM32F105xx/107xx\n");
		break;
	case 0x430:
		printf("STM32F10xxx XL-density\n");
		break;

		/* STM32F2 */
	case 0x411:
		printf("STM32F2xxxx\n");
		break;

		/* STM32F3 */
	case 0x432:
		printf("STM32F373xx/378xx\n");
		break;
	case 0x422:
		printf("STM32F302xB(C)/303xB(C)/358xx\n");
		break;
	case 0x439:
		printf("STM32F301xx/302x4(6/8)/318xx\n");
		break;
	case 0x438:
		printf("STM32F303x4(6/8)/334xx/328xx\n");
		break;
	case 0x446:
		printf("STM32F302xD(E)/303xD(E)/398xx\n");
		break;

		/* STM32F4 */
	case 0x413:
		printf("STM32F40xxx/41xxx\n");
		break;
	case 0x419:
		printf("STM32F42xxx/43xxx\n");
		break;
	case 0x423:
		printf("STM32F401xB(C)\n");
		break;
	case 0x433:
		printf("STM32F401xD(E)\n");
		break;
	case 0x458:
		printf("STM32F410xx\n");
		break;
	case 0x431:
		printf("STM32F411xx\n");
		break;
	case 0x441:
		printf("STM32F412xx\n");
		break;
	case 0x421:
		printf("STM32F446xx\n");
		break;
	case 0x434:
		printf("STM32F469xx/479xx\n");
		break;

		/* STM32F7 */
	case 0x449:
		printf("STM32F74xxx/75xxx\n");
		break;
	case 0x451:
		printf("STM32F76xxx/77xxx\n");
		break;
		
		/* STM32L0 */
	case 0x457:
		printf("STM32L01xxx/02xxx\n");
		break;
	case 0x425:
		printf("STM32L031xx/041xx\n");
		break;
	case 0x417:
		printf("STM32L05xxx/06xxx\n");
		break;
	case 0x447:
		printf("STM32L07xxx/08xxx\n");
		break;
		
		/* STM32L1 */
	case 0x416:
		printf("STM32L1xxx6(8/B)\n");
		break;
	case 0x429:
		printf("STM32L1xxx6(8/B)A\n");
		break;
	case 0x427:
		printf("STM32L1xxxC\n");
		break;
	case 0x436:
		printf("STM32L1xxxD\n");
		break;
	case 0x437:
		printf("STM32L1xxxE\n");
		break;

		/* STM32L4 */
	case 0x435:
		printf("STM32L43xx/44xx\n");
	case 0x415:
		printf("STM32L476xx/486xx\n");
		break;

	default:
		printf("unknown device\n");
		break;
	}

	if (upload_flag)
		r = upload(fd, stream, size);
	if (download_flag) {
		switch (pid) {
		case 0x416:
		case 0x429:
		case 0x427:
		case 0x436:
		case 0x437:
			/* STM32L1 */
			r = download_stm32l1(fd, stream, 256);
			break;
		case 0x457:
		case 0x425:
		case 0x417:
		case 0x447:
			/* STM32L0 */
			r = download_stm32l1(fd, stream, 128);
			break;
		default:
			r = download(fd, stream);
			break;
		}
	}
	if (r < 0)
		goto ioerror;

	if (tcsetattr(fd, TCSANOW, &oldtio)) {
		perror("tcsetattr() failed");
		close(fd);
		fclose(stream);
		return 1;
	}
	if (close(fd)) {
		perror("close() failed");
		fclose(stream);
		return 1;
	}
	if (fclose(stream)) {
		perror("fclose() failed");
		return 1;
	}
	return 0;

ioerror:
	tcsetattr(fd, TCSANOW, &oldtio);
	close(fd);
	fclose(stream);
	return 1;
}
