/*
 * IWDG
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
 * 20  Independent watchdog (IWDG)
 */

/* --- IWDG registers ------------------------------------------------------ */
/*
 * Offset	Register
 * 0x00		IWDG_KR		Key register
 * 0x04		IWDG_PR		Prescaler register
 * 0x08		IWDG_RLR	Reload register
 * 0x0c		IWDG_SR		Status register
 * 0x10		IWDG_WINR	Window register
 */

#define IWDG_KR				(IWDG_BASE + 0x00)
#define IWDG_PR				(IWDG_BASE + 0x04)
#define IWDG_RLR			(IWDG_BASE + 0x08)
#define IWDG_SR				(IWDG_BASE + 0x0c)
#define IWDG_WINR			(IWDG_BASE + 0x10)

/* --- IWDG_KR values ------------------------------------------------------ */

/* IWDG_KR[15:0]: KEY[15:0]: Key value (write-only, reads as 0x0000) */
#define IWDG_KR_RELOAD			0xaaaa
#define IWDG_KR_UNLOCK			0x5555
#define IWDG_KR_START			0xcccc

/* --- IWDG_PR values ------------------------------------------------------ */

/* IWDG_PR[2:0]: PR[2:0]: Prescaler divider */
#define IWDG_PR_DIV4			0
#define IWDG_PR_DIV8			1
#define IWDG_PR_DIV16			2
#define IWDG_PR_DIV32			3
#define IWDG_PR_DIV64			4
#define IWDG_PR_DIV128			5
#define IWDG_PR_DIV256			6

/* --- IWDG_RLR values ----------------------------------------------------- */

/* IWDG_RLR[11:0]: RL[11:0]: Watchdog counter reload value */

/* --- IWDG_SR values ------------------------------------------------------ */

#define IWDG_SR_WVU			(1 << 2)
#define IWDG_SR_RVU			(1 << 1)
#define IWDG_SR_PVU			(1 << 0)

/* --- IWDG_WINR values ---------------------------------------------------- */

/* IWDG_WINR[11:0]: WIN[11:0]: Watchdog counter window value */

/* --- Function prototypes ------------------------------------------------- */

void iwdg_start(int prescaler, int count, int window);
void iwdg_reload(void);
