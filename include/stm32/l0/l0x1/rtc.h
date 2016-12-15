/*
 * RTC
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
 * 22  Real-time clock (RTC)
 */

/* --- RTC registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		RTC_TR		RTC time register
 * 0x04		RTC_DR		RTC date register
 * 0x08		RTC_CR		RTC control register
 * 0x0c		RTC_ISR		RTC initialization and status register
 * 0x10		RTC_PRER	RTC prescaler register
 * 0x14		RTC_WUTR	RTC wakeup timer register
 * 0x1c		RTC_ALRMAR	RTC alarm A register
 * 0x20		RTC_ALRMBR	RTC alarm B register
 * 0x24		RTC_WPR		RTC write protection register
 * 0x28		RTC_SSR		RTC sub second register
 * 0x2c		RTC_SHIFTR	RTC shift control register
 * 0x30		RTC_TSTR	RTC timestamp time register
 * 0x34		RTC_TSDR	RTC timestamp date register
 * 0x38		RTC_TSSSR	RTC timestamp sub second register
 * 0x3c		RTC_CALR	RTC calibration register
 * 0x40		RTC_TAMPCR	RTC tamper configuration register
 * 0x44		RTC_ALRMASSR	RTC alarm A sub second register
 * 0x48		RTC_ALRMBSSR	RTC alarm B sub second register
 * 0x4c		RTC_OR		RTC option register
 * 0x50		RTC_BKP0R	RTC backup register 0
 * 0x54		RTC_BKP1R	RTC backup register 1
 * 0x58		RTC_BKP2R	RTC backup register 2
 * 0x5c		RTC_BKP3R	RTC backup register 3
 * 0x60		RTC_BKP4R	RTC backup register 4
 */

#define RTC_TR				(RTC_BASE + 0x00)
#define RTC_DR				(RTC_BASE + 0x04)
#define RTC_CR				(RTC_BASE + 0x08)
#define RTC_ISR				(RTC_BASE + 0x0c)
#define RTC_PRER			(RTC_BASE + 0x10)
#define RTC_WUTR			(RTC_BASE + 0x14)
#define RTC_ALRMAR			(RTC_BASE + 0x1c)
#define RTC_ALRMBR			(RTC_BASE + 0x20)
#define RTC_WPR				(RTC_BASE + 0x24)
#define RTC_SSR				(RTC_BASE + 0x28)
#define RTC_SHIFTR			(RTC_BASE + 0x2c)
#define RTC_TSTR			(RTC_BASE + 0x30)
#define RTC_TSDR			(RTC_BASE + 0x34)
#define RTC_TSSSR			(RTC_BASE + 0x38)
#define RTC_CALR			(RTC_BASE + 0x3c)
#define RTC_TAMPCR			(RTC_BASE + 0x40)
#define RTC_ALRMASSR			(RTC_BASE + 0x44)
#define RTC_ALRMBSSR			(RTC_BASE + 0x48)
#define RTC_OR				(RTC_BASE + 0x4c)

#define RTC_BKPR(n)			(RTC_BASE + 0x50 + (n) * 4)
#define RTC_BKP0R			RTC_BKPR(0)
#define RTC_BKP1R			RTC_BKPR(1)
#define RTC_BKP2R			RTC_BKPR(2)
#define RTC_BKP3R			RTC_BKPR(3)
#define RTC_BKP4R			RTC_BKPR(4)

/* --- RTC_TR values ------------------------------------------------------- */

#define RTC_TR_PM			(1 << 22)
#define RTC_TR_HT1			(1 << 21)
#define RTC_TR_HT0			(1 << 20)
#define RTC_TR_HU3			(1 << 19)
#define RTC_TR_HU2			(1 << 18)
#define RTC_TR_HU1			(1 << 17)
#define RTC_TR_HU0			(1 << 16)
#define RTC_TR_MNT2			(1 << 14)
#define RTC_TR_MNT1			(1 << 13)
#define RTC_TR_MNT0			(1 << 12)
#define RTC_TR_MNU3			(1 << 11)
#define RTC_TR_MNU2			(1 << 10)
#define RTC_TR_MNU1			(1 << 9)
#define RTC_TR_MNU0			(1 << 8)
#define RTC_TR_ST2			(1 << 6)
#define RTC_TR_ST1			(1 << 5)
#define RTC_TR_ST0			(1 << 4)
#define RTC_TR_SU3			(1 << 3)
#define RTC_TR_SU2			(1 << 2)
#define RTC_TR_SU1			(1 << 1)
#define RTC_TR_SU0			(1 << 0)

