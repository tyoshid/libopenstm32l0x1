/*
 * PWR
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
 * 6  Power control (PWR)
 */

/* --- PWR registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		PWR_CR		PWR power control register
 * 0x04		PWR_CSR		PWR power control/status register
 */

#define PWR_CR				(PWR_BASE + 0x00)
#define PWR_CSR				(PWR_BASE + 0x04)

/* --- PWR_CR values ------------------------------------------------------- */

#define PWR_CR_LPDS			(1 << 16)
#define PWR_CR_LPRUN			(1 << 14)
#define PWR_CR_DS_EE_KOFF		(1 << 13)
#define PWR_CR_VOS1			(1 << 12)
#define PWR_CR_VOS0			(1 << 11)
#define PWR_CR_FWU			(1 << 10)
#define PWR_CR_ULP			(1 << 9)
#define PWR_CR_DBP			(1 << 8)
#define PWR_CR_PLS2			(1 << 7)
#define PWR_CR_PLS1			(1 << 6)
#define PWR_CR_PLS0			(1 << 5)
#define PWR_CR_PVDE			(1 << 4)
#define PWR_CR_CSBF			(1 << 3)
#define PWR_CR_CWUF			(1 << 2)
#define PWR_CR_PDDS			(1 << 1)
#define PWR_CR_LPSDSR			(1 << 0)

/* Voltage scaling range selection */
#define PWR_CR_VOS_1_8V			(1 << 11)
#define PWR_CR_VOS_1_5V			(2 << 11)
#define PWR_CR_VOS_1_2V			(3 << 11)

/* PVD level selection */
#define PWR_CR_PLS_1_9V			(0 << 5)
#define PWR_CR_PLS_2_1V			(1 << 5)
#define PWR_CR_PLS_2_3V			(2 << 5)
#define PWR_CR_PLS_2_5V			(3 << 5)
#define PWR_CR_PLS_2_7V			(4 << 5)
#define PWR_CR_PLS_2_9V			(5 << 5)
#define PWR_CR_PLS_3_1V			(6 << 5)
#define PWR_CR_PLS_EXT			(7 << 5)

/* --- PWR_CSR values ------------------------------------------------------ */

#define PWR_CSR_EWUP3			(1 << 10)
#define PWR_CSR_EWUP2			(1 << 9)
#define PWR_CSR_EWUP1			(1 << 8)
#define PWR_CSR_REGLPF			(1 << 5)
#define PWR_CSR_VOSF			(1 << 4)
#define PWR_CSR_VREFINTRDYF		(1 << 3)
#define PWR_CSR_PVDO			(1 << 2)
#define PWR_CSR_SBF			(1 << 1)
#define PWR_CSR_WUF			(1 << 0)

/* --- Function prototypes ------------------------------------------------- */

/* Voltage scaling range */
enum pwr_vos {
	PWR_1_8V = (1 << 11),
	PWR_1_5V = (2 << 11),
	PWR_1_2V = (3 << 11),
	PWR_RANGE1 = (1 << 11),
	PWR_RANGE2 = (2 << 11),
	PWR_RANGE3 = (3 << 11)
};

/* Low-power mode */
enum pwr_mode {
	PWR_RUN,
	PWR_LOW_POWER_RUN,
	PWR_SLEEP,
	PWR_LOW_POWER_SLEEP,
	PWR_STOP,
	PWR_LOW_POWER_STOP,	/* voltage regulator in low-power mode */
	PWR_STANDBY
};

/* PVD level */
enum pwr_pvd {
	PWR_1_9V = (0 << 5),
	PWR_2_1V = (1 << 5),
	PWR_2_3V = (2 << 5),
	PWR_2_5V = (3 << 5),
	PWR_2_7V = (4 << 5),
	PWR_2_9V = (5 << 5),
	PWR_3_1V = (6 << 5),
	PWR_EXT = (7 << 5)
};

/* WKUP pin */
enum {
	PWR_WKUP1 = (1 << 8),
	PWR_WKUP2 = (1 << 9),
	PWR_WKUP3 = (1 << 10)
};

/* Flag */
enum {
	PWR_REGULATOR_LOW_POWER = (1 << 5),
	PWR_VOS = (1 << 4),
	PWR_VREFINT_RDY = (1 << 3),
	PWR_PVD_OUTPUT = (1 << 2),
	PWR_STANDBY_FLAG = (1 << 1),
	PWR_WAKEUP = (1 << 0)
};

void pwr_set_vos(enum pwr_vos vos);
int pwr_get_vos(void);
void pwr_set_mode(enum pwr_mode mode);
void pwr_enable_ultra_low_power_mode(bool fast_wakeup);
void pwr_disable_ultra_low_power_mode(void);
void pwr_disable_backup_write_protection(void);
void pwr_enable_backup_write_protection(void);
void pwr_set_pvd_level(enum pwr_pvd level);
void pwr_enable_pvd(void);
void pwr_disable_pvd(void);
void pwr_enable_wkup_pin(int ewup);
void pwr_disable_wkup_pin(int ewup);
int pwr_get_flag(int flag);
void pwr_clear_flag(int flag);
void pwr_enable_flash_keep_off(void);
void pwr_disable_flash_keep_off(void);
void pwr_enable_low_power_deepsleep(void);
void pwr_disable_low_power_deepsleep(void);
