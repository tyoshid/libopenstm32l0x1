/*
 * MPU
 *
 * Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>
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
 * PM0223: Programming manual
 * STM32L0 Series Cortex-M0+ programming manual
 * (15-Apr-2014 Rev 1)
 *
 * 4.5  Memory Protection Unit
 */

/* --- NVIC registers ------------------------------------------------------ */
/*
 * Offset	Register
 * 0x00		MPU_TYPE	MPU Type Register
 * 0x04		MPU_CTRL	MPU Control Register
 * 0x08		MPU_RNR		MPU Region Number Register
 * 0x0c		MPU_RBAR	MPU Region Base Address Register
 * 0x10		MPU_RASR	MPU Region Attribute and Size Register
 */

#define MPU_TYPE			(MPU_BASE + 0x00)
#define MPU_CTRL			(MPU_BASE + 0x04)
#define MPU_RNR				(MPU_BASE + 0x08)
#define MPU_RBAR			(MPU_BASE + 0x0c)
#define MPU_RASR			(MPU_BASE + 0x10)

/* --- MPU_TYPE values ----------------------------------------------------- */

#define MPU_TYPE_NONE			0x00000000
#define MPU_TYPE_PRESENCE		0x00000800

/* --- MPU_CTRL values ----------------------------------------------------- */

#define MPU_CTRL_PRIVDEFENA		(1 << 2)
#define MPU_CTRL_HFNMIENA		(1 << 1)
#define MPU_CTRL_ENABLE			(1 << 0)

/* --- MPU_RNR values ------------------------------------------------------ */

/* MPU_RNR[7:0]: REGION[7:0]: Region number */

/* --- MPU_RBAR values ----------------------------------------------------- */

/* MPU_RBAR[31:N]: ADDR[31:N]: Region base address field */
#define MPU_RBAR_VALID			(1 << 4)
#define MPU_RBAR_REGION3		(1 << 3)
#define MPU_RBAR_REGION2		(1 << 2)
#define MPU_RBAR_REGION1		(1 << 1)
#define MPU_RBAR_REGION0		(1 << 0)

/* --- MPU_RASR values ----------------------------------------------------- */

#define MPU_RASR_XN			(1 << 28)
#define MPU_RASR_AP2			(1 << 26)
#define MPU_RASR_AP1			(1 << 25)
#define MPU_RASR_AP0			(1 << 24)
#define MPU_RASR_S			(1 << 18)
#define MPU_RASR_C			(1 << 17)
#define MPU_RASR_B			(1 << 16)
#define MPU_RASR_SRD7			(1 << 15)
#define MPU_RASR_SRD6			(1 << 14)
#define MPU_RASR_SRD5			(1 << 13)
#define MPU_RASR_SRD4			(1 << 12)
#define MPU_RASR_SRD3			(1 << 11)
#define MPU_RASR_SRD2			(1 << 10)
#define MPU_RASR_SRD1			(1 << 9)
#define MPU_RASR_SRD0			(1 << 8)
#define MPU_RASR_SIZE4			(1 << 5)
#define MPU_RASR_SIZE3			(1 << 4)
#define MPU_RASR_SIZE2			(1 << 3)
#define MPU_RASR_SIZE1			(1 << 2)
#define MPU_RASR_SIZE0			(1 << 1)
#define MPU_RASR_ENABLE			(1 << 0)

/* AP encoding */
#define MPU_RASR_AP_NO_NO		(0 << 24)
#define MPU_RASR_AP_RW_NO		(1 << 24)
#define MPU_RASR_AP_RW_RO		(2 << 24)
#define MPU_RASR_AP_RW_RW		(3 << 24)
#define MPU_RASR_AP_RO_NO		(5 << 24)
#define MPU_RASR_AP_RO_RO		(6 << 24)

/* --- Function prototypes ------------------------------------------------- */

/* Attribute */
enum {
	MPU_REGION_ENABLE = (1 << 0),
	MPU_DISABLE_SUBREGION0 = (1 << 8),
	MPU_DISABLE_SUBREGION1 = (1 << 9),
	MPU_DISABLE_SUBREGION2 = (1 << 10),
	MPU_DISABLE_SUBREGION3 = (1 << 11),
	MPU_DISABLE_SUBREGION4 = (1 << 12),
	MPU_DISABLE_SUBREGION5 = (1 << 13),
	MPU_DISABLE_SUBREGION6 = (1 << 14),
	MPU_DISABLE_SUBREGION7 = (1 << 15),
	MPU_BUFFERABLE = (1 << 16),
	MPU_CACHEABLE = (1 << 17),
	MPU_SHAREABLE = (1 << 18),
	MPU_NO_NO = (0 << 24),
	MPU_RW_NO = (1 << 24),
	MPU_RW_RO = (2 << 24),
	MPU_RW_RW = (3 << 24),
	MPU_RO_NO = (5 << 24),
	MPU_RO_RO = (6 << 24),
	MPU_DISABLE_INSTRUCTION = (1 << 28)
};

int mpu_get_type(void);
void mpu_enable_default_memory_map(void);
void mpu_disable_default_memory_map(void);
void mpu_enable_hardfault_nmi(void);
void mpu_disable_hardfault_nmi(void);
void mpu_enable(void);
void mpu_disable(void);
void mpu_set_region(int region, int addr, int n, int attr);
void mpu_enable_region(int region);
void mpu_disable_region(int region);
