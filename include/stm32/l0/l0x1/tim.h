/*
 * TIM
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
 * 16  General-purpose timers (TIM2/TIM3)
 * 17  General-purpose timers (TIM21/22)
 * 18  Basic timers (TIM6/7)
 */

/* --- TIM registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		TIMx_CR1	TIMx control register 1
 * 0x04		TIMx_CR2	TIMx control register 2
 * 0x08		TIMx_SMCR	TIMx slave mode control register
 * 0x0c		TIMx_DIER	TIMx DMA/Interrupt enable register
 * 0x10		TIMx_SR		TIMx status register
 * 0x14		TIMx_EGR	TIMx event generation register
 * 0x18		TIMx_CCMR1	TIMx capture/compare mode register 1
 * 0x1c		TIMx_CCMR2	TIMx capture/compare mode register 2
 * 0x20		TIMx_CCER	TIMx capture/compare enable register
 * 0x24		TIMx_CNT	TIMx counter
 * 0x28		TIMx_PSC	TIMx prescaler
 * 0x2c		TIMx_ARR	TIMx auto-reload register
 * 0x34		TIMx_CCR1	TIMx capture/compare register 1
 * 0x38		TIMx_CCR2	TIMx capture/compare register 2
 * 0x3c		TIMx_CCR3	TIMx capture/compare register 3
 * 0x40		TIMx_CCR4	TIMx capture/compare register 4
 * 0x48		TIMx_DCR	TIMx DMA control register
 * 0x4c		TIMx_DMAR	TIMx DMA address for full transfer
 * 0x50		TIMx_OR		TIMx option register
 */

#define TIM_CR1(base)			((base) + 0x00)
#define TIM2_CR1			TIM_CR1(TIM2_BASE)
#define TIM3_CR1			TIM_CR1(TIM3_BASE)
#define TIM21_CR1			TIM_CR1(TIM21_BASE)
#define TIM22_CR1			TIM_CR1(TIM22_BASE)
#define TIM6_CR1			TIM_CR1(TIM6_BASE)
#define TIM7_CR1			TIM_CR1(TIM7_BASE)

#define TIM_CR2(base)			((base) + 0x04)
#define TIM2_CR2			TIM_CR2(TIM2_BASE)
#define TIM3_CR2			TIM_CR2(TIM3_BASE)
#define TIM21_CR2			TIM_CR2(TIM21_BASE)
#define TIM22_CR2			TIM_CR2(TIM22_BASE)
#define TIM6_CR2			TIM_CR2(TIM6_BASE)
#define TIM7_CR2			TIM_CR2(TIM7_BASE)

#define TIM_SMCR(base)			((base) + 0x08)
#define TIM2_SMCR			TIM_SMCR(TIM2_BASE)
#define TIM3_SMCR			TIM_SMCR(TIM3_BASE)
#define TIM21_SMCR			TIM_SMCR(TIM21_BASE)
#define TIM22_SMCR			TIM_SMCR(TIM22_BASE)

#define TIM_DIER(base)			((base) + 0x0c)
#define TIM2_DIER			TIM_DIER(TIM2_BASE)
#define TIM3_DIER			TIM_DIER(TIM3_BASE)
#define TIM21_DIER			TIM_DIER(TIM21_BASE)
#define TIM22_DIER			TIM_DIER(TIM22_BASE)
#define TIM6_DIER			TIM_DIER(TIM6_BASE)
#define TIM7_DIER			TIM_DIER(TIM7_BASE)

#define TIM_SR(base)			((base) + 0x10)
#define TIM2_SR				TIM_SR(TIM2_BASE)
#define TIM3_SR				TIM_SR(TIM3_BASE)
#define TIM21_SR			TIM_SR(TIM21_BASE)
#define TIM22_SR			TIM_SR(TIM22_BASE)
#define TIM6_SR				TIM_SR(TIM6_BASE)
#define TIM7_SR				TIM_SR(TIM7_BASE)

#define TIM_EGR(base)			((base) + 0x14)
#define TIM2_EGR			TIM_EGR(TIM2_BASE)
#define TIM3_EGR			TIM_EGR(TIM3_BASE)
#define TIM21_EGR			TIM_EGR(TIM21_BASE)
#define TIM22_EGR			TIM_EGR(TIM22_BASE)
#define TIM6_EGR			TIM_EGR(TIM6_BASE)
#define TIM7_EGR			TIM_EGR(TIM7_BASE)

#define TIM_CCMR1(base)			((base) + 0x18)
#define TIM2_CCMR1			TIM_CCMR1(TIM2_BASE)
#define TIM3_CCMR1			TIM_CCMR1(TIM3_BASE)
#define TIM21_CCMR1			TIM_CCMR1(TIM21_BASE)
#define TIM22_CCMR1			TIM_CCMR1(TIM22_BASE)

#define TIM_CCMR2(base)			((base) + 0x1c)
#define TIM2_CCMR2			TIM_CCMR2(TIM2_BASE)
#define TIM3_CCMR2			TIM_CCMR2(TIM3_BASE)

#define TIM_CCER(base)			((base) + 0x20)
#define TIM2_CCER			TIM_CCER(TIM2_BASE)
#define TIM3_CCER			TIM_CCER(TIM3_BASE)
#define TIM21_CCER			TIM_CCER(TIM21_BASE)
#define TIM22_CCER			TIM_CCER(TIM22_BASE)

#define TIM_CNT(base)			((base) + 0x24)
#define TIM2_CNT			TIM_CNT(TIM2_BASE)
#define TIM3_CNT			TIM_CNT(TIM3_BASE)
#define TIM21_CNT			TIM_CNT(TIM21_BASE)
#define TIM22_CNT			TIM_CNT(TIM22_BASE)
#define TIM6_CNT			TIM_CNT(TIM6_BASE)
#define TIM7_CNT			TIM_CNT(TIM7_BASE)

#define TIM_PSC(base)			((base) + 0x28)
#define TIM2_PSC			TIM_PSC(TIM2_BASE)
#define TIM3_PSC			TIM_PSC(TIM3_BASE)
#define TIM21_PSC			TIM_PSC(TIM21_BASE)
#define TIM22_PSC			TIM_PSC(TIM22_BASE)
#define TIM6_PSC			TIM_PSC(TIM6_BASE)
#define TIM7_PSC			TIM_PSC(TIM7_BASE)

