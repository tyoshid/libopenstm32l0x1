/*
 * DMA
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

/*
 * STMicroelectronics(www.st.com)
 *
 * RM0377: Reference manual
 * Ultra-low-power STM32L0x1 advanced ARM-based 32-bit MCUs
 * (14-Nov-2016 Rev 7)
 *
 * 10  Direct memory access controller (DMA)
 */

/* --- DMA registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		DMA_ISR		DMA interrupt status register
 * 0x04		DMA_IFCR	DMA interrupt flag clear register
 * 0x08		DMA_CCR1	DMA channel 1 configuration register
 * 0x0c		DMA_CNDTR1	DMA channel 1 number of data register
 * 0x10		DMA_CPAR1	DMA channel 1 peripheral address register
 * 0x14		DMA_CMAR1	DMA channel 1 memory address register
 * 0x1c		DMA_CCR2	DMA channel 2 configuration register
 * 0x20		DMA_CNDTR2	DMA channel 2 number of data register
 * 0x24		DMA_CPAR2	DMA channel 2 peripheral address register
 * 0x28		DMA_CMAR2	DMA channel 2 memory address register
 * 0x30		DMA_CCR3	DMA channel 3 configuration register
 * 0x34		DMA_CNDTR3	DMA channel 3 number of data register
 * 0x38		DMA_CPAR3	DMA channel 3 peripheral address register
 * 0x3c		DMA_CMAR3	DMA channel 3 memory address register
 * 0x44		DMA_CCR4	DMA channel 4 configuration register
 * 0x48		DMA_CNDTR4	DMA channel 4 number of data register
 * 0x4c		DMA_CPAR4	DMA channel 4 peripheral address register
 * 0x50		DMA_CMAR4	DMA channel 4 memory address register
 * 0x58		DMA_CCR5	DMA channel 5 configuration register
 * 0x5c		DMA_CNDTR5	DMA channel 5 number of data register
 * 0x60		DMA_CPAR5	DMA channel 5 peripheral address register
 * 0x64		DMA_CMAR5	DMA channel 5 memory address register
 * 0x6c		DMA_CCR6	DMA channel 6 configuration register
 * 0x70		DMA_CNDTR6	DMA channel 6 number of data register
 * 0x74		DMA_CPAR6	DMA channel 6 peripheral address register
 * 0x78		DMA_CMAR6	DMA channel 6 memory address register
 * 0x80		DMA_CCR7	DMA channel 7 configuration register
 * 0x84		DMA_CNDTR7	DMA channel 7 number of data register
 * 0x88		DMA_CPAR7	DMA channel 7 peripheral address register
 * 0x8c		DMA_CMAR7	DMA channel 7 memory address register
 * 0xa8		DMA_CSELR	DMA channel selection register
 */

#define DMA_ISR				(DMA1_BASE + 0x00)
#define DMA_IFCR			(DMA1_BASE + 0x04)

#define DMA_CCR(ch)			(DMA1_BASE + 0x08 + (0x14 * (ch)))
#define DMA_CCR1			DMA_CCR(0)
#define DMA_CCR2			DMA_CCR(1)
#define DMA_CCR3			DMA_CCR(2)
#define DMA_CCR4			DMA_CCR(3)
#define DMA_CCR5			DMA_CCR(4)
#define DMA_CCR6			DMA_CCR(5)
#define DMA_CCR7			DMA_CCR(6)

#define DMA_CNDTR(ch)			(DMA1_BASE + 0x0c + (0x14 * (ch)))
#define DMA_CNDTR1			DMA_CNDTR(0)
#define DMA_CNDTR2			DMA_CNDTR(1)
#define DMA_CNDTR3			DMA_CNDTR(2)
#define DMA_CNDTR4			DMA_CNDTR(3)
#define DMA_CNDTR5			DMA_CNDTR(4)
#define DMA_CNDTR6			DMA_CNDTR(5)
#define DMA_CNDTR7			DMA_CNDTR(6)