/* --- RTC_DR values ------------------------------------------------------- */

#define RTC_DR_YT3			(1 << 23)
#define RTC_DR_YT2			(1 << 22)
#define RTC_DR_YT1			(1 << 21)
#define RTC_DR_YT0			(1 << 20)
#define RTC_DR_YU3			(1 << 19)
#define RTC_DR_YU2			(1 << 18)
#define RTC_DR_YU1			(1 << 17)
#define RTC_DR_YU0			(1 << 16)
#define RTC_DR_WDU2			(1 << 15)
#define RTC_DR_WDU1			(1 << 14)
#define RTC_DR_WDU0			(1 << 13)
#define RTC_DR_MT			(1 << 12)
#define RTC_DR_MU3			(1 << 11)
#define RTC_DR_MU2			(1 << 10)
#define RTC_DR_MU1			(1 << 9)
#define RTC_DR_MU0			(1 << 8)
#define RTC_DR_DT1			(1 << 5)
#define RTC_DR_DT0			(1 << 4)
#define RTC_DR_DU3			(1 << 3)
#define RTC_DR_DU2			(1 << 2)
#define RTC_DR_DU1			(1 << 1)
#define RTC_DR_DU0			(1 << 0)

/* --- RTC_CR values ------------------------------------------------------- */

#define RTC_CR_COE			(1 << 23)
#define RTC_CR_OSEL1			(1 << 22)
#define RTC_CR_OSEL0			(1 << 21)
#define RTC_CR_POL			(1 << 20)
#define RTC_CR_COSEL			(1 << 19)
#define RTC_CR_BKP			(1 << 18)
#define RTC_CR_SUB1H			(1 << 17)
#define RTC_CR_ADD1H			(1 << 16)
#define RTC_CR_TSIE			(1 << 15)
#define RTC_CR_WUTIE			(1 << 14)
#define RTC_CR_ALRBIE			(1 << 13)
#define RTC_CR_ALRAIE			(1 << 12)
#define RTC_CR_TSE			(1 << 11)
#define RTC_CR_WUTE			(1 << 10)
#define RTC_CR_ALRBE			(1 << 9)
#define RTC_CR_ALRAE			(1 << 8)
#define RTC_CR_FMT			(1 << 6)
#define RTC_CR_BYPSHAD			(1 << 5)
#define RTC_CR_REFCKON			(1 << 4)
#define RTC_CR_TSEDGE			(1 << 3)
#define RTC_CR_WUCKSEL2			(1 << 2)
#define RTC_CR_WUCKSEL1			(1 << 1)
#define RTC_CR_WUCKSEL0			(1 << 0)

/* Output selection */
#define RTC_CR_OSEL_DISABLE		(0 << 21)
#define RTC_CR_OSEL_ALARM_A		(1 << 21)
#define RTC_CR_OSEL_ALARM_B		(2 << 21)
#define RTC_CR_OSEL_WAKEUP		(3 << 21)

/* Wakeup clock selection */
#define RTC_CR_WUCKSEL_RTC_16		(0 << 0)
#define RTC_CR_WUCKSEL_RTC_8		(1 << 0)
#define RTC_CR_WUCKSEL_RTC_4		(2 << 0)
#define RTC_CR_WUCKSEL_RTC_2		(3 << 0)
#define RTC_CR_WUCKSEL_CK_SPRE		(4 << 0)
#define RTC_CR_WUCKSEL_CK_SPRE_0X10000	(6 << 0)

/* --- RTC_ISR values ------------------------------------------------------ */

