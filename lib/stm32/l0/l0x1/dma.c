/*
 * DMA functions
 *
 * Copyright 2015 Toshiaki Yoshida <yoshida@mpc.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include <mmio.h>
#include <memorymap.h>
#include <dma.h>

void dma_set_request(int request)
{
	int r;
	int i;
	
	r = MMIO32(DMA_CSELR);
	for (i = 0; i < 7; i++) {
		if (request & (0xf << i * 4))
			r &= ~(0xf << i * 4);
	}
	MMIO32(DMA_CSELR) = r | (request & 0xfffffff);
}

void dma_setup_channel(enum dma_channel ch, int ma, int pa, int ndt,
		       int config)
{
	MMIO32(DMA_CMAR(ch)) = ma;
	MMIO32(DMA_CPAR(ch)) = pa;
	MMIO32(DMA_CNDTR(ch)) = ndt & 0xffff;
	MMIO32(DMA_CCR(ch)) = config & (DMA_CCR_MEM2MEM |
					DMA_CCR_PL1 | DMA_CCR_PL0 |
					DMA_CCR_MSIZE1 | DMA_CCR_MSIZE0 |
					DMA_CCR_PSIZE1 | DMA_CCR_PSIZE0 |
					DMA_CCR_MINC | DMA_CCR_PINC |
					DMA_CCR_CIRC |
					DMA_CCR_DIR |
					DMA_CCR_TEIE | DMA_CCR_HTIE |
					DMA_CCR_TCIE | DMA_CCR_EN);
}

void dma_set_memory_address(enum dma_channel ch, int ma)
{
	MMIO32(DMA_CMAR(ch)) = ma;
}

void dma_set_peripheral_address(enum dma_channel ch, int pa)
{
	MMIO32(DMA_CPAR(ch)) = pa;
}

void dma_set_number_of_data(enum dma_channel ch, int ndt)
{
	MMIO32(DMA_CNDTR(ch)) = ndt & 0xffff;
}

int dma_get_number_of_data(enum dma_channel ch)
{
	return MMIO32(DMA_CNDTR(ch));
}

void dma_set_config(enum dma_channel ch, int config)
{
	MMIO32(DMA_CCR(ch)) = config & (DMA_CCR_MEM2MEM |
					DMA_CCR_PL1 | DMA_CCR_PL0 |
					DMA_CCR_MSIZE1 | DMA_CCR_MSIZE0 |
					DMA_CCR_PSIZE1 | DMA_CCR_PSIZE0 |
					DMA_CCR_MINC | DMA_CCR_PINC |
					DMA_CCR_CIRC |
					DMA_CCR_DIR |
					DMA_CCR_TEIE | DMA_CCR_HTIE |
					DMA_CCR_TCIE | DMA_CCR_EN);
}

void dma_enable(enum dma_channel ch)
{
	MMIO32(DMA_CCR(ch)) |= DMA_CCR_EN;
}

void dma_disable(enum dma_channel ch)
{
	MMIO32(DMA_CCR(ch)) &= ~DMA_CCR_EN;
}

void dma_enable_interrupt(enum dma_channel ch, int interrupt)
{
	MMIO32(DMA_CCR(ch)) |= interrupt & (DMA_CCR_TEIE | DMA_CCR_HTIE |
					    DMA_CCR_TCIE);
}

void dma_disable_interrupt(enum dma_channel ch, int interrupt)
{
	MMIO32(DMA_CCR(ch)) &= ~(interrupt & (DMA_CCR_TEIE | DMA_CCR_HTIE |
					      DMA_CCR_TCIE));
}

int dma_get_interrupt_mask(enum dma_channel ch, int interrupt)
{
	return MMIO32(DMA_CCR(ch)) & interrupt & (DMA_CCR_TEIE | DMA_CCR_HTIE |
						  DMA_CCR_TCIE);
}

int dma_get_interrupt_status(enum dma_channel ch, int interrupt)
{
	return (MMIO32(DMA_ISR) >> ch * 4) & interrupt;
}

void dma_clear_interrupt(enum dma_channel ch, int interrupt)
{
	MMIO32(DMA_IFCR) = (interrupt & 0xf) << ch * 4;
}