#define TIM_ARR(base)			((base) + 0x2c)
#define TIM2_ARR			TIM_ARR(TIM2_BASE)
#define TIM3_ARR			TIM_ARR(TIM3_BASE)
#define TIM21_ARR			TIM_ARR(TIM21_BASE)
#define TIM22_ARR			TIM_ARR(TIM22_BASE)
#define TIM6_ARR			TIM_ARR(TIM6_BASE)
#define TIM7_ARR			TIM_ARR(TIM7_BASE)

#define TIM_CCR1(base)			((base) + 0x34)
#define TIM2_CCR1			TIM_CCR1(TIM2_BASE)
#define TIM3_CCR1			TIM_CCR1(TIM3_BASE)
#define TIM21_CCR1			TIM_CCR1(TIM21_BASE)
#define TIM22_CCR1			TIM_CCR1(TIM22_BASE)

#define TIM_CCR2(base)			((base) + 0x38)
#define TIM2_CCR2			TIM_CCR2(TIM2_BASE)
#define TIM3_CCR2			TIM_CCR2(TIM3_BASE)
#define TIM21_CCR2			TIM_CCR2(TIM21_BASE)
#define TIM22_CCR2			TIM_CCR2(TIM22_BASE)

#define TIM_CCR3(base)			((base) + 0x3c)
#define TIM2_CCR3			TIM_CCR3(TIM2_BASE)
#define TIM3_CCR3			TIM_CCR3(TIM3_BASE)

#define TIM_CCR4(base)			((base) + 0x40)
#define TIM2_CCR4			TIM_CCR4(TIM2_BASE)
#define TIM3_CCR4			TIM_CCR4(TIM3_BASE)

#define TIM_DCR(base)			((base) + 0x48)
#define TIM2_DCR			TIM_DCR(TIM2_BASE)
#define TIM3_DCR			TIM_DCR(TIM3_BASE)

#define TIM_DMAR(base)			((base) + 0x4c)
#define TIM2_DMAR			TIM_DMAR(TIM2_BASE)
#define TIM3_DMAR			TIM_DMAR(TIM3_BASE)

#define TIM_OR(base)			((base) + 0x50)
#define TIM2_OR				TIM_OR(TIM2_BASE)
#define TIM3_OR				TIM_OR(TIM3_BASE)
#define TIM21_OR			TIM_OR(TIM21_BASE)
#define TIM22_OR			TIM_OR(TIM22_BASE)

/* --- TIMx_CR1 values ----------------------------------------------------- */

#define TIM_CR1_CKD1			(1 << 9)
#define TIM_CR1_CKD0			(1 << 8)
#define TIM_CR1_ARPE			(1 << 7)
#define TIM_CR1_CMS1			(1 << 6)
#define TIM_CR1_CMS0			(1 << 5)
#define TIM_CR1_DIR			(1 << 4)
#define TIM_CR1_OPM			(1 << 3)
#define TIM_CR1_URS			(1 << 2)
#define TIM_CR1_UDIS			(1 << 1)
#define TIM_CR1_CEN			(1 << 0)

/* Clock division */
#define TIM_CR1_CKD_1			(0 << 8)
#define TIM_CR1_CKD_2			(1 << 8)
#define TIM_CR1_CKD_4			(2 << 8)

/* Center-aligned mode selection */
#define TIM_CR1_CMS_EDGE_ALIGNED_MODE	(0 << 5)
#define TIM_CR1_CMS_MODE1		(1 << 5)
#define TIM_CR1_CMS_MODE2		(2 << 5)
#define TIM_CR1_CMS_MODE3		(3 << 5)

/* --- TIMx_CR2 values ----------------------------------------------------- */

#define TIM_CR2_TI1S			(1 << 7)
#define TIM_CR2_MMS2			(1 << 6)
#define TIM_CR2_MMS1			(1 << 5)
#define TIM_CR2_MMS0			(1 << 4)
#define TIM_CR2_CCDS			(1 << 3)

/* Master mode selection */
#define TIM_CR2_MMS_RESET		(0 << 4)
#define TIM_CR2_MMS_ENABLE		(1 << 4)
#define TIM_CR2_MMS_UPDATE		(2 << 4)
#define TIM_CR2_MMS_COMPARE_PULSE	(3 << 4)
#define TIM_CR2_MMS_COMPARE_OC1REF	(4 << 4)
#define TIM_CR2_MMS_COMPARE_OC2REF	(5 << 4)
#define TIM_CR2_MMS_COMPARE_OC3REF	(6 << 4)
#define TIM_CR2_MMS_COMPARE_OC4REF	(7 << 4)

/* --- TIMx_SMCR values ---------------------------------------------------- */

#define TIM_SMCR_ETP			(1 << 15)
#define TIM_SMCR_ECE			(1 << 14)
#define TIM_SMCR_ETPS1			(1 << 13)
#define TIM_SMCR_ETPS0			(1 << 12)
#define TIM_SMCR_ETF3			(1 << 11)
#define TIM_SMCR_ETF2			(1 << 10)
#define TIM_SMCR_ETF1			(1 << 9)
#define TIM_SMCR_ETF0			(1 << 8)
#define TIM_SMCR_MSM			(1 << 7)
#define TIM_SMCR_TS2			(1 << 6)
#define TIM_SMCR_TS1			(1 << 5)
#define TIM_SMCR_TS0			(1 << 4)
#define TIM_SMCR_SMS2			(1 << 2)
#define TIM_SMCR_SMS1			(1 << 1)
#define TIM_SMCR_SMS0			(1 << 0)

/* External trigger prescaler */
#define TIM_SMCR_ETPS_1			(0 << 12)
#define TIM_SMCR_ETPS_2			(1 << 12)
#define TIM_SMCR_ETPS_4			(2 << 12)
#define TIM_SMCR_ETPS_8			(3 << 12)

/* External trigger filter */
#define TIM_SMCR_ETF_DTS_N_1		(0 << 8)
#define TIM_SMCR_ETF_CK_INT_N_2		(1 << 8)
#define TIM_SMCR_ETF_CK_INT_N_4		(2 << 8)
#define TIM_SMCR_ETF_CK_INT_N_8		(3 << 8)
#define TIM_SMCR_ETF_DTS_2_N_6		(4 << 8)
#define TIM_SMCR_ETF_DTS_2_N_8		(5 << 8)
#define TIM_SMCR_ETF_DTS_4_N_6		(6 << 8)
#define TIM_SMCR_ETF_DTS_4_N_8		(7 << 8)
#define TIM_SMCR_ETF_DTS_8_N_6		(8 << 8)
#define TIM_SMCR_ETF_DTS_8_N_8		(9 << 8)
#define TIM_SMCR_ETF_DTS_16_N_5		(10 << 8)
#define TIM_SMCR_ETF_DTS_16_N_6		(11 << 8)
#define TIM_SMCR_ETF_DTS_16_N_8		(12 << 8)
#define TIM_SMCR_ETF_DTS_32_N_5		(13 << 8)
#define TIM_SMCR_ETF_DTS_32_N_6		(14 << 8)
#define TIM_SMCR_ETF_DTS_32_N_8		(15 << 8)