#define RTC_ISR_RECALPF			(1 << 16)
#define RTC_ISR_TAMP3F			(1 << 15)
#define RTC_ISR_TAMP2F			(1 << 14)
#define RTC_ISR_TAMP1F			(1 << 13)
#define RTC_ISR_TSOVF			(1 << 12)
#define RTC_ISR_TSF			(1 << 11)
#define RTC_ISR_WUTF			(1 << 10)
#define RTC_ISR_ALRBF			(1 << 9)
#define RTC_ISR_ALRAF			(1 << 8)
#define RTC_ISR_INIT			(1 << 7)
#define RTC_ISR_INITF			(1 << 6)
#define RTC_ISR_RSF			(1 << 5)
#define RTC_ISR_INITS			(1 << 4)
#define RTC_ISR_SHPF			(1 << 3)
#define RTC_ISR_WUTWF			(1 << 2)
#define RTC_ISR_ALRBWF			(1 << 1)
#define RTC_ISR_ALRAWF			(1 << 0)

/* --- RTC_PRER values ----------------------------------------------------- */

/* RTC_PRER[22:16]: PREDIV_A[6:0]: Asynchronous prescaler factor */
/* RTC_PRER[14:0]: PREDIV_S[14:0]: Synchronous prescaler factor */

/* --- RTC_WUTR values ----------------------------------------------------- */

/* RTC_WUTR[15:0]: WUT[15:0]: Wakeup auto-reload value bits */

/* --- RTC_ALRMAR values --------------------------------------------------- */

#define RTC_ALRMAR_MSK4			(1 << 31)
#define RTC_ALRMAR_WDSEL		(1 << 30)
#define RTC_ALRMAR_DT1			(1 << 29)
#define RTC_ALRMAR_DT0			(1 << 28)
#define RTC_ALRMAR_DU3			(1 << 27)
#define RTC_ALRMAR_DU2			(1 << 26)
#define RTC_ALRMAR_DU1			(1 << 25)
#define RTC_ALRMAR_DU0			(1 << 24)
#define RTC_ALRMAR_MSK3			(1 << 23)
#define RTC_ALRMAR_PM			(1 << 22)
#define RTC_ALRMAR_HT1			(1 << 21)
#define RTC_ALRMAR_HT0			(1 << 20)
#define RTC_ALRMAR_HU3			(1 << 19)
#define RTC_ALRMAR_HU2			(1 << 18)
#define RTC_ALRMAR_HU1			(1 << 17)
#define RTC_ALRMAR_HU0			(1 << 16)
#define RTC_ALRMAR_MSK2			(1 << 15)
#define RTC_ALRMAR_MNT2			(1 << 14)
#define RTC_ALRMAR_MNT1			(1 << 13)
#define RTC_ALRMAR_MNT0			(1 << 12)
#define RTC_ALRMAR_MNU3			(1 << 11)
#define RTC_ALRMAR_MNU2			(1 << 10)
#define RTC_ALRMAR_MNU1			(1 << 9)
#define RTC_ALRMAR_MNU0			(1 << 8)
#define RTC_ALRMAR_MSK1			(1 << 7)
#define RTC_ALRMAR_ST2			(1 << 6)
#define RTC_ALRMAR_ST1			(1 << 5)
#define RTC_ALRMAR_ST0			(1 << 4)
#define RTC_ALRMAR_SU3			(1 << 3)
#define RTC_ALRMAR_SU2			(1 << 2)
#define RTC_ALRMAR_SU1			(1 << 1)
#define RTC_ALRMAR_SU0			(1 << 0)

/* --- RTC_ALRMBR values --------------------------------------------------- */

