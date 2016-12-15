/*
 * GPIO
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
 * Ultra-low-power STM32L0x2 advanced ARM-based 32-bit MCUs
 * (14-Nov-2016 Rev 7)
 *
 * 8  General-purpose I/Os (GPIO)
 */

/* --- GPIO registers ------------------------------------------------------ */
/*
 * Offset	Register
 * 0x00		GPIOx_MODER	GPIO port mode register
 * 0x04		GPIOx_OTYPER	GPIO port output type register
 * 0x08		GPIOx_OSPEEDR	GPIO port output speed register
 * 0x0c		GPIOx_PUPDR	GPIO port pull-up/pull-down register
 * 0x10		GPIOx_IDR	GPIO port input data register
 * 0x14		GPIOx_ODR	GPIO port output data register
 * 0x18		GPIOx_BSRR	GPIO port bit set/reset register
 * 0x1c		GPIOx_LCKR	GPIO port configuration lock register
 * 0x20		GPIOx_AFRL	GPIO alternate function low register
 * 0x24		GPIOx_AFRH	GPIO alternate function high register
 * 0x28		GPIOx_BRR	GPIO port bit reset register
 */

#define GPIO_MODER(base)		((base) + 0x00)
#define GPIOA_MODER			GPIO_MODER(GPIOA_BASE)
#define GPIOB_MODER			GPIO_MODER(GPIOB_BASE)
#define GPIOC_MODER			GPIO_MODER(GPIOC_BASE)
#define GPIOD_MODER			GPIO_MODER(GPIOD_BASE)
#define GPIOE_MODER			GPIO_MODER(GPIOE_BASE)
#define GPIOH_MODER			GPIO_MODER(GPIOH_BASE)

#define GPIO_OTYPER(base)		((base) + 0x04)
#define GPIOA_OTYPER			GPIO_OTYPER(GPIOA_BASE)
#define GPIOB_OTYPER			GPIO_OTYPER(GPIOB_BASE)
#define GPIOC_OTYPER			GPIO_OTYPER(GPIOC_BASE)
#define GPIOD_OTYPER			GPIO_OTYPER(GPIOD_BASE)
#define GPIOE_OTYPER			GPIO_OTYPER(GPIOE_BASE)
#define GPIOH_OTYPER			GPIO_OTYPER(GPIOH_BASE)

#define GPIO_OSPEEDR(base)		((base) + 0x08)
#define GPIOA_OSPEEDR			GPIO_OSPEEDR(GPIOA_BASE)
#define GPIOB_OSPEEDR			GPIO_OSPEEDR(GPIOB_BASE)
#define GPIOC_OSPEEDR			GPIO_OSPEEDR(GPIOC_BASE)
#define GPIOD_OSPEEDR			GPIO_OSPEEDR(GPIOD_BASE)
#define GPIOE_OSPEEDR			GPIO_OSPEEDR(GPIOE_BASE)
#define GPIOH_OSPEEDR			GPIO_OSPEEDR(GPIOH_BASE)

#define GPIO_PUPDR(base)		((base) + 0x0c)
#define GPIOA_PUPDR			GPIO_PUPDR(GPIOA_BASE)
#define GPIOB_PUPDR			GPIO_PUPDR(GPIOB_BASE)
#define GPIOC_PUPDR			GPIO_PUPDR(GPIOC_BASE)
#define GPIOD_PUPDR			GPIO_PUPDR(GPIOD_BASE)
#define GPIOE_PUPDR			GPIO_PUPDR(GPIOE_BASE)
#define GPIOH_PUPDR			GPIO_PUPDR(GPIOH_BASE)

#define GPIO_IDR(base)			((base) + 0x10)
#define GPIOA_IDR			GPIO_IDR(GPIOA_BASE)
#define GPIOB_IDR			GPIO_IDR(GPIOB_BASE)
#define GPIOC_IDR			GPIO_IDR(GPIOC_BASE)
#define GPIOD_IDR			GPIO_IDR(GPIOD_BASE)
#define GPIOE_IDR			GPIO_IDR(GPIOE_BASE)
#define GPIOH_IDR			GPIO_IDR(GPIOH_BASE)