/* Trigger selection */
#define TIM_SMCR_TS_ITR0		(0 << 4)
#define TIM_SMCR_TS_ITR1		(1 << 4)
#define TIM_SMCR_TS_ITR2		(2 << 4)
#define TIM_SMCR_TS_TI1F_ED		(4 << 4)
#define TIM_SMCR_TS_TI1FP1		(5 << 4)
#define TIM_SMCR_TS_TI2FP2		(6 << 4)
#define TIM_SMCR_TS_ETRF		(7 << 4)

/* Slave mode selection */
#define TIM_SMCR_SMS_DISABLE		(0 << 0)
#define TIM_SMCR_SMS_ENCODER_MODE1	(1 << 0)
#define TIM_SMCR_SMS_ENCODER_MODE2	(2 << 0)
#define TIM_SMCR_SMS_ENCODER_MODE3	(3 << 0)
#define TIM_SMCR_SMS_RESET_MODE		(4 << 0)
#define TIM_SMCR_SMS_GATED_MODE		(5 << 0)
#define TIM_SMCR_SMS_TRIGGER_MODE	(6 << 0)
#define TIM_SMCR_SMS_EXT_CLOCK_MODE1	(7 << 0)

/* --- TIMx_DIER values ---------------------------------------------------- */

#define TIM_DIER_TDE			(1 << 14)
#define TIM_DIER_CC4DE			(1 << 12)
#define TIM_DIER_CC3DE			(1 << 11)
#define TIM_DIER_CC2DE			(1 << 10)
#define TIM_DIER_CC1DE			(1 << 9)
#define TIM_DIER_UDE			(1 << 8)
#define TIM_DIER_TIE			(1 << 6)
#define TIM_DIER_CC4IE			(1 << 4)
#define TIM_DIER_CC3IE			(1 << 3)
#define TIM_DIER_CC2IE			(1 << 2)
#define TIM_DIER_CC1IE			(1 << 1)
#define TIM_DIER_UIE			(1 << 0)

/* --- TIMx_SR values ------------------------------------------------------ */

#define TIM_SR_CC4OF			(1 << 12)
#define TIM_SR_CC3OF			(1 << 11)
#define TIM_SR_CC2OF			(1 << 10)
#define TIM_SR_CC1OF			(1 << 9)
#define TIM_SR_TIF			(1 << 6)
#define TIM_SR_CC4IF			(1 << 4)
#define TIM_SR_CC3IF			(1 << 3)
#define TIM_SR_CC2IF			(1 << 2)
#define TIM_SR_CC1IF			(1 << 1)
#define TIM_SR_UIF			(1 << 0)

/* --- TIMx_EGR values ----------------------------------------------------- */

#define TIM_EGR_TG			(1 << 6)
#define TIM_EGR_CC4G			(1 << 4)
#define TIM_EGR_CC3G			(1 << 3)
#define TIM_EGR_CC2G			(1 << 2)
#define TIM_EGR_CC1G			(1 << 1)
#define TIM_EGR_UG			(1 << 0)

/* --- TIMx_CCMR1 values --------------------------------------------------- */

/* Output compare mode */
#define TIM_CCMR1_OC2CE			(1 << 15)
#define TIM_CCMR1_OC2M2			(1 << 14)
#define TIM_CCMR1_OC2M1			(1 << 13)
#define TIM_CCMR1_OC2M0			(1 << 12)
#define TIM_CCMR1_OC2PE			(1 << 11)
#define TIM_CCMR1_OC2FE			(1 << 10)
#define TIM_CCMR1_CC2S1			(1 << 9)
#define TIM_CCMR1_CC2S0			(1 << 8)
#define TIM_CCMR1_OC1CE			(1 << 7)
#define TIM_CCMR1_OC1M2			(1 << 6)
#define TIM_CCMR1_OC1M1			(1 << 5)
#define TIM_CCMR1_OC1M0			(1 << 4)
#define TIM_CCMR1_OC1PE			(1 << 3)
#define TIM_CCMR1_OC1FE			(1 << 2)
#define TIM_CCMR1_CC1S1			(1 << 1)
#define TIM_CCMR1_CC1S0			(1 << 0)

/* Output compare 2 mode */
#define TIM_CCMR1_OC2M_FROZEN		(0 << 12)
#define TIM_CCMR1_OC2M_MATCH_ACTIVE	(1 << 12)
#define TIM_CCMR1_OC2M_MATCH_INACTIVE	(2 << 12)
#define TIM_CCMR1_OC2M_MATCH_TOGGLE	(3 << 12)
#define TIM_CCMR1_OC2M_FORCE_INACTIVE	(4 << 12)
#define TIM_CCMR1_OC2M_FORCE_ACTIVE	(5 << 12)
#define TIM_CCMR1_OC2M_PWM_MODE1	(6 << 12)
#define TIM_CCMR1_OC2M_PWM_MODE2	(7 << 12)

/* Capture/Compare 2 selection */
#define TIM_CCMR1_CC2S_OUTPUT		(0 << 8)
#define TIM_CCMR1_CC2S_INPUT_TI2	(1 << 8)
#define TIM_CCMR1_CC2S_INPUT_TI1	(2 << 8)
#define TIM_CCMR1_CC2S_INPUT_TRC	(3 << 8)

/* Output compare 1 mode */
#define TIM_CCMR1_OC1M_FROZEN		(0 << 4)
#define TIM_CCMR1_OC1M_MATCH_ACTIVE	(1 << 4)
#define TIM_CCMR1_OC1M_MATCH_INACTIVE	(2 << 4)
#define TIM_CCMR1_OC1M_MATCH_TOGGLE	(3 << 4)
#define TIM_CCMR1_OC1M_FORCE_INACTIVE	(4 << 4)
#define TIM_CCMR1_OC1M_FORCE_ACTIVE	(5 << 4)
#define TIM_CCMR1_OC1M_PWM_MODE1	(6 << 4)
#define TIM_CCMR1_OC1M_PWM_MODE2	(7 << 4)