#define RTC_ALRMBR_MSK4			(1 << 31)
#define RTC_ALRMBR_WDSEL		(1 << 30)
#define RTC_ALRMBR_DT1			(1 << 29)
#define RTC_ALRMBR_DT0			(1 << 28)
#define RTC_ALRMBR_DU3			(1 << 27)
#define RTC_ALRMBR_DU2			(1 << 26)
#define RTC_ALRMBR_DU1			(1 << 25)
#define RTC_ALRMBR_DU0			(1 << 24)
#define RTC_ALRMBR_MSK3			(1 << 23)
#define RTC_ALRMBR_PM			(1 << 22)
#define RTC_ALRMBR_HT1			(1 << 21)
#define RTC_ALRMBR_HT0			(1 << 20)
#define RTC_ALRMBR_HU3			(1 << 19)
#define RTC_ALRMBR_HU2			(1 << 18)
#define RTC_ALRMBR_HU1			(1 << 17)
#define RTC_ALRMBR_HU0			(1 << 16)
#define RTC_ALRMBR_MSK2			(1 << 15)
#define RTC_ALRMBR_MNT2			(1 << 14)
#define RTC_ALRMBR_MNT1			(1 << 13)
#define RTC_ALRMBR_MNT0			(1 << 12)
#define RTC_ALRMBR_MNU3			(1 << 11)
#define RTC_ALRMBR_MNU2			(1 << 10)
#define RTC_ALRMBR_MNU1			(1 << 9)
#define RTC_ALRMBR_MNU0			(1 << 8)
#define RTC_ALRMBR_MSK1			(1 << 7)
#define RTC_ALRMBR_ST2			(1 << 6)
#define RTC_ALRMBR_ST1			(1 << 5)
#define RTC_ALRMBR_ST0			(1 << 4)
#define RTC_ALRMBR_SU3			(1 << 3)
#define RTC_ALRMBR_SU2			(1 << 2)
#define RTC_ALRMBR_SU1			(1 << 1)
#define RTC_ALRMBR_SU0			(1 << 0)

/* --- RTC_WPR values ------------------------------------------------------ */

/* RTC_WPR[7:0]: KEY[7:0]: Write protection key */

/* --- RTC_SSR values ------------------------------------------------------ */

/* RTC_SSR[15:0]: SS[15:0]: Sub second value */

/* --- RTC_SHIFTR values --------------------------------------------------- */

#define RTC_SHIFTR_ADD1S		(1 << 31)

/* RTC_SHIFTR[14:0]: SUBFS[14:0]: Subtract a fraction of a second */

/* --- RTC_TSTR values ----------------------------------------------------- */

#define RTC_TSTR_PM			(1 << 22)
#define RTC_TSTR_HT1			(1 << 21)
#define RTC_TSTR_HT0			(1 << 20)
#define RTC_TSTR_HU3			(1 << 19)
#define RTC_TSTR_HU2			(1 << 18)
#define RTC_TSTR_HU1			(1 << 17)
#define RTC_TSTR_HU0			(1 << 16)
#define RTC_TSTR_MNT2			(1 << 14)
#define RTC_TSTR_MNT1			(1 << 13)
#define RTC_TSTR_MNT0			(1 << 12)
#define RTC_TSTR_MNU3			(1 << 11)
#define RTC_TSTR_MNU2			(1 << 10)
#define RTC_TSTR_MNU1			(1 << 9)
#define RTC_TSTR_MNU0			(1 << 8)
#define RTC_TSTR_ST2			(1 << 6)
#define RTC_TSTR_ST1			(1 << 5)
#define RTC_TSTR_ST0			(1 << 4)
#define RTC_TSTR_SU3			(1 << 3)
#define RTC_TSTR_SU2			(1 << 2)
#define RTC_TSTR_SU1			(1 << 1)
#define RTC_TSTR_SU0			(1 << 0)

/* --- RTC_TSDR values ----------------------------------------------------- */

#define RTC_TSDR_WDU2			(1 << 15)
#define RTC_TSDR_WDU1			(1 << 14)
#define RTC_TSDR_WDU0			(1 << 13)
#define RTC_TSDR_MT			(1 << 12)
#define RTC_TSDR_MU3			(1 << 11)
#define RTC_TSDR_MU2			(1 << 10)
#define RTC_TSDR_MU1			(1 << 9)
#define RTC_TSDR_MU0			(1 << 8)
#define RTC_TSDR_DT1			(1 << 5)
#define RTC_TSDR_DT0			(1 << 4)
#define RTC_TSDR_DU3			(1 << 3)
#define RTC_TSDR_DU2			(1 << 2)
#define RTC_TSDR_DU1			(1 << 1)
#define RTC_TSDR_DU0			(1 << 0)

/* --- RTC_TSSSR values ---------------------------------------------------- */

/* RTC_TSSSR[15:0]: SS[15:0]: Sub second value */

/* --- RTC_CALR values ----------------------------------------------------- */