#define GPIO_ODR(base)			((base) + 0x14)
#define GPIOA_ODR			GPIO_ODR(GPIOA_BASE)
#define GPIOB_ODR			GPIO_ODR(GPIOB_BASE)
#define GPIOC_ODR			GPIO_ODR(GPIOC_BASE)
#define GPIOD_ODR			GPIO_ODR(GPIOD_BASE)
#define GPIOE_ODR			GPIO_ODR(GPIOE_BASE)
#define GPIOH_ODR			GPIO_ODR(GPIOH_BASE)

#define GPIO_BSRR(base)			((base) + 0x18)
#define GPIOA_BSRR			GPIO_BSRR(GPIOA_BASE)
#define GPIOB_BSRR			GPIO_BSRR(GPIOB_BASE)
#define GPIOC_BSRR			GPIO_BSRR(GPIOC_BASE)
#define GPIOD_BSRR			GPIO_BSRR(GPIOD_BASE)
#define GPIOE_BSRR			GPIO_BSRR(GPIOE_BASE)
#define GPIOH_BSRR			GPIO_BSRR(GPIOH_BASE)

#define GPIO_LCKR(base)			((base) + 0x1c)
#define GPIOA_LCKR			GPIO_LCKR(GPIOA_BASE)
#define GPIOB_LCKR			GPIO_LCKR(GPIOB_BASE)
#define GPIOC_LCKR			GPIO_LCKR(GPIOC_BASE)
#define GPIOD_LCKR			GPIO_LCKR(GPIOD_BASE)
#define GPIOE_LCKR			GPIO_LCKR(GPIOE_BASE)
#define GPIOH_LCKR			GPIO_LCKR(GPIOH_BASE)

#define GPIO_AFRL(base)			((base) + 0x20)
#define GPIOA_AFRL			GPIO_AFRL(GPIOA_BASE)
#define GPIOB_AFRL			GPIO_AFRL(GPIOB_BASE)
#define GPIOC_AFRL			GPIO_AFRL(GPIOC_BASE)
#define GPIOD_AFRL			GPIO_AFRL(GPIOD_BASE)
#define GPIOE_AFRL			GPIO_AFRL(GPIOE_BASE)
#define GPIOH_AFRL			GPIO_AFRL(GPIOH_BASE)

#define GPIO_AFRH(base)			((base) + 0x24)
#define GPIOA_AFRH			GPIO_AFRH(GPIOA_BASE)
#define GPIOB_AFRH			GPIO_AFRH(GPIOB_BASE)
#define GPIOC_AFRH			GPIO_AFRH(GPIOC_BASE)
#define GPIOD_AFRH			GPIO_AFRH(GPIOD_BASE)
#define GPIOE_AFRH			GPIO_AFRH(GPIOE_BASE)
#define GPIOH_AFRH			GPIO_AFRH(GPIOH_BASE)

#define GPIO_BRR(base)			((base) + 0x28)
#define GPIOA_BRR			GPIO_BRR(GPIOA_BASE)
#define GPIOB_BRR			GPIO_BRR(GPIOB_BASE)
#define GPIOC_BRR			GPIO_BRR(GPIOC_BASE)
#define GPIOD_BRR			GPIO_BRR(GPIOD_BASE)
#define GPIOE_BRR			GPIO_BRR(GPIOE_BASE)
#define GPIOH_BRR			GPIO_BRR(GPIOH_BASE)

/* --- GPIOx_MODER values -------------------------------------------------- */

/* GPIO_MODER[2y+1:2y]: MODERy[1:0]: Port configuration bits (y = 0..15) */
#define GPIO_MODER_INPUT		0
#define GPIO_MODER_OUTPUT		1
#define GPIO_MODER_ALTFN		2
#define GPIO_MODER_ANALOG		3