/* Capture/Compare 1 selection */
#define TIM_CCMR1_CC1S_OUTPUT		(0 << 0)
#define TIM_CCMR1_CC1S_INPUT_TI1	(1 << 0)
#define TIM_CCMR1_CC1S_INPUT_TI2	(2 << 0)
#define TIM_CCMR1_CC1S_INPUT_TRC	(3 << 0)


/* Input capture mode */
#define TIM_CCMR1_IC2F3			(1 << 15)
#define TIM_CCMR1_IC2F2			(1 << 14)
#define TIM_CCMR1_IC2F1			(1 << 13)
#define TIM_CCMR1_IC2F0			(1 << 12)
#define TIM_CCMR1_IC2PSC1		(1 << 11)
#define TIM_CCMR1_IC2PSC0		(1 << 10)
#define TIM_CCMR1_IC1F3			(1 << 7)
#define TIM_CCMR1_IC1F2			(1 << 6)
#define TIM_CCMR1_IC1F1			(1 << 5)
#define TIM_CCMR1_IC1F0			(1 << 4)
#define TIM_CCMR1_IC1PSC1		(1 << 3)
#define TIM_CCMR1_IC1PSC0		(1 << 2)

/* Input capture 2 filter */
#define TIM_CCMR1_IC2F_DTS_N_1		(0 << 12)
#define TIM_CCMR1_IC2F_CK_INT_N_2	(1 << 12)
#define TIM_CCMR1_IC2F_CK_INT_N_4	(2 << 12)
#define TIM_CCMR1_IC2F_CK_INT_N_8	(3 << 12)
#define TIM_CCMR1_IC2F_DTS_2_N_6	(4 << 12)
#define TIM_CCMR1_IC2F_DTS_2_N_8	(5 << 12)
#define TIM_CCMR1_IC2F_DTS_4_N_6	(6 << 12)
#define TIM_CCMR1_IC2F_DTS_4_N_8	(7 << 12)
#define TIM_CCMR1_IC2F_DTS_8_N_6	(8 << 12)
#define TIM_CCMR1_IC2F_DTS_8_N_8	(9 << 12)
#define TIM_CCMR1_IC2F_DTS_16_N_5	(10 << 12)
#define TIM_CCMR1_IC2F_DTS_16_N_6	(11 << 12)
#define TIM_CCMR1_IC2F_DTS_16_N_8	(12 << 12)
#define TIM_CCMR1_IC2F_DTS_32_N_5	(13 << 12)
#define TIM_CCMR1_IC2F_DTS_32_N_6	(14 << 12)
#define TIM_CCMR1_IC2F_DTS_32_N_8	(15 << 12)

/* Input capture 2 prescaler */
#define TIM_CCMR1_IC2PSC_1		(0 << 10)
#define TIM_CCMR1_IC2PSC_2		(1 << 10)
#define TIM_CCMR1_IC2PSC_4		(2 << 10)
#define TIM_CCMR1_IC2PSC_8		(3 << 10)

/* Input capture 1 filter */
#define TIM_CCMR1_IC1F_DTS_N_1		(0 << 4)
#define TIM_CCMR1_IC1F_CK_INT_N_2	(1 << 4)
#define TIM_CCMR1_IC1F_CK_INT_N_4	(2 << 4)
#define TIM_CCMR1_IC1F_CK_INT_N_8	(3 << 4)
#define TIM_CCMR1_IC1F_DTS_2_N_6	(4 << 4)
#define TIM_CCMR1_IC1F_DTS_2_N_8	(5 << 4)
#define TIM_CCMR1_IC1F_DTS_4_N_6	(6 << 4)
#define TIM_CCMR1_IC1F_DTS_4_N_8	(7 << 4)
#define TIM_CCMR1_IC1F_DTS_8_N_6	(8 << 4)
#define TIM_CCMR1_IC1F_DTS_8_N_8	(9 << 4)
#define TIM_CCMR1_IC1F_DTS_16_N_5	(10 << 4)
#define TIM_CCMR1_IC1F_DTS_16_N_6	(11 << 4)
#define TIM_CCMR1_IC1F_DTS_16_N_8	(12 << 4)
#define TIM_CCMR1_IC1F_DTS_32_N_5	(13 << 4)
#define TIM_CCMR1_IC1F_DTS_32_N_6	(14 << 4)
#define TIM_CCMR1_IC1F_DTS_32_N_8	(15 << 4)

/* Input capture 1 prescaler */
#define TIM_CCMR1_IC1PSC_1		(0 << 2)
#define TIM_CCMR1_IC1PSC_2		(1 << 2)
#define TIM_CCMR1_IC1PSC_4		(2 << 2)
#define TIM_CCMR1_IC1PSC_8		(3 << 2)

/* --- TIMx_CCMR2 values --------------------------------------------------- */

/* Ooutput compare mode */
#define TIM_CCMR2_OC4CE			(1 << 15)
#define TIM_CCMR2_OC4M2			(1 << 14)
#define TIM_CCMR2_OC4M1			(1 << 13)
#define TIM_CCMR2_OC4M0			(1 << 12)
#define TIM_CCMR2_OC4PE			(1 << 11)
#define TIM_CCMR2_OC4FE			(1 << 10)
#define TIM_CCMR2_CC4S1			(1 << 9)
#define TIM_CCMR2_CC4S0			(1 << 8)
#define TIM_CCMR2_OC3CE			(1 << 7)
#define TIM_CCMR2_OC3M2			(1 << 6)
#define TIM_CCMR2_OC3M1			(1 << 5)
#define TIM_CCMR2_OC3M0			(1 << 4)
#define TIM_CCMR2_OC3PE			(1 << 3)
#define TIM_CCMR2_OC3FE			(1 << 2)
#define TIM_CCMR2_CC3S1			(1 << 1)
#define TIM_CCMR2_CC3S0			(1 << 0)

/* Output compare 4 mode */
#define TIM_CCMR2_OC4M_FROZEN		(0 << 12)
#define TIM_CCMR2_OC4M_MATCH_ACTIVE	(1 << 12)
#define TIM_CCMR2_OC4M_MATCH_INACTIVE	(2 << 12)
#define TIM_CCMR2_OC4M_MATCH_TOGGLE	(3 << 12)
#define TIM_CCMR2_OC4M_FORCE_INACTIVE	(4 << 12)
#define TIM_CCMR2_OC4M_FORCE_ACTIVE	(5 << 12)
#define TIM_CCMR2_OC4M_PWM_MODE1	(6 << 12)
#define TIM_CCMR2_OC4M_PWM_MODE2	(7 << 12)