#define DMA_CPAR(ch)			(DMA1_BASE + 0x10 + (0x14 * (ch)))
#define DMA_CPAR1			DMA_CPAR(0)
#define DMA_CPAR2			DMA_CPAR(1)
#define DMA_CPAR3			DMA_CPAR(2)
#define DMA_CPAR4			DMA_CPAR(3)
#define DMA_CPAR5			DMA_CPAR(4)
#define DMA_CPAR6			DMA_CPAR(5)
#define DMA_CPAR7			DMA_CPAR(6)

#define DMA_CMAR(ch)			(DMA1_BASE + 0x14 + (0x14 * (ch)))
#define DMA_CMAR1			DMA_CMAR(0)
#define DMA_CMAR2			DMA_CMAR(1)
#define DMA_CMAR3			DMA_CMAR(2)
#define DMA_CMAR4			DMA_CMAR(3)
#define DMA_CMAR5			DMA_CMAR(4)
#define DMA_CMAR6			DMA_CMAR(5)
#define DMA_CMAR7			DMA_CMAR(6)

#define DMA_CSELR			(DMA1_BASE + 0xa8)

/* --- DMA_ISR values ------------------------------------------------------ */

#define DMA_ISR_TEIF7			(1 << 27)
#define DMA_ISR_HTIF7			(1 << 26)
#define DMA_ISR_TCIF7			(1 << 25)
#define DMA_ISR_GIF7			(1 << 24)
#define DMA_ISR_TEIF6			(1 << 23)
#define DMA_ISR_HTIF6			(1 << 22)
#define DMA_ISR_TCIF6			(1 << 21)
#define DMA_ISR_GIF6			(1 << 20)
#define DMA_ISR_TEIF5			(1 << 19)
#define DMA_ISR_HTIF5			(1 << 18)
#define DMA_ISR_TCIF5			(1 << 17)
#define DMA_ISR_GIF5			(1 << 16)
#define DMA_ISR_TEIF4			(1 << 15)
#define DMA_ISR_HTIF4			(1 << 14)
#define DMA_ISR_TCIF4			(1 << 13)
#define DMA_ISR_GIF4			(1 << 12)
#define DMA_ISR_TEIF3			(1 << 11)
#define DMA_ISR_HTIF3			(1 << 10)
#define DMA_ISR_TCIF3			(1 << 9)
#define DMA_ISR_GIF3			(1 << 8)
#define DMA_ISR_TEIF2			(1 << 7)
#define DMA_ISR_HTIF2			(1 << 6)
#define DMA_ISR_TCIF2			(1 << 5)
#define DMA_ISR_GIF2			(1 << 4)
#define DMA_ISR_TEIF1			(1 << 3)
#define DMA_ISR_HTIF1			(1 << 2)
#define DMA_ISR_TCIF1			(1 << 1)
#define DMA_ISR_GIF1			(1 << 0)

/* --- DMA_IFCR values ----------------------------------------------------- */

#define DMA_IFCR_CTEIF7			(1 << 27)
#define DMA_IFCR_CHTIF7			(1 << 26)
#define DMA_IFCR_CTCIF7			(1 << 25)
#define DMA_IFCR_CGIF7			(1 << 24)
#define DMA_IFCR_CTEIF6			(1 << 23)
#define DMA_IFCR_CHTIF6			(1 << 22)
#define DMA_IFCR_CTCIF6			(1 << 21)
#define DMA_IFCR_CGIF6			(1 << 20)
#define DMA_IFCR_CTEIF5			(1 << 19)
#define DMA_IFCR_CHTIF5			(1 << 18)
#define DMA_IFCR_CTCIF5			(1 << 17)
#define DMA_IFCR_CGIF5			(1 << 16)
#define DMA_IFCR_CTEIF4			(1 << 15)
#define DMA_IFCR_CHTIF4			(1 << 14)
#define DMA_IFCR_CTCIF4			(1 << 13)
#define DMA_IFCR_CGIF4			(1 << 12)
#define DMA_IFCR_CTEIF3			(1 << 11)
#define DMA_IFCR_CHTIF3			(1 << 10)
#define DMA_IFCR_CTCIF3			(1 << 9)
#define DMA_IFCR_CGIF3			(1 << 8)
#define DMA_IFCR_CTEIF2			(1 << 7)
#define DMA_IFCR_CHTIF2			(1 << 6)
#define DMA_IFCR_CTCIF2			(1 << 5)
#define DMA_IFCR_CGIF2			(1 << 4)
#define DMA_IFCR_CTEIF1			(1 << 3)
#define DMA_IFCR_CHTIF1			(1 << 2)
#define DMA_IFCR_CTCIF1			(1 << 1)
#define DMA_IFCR_CGIF1			(1 << 0)