/* --- GPIOx_OTYPER values ------------------------------------------------- */

/* GPIO_OTYPER[15:0]: OTy: Port configuration bits (y = 0..15) */
#define GPIO_OTYPER_PUSHPULL		0
#define GPIO_OTYPER_OPENDRAIN		1

/* --- GPIOx_OSPEEDR values ------------------------------------------------ */

/* GPIO_OSPEEDR[2y+1:2y]: OSPEEDRy[1:0]: Port configuration bits (y = 0..15) */
#define GPIO_OSPEEDR_LOW		0
#define GPIO_OSPEEDR_MEDIUM		1
#define GPIO_OSPEEDR_HIGH		2
#define GPIO_OSPEEDR_VERY_HIGH		3

/* --- GPIOx_PUPDR values -------------------------------------------------- */

/* GPIO_PUPDR[2y+1:2y]: PUPDRy[1:0]: Port configuration bits (y = 0..15) */
#define GPIO_PUPDR_NONE			0
#define GPIO_PUPDR_FLOAT		0
#define GPIO_PUPDR_PULLUP		1
#define GPIO_PUPDR_PULLDOWN		2

/* --- GPIOx_IDR values ---------------------------------------------------- */

/* GPIO_IDR[15:0]: IDRy: Port input data (y = 0..15) */

/* --- GPIOx_ODR values ---------------------------------------------------- */

/* GPIO_ODR[15:0]: ODRy: Port output data (y = 0..15) */

/* --- GPIOx_BSRR values --------------------------------------------------- */

/* GPIO_BSRR[31:16]: BRy: Port reset bit y (y = 0..15) */
/* GPIO_BSRR[15:0]: BSy: Port set bit y (y = 0..15) */

/* --- GPIOx_LCKR values --------------------------------------------------- */

#define GPIO_LCKK			(1 << 16)
/* GPIO_LCKR[15:0]: LCKy: Port lock bit y (y = 0..15) */

/* --- GPIOx_AFRL/GPIOx_AFRH values ---------------------------------------- */

/*
 * GPIO_AFRL[4y+3:4y]: AFRLy[3:0]: Alternate function selection (y = 0..7)
 * GPIO_AFRH[4(y-8)+3:4(y-8)]: AFRHy[3:0]: Alternate function selection
 *   (y = 8..15)
 */
#define GPIO_AFR_AF0			0
#define GPIO_AFR_AF1			1
#define GPIO_AFR_AF2			2
#define GPIO_AFR_AF3			3
#define GPIO_AFR_AF4			4
#define GPIO_AFR_AF5			5
#define GPIO_AFR_AF6			6
#define GPIO_AFR_AF7			7

/* --- GPIOx_BRR values --------------------------------------------------- */

/* GPIO_BRR[15:0]: BRy: Port reset bit y (y = 0..15) */

/* --- Port definitions ---------------------------------------------------- */

/* GPIO port name definitions */
enum {
	GPIOA = (0 << 16),
	GPIOB = (1 << 16),
	GPIOC = (2 << 16),
	GPIOD = (3 << 16),
	GPIOE = (4 << 16),
	GPIOH = (7 << 16)
};

#define GPIO_PORT(x)			((x) & ~0xffff)

/* GPIO bit number definitions */
enum {
	GPIO0 = (1 << 0),
	GPIO1 = (1 << 1),
	GPIO2 = (1 << 2),
	GPIO3 = (1 << 3),
	GPIO4 = (1 << 4),
	GPIO5 = (1 << 5),
	GPIO6 = (1 << 6),
	GPIO7 = (1 << 7),
	GPIO8 = (1 << 8),
	GPIO9 = (1 << 9),
	GPIO10 = (1 << 10),
	GPIO11 = (1 << 11),
	GPIO12 = (1 << 12),
	GPIO13 = (1 << 13),
	GPIO14 = (1 << 14),
	GPIO15 = (1 << 15),
	GPIO_ALL = 0xffff
};