/* Capture/Compare 4 selection */
#define TIM_CCMR2_CC4S_OUTPUT		(0 << 8)
#define TIM_CCMR2_CC4S_INPUT_TI4	(1 << 8)
#define TIM_CCMR2_CC4S_INPUT_TI3	(2 << 8)
#define TIM_CCMR2_CC4S_INPUT_TRC	(3 << 8)

/* Output compare 3 mode */
#define TIM_CCMR2_OC3M_FROZEN		(0 << 4)
#define TIM_CCMR2_OC3M_MATCH_ACTIVE	(1 << 4)
#define TIM_CCMR2_OC3M_MATCH_INACTIVE	(2 << 4)
#define TIM_CCMR2_OC3M_MATCH_TOGGLE	(3 << 4)
#define TIM_CCMR2_OC3M_FORCE_INACTIVE	(4 << 4)
#define TIM_CCMR2_OC3M_FORCE_ACTIVE	(5 << 4)
#define TIM_CCMR2_OC3M_PWM_MODE1	(6 << 4)
#define TIM_CCMR2_OC3M_PWM_MODE2	(7 << 4)

/* Capture/Compare 3 selection */
#define TIM_CCMR2_CC3S_OUTPUT		(0 << 0)
#define TIM_CCMR2_CC3S_INPUT_TI3	(1 << 0)
#define TIM_CCMR2_CC3S_INPUT_TI4	(2 << 0)
#define TIM_CCMR2_CC3S_INPUT_TRC	(3 << 0)


/* Input capture mode */
#define TIM_CCMR2_IC4F3			(1 << 15)
#define TIM_CCMR2_IC4F2			(1 << 14)
#define TIM_CCMR2_IC4F1			(1 << 13)
#define TIM_CCMR2_IC4F0			(1 << 12)
#define TIM_CCMR2_IC4PSC1		(1 << 11)
#define TIM_CCMR2_IC4PSC0		(1 << 10)
#define TIM_CCMR2_IC3F3			(1 << 7)
#define TIM_CCMR2_IC3F2			(1 << 6)
#define TIM_CCMR2_IC3F1			(1 << 5)
#define TIM_CCMR2_IC3F0			(1 << 4)
#define TIM_CCMR2_IC3PSC1		(1 << 3)
#define TIM_CCMR2_IC3PSC0		(1 << 2)

/* Input capture 4 filter */
#define TIM_CCMR2_IC4F_DTS_N_1		(0 << 12)
#define TIM_CCMR2_IC4F_CK_INT_N_2	(1 << 12)
#define TIM_CCMR2_IC4F_CK_INT_N_4	(2 << 12)
#define TIM_CCMR2_IC4F_CK_INT_N_8	(3 << 12)
#define TIM_CCMR2_IC4F_DTS_2_N_6	(4 << 12)
#define TIM_CCMR2_IC4F_DTS_2_N_8	(5 << 12)
#define TIM_CCMR2_IC4F_DTS_4_N_6	(6 << 12)
#define TIM_CCMR2_IC4F_DTS_4_N_8	(7 << 12)
#define TIM_CCMR2_IC4F_DTS_8_N_6	(8 << 12)
#define TIM_CCMR2_IC4F_DTS_8_N_8	(9 << 12)
#define TIM_CCMR2_IC4F_DTS_16_N_5	(10 << 12)
#define TIM_CCMR2_IC4F_DTS_16_N_6	(11 << 12)
#define TIM_CCMR2_IC4F_DTS_16_N_8	(12 << 12)
#define TIM_CCMR2_IC4F_DTS_32_N_5	(13 << 12)
#define TIM_CCMR2_IC4F_DTS_32_N_6	(14 << 12)
#define TIM_CCMR2_IC4F_DTS_32_N_8	(15 << 12)

/* Input capture 4 prescaler */
#define TIM_CCMR2_IC4PSC_1		(0 << 10)
#define TIM_CCMR2_IC4PSC_2		(1 << 10)
#define TIM_CCMR2_IC4PSC_4		(2 << 10)
#define TIM_CCMR2_IC4PSC_8		(3 << 10)

/* Input capture 3 filter */
#define TIM_CCMR2_IC3F_DTS_N_1		(0 << 4)
#define TIM_CCMR2_IC3F_CK_INT_N_2	(1 << 4)
#define TIM_CCMR2_IC3F_CK_INT_N_4	(2 << 4)
#define TIM_CCMR2_IC3F_CK_INT_N_8	(3 << 4)
#define TIM_CCMR2_IC3F_DTS_2_N_6	(4 << 4)
#define TIM_CCMR2_IC3F_DTS_2_N_8	(5 << 4)
#define TIM_CCMR2_IC3F_DTS_4_N_6	(6 << 4)
#define TIM_CCMR2_IC3F_DTS_4_N_8	(7 << 4)
#define TIM_CCMR2_IC3F_DTS_8_N_6	(8 << 4)
#define TIM_CCMR2_IC3F_DTS_8_N_8	(9 << 4)
#define TIM_CCMR2_IC3F_DTS_16_N_5	(10 << 4)
#define TIM_CCMR2_IC3F_DTS_16_N_6	(11 << 4)
#define TIM_CCMR2_IC3F_DTS_16_N_8	(12 << 4)
#define TIM_CCMR2_IC3F_DTS_32_N_5	(13 << 4)
#define TIM_CCMR2_IC3F_DTS_32_N_6	(14 << 4)
#define TIM_CCMR2_IC3F_DTS_32_N_8	(15 << 4)

/* Input capture 3 prescaler */
#define TIM_CCMR2_IC3PSC_1		(0 << 2)
#define TIM_CCMR2_IC3PSC_2		(1 << 2)
#define TIM_CCMR2_IC3PSC_4		(2 << 2)
#define TIM_CCMR2_IC3PSC_8		(3 << 2)

/* --- TIMx_CCER values ---------------------------------------------------- */