#define RTC_CALR_CALP			(1 << 15)
#define RTC_CALR_CALW8			(1 << 14)
#define RTC_CALR_CALW16			(1 << 13)
#define RTC_CALR_CALM8			(1 << 8)
#define RTC_CALR_CALM7			(1 << 7)
#define RTC_CALR_CALM6			(1 << 6)
#define RTC_CALR_CALM5			(1 << 5)
#define RTC_CALR_CALM4			(1 << 4)
#define RTC_CALR_CALM3			(1 << 3)
#define RTC_CALR_CALM2			(1 << 2)
#define RTC_CALR_CALM1			(1 << 1)
#define RTC_CALR_CALM0			(1 << 0)

/* --- RTC_TAMPCR values --------------------------------------------------- */

#define RTC_TAMPCR_TAMP3MF		(1 << 24)
#define RTC_TAMPCR_TAMP3NOERASE		(1 << 23)
#define RTC_TAMPCR_TAMP3IE		(1 << 22)
#define RTC_TAMPCR_TAMP2MF		(1 << 21)
#define RTC_TAMPCR_TAMP2NOERASE		(1 << 20)
#define RTC_TAMPCR_TAMP2IE		(1 << 19)
#define RTC_TAMPCR_TAMP1MF		(1 << 18)
#define RTC_TAMPCR_TAMP1NOERASE		(1 << 17)
#define RTC_TAMPCR_TAMP1IE		(1 << 16)
#define RTC_TAMPCR_TAMPPUDIS		(1 << 15)
#define RTC_TAMPCR_TAMPPRCH1		(1 << 14)
#define RTC_TAMPCR_TAMPPRCH0		(1 << 13)
#define RTC_TAMPCR_TAMPFLT1		(1 << 12)
#define RTC_TAMPCR_TAMPFLT0		(1 << 11)
#define RTC_TAMPCR_TAMPFREQ2		(1 << 10)
#define RTC_TAMPCR_TAMPFREQ1		(1 << 9)
#define RTC_TAMPCR_TAMPFREQ0		(1 << 8)
#define RTC_TAMPCR_TAMPTS		(1 << 7)
#define RTC_TAMPCR_TAMP3TRG		(1 << 6)
#define RTC_TAMPCR_TAMP3E		(1 << 5)
#define RTC_TAMPCR_TAMP2TRG		(1 << 4)
#define RTC_TAMPCR_TAMP2E		(1 << 3)
#define RTC_TAMPCR_TAMPIE		(1 << 2)
#define RTC_TAMPCR_TAMP1TRG		(1 << 1)
#define RTC_TAMPCR_TAMP1E		(1 << 0)

/* RTC_TAMPx precharge duration */
#define RTC_TAMPCR_TAMPPRCH_RTCCLK_1	(0 << 13)
#define RTC_TAMPCR_TAMPPRCH_RTCCLK_2	(1 << 13)
#define RTC_TAMPCR_TAMPPRCH_RTCCLK_4	(2 << 13)
#define RTC_TAMPCR_TAMPPRCH_RTCCLK_8	(3 << 13)

/* RTC_TAMPx filter count */
#define RTC_TAMPCR_TAMPFLT_0		(0 << 11)
#define RTC_TAMPCR_TAMPFLT_2		(1 << 11)
#define RTC_TAMPCR_TAMPFLT_4		(2 << 11)
#define RTC_TAMPCR_TAMPFLT_8		(3 << 11)

/* Tamper sampling frequency */
#define RTC_TAMPCR_TAMPFREQ_32768	(0 << 8)
#define RTC_TAMPCR_TAMPFREQ_16384	(1 << 8)
#define RTC_TAMPCR_TAMPFREQ_8192	(2 << 8)
#define RTC_TAMPCR_TAMPFREQ_4096	(3 << 8)
#define RTC_TAMPCR_TAMPFREQ_2048	(4 << 8)
#define RTC_TAMPCR_TAMPFREQ_1024	(5 << 8)
#define RTC_TAMPCR_TAMPFREQ_512		(6 << 8)
#define RTC_TAMPCR_TAMPFREQ_256		(7 << 8)

/* --- RTC_ALRMASSR values ------------------------------------------------- */