#define GPIO_BITS(x)			((x) & 0xffff)

/* GPIO port name and bit number definitions */
/* GPIOA */
enum {
	GPIO_PA0 = (GPIOA | GPIO0),
	GPIO_PA1 = (GPIOA | GPIO1),
	GPIO_PA2 = (GPIOA | GPIO2),
	GPIO_PA3 = (GPIOA | GPIO3),
	GPIO_PA4 = (GPIOA | GPIO4),
	GPIO_PA5 = (GPIOA | GPIO5),
	GPIO_PA6 = (GPIOA | GPIO6),
	GPIO_PA7 = (GPIOA | GPIO7),
	GPIO_PA8 = (GPIOA | GPIO8),
	GPIO_PA9 = (GPIOA | GPIO9),
	GPIO_PA10 = (GPIOA | GPIO10),
	GPIO_PA11 = (GPIOA | GPIO11),
	GPIO_PA12 = (GPIOA | GPIO12),
	GPIO_PA13 = (GPIOA | GPIO13),
	GPIO_PA14 = (GPIOA | GPIO14),
	GPIO_PA15 = (GPIOA | GPIO15),
	GPIO_PA_ALL = (GPIOA | GPIO_ALL),
	GPIO_PA_NONE = 0
};

/* GPIOB */
enum {
	GPIO_PB0 = (GPIOB | GPIO0),
	GPIO_PB1 = (GPIOB | GPIO1),
	GPIO_PB2 = (GPIOB | GPIO2),
	GPIO_PB3 = (GPIOB | GPIO3),
	GPIO_PB4 = (GPIOB | GPIO4),
	GPIO_PB5 = (GPIOB | GPIO5),
	GPIO_PB6 = (GPIOB | GPIO6),
	GPIO_PB7 = (GPIOB | GPIO7),
	GPIO_PB8 = (GPIOB | GPIO8),
	GPIO_PB9 = (GPIOB | GPIO9),
	GPIO_PB10 = (GPIOB | GPIO10),
	GPIO_PB11 = (GPIOB | GPIO11),
	GPIO_PB12 = (GPIOB | GPIO12),
	GPIO_PB13 = (GPIOB | GPIO13),
	GPIO_PB14 = (GPIOB | GPIO14),
	GPIO_PB15 = (GPIOB | GPIO15),
	GPIO_PB_ALL = (GPIOB | GPIO_ALL),
	GPIO_PB_NONE = 0
};

/* GPIOC */
enum {
	GPIO_PC0 = (GPIOC | GPIO0),
	GPIO_PC1 = (GPIOC | GPIO1),
	GPIO_PC2 = (GPIOC | GPIO2),
	GPIO_PC3 = (GPIOC | GPIO3),
	GPIO_PC4 = (GPIOC | GPIO4),
	GPIO_PC5 = (GPIOC | GPIO5),
	GPIO_PC6 = (GPIOC | GPIO6),
	GPIO_PC7 = (GPIOC | GPIO7),
	GPIO_PC8 = (GPIOC | GPIO8),
	GPIO_PC9 = (GPIOC | GPIO9),
	GPIO_PC10 = (GPIOC | GPIO10),
	GPIO_PC11 = (GPIOC | GPIO11),
	GPIO_PC12 = (GPIOC | GPIO12),
	GPIO_PC13 = (GPIOC | GPIO13),
	GPIO_PC14 = (GPIOC | GPIO14),
	GPIO_PC15 = (GPIOC | GPIO15),
	GPIO_PC_ALL = (GPIOC | GPIO_ALL),
	GPIO_PC_NONE = 0
};