#define TIM_CCER_CC4NP			(1 << 15)
#define TIM_CCER_CC4P			(1 << 13)
#define TIM_CCER_CC4E			(1 << 12)
#define TIM_CCER_CC3NP			(1 << 11)
#define TIM_CCER_CC3P			(1 << 9)
#define TIM_CCER_CC3E			(1 << 8)
#define TIM_CCER_CC2NP			(1 << 7)
#define TIM_CCER_CC2P			(1 << 5)
#define TIM_CCER_CC2E			(1 << 4)
#define TIM_CCER_CC1NP			(1 << 3)
#define TIM_CCER_CC1P			(1 << 1)
#define TIM_CCER_CC1E			(1 << 0)

/* --- TIMx_CNT values ----------------------------------------------------- */

/* TIM_CNT[15:0]: CNT[15:0]: Counter value */

/* --- TIMx_PSC values ----------------------------------------------------- */

/* TIM_PSC[15:0]: PSC[15:0]: Prescaler value */

/* --- TIMx_ARR values ----------------------------------------------------- */

/* TIM_ARR[15:0]: ARR[15:0]: Auto-reload value */

/* --- TIMx_CCR1 values ---------------------------------------------------- */

/* TIM_CCR1[15:0]: CCR1[15:0]: Capture/Compare 1 value */

/* --- TIMx_CCR2 values ---------------------------------------------------- */

/* TIM_CCR2[15:0]: CCR2[15:0]: Capture/Compare 2 value */

/* --- TIMx_CCR3 values ---------------------------------------------------- */

/* TIM_CCR3[15:0]: CCR3[15:0]: Capture/Compare 3 value */

/* --- TIMx_CCR4 values ---------------------------------------------------- */

/* TIM_CCR4[15:0]: CCR4[15:0]: Capture/Compare 4 value */

/* --- TIMx_DCR values ----------------------------------------------------- */

#define TIM_DCR_DBL4			(1 << 12)
#define TIM_DCR_DBL3			(1 << 11)
#define TIM_DCR_DBL2			(1 << 10)
#define TIM_DCR_DBL1			(1 << 9)
#define TIM_DCR_DBL0			(1 << 8)
#define TIM_DCR_DBA4			(1 << 4)
#define TIM_DCR_DBA3			(1 << 3)
#define TIM_DCR_DBA2			(1 << 2)
#define TIM_DCR_DBA1			(1 << 1)
#define TIM_DCR_DBA0			(1 << 0)

/* --- TIMx_DMAR values ---------------------------------------------------- */

/* TIM_DMAR[15:0]: DMAB[15:0]: DMA register for bust accesses */

/* --- TIM2_OR values ------------------------------------------------------ */

#define TIM2_OR_TI4_RMP1		(1 << 4)
#define TIM2_OR_TI4_RMP0		(1 << 3)
#define TIM2_OR_ETR_RMP2		(1 << 2)
#define TIM2_OR_ETR_RMP1		(1 << 1)
#define TIM2_OR_ETR_RMP0		(1 << 0)

/* Internal trigger (TI4 connected to TIM2_CH4) remap */
#define TIM2_OR_TI4_RMP_GPIO		(0 << 3)
#define TIM2_OR_TI4_RMP_COMP2_OUT	(1 << 3)
#define TIM2_OR_TI4_RMP_COMP1_OUT	(2 << 3)

/* Timer2 ETR remap */
#define TIM2_OR_ETR_RMP_GPIO		(0 << 0)
#define TIM2_OR_ETR_RMP_HSI16		(3 << 0)
#define TIM2_OR_ETR_RMP_LSE		(5 << 0)
#define TIM2_OR_ETR_RMP_COMP2_OUT	(6 << 0)
#define TIM2_OR_ETR_RMP_COMP1_OUT	(7 << 0)

/* --- TIM3_OR values ------------------------------------------------------ */

#define TIM3_OR_PC9_RMP			(1 << 4)
#define TIM3_OR_PB5_RMP			(1 << 3)
#define TIM3_OR_TI1_RMP			(1 << 2)
#define TIM3_OR_ETR_RMP1		(1 << 1)
#define TIM3_OR_ETR_RMP0		(1 << 0)

/* Timer3 ETR remap */
#define TIM3_OR_ETR_RMP_GPIO		(0 << 0)

/* --- TIM21_OR values ----------------------------------------------------- */

#define TIM21_OR_TI2_RMP		(1 << 5)
#define TIM21_OR_TI1_RMP2		(1 << 4)
#define TIM21_OR_TI1_RMP1		(1 << 3)
#define TIM21_OR_TI1_RMP0		(1 << 2)
#define TIM21_OR_ETR_RMP1		(1 << 1)
#define TIM21_OR_ETR_RMP0		(1 << 0)

/* Timer21 TI1 (connected to TIM21_CH1) remap */
#define TIM21_OR_TI1_RMP_GPIO		(0 << 2)
#define TIM21_OR_TI1_RMP_RTC_WAKEUP	(1 << 2)
#define TIM21_OR_TI1_RMP_HSE_RTC	(2 << 2)
#define TIM21_OR_TI1_RMP_MSI		(3 << 2)
#define TIM21_OR_TI1_RMP_LSE		(4 << 2)
#define TIM21_OR_TI1_RMP_LSI		(5 << 2)
#define TIM21_OR_TI1_RMP_COMP1_OUT	(6 << 2)
#define TIM21_OR_TI1_RMP_MCO		(7 << 2)

/* Timer21 ETR remap */
#define TIM21_OR_ETR_RMP_GPIO		(0 << 0)
#define TIM21_OR_ETR_RMP_COMP2_OUT	(1 << 0)
#define TIM21_OR_ETR_RMP_COMP1_OUT	(2 << 0)
#define TIM21_OR_ETR_RMP_LSE		(3 << 0)

/* --- TIM22_OR values ----------------------------------------------------- */

#define TIM22_OR_TI1_RMP1		(1 << 3)
#define TIM22_OR_TI1_RMP0		(1 << 2)
#define TIM22_OR_ETR_RMP1		(1 << 1)
#define TIM22_OR_ETR_RMP0		(1 << 0)

/* Timer22 TI1 (connected to TIM22_CH1) remap */
#define TIM22_OR_TI1_RMP_GPIO		(0 << 2)
#define TIM22_OR_TI1_RMP_COMP2_OUT	(1 << 2)
#define TIM22_OR_TI1_RMP_COMP1_OUT	(2 << 2)