/* --- DMA_CCRx values ----------------------------------------------------- */

#define DMA_CCR_MEM2MEM			(1 << 14)
#define DMA_CCR_PL1			(1 << 13)
#define DMA_CCR_PL0			(1 << 12)
#define DMA_CCR_MSIZE1			(1 << 11)
#define DMA_CCR_MSIZE0			(1 << 10)
#define DMA_CCR_PSIZE1			(1 << 9)
#define DMA_CCR_PSIZE0			(1 << 8)
#define DMA_CCR_MINC			(1 << 7)
#define DMA_CCR_PINC			(1 << 6)
#define DMA_CCR_CIRC			(1 << 5)
#define DMA_CCR_DIR			(1 << 4)
#define DMA_CCR_TEIE			(1 << 3)
#define DMA_CCR_HTIE			(1 << 2)
#define DMA_CCR_TCIE			(1 << 1)
#define DMA_CCR_EN			(1 << 0)

/* Channel priority level */
#define DMA_CCR_PL_LOW			(0 << 12)
#define DMA_CCR_PL_MEDIUM		(1 << 12)
#define DMA_CCR_PL_HIGH			(2 << 12)
#define DMA_CCR_PL_VERY_HIGH		(3 << 12)

/* Memory size */
#define DMA_CCR_MSIZE_8			(0 << 10)
#define DMA_CCR_MSIZE_16		(1 << 10)
#define DMA_CCR_MSIZE_32		(2 << 10)

/* Peripheral size */
#define DMA_CCR_PSIZE_8			(0 << 8)
#define DMA_CCR_PSIZE_16		(1 << 8)
#define DMA_CCR_PSIZE_32		(2 << 8)

/* --- DMA_CNDTRx values --------------------------------------------------- */

/* DMA_CNDTR[15:0]: NDT[15:0]: Number of data to transfer */

/* --- DMA_CPARx values ---------------------------------------------------- */

/* DMA_CPAR[31:0]: PA[31:0]: Peripheral address */

/* --- DMA_CMARx values ---------------------------------------------------- */

/* DMA_CMAR[31:0]: MA[31:0]: Memory address */

/* --- DMA_CSELR values ---------------------------------------------------- */

#define DMA_CSELR_C7S3			(1 << 27)
#define DMA_CSELR_C7S2			(1 << 26)
#define DMA_CSELR_C7S1			(1 << 25)
#define DMA_CSELR_C7S0			(1 << 24)
#define DMA_CSELR_C6S3			(1 << 23)
#define DMA_CSELR_C6S2			(1 << 22)
#define DMA_CSELR_C6S1			(1 << 21)
#define DMA_CSELR_C6S0			(1 << 20)
#define DMA_CSELR_C5S3			(1 << 19)
#define DMA_CSELR_C5S2			(1 << 18)
#define DMA_CSELR_C5S1			(1 << 17)
#define DMA_CSELR_C5S0			(1 << 16)
#define DMA_CSELR_C4S3			(1 << 15)
#define DMA_CSELR_C4S2			(1 << 14)
#define DMA_CSELR_C4S1			(1 << 13)
#define DMA_CSELR_C4S0			(1 << 12)
#define DMA_CSELR_C3S3			(1 << 11)
#define DMA_CSELR_C3S2			(1 << 10)
#define DMA_CSELR_C3S1			(1 << 9)
#define DMA_CSELR_C3S0			(1 << 8)
#define DMA_CSELR_C2S3			(1 << 7)
#define DMA_CSELR_C2S2			(1 << 6)
#define DMA_CSELR_C2S1			(1 << 5)
#define DMA_CSELR_C2S0			(1 << 4)
#define DMA_CSELR_C1S3			(1 << 3)
#define DMA_CSELR_C1S2			(1 << 2)
#define DMA_CSELR_C1S1			(1 << 1)
#define DMA_CSELR_C1S0			(1 << 0)