#define RTC_ALRMASSR_MASKSS3		(1 << 27)
#define RTC_ALRMASSR_MASKSS2		(1 << 26)
#define RTC_ALRMASSR_MASKSS1		(1 << 25)
#define RTC_ALRMASSR_MASKSS0		(1 << 24)

/* RTC_ALRMASSR[14:0]: SS[14:0]: Sub second value */

/* Mask the most-significant bits starting at this bit */
#define RTC_ALRMASSR_MASKSS_NO		(0 << 24)
#define RTC_ALRMASSR_MASKSS_0		(1 << 24)
#define RTC_ALRMASSR_MASKSS_1_0		(2 << 24)
#define RTC_ALRMASSR_MASKSS_2_0		(3 << 24)
#define RTC_ALRMASSR_MASKSS_3_0		(4 << 24)
#define RTC_ALRMASSR_MASKSS_4_0		(5 << 24)
#define RTC_ALRMASSR_MASKSS_5_0		(6 << 24)
#define RTC_ALRMASSR_MASKSS_6_0		(7 << 24)
#define RTC_ALRMASSR_MASKSS_7_0		(8 << 24)
#define RTC_ALRMASSR_MASKSS_8_0		(9 << 24)
#define RTC_ALRMASSR_MASKSS_9_0		(10 << 24)
#define RTC_ALRMASSR_MASKSS_10_0	(11 << 24)
#define RTC_ALRMASSR_MASKSS_11_0	(12 << 24)
#define RTC_ALRMASSR_MASKSS_12_0	(13 << 24)
#define RTC_ALRMASSR_MASKSS_13_0	(14 << 24)
#define RTC_ALRMASSR_MASKSS_14_0	(15 << 24)

/* --- RTC_ALRMBSSR values ------------------------------------------------- */

#define RTC_ALRMBSSR_MASKSS3		(1 << 27)
#define RTC_ALRMBSSR_MASKSS2		(1 << 26)
#define RTC_ALRMBSSR_MASKSS1		(1 << 25)
#define RTC_ALRMBSSR_MASKSS0		(1 << 24)

/* RTC_ALRMBSSR[14:0]: SS[14:0]: Sub second value */

/* Mask the most-significant bits starting at this bit */
#define RTC_ALRMBSSR_MASKSS_NO		(0 << 24)
#define RTC_ALRMBSSR_MASKSS_0		(1 << 24)
#define RTC_ALRMBSSR_MASKSS_1_0		(2 << 24)
#define RTC_ALRMBSSR_MASKSS_2_0		(3 << 24)
#define RTC_ALRMBSSR_MASKSS_3_0		(4 << 24)
#define RTC_ALRMBSSR_MASKSS_4_0		(5 << 24)
#define RTC_ALRMBSSR_MASKSS_5_0		(6 << 24)
#define RTC_ALRMBSSR_MASKSS_6_0		(7 << 24)
#define RTC_ALRMBSSR_MASKSS_7_0		(8 << 24)
#define RTC_ALRMBSSR_MASKSS_8_0		(9 << 24)
#define RTC_ALRMBSSR_MASKSS_9_0		(10 << 24)
#define RTC_ALRMBSSR_MASKSS_10_0	(11 << 24)
#define RTC_ALRMBSSR_MASKSS_11_0	(12 << 24)
#define RTC_ALRMBSSR_MASKSS_12_0	(13 << 24)
#define RTC_ALRMBSSR_MASKSS_13_0	(14 << 24)
#define RTC_ALRMBSSR_MASKSS_14_0	(15 << 24)

/* --- RTC_OR values ------------------------------------------------------- */

#define RTC_OR_RTC_OUT_RMP		(1 << 1)
#define RTC_OR_RTC_ALARM_TYPE		(1 << 0)

/* --- RTC_BKPxR values ---------------------------------------------------- */

/* RTC_BKPxR[31:0]: BKP[31:0]: Backup data */

/* --- Function prototypes ------------------------------------------------- */

/* Wakeup clock */
enum rtc_wakeup_clock {
	RTC_16 = 0,
	RTC_8 = 1,
	RTC_4 = 2,
	RTC_2 = 3,
	RTC_CK_SPRE = 4,
	RTC_CK_SPRE_0X10000 = 6
};