/* Timer22 ETR remap */
#define TIM22_OR_ETR_RMP_GPIO		(0 << 0)
#define TIM22_OR_ETR_RMP_COMP2_OUT	(1 << 0)
#define TIM22_OR_ETR_RMP_COMP1_OUT	(2 << 0)
#define TIM22_OR_ETR_RMP_LSE		(3 << 0)

/* --- Function prototypes ------------------------------------------------- */

/* Device number */
enum tim {
	TIM2,
	TIM3,
	TIM21,
	TIM22,
	TIM6,
	TIM7
};

/* Channel number */
enum tim_cc {
	TIM2_CC1,
	TIM2_CC2,
	TIM2_CC3,
	TIM2_CC4,
	TIM3_CC1,
	TIM3_CC2,
	TIM3_CC3,
	TIM3_CC4,
	TIM21_CC1,
	TIM21_CC2,
	TIM22_CC1,
	TIM22_CC2
};

/* Center-aligned mode */
enum tim_center_aligned_mode {
	TIM_EDGE_ALIGNED_MODE = (0 << 5),
	TIM_MODE1 = (1 << 5),
	TIM_MODE2 = (2 << 5),
	TIM_MODE3 = (3 << 5)
};

/* Master mode */
enum tim_master_mode {
	TIM_TRGO_RESET = (0 << 4),
	TIM_TRGO_ENABLE = (1 << 4),
	TIM_TRGO_UPDATE = (2 << 4),
	TIM_TRGO_COMPARE_PULSE = (3 << 4),
	TIM_TRGO_OC1REF = (4 << 4),
	TIM_TRGO_OC2REF = (5 << 4),
	TIM_TRGO_OC3REF = (6 << 4),
	TIM_TRGO_OC4REF = (7 << 4)
};

/* Slave mode */
enum {
	TIM_SLAVE_DISABLE = 0,
	TIM_ENCODER_MODE1 = 1,
	TIM_ENCODER_MODE2 = 2,
	TIM_ENCODER_MODE3 = 3,
	TIM_TRGI_RESET = 4,
	TIM_TRGI_GATED = 5,
	TIM_TRGI_TRIGGER = 6,
	TIM_EXTERNAL_CLOCK_MODE1 = 7,

	/* Trigger selection */
	TIM_ITR0 = (0 << 4),
	TIM_ITR1 = (1 << 4),
	TIM_TI1F_ED = (4 << 4),
	TIM_TI1FP1 = (5 << 4),
	TIM_TI2FP2 = (6 << 4),
	TIM_ETRF = (7 << 4),

	TIM_SYNC = (1 << 7),

	/* External trigger filter */
	TIM_ET_DTS_N_1 = (0 << 8),
	TIM_ET_CK_INT_N_2 = (1 << 8),
	TIM_ET_CK_INT_N_4 = (2 << 8),
	TIM_ET_CK_INT_N_8 = (3 << 8),
	TIM_ET_DTS_2_N_6 = (4 << 8),
	TIM_ET_DTS_2_N_8 = (5 << 8),
	TIM_ET_DTS_4_N_6 = (6 << 8),
	TIM_ET_DTS_4_N_8 = (7 << 8),
	TIM_ET_DTS_8_N_6 = (8 << 8),
	TIM_ET_DTS_8_N_8 = (9 << 8),
	TIM_ET_DTS_16_N_5 = (10 << 8),
	TIM_ET_DTS_16_N_6 = (11 << 8),
	TIM_ET_DTS_16_N_8 = (12 << 8),
	TIM_ET_DTS_32_N_5 = (13 << 8),
	TIM_ET_DTS_32_N_6 = (14 << 8),
	TIM_ET_DTS_32_N_8 = (15 << 8),

	/* External trigger prescaler */
	TIM_ETRP_2 = (1 << 12),
	TIM_ETRP_4 = (2 << 12),
	TIM_ETRP_8 = (3 << 12),

	TIM_EXTERNAL_CLOCK_MODE2 = (1 << 14),

	TIM_ETR_INVERTED = (1 << 15)
};

/* Interrupt (event) and status */
enum {
	TIM_UPDATE = (1 << 0),
	TIM_CC1 = (1 << 1),
	TIM_CC2 = (1 << 2),
	TIM_CC3 = (1 << 3),
	TIM_CC4 = (1 << 4),
	TIM_TRIGGER = (1 << 6),

	TIM_CC1_OVERCAPTURE = (1 << 9),
	TIM_CC2_OVERCAPTURE = (1 << 10),
	TIM_CC3_OVERCAPTURE = (1 << 11),
	TIM_CC4_OVERCAPTURE = (1 << 12)
};

/* DMA request */
enum {
	TIM_DMA_UPDATE = (1 << 8),
	TIM_DMA_CC1 = (1 << 9),
	TIM_DMA_CC2 = (1 << 10),
	TIM_DMA_CC3 = (1 << 11),
	TIM_DMA_CC4 = (1 << 12),
	TIM_DMA_TRIGGER = (1 << 14)
};

/* Capture / Compare mode */
enum {
	TIM_CC_OUTPUT = 0,
	TIM_CC_INPUT1 = 1,
	TIM_CC_INPUT2 = 2,
	TIM_CC_INPUT3 = 3,

	TIM_OC_FAST = (1 << 2),
	TIM_OC_PRELOAD = (1 << 3),

	TIM_OC_FROZEN = (0 << 4),
	TIM_OC_MATCH_ACTIVE = (1 << 4),
	TIM_OC_MATCH_INACTIVE = (2 << 4),
	TIM_OC_MATCH_TOGGLE = (3 << 4),
	TIM_OC_FORCE_INACTIVE = (4 << 4),
	TIM_OC_FORCE_ACTIVE = (5 << 4),
	TIM_OC_PWM1 = (6 << 4),
	TIM_OC_PWM2 = (7 << 4),

	TIM_OC_CLEAR = (1 << 7),

	TIM_IC_PRESCALER_1 = (0 << 2),
	TIM_IC_PRESCALER_2 = (1 << 2),
	TIM_IC_PRESCALER_4 = (2 << 2),
	TIM_IC_PRESCALER_8 = (3 << 2),