/* DMA channel 7 selection */
#define DMA_CSELR_C7S_SPI2_TX		(2 << 24)
#define DMA_CSELR_C7S_USART2_TX		(4 << 24)
#define DMA_CSELR_C7S_LPUART1_TX	(5 << 24)
#define DMA_CSELR_C7S_I2C1_RX		(6 << 24)
#define DMA_CSELR_C7S_TIM2_CH2_CH4	(8 << 24)
#define DMA_CSELR_C7S_USART4_TX		(12 << 24)
#define DMA_CSELR_C7S_USART5_TX		(13 << 24)

/* DMA channel 6 selection */
#define DMA_CSELR_C6S_SPI2_RX		(2 << 20)
#define DMA_CSELR_C6S_USART2_RX		(4 << 20)
#define DMA_CSELR_C6S_LPUART1_RX	(5 << 20)
#define DMA_CSELR_C6S_I2C1_TX		(6 << 20)
#define DMA_CSELR_C6S_TIM3_TRIG		(10 << 20)
#define DMA_CSELR_C6S_USART4_RX		(12 << 20)
#define DMA_CSELR_C6S_USART5_RX		(13 << 20)

/* DMA channel 5 selection */
#define DMA_CSELR_C5S_SPI1_TX		(1 << 16)
#define DMA_CSELR_C5S_SPI2_TX		(2 << 16)
#define DMA_CSELR_C5S_USART1_RX		(3 << 16)
#define DMA_CSELR_C5S_USART2_RX		(4 << 16)
#define DMA_CSELR_C5S_LPUART1_RX	(5 << 16)
#define DMA_CSELR_C5S_I2C1_RX		(6 << 16)
#define DMA_CSELR_C5S_I2C2_RX		(7 << 16)
#define DMA_CSELR_C5S_TIM2_CH1		(8 << 16)
#define DMA_CSELR_C5S_TIM3_CH1		(10 << 16)
#define DMA_CSELR_C5S_AES_IN		(11 << 16)
#define DMA_CSELR_C5S_I2C3_RX		(14 << 16)

/* DMA channel 4 selection */
#define DMA_CSELR_C4S_ADC		(0 << 12)
#define DMA_CSELR_C4S_SPI1_RX		(1 << 12)
#define DMA_CSELR_C4S_SPI2_RX		(2 << 12)
#define DMA_CSELR_C4S_USART1_TX		(3 << 12)
#define DMA_CSELR_C4S_USART2_TX		(4 << 12)
#define DMA_CSELR_C4S_LPUART1_TX	(5 << 12)
#define DMA_CSELR_C4S_I2C1_TX		(6 << 12)
#define DMA_CSELR_C4S_I2C2_TX		(7 << 12)
#define DMA_CSELR_C4S_TIM2_CH4		(8 << 12)
#define DMA_CSELR_C4S_I2C3_TX		(14 << 12)
#define DMA_CSELR_C4S_TIM7_UP		(15 << 12)

/* DMA channel 3 selection */
#define DMA_CSELR_C3S_SPI1_TX		(1 << 8)
#define DMA_CSELR_C3S_USART1_RX		(3 << 8)
#define DMA_CSELR_C3S_USART2_RX		(4 << 8)
#define DMA_CSELR_C3S_LPUART1_RX	(5 << 8)
#define DMA_CSELR_C3S_I2C1_RX		(6 << 8)
#define DMA_CSELR_C3S_TIM2_CH2		(8 << 8)
#define DMA_CSELR_C3S_TIM3_CH4_UP	(10 << 8)
#define DMA_CSELR_C3S_AES_OUT		(11 << 8)
#define DMA_CSELR_C3S_USART4_TX		(12 << 8)
#define DMA_CSELR_C3S_USART5_TX		(13 << 8)
#define DMA_CSELR_C3S_I2C3_RX		(14 << 8)