/* GPIOD */
enum {
	GPIO_PD0 = (GPIOD | GPIO0),
	GPIO_PD1 = (GPIOD | GPIO1),
	GPIO_PD2 = (GPIOD | GPIO2),
	GPIO_PD3 = (GPIOD | GPIO3),
	GPIO_PD4 = (GPIOD | GPIO4),
	GPIO_PD5 = (GPIOD | GPIO5),
	GPIO_PD6 = (GPIOD | GPIO6),
	GPIO_PD7 = (GPIOD | GPIO7),
	GPIO_PD8 = (GPIOD | GPIO8),
	GPIO_PD9 = (GPIOD | GPIO9),
	GPIO_PD10 = (GPIOD | GPIO10),
	GPIO_PD11 = (GPIOD | GPIO11),
	GPIO_PD12 = (GPIOD | GPIO12),
	GPIO_PD13 = (GPIOD | GPIO13),
	GPIO_PD14 = (GPIOD | GPIO14),
	GPIO_PD15 = (GPIOD | GPIO15),
	GPIO_PD_ALL = (GPIOD | GPIO_ALL),
	GPIO_PD_NONE = 0
};

/* GPIOE */
enum {
	GPIO_PE0 = (GPIOE | GPIO0),
	GPIO_PE1 = (GPIOE | GPIO1),
	GPIO_PE2 = (GPIOE | GPIO2),
	GPIO_PE3 = (GPIOE | GPIO3),
	GPIO_PE4 = (GPIOE | GPIO4),
	GPIO_PE5 = (GPIOE | GPIO5),
	GPIO_PE6 = (GPIOE | GPIO6),
	GPIO_PE7 = (GPIOE | GPIO7),
	GPIO_PE8 = (GPIOE | GPIO8),
	GPIO_PE9 = (GPIOE | GPIO9),
	GPIO_PE10 = (GPIOE | GPIO10),
	GPIO_PE11 = (GPIOE | GPIO11),
	GPIO_PE12 = (GPIOE | GPIO12),
	GPIO_PE13 = (GPIOE | GPIO13),
	GPIO_PE14 = (GPIOE | GPIO14),
	GPIO_PE15 = (GPIOE | GPIO15),
	GPIO_PE_ALL = (GPIOE | GPIO_ALL),
	GPIO_PE_NONE = 0
};

/* GPIOH */
enum {
	GPIO_PH0 = (GPIOH | GPIO0),
	GPIO_PH1 = (GPIOH | GPIO1),
	GPIO_PH2 = (GPIOH | GPIO2),
	GPIO_PH3 = (GPIOH | GPIO3),
	GPIO_PH4 = (GPIOH | GPIO4),
	GPIO_PH5 = (GPIOH | GPIO5),
	GPIO_PH6 = (GPIOH | GPIO6),
	GPIO_PH7 = (GPIOH | GPIO7),
	GPIO_PH8 = (GPIOH | GPIO8),
	GPIO_PH9 = (GPIOH | GPIO9),
	GPIO_PH10 = (GPIOH | GPIO10),
	GPIO_PH11 = (GPIOH | GPIO11),
	GPIO_PH12 = (GPIOH | GPIO12),
	GPIO_PH13 = (GPIOH | GPIO13),
	GPIO_PH14 = (GPIOH | GPIO14),
	GPIO_PH15 = (GPIOH | GPIO15),
	GPIO_PH_ALL = (GPIOH | GPIO_ALL),
	GPIO_PH_NONE = 0
};

#define GPIO_CONCAT(port, num) GPIO_P##port##num

#define GPIO_OR(port, b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, \
		b12, b13, b14, b15, ...)				\
	(GPIO_CONCAT(port, b0) | GPIO_CONCAT(port, b1) | \
	 GPIO_CONCAT(port, b2) | GPIO_CONCAT(port, b3) | \
	 GPIO_CONCAT(port, b4) | GPIO_CONCAT(port, b5) | \
	 GPIO_CONCAT(port, b6) | GPIO_CONCAT(port, b7) | \
	 GPIO_CONCAT(port, b8) | GPIO_CONCAT(port, b9) | \
	 GPIO_CONCAT(port, b10) | GPIO_CONCAT(port, b11) | \
	 GPIO_CONCAT(port, b12) | GPIO_CONCAT(port, b13) | \
	 GPIO_CONCAT(port, b14) | GPIO_CONCAT(port, b15))

