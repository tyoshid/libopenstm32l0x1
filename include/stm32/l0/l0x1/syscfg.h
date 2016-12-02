/*
 * SYSCFG
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
 * (30-Aug-2016 Rev 6)
 *
 * 9  System configuration controller (SYSCFG)
 */

/* --- SYSCFG registers ---------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		SYSCFG_CFGR1	SYSCFG memory remap register
 * 0x04		SYSCFG_CFGR2	SYSCFG perioheral mode configuration register
 * 0x08		SYSCFG_EXTICR1	SYSCFG external interrupt configuration
 *				register 1
 * 0x0c		SYSCFG_EXTICR2	SYSCFG external interrupt configuration
 *				register 2
 * 0x10		SYSCFG_EXTICR3	SYSCFG external interrupt configuration
 *				register 3
 * 0x14		SYSCFG_EXTICR4	SYSCFG external interrupt configuration
 *				register 4
 *
 * (0x18	COMP1_CSR)
 * (0x1c	COMP2_CSR)
 *
 * 0x20		SYSCFG_CFGR3	Reference control and status register
 */

#define SYSCFG_CFGR1			(SYSCFG_BASE + 0x00)
#define SYSCFG_CFGR2			(SYSCFG_BASE + 0x04)
#define SYSCFG_EXTICR1			(SYSCFG_BASE + 0x08)
#define SYSCFG_EXTICR2			(SYSCFG_BASE + 0x0c)
#define SYSCFG_EXTICR3			(SYSCFG_BASE + 0x10)
#define SYSCFG_EXTICR4			(SYSCFG_BASE + 0x14)
#define SYSCFG_CFGR3			(SYSCFG_BASE + 0x20)

/* --- SYSCFG_CFGR1 values ------------------------------------------------- */

#define SYSCFG_CFGR1_BOOT_MODE1		(1 << 9)
#define SYSCFG_CFGR1_BOOT_MODE0		(1 << 8)
#define SYSCFG_CFGR1_UFB		(1 << 3)
#define SYSCFG_CFGR1_MEM_MODE1		(1 << 1)
#define SYSCFG_CFGR1_MEM_MODE0		(1 << 0)

/* Boot mode selected by the boot pins status bits */
#define SYSCFG_CFGR1_BOOT_MODE_FLASH	(0 << 8)
#define SYSCFG_CFGR1_BOOT_MODE_SYSTEM	(1 << 8)
#define SYSCFG_CFGR1_BOOT_MODE_SRAM	(3 << 8)

/* Memory mapping selection bits */
#define SYSCFG_CFGR1_MEM_MODE_FLASH	(0 << 0)
#define SYSCFG_CFGR1_MEM_MODE_SYSTEM	(1 << 0)
#define SYSCFG_CFGR1_MEM_MODE_SRAM	(3 << 0)

/* --- SYSCFG_CFGR2 values ------------------------------------------------- */

#define SYSCFG_CFGR2_I2C3_FMP		(1 << 14)
#define SYSCFG_CFGR2_I2C2_FMP		(1 << 13)
#define SYSCFG_CFGR2_I2C1_FMP		(1 << 12)
#define SYSCFG_CFGR2_I2C_PB9_FMP	(1 << 11)
#define SYSCFG_CFGR2_I2C_PB8_FMP	(1 << 10)
#define SYSCFG_CFGR2_I2C_PB7_FMP	(1 << 9)
#define SYSCFG_CFGR2_I2C_PB6_FMP	(1 << 8)
#define SYSCFG_CFGR2_FWDIS		(1 << 0)

/* --- SYSCFG_EXTICR1-4 values --------------------------------------------- */

/*
 * SYSCFG_EXTICRn[15:0]: EXTIx[3:0]: EXTI x configuration
 * (x = 4(n-1)..4(n-1)+3)
 */

#define SYSCFG_EXTICR_PA		0
#define SYSCFG_EXTICR_PB		1
#define SYSCFG_EXTICR_PC		2
#define SYSCFG_EXTICR_PD		3
#define SYSCFG_EXTICR_PE		4
#define SYSCFG_EXTICR_PH		5

/* --- SYSCFG_CFGR3 values ------------------------------------------------- */

#define SYSCFG_CFGR3_REF_LOCK		(1 << 31)
#define SYSCFG_CFGR3_VREFINT_RDYF	(1 << 30)
#define SYSCFG_CFGR3_ENBUF_VREFINT_COMP	(1 << 12)
#define SYSCFG_CFGR3_ENBUF_SENSOR_ADC	(1 << 9)
#define SYSCFG_CFGR3_ENBUF_VREFINT_ADC	(1 << 8)
#define SYSCFG_CFGR3_SEL_VREF_OUT1	(1 << 5)
#define SYSCFG_CFGR3_SEL_VREF_OUT0	(1 << 4)
#define SYSCFG_CFGR3_EN_VREFINT		(1 << 0) /* ??? */

/* VREFINT_ADC connection bit */
#define SYSCFG_CFGR3_SEL_VREF_OUT_NONE	(0 << 4)
#define SYSCFG_CFGR3_SEL_VREF_OUT_PB0	(1 << 4)
#define SYSCFG_CFGR3_SEL_VREF_OUT_PB1	(2 << 4)
#define SYSCFG_CFGR3_SEL_VREF_OUT_PB0_1	(3 << 4)

/* --- Function prototypes ------------------------------------------------- */

/* Memory mapping */
enum syscfg_mem {
	SYSCFG_FLASH = 0,
	SYSCFG_SYSTEM = 1,
	SYSCFG_SRAM = 3
};

/* I2C Fast-mode plus */
enum {
	SYSCFG_I2C1_PB6 = (1 << 8),
	SYSCFG_I2C1_PB7 = (1 << 9),
	SYSCFG_I2C1_PB8 = (1 << 10),
	SYSCFG_I2C1_PB9 = (1 << 11),
	SYSCFG_I2C1 = (1 << 12),
	SYSCFG_I2C2 = (1 << 13),
	SYSCFG_I2C3 = (1 << 14)
};

/* EXTI configuration */
enum syscfg_exti {
	SYSCFG_PA,
	SYSCFG_PB,
	SYSCFG_PC,
	SYSCFG_PD,
	SYSCFG_PE,
	SYSCFG_PH
};

/* VREFINT and temperature sensor control */
enum {
	SYSCFG_VREFINT_ADC = (1 << 8),
	SYSCFG_SENSOR_ADC = (1 << 9),
	SYSCFG_VREFINT_COMP = ((1 << 12) | 1) /* ??? */
};

/* VREFINT_ADC connection */
enum syscfg_vrefint_out {
	SYSCFG_NONE = (0 << 4),
	SYSCFG_PB0 = (1 << 4),
	SYSCFG_PB1 = (2 << 4),
	SYSCFG_PB0_PB1 = (3 << 4)
};

enum syscfg_mem syscfg_get_boot_mode(void);
enum syscfg_mem syscfg_get_memory_mapping(void);
void syscfg_set_memory_mapping(enum syscfg_mem mem);
void syscfg_enable_i2c_fmp(int i2c);
void syscfg_disable_i2c_fmp(int i2c);
void syscfg_enable_firewall(void);
void syscfg_set_exti_source(int exti, enum syscfg_exti src);
void syscfg_enable_vrefint(int control);
void syscfg_disable_vrefint(int control);
int syscfg_get_vrefint_status(void);
void syscfg_set_vrefint_adc_out(enum syscfg_vrefint_out pin);
void syscfg_lock_vrefint(void);
void syscfg_set_bank_map(int bank);
