/*
 * barometer.c
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

#include <stdint.h>
#include <stdbool.h>

#include <gpio.h>
#include <dma.h>
#include <memorymap.h>
#include <spi.h>

#include "spi_barometer.h"

/*
 * Freescale MPL115A1
 * Miniature SPI Digital Barometer
 *
 * Ofmax	8MHz		Operating Frequency
 *
 * /CS - PA4
 */
#define START_CONVERSIONS	0x24
#define READ_PRESSURE_MSB	0x80
#define READ_PRESSURE_LSB	0x82
#define READ_TEMPERATURE_MSB	0x84
#define READ_TEMPERATURE_LSB	0x86
#define READ_A0_MSB		0x88
#define READ_A0_LSB		0x8a
#define READ_B1_MSB		0x8c
#define READ_B1_LSB		0x8e
#define READ_B2_MSB		0x90
#define READ_B2_LSB		0x92
#define READ_C12_MSB		0x94
#define READ_C12_LSB		0x96
#define TC			3	/* Conversion Time: 3 ms */
#define TW			5	/* Wakeup Time: 5 ms */

static int16_t a0;
static int16_t b1;
static int16_t b2;
static int16_t c12;

static void baro_transfer(const char *sndbuf, char *rcvbuf, int n)
{
	gpio_clear(GPIO_PA4);
	dma_setup_channel(DMA_CH2, (int)rcvbuf, SPI1_DR, n,
			  DMA_M_INC | DMA_ENABLE);
	dma_setup_channel(DMA_CH3, (int)sndbuf, SPI1_DR, n,
			  DMA_M_INC | DMA_M_TO_P | DMA_ENABLE);
	spi_enable_dma(SPI1, SPI_DMA_TX_RX);
	while (!dma_get_interrupt_status(DMA_CH2, DMA_COMPLETE))
		;
	gpio_set(GPIO_PA4);
	spi_disable_dma(SPI1, SPI_DMA_TX_RX);
	dma_disable(DMA_CH2);
	dma_disable(DMA_CH3);
	dma_clear_interrupt(DMA_CH2, DMA_GLOBAL);
	dma_clear_interrupt(DMA_CH3, DMA_GLOBAL);
}

/*
 * Calculate the compensated pressure PComp value
 * PComp = a0 + (b1 + c12 * Tadc) * Padc + b2 * Tadc
 *
 * c12 Signed, Integer Bits = 0, Fractional Bits = 13,
 * dec pt zero pad = 9
 *
 * c12x2 = c12 * Tadc
 *
 * b1 Signed, Integer Bits = 2, Fractional Bits = 13
 * a1 = b1 + c12x2
 *
 * a1x1 = a1 * Padc
 *
 * a0 Signed, Integer Bits = 12, Fractional Bits = 3
 * y1 = a0 + a1x1
 *
 * b2 Signed, Integer Bits = 1, Fractional Bits = 14
 * a2x2 = b2 * Tadc
 *
 * Pcomp = y1 + a2x2
 * Fractional Bits = 4
 */
static int16_t calc_pcomp(uint16_t padc, uint16_t tadc)
{
	int32_t c12x2;
	int32_t a1;
	int32_t a1x1;
	int32_t y1;
	int32_t a2x2;
	int32_t pcomp;

	c12x2 = ((int32_t)c12 * tadc) >> 11;
	a1 = (int32_t)b1 + c12x2;
	a1x1 = a1 * padc;
	y1 = ((int32_t)a0 << 10) + a1x1;
	a2x2 = ((int32_t)b2 * tadc) >> 1;
	pcomp = (y1 + a2x2) >> 9;
	return pcomp;
}

void baro_init(void)
{
	static const char coeff[] = {
		READ_A0_MSB, 0,
		READ_A0_LSB, 0,
		READ_B1_MSB, 0,
		READ_B1_LSB, 0,
		READ_B2_MSB, 0,
		READ_B2_LSB, 0,
		READ_C12_MSB, 0,
		READ_C12_LSB, 0,
		0
	};
	uint8_t buf[32];

	delay_ms(TW);
	baro_transfer(coeff, (char *)buf, sizeof(coeff));
	/*
	printf("a0=0x%02x%02x b1=0x%02x%02x b2=0x%02x%02x "
	       "c12=0x%02x%02x\n", (unsigned int)buf[1],
	       (unsigned int)buf[3], (unsigned int)buf[5],
	       (unsigned int)buf[7], (unsigned int)buf[9],
	       (unsigned int)buf[11], (unsigned int)buf[13],
	       (unsigned int)buf[15]);
	*/
	a0 = (buf[1] << 8) | buf[3];
	b1 = (buf[5] << 8) | buf[7];
	b2 = (buf[9] << 8) | buf[11];
	c12 = (buf[13] << 8) | buf[15];
}

/*
 * Pressure = PComp * ((115.0 - 50.0) / 1023.0) + 50
 * Pressure = ((PComp * 1041) >> 14) + 50
 * Fractional Bits = 4
 */
int baro_measure(void)
{
	static const char conv[] = {
		START_CONVERSIONS,
		0
	};
	uint8_t buf[32];
	static const char press[] = {
		READ_PRESSURE_MSB, 0,
		READ_PRESSURE_LSB, 0,
		READ_TEMPERATURE_MSB, 0,
		READ_TEMPERATURE_LSB, 0,
		0
	};
	uint16_t padc;
	uint16_t tadc;
	int16_t pcomp;

	baro_transfer(conv, (char *)buf, sizeof(conv));
	delay_ms(TC);
	baro_transfer(press, (char *)buf, sizeof(press));
	padc = (buf[1] << 8) | buf[3];
	padc >>= 6;
	tadc = (buf[5] << 8) | buf[7];
	tadc >>= 6;
	/*
	printf("padc=%u tadc=%u\n", padc, tadc);
	*/
	pcomp = calc_pcomp(padc, tadc);
	return (((int)pcomp * 1041) >> 14) + 800;
}