#define GPIO_PA(...) GPIO_OR(A, __VA_ARGS__, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE)

#define GPIO_PB(...) GPIO_OR(B, __VA_ARGS__, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE)

#define GPIO_PC(...) GPIO_OR(C, __VA_ARGS__, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE)

#define GPIO_PD(...) GPIO_OR(D, __VA_ARGS__, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE, _NONE, \
	 		     _NONE, _NONE, _NONE, _NONE, _NONE)

#define GPIO_PE(...) GPIO_OR(E, __VA_ARGS__, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE)

#define GPIO_PH(...) GPIO_OR(H, __VA_ARGS__, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE, _NONE, \
			     _NONE, _NONE, _NONE, _NONE, _NONE)

/* --- Alternate functions ------------------------------------------------- */
/*
 *	AF0		AF1		AF2		AF3
 * PA0	USART2_RX	LPTIM1_IN1	TIM2_CH1
 * PA1	EVENTOUT	LPTIM1_IN2	TIM2_CH2	I2C1_SMBA
 * PA2	TIM21_CH1			TIM2_CH3
 * PA3	TIM21_CH2			TIM2_CH4
 * PA4	SPI1_NSS	LPTIM1_IN1	LPTIM1_ETR	I2C1_SCL
 * PA5	SPI1_SCK	LPTIM1_IN2	TIM2_ETR
 * PA6	SPI1_MISO	LPTIM1_ETR	TIM3_CH1
 * PA7	SPI1_MOSI	LPTIM1_OUT	TIM3_CH2
 * PA8	MCO				LPTIM1_IN1	EVENTOUT
 * PA9	MCO		I2C1_SCL	LPTIM1_OUT
 * PA10	TIM21_CH1	I2C1_SDA	RTC_REFIN
 * PA11	SPI1_MISO	LPTIM1_OUT	EVENTOUT
 * PA12	SPI1_MOSI			EVENTOUT
 * PA13	SWDIO		LPTIM1_ETR			I2C1_SDA
 * PA14	SWCLK		LPTIM1_OUT			I2C1_SMBA
 * PA15	SPI1_NSS			TIM2_ETR	EVENTOUT
 *
 *
 *	AF4		AF5		AF6		AF7
 * PA0	USART2_CTS	TIM2_ETR	LPUART1_RX/	COMP1_OUT
 *					USART4_TX
 * PA1	USART2_RTS	TIM21_ETR	LPUART1_TX/
 *					USART4_RX
 * PA2	USART2_TX			LPUART1_TX	COMP2_OUT
 * PA3	USART2_RX			LPUART1_RX
 * PA4	USART2_CK	TIM2/22_ETR	LPUART1_TX	COMP2_OUT
 * PA5			TIM2_CH1
 * PA6	LPUART1_CTS	TIM22_CH1	EVENTOUT	COMP1_OUT
 * PA7	USART2_CTS	TIM21_ETR/	EVENTOUT	COMP2_OUT
 *			TIM22_CH2
 * PA8	USART1/2_CK	TIM2_CH1			I2C3_SCL
 * PA9	USART1/2_TX	TIM21_CH2/	I2C1_SCL	COMP1_OUT/
 *			TIM22_CH1			I2C3_SMBA
 * PA10	USART1/2_RX	TIM2_CH3/	I2C1_SDA	COMP1_OUT
 *			TIM22_CH2
 * PA11	USART1/2_CTS	TIM21_CH2			COMP1_OUT
 * PA12	USART1/2_RTS					COMP2_OUT
 * PA13			SPI1_SCK	LPUART1_RX	COMP1_OUT
 * PA14	USART2_TX	SPI1_MISO	LPUART1_TX	COMP2_OUT
 * PA15	USART2_RX	TIM2_CH1	USART4_RTS
 */