/* Calibration cycle period */
enum rtc_cal_period {
	RTC_32S = (0 << 13),
	RTC_16S = (1 << 13),
	RTC_8S = (2 << 13)
};

/* Interrupt and status */
enum {
	RTC_ALARM_A = (1 << 8),
	RTC_ALARM_B = (1 << 9),
	RTC_WAKEUP = (1 << 10),
	RTC_TIMESTAMP = (1 << 11),
	RTC_TIMESTAMP_OVERFLOW = (1 << 12),
	RTC_TAMPER1 = (1 << 13),
	RTC_TAMPER2 = (1 << 14),
	RTC_TAMPER3 = (1 << 15),

	RTC_CALIBRATION = (1 << 16),
	RTC_INIT_MODE = (1 << 7),
	RTC_INIT_FLAG = (1 << 6),
	RTC_INIT_STATUS = (1 << 4),
	RTC_REGISTER_SYNC = (1 << 5),
	RTC_SHIFT = (1 << 3),
	RTC_WAKEUP_WRITE = (1 << 2),
	RTC_ALARM_B_WRITE = (1 << 1),
	RTC_ALARM_A_WRITE = (1 << 0)
};

/* RTC_CALIB output */
enum rtc_cal_output {
	RTC_CO_DISABLE = (0 << 19),
	RTC_512HZ = (16 << 19),
	RTC_1HZ = (17 << 19)
};

/* RTC_ALARM output */
enum rtc_alarm_output {
	RTC_AO_DISABLE = (0 << 21),
	RTC_AO_ALARM_A = (1 << 21),
	RTC_AO_ALARM_B = (2 << 21),
	RTC_AO_WAKEUP = (3 << 21)
};

/* Active level for RTC_TAMPx input */
enum rtc_tamp_trigger {
	RTC_LOW = 0,
	RTC_HIGH = 1,
	RTC_RISING = 0,
	RTC_FALLING = 1
};

void rtc_unlock(void);
void rtc_lock(void);
void rtc_init(int prediv_a, int prediv_s, int date, int time, bool fmt,
	      bool refck);
void rtc_disable_shadow_register(void);
void rtc_enable_shadow_register(void);
void rtc_enable_daylight_saving_time(void);
void rtc_disable_daylight_saving_time(void);
void rtc_enable_alarm_a(int time, int ss);
void rtc_disable_alarm_a(void);
void rtc_enable_alarm_b(int time, int ss);
void rtc_disable_alarm_b(void);
void rtc_enable_wakeup_timer(enum rtc_wakeup_clock wucksel, int autoreload);
void rtc_disable_wakeup_timer(void);
void rtc_get_calendar(int *date, int *time, int *ss);
void rtc_get_calendar_read_twice(int *date, int *time, int *ss);
void rtc_synchronize(int add, int sub);
void rtc_set_smooth_digital_calibration(int calp, int calm,
					enum rtc_cal_period calw);
void rtc_get_timestamp(int *date, int *time, int *ss);
void rtc_enable_interrupt(int interrupt);
void rtc_disable_interrupt(int interrupt);
int rtc_get_interrupt_mask(int interrupt);
int rtc_get_interrupt_status(int interrupt);
void rtc_clear_interrupt(int interrupt);
void rtc_set_rtc_calib(enum rtc_cal_output cosel);
void rtc_set_rtc_alarm(enum rtc_alarm_output osel, bool low_level);
void rtc_remap_rtc_out(bool pb14, bool push_pull);
void rtc_enable_timestamp(bool falling);
void rtc_disable_timestamp(void);
void rtc_setup_tamper(int precharge, int sample_div, int filter_count,
		      bool timestamp);
void rtc_enable_tamp1(enum rtc_tamp_trigger trigger, bool mask, bool no_erase);
void rtc_disable_tamp1(void);
void rtc_enable_tamp2(enum rtc_tamp_trigger trigger, bool mask, bool no_erase);
void rtc_disable_tamp2(void);
void rtc_enable_tamp3(enum rtc_tamp_trigger trigger, bool mask, bool no_erase);
void rtc_disable_tamp3(void);