/* DMA channel 2 selection */
#define DMA_CSELR_C2S_ADC		(0 << 4)
#define DMA_CSELR_C2S_SPI1_RX		(1 << 4)
#define DMA_CSELR_C2S_USART1_TX		(3 << 4)
#define DMA_CSELR_C2S_USART2_TX		(4 << 4)
#define DMA_CSELR_C2S_LPUART1_TX	(5 << 4)
#define DMA_CSELR_C2S_I2C1_TX		(6 << 4)
#define DMA_CSELR_C2S_TIM2_UP		(8 << 4)
#define DMA_CSELR_C2S_TIM6_UP		(9 << 4)
#define DMA_CSELR_C2S_TIM3_CH3		(10 << 4)
#define DMA_CSELR_C2S_AES_OUT		(11 << 4)
#define DMA_CSELR_C2S_USART4_RX		(12 << 4)
#define DMA_CSELR_C2S_USART5_RX		(13 << 4)
#define DMA_CSELR_C2S_I2C3_TX		(14 << 4)

/* DMA channel 1 selection */
#define DMA_CSELR_C1S_ADC		(0 << 0)
#define DMA_CSELR_C1S_TIM2_CH3		(8 << 0)
#define DMA_CSELR_C1S_AES_IN		(11 << 0)

/* --- Function prototypes ------------------------------------------------- */

/* Request */
enum {
	DMA_CH1_ADC = (0 << 0),
	DMA_CH1_TIM2_CH3 = (8 << 0),
	DMA_CH1_AES_IN = (11 << 0),

	DMA_CH2_ADC = (0 << 4),
	DMA_CH2_SPI1_RX = (1 << 4),
	DMA_CH2_USART1_TX = (3 << 4),
	DMA_CH2_USART2_TX = (4 << 4),
	DMA_CH2_LPUART1_TX = (5 << 4),
	DMA_CH2_I2C1_TX = (6 << 4),
	DMA_CH2_TIM2_UP = (8 << 4),
	DMA_CH2_TIM6_UP = (9 << 4),
	DMA_CH2_TIM3_CH3 = (10 << 4),
	DMA_CH2_AES_OUT = (11 << 4),
	DMA_CH2_USART4_RX = (12 << 4),
	DMA_CH2_USART5_RX = (13 << 4),
	DMA_CH2_I2C3_TX = (14 << 4),

	DMA_CH3_SPI1_TX = (1 << 8),
	DMA_CH3_USART1_RX = (3 << 8),
	DMA_CH3_USART2_RX = (4 << 8),
	DMA_CH3_LPUART1_RX = (5 << 8),
	DMA_CH3_I2C1_RX = (6 << 8),
	DMA_CH3_TIM2_CH2 = (8 << 8),
	DMA_CH3_TIM3_CH4 = (10 << 8),
	DMA_CH3_TIM3_UP = (10 << 8),
	DMA_CH3_AES_OUT = (11 << 8),
	DMA_CH3_USART4_TX = (12 << 8),
	DMA_CH3_USART5_TX = (13 << 8),
	DMA_CH3_I2C3_RX = (14 << 8),

	DMA_CH4_ADC = (0 << 12),
	DMA_CH4_SPI1_RX = (1 << 12),
	DMA_CH4_SPI2_RX = (2 << 12),
	DMA_CH4_USART1_TX = (3 << 12),
	DMA_CH4_USART2_TX = (4 << 12),
	DMA_CH4_LPUART1_TX = (5 << 12),
	DMA_CH4_I2C1_TX = (6 << 12),
	DMA_CH4_I2C2_TX = (7 << 12),
	DMA_CH4_TIM2_CH4 = (8 << 12),
	DMA_CH4_I2C3_TX = (14 << 12),
	DMA_CH4_TIM7_UP = (15 << 12),