	TIM_IC_DTS_N_1 = (0 << 4),
	TIM_IC_CK_INT_N_2 = (1 << 4),
	TIM_IC_CK_INT_N_4 = (2 << 4),
	TIM_IC_CK_INT_N_8 = (3 << 4),
	TIM_IC_DTS_2_N_6 = (4 << 4),
	TIM_IC_DTS_2_N_8 = (5 << 4),
	TIM_IC_DTS_4_N_6 = (6 << 4),
	TIM_IC_DTS_4_N_8 = (7 << 4),
	TIM_IC_DTS_8_N_6 = (8 << 4),
	TIM_IC_DTS_8_N_8 = (9 << 4),
	TIM_IC_DTS_16_N_5 = (10 << 4),
	TIM_IC_DTS_16_N_6 = (11 << 4),
	TIM_IC_DTS_16_N_8 = (12 << 4),
	TIM_IC_DTS_32_N_5 = (13 << 4),
	TIM_IC_DTS_32_N_6 = (14 << 4),
	TIM_IC_DTS_32_N_8 = (15 << 4),

	TIM_CC_ENABLE = (1 << 8),
	TIM_OC_ACTIVE_LOW = (1 << 9),
	TIM_OC_ACTIVE_HIGH = 0,

	TIM_IC_RISING = 0,
	TIM_IC_FALLING = (1 << 9),
	TIM_IC_BOTH = (5 << 9),
	TIM_IC_NONINVERTED = 0,
	TIM_IC_INVERTED = (1 << 9)
};

/* TIM2 TI4 remap */
enum tim_tim2_ti4 {
	TIM2_TI4_GPIO = 0,
	TIM2_TI4_COMP2_OUT = (1 << 3),
	TIM2_TI4_COMP1_OUT = (2 << 3)
};

/* TIM2 ETR remap */
enum tim_tim2_etr {
	TIM2_ETR_GPIO = 0,
	TIM2_ETR_HSI16 = 3,
	TIM2_ETR_LSE = 5,
	TIM2_ETR_COMP2_OUT = 6,
	TIM2_ETR_COMP1_OUT = 7
};

/* TIM3 remap */
enum {
	TIM3_PC9_CH4 = (1 << 4),
	TIM3_PB5_TIM22_CH2 = 0,
	TIM3_PB5_CH2 = (1 << 3),
	TIM3_TI1_GPIO = (1 << 2),
	TIM3_ETR_GPIO = 0
};

/* TIM21 TI2 remap */
enum tim_tim21_ti2 {
	TIM21_TI2_GPIO = 0,
	TIM21_TI2_COMP2_OUT = (1 << 5)
};

/* TIM21 TI1 remap */
enum tim_tim21_ti1 {
	TIM21_TI1_GPIO = 0,
	TIM21_TI1_RTC_WAKEUP = (1 << 2),
	TIM21_TI1_HSE_RTC = (2 << 2),
	TIM21_TI1_MSI = (3 << 2),
	TIM21_TI1_LSE = (4 << 2),
	TIM21_TI1_LSI = (5 << 2),
	TIM21_TI1_COMP1_OUT = (6 << 2),
	TIM21_TI1_MCO = (7 << 2)
};

/* TIM21 ETR remap */
enum tim_tim21_etr {
	TIM21_ETR_GPIO = 0,
	TIM21_ETR_COMP2_OUT = 1,
	TIM21_ETR_COMP1_OUT = 2,
	TIM21_ETR_LSE = 3
};

/* TIM22 TI1 remap */
enum tim_tim22_ti1 {
	TIM22_TI1_GPIO = 0,
	TIM22_TI1_COMP2_OUT = (1 << 2),
	TIM22_TI1_COMP1_OUT = (2 << 2)
};

/* TIM22 ETR remap */
enum tim_tim22_etr {
	TIM22_ETR_GPIO = 0,
	TIM22_ETR_COMP2_OUT = 1,
	TIM22_ETR_COMP1_OUT = 2,
	TIM22_ETR_LSE = 3
};

void tim_set_prescaler(enum tim tim, int pcount);
void tim_load_prescaler(enum tim tim, int pcount);
void tim_set_autoreload(enum tim tim, int count);
void tim_setup_counter(enum tim tim, int pcount, int count);
void tim_set_counter(enum tim tim, int cnt);
int tim_get_counter(enum tim tim);
void tim_enable_counter(enum tim tim);
void tim_disable_counter(enum tim tim);
void tim_set_dts_division(enum tim tim, int div);
void tim_enable_autoreload_preload(enum tim tim);
void tim_disable_autoreload_preload(enum tim tim);
void tim_set_center_aligned_mode(enum tim tim,
				 enum tim_center_aligned_mode mode);
void tim_set_downcounter(enum tim tim);
void tim_set_upcounter(enum tim tim);
bool tim_downcounter(enum tim tim);
void tim_enable_one_pulse_mode(enum tim tim);
void tim_disable_one_pulse_mode(enum tim tim);
void tim_disable_update_interrupt_on_any(enum tim tim);
void tim_enable_update_interrupt_on_any(enum tim tim);
void tim_disable_update_event(enum tim tim);
void tim_enable_update_event(enum tim tim);
void tim_enable_ti1_ch123_xor(enum tim tim);
void tim_disable_ti1_ch123_xor(enum tim tim);
void tim_set_master_mode(enum tim tim, enum tim_master_mode mode);
void tim_enable_ccx_dma_on_update_event(enum tim tim);
void tim_disable_ccx_dma_on_update_event(enum tim tim);
void tim_set_slave_mode(enum tim tim, int mode);
void tim_enable_interrupt(enum tim tim, int interrupt);
void tim_disable_interrupt(enum tim tim, int interrupt);
int tim_get_interrupt_mask(enum tim tim, int interrupt);
int tim_get_interrupt_status(enum tim tim, int interrupt);
void tim_clear_interrupt(enum tim tim, int interrupt);
void tim_enable_dma(enum tim tim, int request);
void tim_disable_dma(enum tim tim, int request);
void tim_generate_event(enum tim tim, int event);
void tim_set_capture_compare_mode(enum tim_cc tim_cc, int mode);
void tim_set_capture_compare_value(enum tim_cc tim_cc, int value);
int tim_get_capture_compare_value(enum tim_cc tim_cc);
void tim_setup_dma(enum tim tim, int dba, int dbl);
void tim_tim2_remap(enum tim_tim2_ti4 tim2_ti4, enum tim_tim2_etr tim2_etr);
void tim_tim3_remap(int remap);
void tim_tim21_remap(enum tim_tim21_ti2 tim21_ti2,
		     enum tim_tim21_ti1 tim21_ti1,
		     enum tim_tim21_etr tim21_etr);
void tim_tim22_remap(enum tim_tim22_ti1 tim22_ti1,
		     enum tim_tim22_etr tim22_etr);
