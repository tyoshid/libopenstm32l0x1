/*
 * Private peripheral bus memory map
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
 * PM0223: Programming manual
 * STM32L0 Series Cortex-M0+ programming manual
 * (15-Apr-2014 Rev 1)
 *
 * 4  STM32L0 Core peripherals
 */

/* --- STM32L0 Cortex-M0+ Core peripherals --------------------------------- */

#define PPB_BASE			0xe0000000

#define STK_BASE			(PPB_BASE + 0xe010)
#define NVIC_BASE			(PPB_BASE + 0xe100)
#define SCB_BASE			(PPB_BASE + 0xed00)
#define MPU_BASE			(PPB_BASE + 0xed90)