	DMA_CH5_SPI1_TX = (1 << 16),
	DMA_CH5_SPI2_TX = (2 << 16),
	DMA_CH5_USART1_RX = (3 << 16),
	DMA_CH5_USART2_RX = (4 << 16),
	DMA_CH5_LPUART1_RX = (5 << 16),
	DMA_CH5_I2C1_RX = (6 << 16),
	DMA_CH5_I2C2_RX = (7 << 16),
	DMA_CH5_TIM2_CH1 = (8 << 16),
	DMA_CH5_TIM3_CH1 = (10 << 16),
	DMA_CH5_AES_IN = (11 << 16),
	DMA_CH5_I2C3_RX = (14 << 16),

	DMA_CH6_SPI2_RX = (2 << 20),
	DMA_CH6_USART2_RX = (4 << 20),
	DMA_CH6_LPUART1_RX = (5 << 20),
	DMA_CH6_I2C1_TX = (6 << 20),
	DMA_CH6_TIM3_TRIG = (10 << 20),
	DMA_CH6_USART4_RX = (12 << 20),
	DMA_CH6_USART5_RX = (13 << 20),

	DMA_CH7_SPI2_TX = (2 << 24),
	DMA_CH7_USART2_TX = (4 << 24),
	DMA_CH7_LPUART1_TX = (5 << 24),
	DMA_CH7_I2C1_RX = (6 << 24),
	DMA_CH7_TIM2_CH2 = (8 << 24),
	DMA_CH7_TIM2_CH4 = (8 << 24),
	DMA_CH7_USART4_TX = (12 << 24),
	DMA_CH7_USART5_TX = (13 << 24)
};

/* Channel number */
enum dma_channel {
	DMA_CH1,
	DMA_CH2,
	DMA_CH3,
	DMA_CH4,
	DMA_CH5,
	DMA_CH6,
	DMA_CH7
};

/* Configuration */
enum {
	DMA_ENABLE = (1 << 0),
	DMA_M_TO_P = (1 << 4),
	DMA_P_TO_M = 0,
	DMA_CIRCULAR = (1 << 5),
	DMA_P_INC = (1 << 6),
	DMA_M_INC = (1 << 7),
	DMA_P_8BIT = (0 << 8),
	DMA_P_16BIT = (1 << 8),
	DMA_P_32BIT = (2 << 8),
	DMA_M_8BIT = (0 << 10),
	DMA_M_16BIT = (1 << 10),
	DMA_M_32BIT = (2 << 10),
	DMA_LOW = (0 << 12),
	DMA_MEDIUM = (1 << 12),
	DMA_HIGH = (2 << 12),
	DMA_VERY_HIGH = (3 << 12),
	DMA_M_TO_M = (1 << 14)
};

/* Interrupt */
enum {
	DMA_GLOBAL = (1 << 0),
	DMA_COMPLETE = (1 << 1),
	DMA_HALF = (1 << 2),
	DMA_ERROR = (1 << 3)
};

void dma_set_request(int request);
void dma_setup_channel(enum dma_channel ch, int ma, int pa, int ndt,
		       int config);
void dma_set_memory_address(enum dma_channel ch, int ma);
void dma_set_peripheral_address(enum dma_channel ch, int pa);
void dma_set_number_of_data(enum dma_channel ch, int ndt);
int dma_get_number_of_data(enum dma_channel ch);
void dma_set_config(enum dma_channel ch, int config);
void dma_enable(enum dma_channel ch);
void dma_disable(enum dma_channel ch);
void dma_enable_interrupt(enum dma_channel ch, int interrupt);
void dma_disable_interrupt(enum dma_channel ch, int interrupt);
int dma_get_interrupt_mask(enum dma_channel ch, int interrupt);
int dma_get_interrupt_status(enum dma_channel ch, int interrupt);
void dma_clear_interrupt(enum dma_channel ch, int interrupt);