/*
 *	AF0		AF1		AF2		AF3
 * PB0	EVENTOUT	SPI1_MISO	TIM2_CH2/
 *					TIM3_CH3
 * PB1	USART2_CK	SPI1_MOSI	LPTIM1_IN1/
 *					TIM3_CH4
 * PB2					LPTIM1_OUT
 * PB3	SPI1_SCK			TIM2_CH2
 * PB4	SPI1_MISO			EVENTOUT/
 *					TIM3_CH1
 * PB5	SPI1_MOSI			LPTIM1_IN1	I2C1_SMBA
 * PB6	USART1/2_TX	I2C1_SCL	LPTIM1_ETR
 * PB7	USART1/2_RX	I2C1_SDA	LPTIM1_IN2
 * PB8	USART2_TX			EVENTOUT
 * PB9					EVENTOUT
 * PB10					TIM2_CH3
 * PB11	EVENTOUT			TIM2_CH4
 * PB12	SPI1/2_NSS			LPUART1_RTS
 * PB13	SPI1/2_SCK			MCO
 * PB14	SPI1/2_MISO			RTC_OUT
 * PB15	SPI1/2_MOSI			RTC_REFIN
 *
 *
 *	AF4		AF5		AF6		AF7
 * PB0	USART2_RTS	TIM2_CH3
 * PB1	LPUART1_RTS	TIM2_CH4
 * PB2							I2C3_SMBA
 * PB3	EVENTOUT	USART1_RTS	USART5_TX
 * PB4	TIM22_CH1	USART1_CTS	USART5_RX	I2C3_SDA
 * PB5	TIM22_CH2/	TIM21_CH1/	USART5_CK/
 *	TIM3_CH2	USART1_CK	USART5_RTS
 * PB6			TIM2_CH3/	LPUART1_TX
 *			TIM21_CH1
 * PB7			TIM2_CH4	LPUART1_RX/
 *					USART4_CTS
 * PB8	I2C1_SCL	SPI1_NSS
 * PB9	I2C1_SDA	SPI2_NSS
 * PB10	LPUART1_TX	SPI2_SCK	LPUART1_TX/	LPUART1_RX
 *					I2C2_SCL
 * PB11	LPUART1_RX			LPUART1_RX/	LPUART1_TX
 *					I2C2_SDA
 * PB12			I2C2_SMBA	EVENTOUT
 * PB13	LPUART1_CTS	TIM21_CH1/	LPUART1_CTS/
 *			I2C2_SCL	TIM21_CH1
 * PB14	LPUART1_RTS	TIM21_CH2/	LPUART1_RTS/
 *			I2C2_SDA	TIM21_CH2
 * PB15
 */
/*
 *	AF0		AF1		AF2		AF3
 * PC0	LPTIM1_IN1			EVENTOUT
 * PC1	LPTIM1_OUT			EVENTOUT
 * PC2	LPTIM1_IN2			SPI2_MISO
 * PC3	LPTIM1_ETR			SPI2_MOSI
 * PC4	EVENTOUT			LPUART1_TX
 * PC5					LPUART1_RX
 * PC6	TIM22_CH1			TIM3_CH1
 * PC7	TIM22_CH2			TIM3_CH2
 * PC8	TIM22_ETR			TIM3_CH3
 * PC9	TIM21_ETR			TIM3_CH4
 * PC10	LPUART1_TX
 * PC11	LPUART1_RX
 * PC12					USART5_TX
 * PC13
 * PC14
 * PC15
 */
/*
 *	AF4		AF5		AF6		AF7
 * PC0					LPUART1_RX	I2C3_SCL
 * PC1					LPUART1_TX	I2C3_SDA
 * PC2
 * PC3
 * PC4
 * PC5
 * PC6
 * PC7
 * PC8
 * PC9							I2C3_SDA
 * PC10					USART4_TX
 * PC11					USART4_RX
 * PC12					USART4_CK
 * PC13
 * PC14
 * PC15
 */
