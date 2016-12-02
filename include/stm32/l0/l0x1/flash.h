/*
 * Flash interface
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
 * 3  Flash program memory and data EEPROM (FLASH)
 */

/* --- Flash registers ----------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		FLASH_ACR	Access control register
 * 0x04		FLASH_PECR	Program and erase control register
 * 0x08		FLASH_PDKEYR	Power-down key register
 * 0x0c		FLASH_PEKEYR	PECR unlock key register
 * 0x10		FLASH_PRGKEYR	Program and erase key register
 * 0x14		FLASH_OPTKEYR	Option bytes unlock key register
 * 0x18		FLASH_SR	Status register
 * 0x1c		FLASH_OPTR	Option bytes register
 * 0x20		FLASH_WRPROT1	Write protection register 1
 * 0x80		FLASH_WRPROT2	Write protection register 2
 */

#define FLASH_ACR			(FLASH_INTERFACE_BASE + 0x00)
#define FLASH_PECR			(FLASH_INTERFACE_BASE + 0x04)
#define FLASH_PDKEYR			(FLASH_INTERFACE_BASE + 0x08)
#define FLASH_PEKEYR			(FLASH_INTERFACE_BASE + 0x0c)
#define FLASH_PRGKEYR			(FLASH_INTERFACE_BASE + 0x10)
#define FLASH_OPTKEYR			(FLASH_INTERFACE_BASE + 0x14)
#define FLASH_SR			(FLASH_INTERFACE_BASE + 0x18)
#define FLASH_OPTR			(FLASH_INTERFACE_BASE + 0x1c)
#define FLASH_WRPROT1			(FLASH_INTERFACE_BASE + 0x20)
#define FLASH_WRPROT2			(FLASH_INTERFACE_BASE + 0x80)

/* --- FLASH_ACR values ---------------------------------------------------- */

#define FLASH_ACR_PRE_READ		(1 << 6)
#define FLASH_ACR_DISAB_BUF		(1 << 5)
#define FLASH_ACR_RUN_PD		(1 << 4)
#define FLASH_ACR_SLEEP_PD		(1 << 3)
#define FLASH_ACR_PRFTEN		(1 << 1)
#define FLASH_ACR_LATENCY		(1 << 0)

/* --- FLASH_PECR values --------------------------------------------------- */

#define FLASH_PECR_NZDISABLE		(1 << 23)
#define FLASH_PECR_OBL_LAUNCH		(1 << 18)
#define FLASH_PECR_ERRIE		(1 << 17)
#define FLASH_PECR_EOPIE		(1 << 16)
#define FLASH_PECR_PARALLELBANK		(1 << 15)
#define FLASH_PECR_FPRG			(1 << 10)
#define FLASH_PECR_ERASE		(1 << 9)
#define FLASH_PECR_FIX			(1 << 8)
#define FLASH_PECR_DATA			(1 << 4)
#define FLASH_PECR_PROG			(1 << 3)
#define FLASH_PECR_OPTLOCK		(1 << 2)
#define FLASH_PECR_PRGLOCK		(1 << 1)
#define FLASH_PECR_PELOCK		(1 << 0)

/* --- FLASH_PDKEYR values ------------------------------------------------- */

#define FLASH_PDKEYR_KEY1		0x04152637
#define FLASH_PDKEYR_KEY2		0xfafbfcfd

/* --- FLASH_PEKEYR values ------------------------------------------------- */

#define FLASH_PEKEYR_KEY1		0x89abcdef
#define FLASH_PEKEYR_KEY2		0x02030405

/* --- FLASH_PRGKEYR values ------------------------------------------------ */

#define FLASH_PRGKEYR_KEY1		0x8c9daebf
#define FLASH_PRGKEYR_KEY2		0x13141516

/* --- FLASH_OPTKEYR values ------------------------------------------------ */

#define FLASH_OPTKEYR_KEY1		0xfbead9c8
#define FLASH_OPTKEYR_KEY2		0x24252627

/* --- FLASH_SR values ----------------------------------------------------- */

#define FLASH_SR_FWWERR			(1 << 17)
#define FLASH_SR_NOTZEROERR		(1 << 16)
#define FLASH_SR_RDERR			(1 << 13)
#define FLASH_SR_OPTVERR		(1 << 11)
#define FLASH_SR_SIZERR			(1 << 10)
#define FLASH_SR_PGAERR			(1 << 9)
#define FLASH_SR_WRPERR			(1 << 8)
#define FLASH_SR_READY			(1 << 3)
#define FLASH_SR_ENDHV			(1 << 2)
#define FLASH_SR_EOP			(1 << 1)
#define FLASH_SR_BSY			(1 << 0)

/* --- FLASH_OPTR values --------------------------------------------------- */

#define FLASH_OPTR_NBOOT1		(1 << 31)
#define FLASH_OPTR_NBOOT0		(1 << 30)
#define FLASH_OPTR_NBOOT_SEL		(1 << 29)
#define FLASH_OPTR_BFB2			(1 << 23)
#define FLASH_OPTR_NRST_STDBY		(1 << 22)
#define FLASH_OPTR_NRST_STOP		(1 << 21)
#define FLASH_OPTR_WDG_SW		(1 << 20)
#define FLASH_OPTR_BOR_LEV3		(1 << 19)
#define FLASH_OPTR_BOR_LEV2		(1 << 18)
#define FLASH_OPTR_BOR_LEV1		(1 << 17)
#define FLASH_OPTR_BOR_LEV0		(1 << 16)
#define FLASH_OPTR_WPRMOD		(1 << 8)

/* FLASH_OPTR[7:0]: RDPROT[7:0] */

/* Brown out reset threshold level */
#define FLASH_OPTR_BOR_LEV_LEVEL1	(8 << 16)
#define FLASH_OPTR_BOR_LEV_LEVEL2	(9 << 16)
#define FLASH_OPTR_BOR_LEV_LEVEL3	(10 << 16)
#define FLASH_OPTR_BOR_LEV_LEVEL4	(11 << 16)
#define FLASH_OPTR_BOR_LEV_LEVEL5	(12 << 16)

/* Read protection */
#define FLASH_OPTR_RDPROT_LEVEL0	(0xaa)
#define FLASH_OPTR_RDPROT_LEVEL2	(0xcc)

/* --- FLASH_WRPROT1 values ------------------------------------------------ */

/* FLASH_WRPROT1[31:0]: WRPROT1[31:0] */

/* --- FLASH_WRPROT2 values ------------------------------------------------ */

/* FLASH_WRPROT2[15:0]: WRPROT2[15:0] */

/* --- Organization -------------------------------------------------------- */

#define FLASH_PAGE_SIZE			128
#define FLASH_SECTOR_SIZE		4096

/* --- Function prototypes ------------------------------------------------- */

/* Access options */
enum {
	FLASH_PREFETCH = (1 << 1),
	FLASH_PREREAD = (1 << 6),
	FLASH_DISABLE_BUFFER = (1 << 5)
};

/* Power-down mode */
enum {
	FLASH_RUN_PD = (1 << 4),
	FLASH_SLEEP_PD = (1 << 3)
};

/* Lock */
enum flash_lock {
	FLASH_LOCK_POWER_DOWN,
	FLASH_LOCK_PECR,
	FLASH_LOCK_PROGRAM_ERASE,
	FLASH_LOCK_OPTION_BYTES
};

/* Object */
enum flash_obj {
	FLASH_PROGRAM_MEMORY,
	FLASH_DATA_EEPROM,
	FLASH_OPTION_BYTES
};

/* Interrupt */
enum {
	FLASH_END_OF_PROGRAM = (1 << 16),
	FLASH_ERROR = (1 << 17)
};

/* Status bits */
enum {
	FLASH_BSY = (1 << 0),
	FLASH_EOP = (1 << 1),
	FLASH_ENDHV = (1 << 2),
	FLASH_READY = (1 << 3),
	FLASH_WRPERR = (1 << 8),
	FLASH_PGAERR = (1 << 9),
	FLASH_SIZERR = (1 << 10),
	FLASH_OPTVERR = (1 << 11),
	FLASH_RDERR = (1 << 13),
	FLASH_NOTZEROERR = (1 << 16),
	FLASH_FWWERR = (1 << 17)
};

/* Option bytes information */
enum {
	FLASH_NBOOT1 = (1 << 31),
	FLASH_NBOOT0 = (1 << 30),
	FLASH_NBOOT_SEL = (1 << 29),
	FLASH_BFB2 = (1 << 23),
	FLASH_NRST_STDBY = (1 << 22),
	FLASH_NRST_STOP = (1 << 21),
	FLASH_WDG_SW = (1 << 20),
	FLASH_BOR_LEVEL = (15 << 16),
	FLASH_BOR_LEVEL1 = (8 << 16),
	FLASH_BOR_LEVEL2 = (9 << 16),
	FLASH_BOR_LEVEL3 = (10 << 16),
	FLASH_BOR_LEVEL4 = (11 << 16),
	FLASH_BOR_LEVEL5 = (12 << 16),
	FLASH_WPRMOD = (1 << 8),
	FLASH_RDPROT = (255 << 0)
};

void flash_config_access(int wait, int option);
void flash_enable_power_down(int mode);
void flash_disable_power_down(int mode);
void flash_unlock(enum flash_lock lock);
void flash_lock(enum flash_lock lock);
void flash_enable_fixed_time_data_write(void);
void flash_enable_erase(enum flash_obj obj);
void flash_enable_half_page_write(void);
void flash_launch_option_byte_loading(void);
void flash_enable_interrupt(int interrupt);
void flash_disable_interrupt(int interrupt);
int flash_get_interrupt_mask(int interrupt);
int flash_get_status(int status);
void flash_clear_status(int status);
int flash_get_option_byte_info(int info);
int flash_get_write_protection1(void);
int flash_get_write_protection2(void);
void flash_enable_parallel_bank(void);
void flash_disable_parallel_bank(void);
void flash_disable_non_zero_check(void);
void flash_enable_non_zero_check(void);