/*
 *	AF0		AF1		AF2		AF3
 * PD0	TIM21_CH1	SPI2_NSS
 * PD1			SPI2_SCK
 * PD2	LPUART1_RTS			TIM3_ETR
 * PD3	USART2_CTS			SPI2_MISO
 * PD4	USART2_RTS	SPI2_MOSI
 * PD5	USART2_TX
 * PD6	USART2_RX
 * PD7	USART2_CK	TIM21_CH2
 * PD8	LPUART1_TX
 * PD9	LPUART1_RX
 * PD10
 * PD11	LPUART1_CTS
 * PD12	LPUART1_RTS
 * PD13
 * PD14
 * PD15
 */
/*
 *	AF4		AF5		AF6		AF7
 * PD0
 * PD1
 * PD2					USART5_RX
 * PD3
 * PD4
 * PD5
 * PD6
 * PD7
 * PD8
 * PD9
 * PD10
 * PD11
 * PD12
 * PD13
 * PD14
 * PD15
 */
/*
 *	AF0		AF1		AF2		AF3
 * PE0					EVENTOUT
 * PE1					EVENTOUT
 * PE2					TIM3_ETR
 * PE3	TIM22_CH1			TIM3_CH1
 * PE4	TIM22_CH2			TIM3_CH2
 * PE5	TIM21_CH1			TIM3_CH3
 * PE6	TIM21_CH2			TIM3_CH4
 * PE7
 * PE8
 * PE9	TIM2_CH1			TIM2_ETR
 * PE10	TIM2_CH2
 * PE11	TIM2_CH3
 * PE12	TIM2_CH4			SPI1_NSS
 * PE13					SPI1_SCK
 * PE14					SPI1_MISO
 * PE15					SPI1_MOSI
 */
/*
 *	AF4		AF5		AF6		AF7
 * PE0
 * PE1
 * PE2
 * PE3
 * PE4
 * PE5
 * PE6
 * PE7					USART5_CK/
 *					USART5_RTS
 * PE8					USART4_TX
 * PE9					USART4_RX
 * PE10					USART5_TX
 * PE11					USART5_RX
 * PE12
 * PE13
 * PE14
 * PE15
 */

/* --- Function prototypes ------------------------------------------------- */

/* Mode */
enum gpio_mode {
	GPIO_AF0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,

	GPIO_INPUT,
	GPIO_OUTPUT,
	GPIO_ANALOG,
	GPIO_ALTFUNC
};

/* Option */
enum {
	/* output type */
	GPIO_PUSHPULL = (0 << 0),
	GPIO_OPENDRAIN = (1 << 0),

	/* output speed */
	GPIO_LOW_SPEED = (0 << 1),
	GPIO_MEDIUM_SPEED = (1 << 1),
	GPIO_HIGH_SPEED = (2 << 1),
	GPIO_VERY_HIGH_SPEED = (3 << 1),
	GPIO_400KHZ = (0 << 1),
	GPIO_2MHZ = (1 << 1),
	GPIO_10MHZ = (2 << 1),
	GPIO_35MHZ = (3 << 1),

	/* pull-up or pull-down */
	GPIO_NOPUPD = (0 << 3),
	GPIO_FLOAT = (0 << 3),
	GPIO_PULLUP = (1 << 3),
	GPIO_PULLDOWN = (2 << 3)
};

void gpio_set_mode(enum gpio_mode mode, int portbits);
void gpio_config(enum gpio_mode mode, int options, int portbits);
void gpio_set(int portbits);
void gpio_clear(int portbits);
int gpio_get(int portbits);
void gpio_toggle(int portbits);
int gpio_read_port(int port);
void gpio_write_port(int port, int data);
int gpio_lock_config(int portbits);
