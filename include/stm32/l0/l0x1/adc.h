/*
 * ADC
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
 * 13  Analog-to-digital converter (ADC)
 */

/* --- ADC registers ------------------------------------------------------- */
/*
 * Offset	Register
 * 0x00		ADC_ISR		ADC interrupt and status register
 * 0x04		ADC_IER		ADC interrupt enable register
 * 0x08		ADC_CR		ADC control register
 * 0x0c		ADC_CFGR1	ADC configuration register 1
 * 0x10		ADC_CFGR2	ADC configuration register 2
 * 0x14		ADC_SMPR	ADC sampling time register
 * 0x20		ADC_TR		ADC watchdog threshold register
 * 0x28		ADC_CHSELR	ADC channel selection register
 * 0x40		ADC_DR		ADC data register
 * 0xb4		ADC_CALFACT	ADC calibration factor
 * 0x308	ADC_CCR		ADC common configuration register
 */

#define ADC_ISR				(ADC1_BASE + 0x00)
#define ADC_IER				(ADC1_BASE + 0x04)
#define ADC_CR				(ADC1_BASE + 0x08)
#define ADC_CFGR1			(ADC1_BASE + 0x0c)
#define ADC_CFGR2			(ADC1_BASE + 0x10)
#define ADC_SMPR			(ADC1_BASE + 0x14)
#define ADC_TR				(ADC1_BASE + 0x20)
#define ADC_CHSELR			(ADC1_BASE + 0x28)
#define ADC_DR				(ADC1_BASE + 0x40)
#define ADC_CALFACT			(ADC1_BASE + 0xb4)
#define ADC_CCR				(ADC1_BASE + 0x308)

/* --- ADC_ISR values ------------------------------------------------------ */

#define ADC_ISR_EOCAL			(1 << 11)
#define ADC_ISR_AWD			(1 << 7)
#define ADC_ISR_OVR			(1 << 4)
#define ADC_ISR_EOSEQ			(1 << 3)
#define ADC_ISR_EOC			(1 << 2)
#define ADC_ISR_EOSMP			(1 << 1)
#define ADC_ISR_ADRDY			(1 << 0)

/* --- ADC_IER values ------------------------------------------------------ */

#define ADC_IER_EOCALIE			(1 << 11)
#define ADC_IER_AWDIE			(1 << 7)
#define ADC_IER_OVRIE			(1 << 4)
#define ADC_IER_EOSEQIE			(1 << 3)
#define ADC_IER_EOCIE			(1 << 2)
#define ADC_IER_EOSMPIE			(1 << 1)
#define ADC_IER_ADRDYIE			(1 << 0)

/* --- ADC_CR values ------------------------------------------------------- */

#define ADC_CR_ADCAL			(1 << 31)
#define ADC_CR_ADVREGEN			(1 << 28)
#define ADC_CR_ADSTP			(1 << 4)
#define ADC_CR_ADSTART			(1 << 2)
#define ADC_CR_ADDIS			(1 << 1)
#define ADC_CR_ADEN			(1 << 0)

/* --- ADC_CFGR1 values ---------------------------------------------------- */

#define ADC_CFGR1_AWDCH4		(1 << 30)
#define ADC_CFGR1_AWDCH3		(1 << 29)
#define ADC_CFGR1_AWDCH2		(1 << 28)
#define ADC_CFGR1_AWDCH1		(1 << 27)
#define ADC_CFGR1_AWDCH0		(1 << 26)
#define ADC_CFGR1_AWDEN			(1 << 23)
#define ADC_CFGR1_AWDSGL		(1 << 22)
#define ADC_CFGR1_DISCEN		(1 << 16)
#define ADC_CFGR1_AUTOFF		(1 << 15)
#define ADC_CFGR1_WAIT			(1 << 14)
#define ADC_CFGR1_CONT			(1 << 13)
#define ADC_CFGR1_OVRMOD		(1 << 12)
#define ADC_CFGR1_EXTEN1		(1 << 11)
#define ADC_CFGR1_EXTEN0		(1 << 10)
#define ADC_CFGR1_EXTSEL2		(1 << 8)
#define ADC_CFGR1_EXTSEL1		(1 << 7)
#define ADC_CFGR1_EXTSEL0		(1 << 6)
#define ADC_CFGR1_ALIGN			(1 << 5)
#define ADC_CFGR1_RES1			(1 << 4)
#define ADC_CFGR1_RES0			(1 << 3)
#define ADC_CFGR1_SCANDIR		(1 << 2)
#define ADC_CFGR1_DMACFG		(1 << 1)
#define ADC_CFGR1_DMAEN			(1 << 0)

/* Analog watchdog channel selection */
#define ADC_CFGR1_AWDCH_CHANNEL0	(0 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL1	(1 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL2	(2 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL3	(3 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL4	(4 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL5	(5 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL6	(6 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL7	(7 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL8	(8 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL9	(9 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL10	(10 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL11	(11 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL12	(12 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL13	(13 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL14	(14 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL15	(15 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL16	(16 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL17	(17 << 26)
#define ADC_CFGR1_AWDCH_CHANNEL18	(18 << 26)

/* External trigger enable and polarity selection */
#define ADC_CFGR1_EXTEN_DISABLE		(0 << 10)
#define ADC_CFGR1_EXTEN_RISING		(1 << 10)
#define ADC_CFGR1_EXTEN_FALLING		(2 << 10)
#define ADC_CFGR1_EXTEN_BOTH		(3 << 10)

/* External trigger selection */
#define ADC_CFGR1_EXTSEL_TRG0		(0 << 6)
#define ADC_CFGR1_EXTSEL_TRG1		(1 << 6)
#define ADC_CFGR1_EXTSEL_TRG2		(2 << 6)
#define ADC_CFGR1_EXTSEL_TRG3		(3 << 6)
#define ADC_CFGR1_EXTSEL_TRG4		(4 << 6)
#define ADC_CFGR1_EXTSEL_TRG5		(5 << 6)
#define ADC_CFGR1_EXTSEL_TRG6		(6 << 6)
#define ADC_CFGR1_EXTSEL_TRG7		(7 << 6)
#define ADC_CFGR1_EXTSEL_TIM6_TRGO	(0 << 6)
#define ADC_CFGR1_EXTSEL_TIM21_CH2	(1 << 6)
#define ADC_CFGR1_EXTSEL_TIM2_TRGO	(2 << 6)
#define ADC_CFGR1_EXTSEL_TIM2_CH4	(3 << 6)
#define ADC_CFGR1_EXTSEL_TIM22_TRGO	(4 << 6)
#define ADC_CFGR1_EXTSEL_TIM21_TRGO	(4 << 6)
#define ADC_CFGR1_EXTSEL_TIM2_CH3	(5 << 6)
#define ADC_CFGR1_EXTSEL_TIM3_TRGO	(6 << 6)
#define ADC_CFGR1_EXTSEL_EXTI11		(7 << 6)

/* Data resolution */
#define ADC_CFGR1_RES_12BIT		(0 << 3)
#define ADC_CFGR1_RES_10BIT		(1 << 3)
#define ADC_CFGR1_RES_8BIT		(2 << 3)
#define ADC_CFGR1_RES_6BIT		(3 << 3)

/* --- ADC_CFGR2 values ---------------------------------------------------- */

#define ADC_CFGR2_CKMODE1		(1 << 31)
#define ADC_CFGR2_CKMODE0		(1 << 30)
#define ADC_CFGR2_TOVS			(1 << 9)
#define ADC_CFGR2_OVSS3			(1 << 8)
#define ADC_CFGR2_OVSS2			(1 << 7)
#define ADC_CFGR2_OVSS1			(1 << 6)
#define ADC_CFGR2_OVSS0			(1 << 5)
#define ADC_CFGR2_OVSR2			(1 << 4)
#define ADC_CFGR2_OVSR1			(1 << 3)
#define ADC_CFGR2_OVSR0			(1 << 2)
#define ADC_CFGR2_OVSE			(1 << 0)

/* ADC clock mode */
#define ADC_CFGR2_CKMODE_ADCCLK		(0 << 30)
#define ADC_CFGR2_CKMODE_PCLK_2		(1 << 30)
#define ADC_CFGR2_CKMODE_PCLK_4		(2 << 30)
#define ADC_CFGR2_CKMODE_PCLK		(3 << 30)

/* Oversampling shift */
#define ADC_CFGR2_OVSS_NONE		(0 << 5)
#define ADC_CFGR2_OVSS_1BIT		(1 << 5)
#define ADC_CFGR2_OVSS_2BIT		(2 << 5)
#define ADC_CFGR2_OVSS_3BIT		(3 << 5)
#define ADC_CFGR2_OVSS_4BIT		(4 << 5)
#define ADC_CFGR2_OVSS_5BIT		(5 << 5)
#define ADC_CFGR2_OVSS_6BIT		(6 << 5)
#define ADC_CFGR2_OVSS_7BIT		(7 << 5)
#define ADC_CFGR2_OVSS_8BIT		(8 << 5)

/* Oversampling ratio */
#define ADC_CFGR2_OVSR_2X		(0 << 2)
#define ADC_CFGR2_OVSR_4X		(1 << 2)
#define ADC_CFGR2_OVSR_8X		(2 << 2)
#define ADC_CFGR2_OVSR_16X		(3 << 2)
#define ADC_CFGR2_OVSR_32X		(4 << 2)
#define ADC_CFGR2_OVSR_64X		(5 << 2)
#define ADC_CFGR2_OVSR_128X		(6 << 2)
#define ADC_CFGR2_OVSR_256X		(7 << 2)

/* --- ADC_SMPR values ----------------------------------------------------- */

#define ADC_SMPR_SMP2			(1 << 2)
#define ADC_SMPR_SMP1			(1 << 1)
#define ADC_SMPR_SMP0			(1 << 0)

/* Sampling time selection */
#define ADC_SMPR_SMP_1_5		(0 << 0)
#define ADC_SMPR_SMP_3_5		(1 << 0)
#define ADC_SMPR_SMP_7_5		(2 << 0)
#define ADC_SMPR_SMP_12_5		(3 << 0)
#define ADC_SMPR_SMP_19_5		(4 << 0)
#define ADC_SMPR_SMP_39_5		(5 << 0)
#define ADC_SMPR_SMP_79_5		(6 << 0)
#define ADC_SMPR_SMP_160_5		(7 << 0)

/* --- ADC_TR values ------------------------------------------------------- */

/* ADC_TR[27:16]: HT[11:0]: Analog watchdog higher threshold */
/* ADC_TR[11:0]: LT[11:0]: Analog watchdog lower threshold */

/* --- ADC_CHSELR values --------------------------------------------------- */

/* ADC_CHSELR[18:0]: CHSELx: Channel-x selection */

/* --- ADC_DR values ------------------------------------------------------- */

/* ADC_DR[15:0]: DATA[15:0]: Converted data */

/* --- ADC_CALFACT values -------------------------------------------------- */

/* ADC_CALFACT[6:0]: CALFACT[6:0]: Calibration factor */

/* --- ADC_CCR values ------------------------------------------------------ */

#define ADC_CCR_LFMEN			(1 << 25)
#define ADC_CCR_TSEN			(1 << 23)
#define ADC_CCR_VREFEN			(1 << 22)
#define ADC_CCR_PRESC3			(1 << 21)
#define ADC_CCR_PRESC2			(1 << 20)
#define ADC_CCR_PRESC1			(1 << 19)
#define ADC_CCR_PRESC0			(1 << 18)

/* ADC prescaler */
#define ADC_CCR_PRESC_1			(0 << 18)
#define ADC_CCR_PRESC_2			(1 << 18)
#define ADC_CCR_PRESC_4			(2 << 18)
#define ADC_CCR_PRESC_6			(3 << 18)
#define ADC_CCR_PRESC_8			(4 << 18)
#define ADC_CCR_PRESC_10		(5 << 18)
#define ADC_CCR_PRESC_12		(6 << 18)
#define ADC_CCR_PRESC_16		(7 << 18)
#define ADC_CCR_PRESC_32		(8 << 18)
#define ADC_CCR_PRESC_64		(9 << 18)
#define ADC_CCR_PRESC_128		(10 << 18)
#define ADC_CCR_PRESC_256		(11 << 18)

/* --- Function prototypes ------------------------------------------------- */

/* Clock mode */
enum adc_clock {
	ADC_ADCCLK = (0 << 30),
	ADC_PCLK_2 = (1 << 30),
	ADC_PCLK_4 = (2 << 30),
	ADC_PCLK = (3 << 30)
};

/* Data resolution */
enum adc_resolution {
	ADC_12BIT = (0 << 3),
	ADC_10BIT = (1 << 3),
	ADC_8BIT = (2 << 3),
	ADC_6BIT = (3 << 3)
};

/* Channel */
enum {
	ADC_IN0 = (1 << 0),
	ADC_IN1 = (1 << 1),
	ADC_IN2 = (1 << 2),
	ADC_IN3 = (1 << 3),
	ADC_IN4 = (1 << 4),
	ADC_IN5 = (1 << 5),
	ADC_IN6 = (1 << 6),
	ADC_IN7 = (1 << 7),
	ADC_IN8 = (1 << 8),
	ADC_IN9 = (1 << 9),
	ADC_IN10 = (1 << 10),
	ADC_IN11 = (1 << 11),
	ADC_IN12 = (1 << 12),
	ADC_IN13 = (1 << 13),
	ADC_IN14 = (1 << 14),
	ADC_IN15 = (1 << 15),
	ADC_IN16 = (1 << 16),
	ADC_IN17 = (1 << 17),
	ADC_IN18 = (1 << 18),

	ADC_IN_PA0 = (1 << 0),
	ADC_IN_PA1 = (1 << 1),
	ADC_IN_PA2 = (1 << 2),
	ADC_IN_PA3 = (1 << 3),
	ADC_IN_PA4 = (1 << 4),
	ADC_IN_PA5 = (1 << 5),
	ADC_IN_PA6 = (1 << 6),
	ADC_IN_PA7 = (1 << 7),
	ADC_IN_PB0 = (1 << 8),
	ADC_IN_PB1 = (1 << 9),
	ADC_IN_PC0 = (1 << 10),
	ADC_IN_PC1 = (1 << 11),
	ADC_IN_PC2 = (1 << 12),
	ADC_IN_PC3 = (1 << 13),
	ADC_IN_PC4 = (1 << 14),
	ADC_IN_PC5 = (1 << 15),
	ADC_IN_VREFINT = (1 << 17),
	ADC_IN_TS = (1 << 18)
};

/* Sampling time */
enum adc_sampling_time {
	ADC_1_5CLK,
	ADC_3_5CLK,
	ADC_7_5CLK,
	ADC_12_5CLK,
	ADC_19_5CLK,
	ADC_39_5CLK,
	ADC_79_5CLK,
	ADC_160_5CLK
};

/* Conversion mode */
enum adc_conversion_mode {
	ADC_SINGLE,
	ADC_CONTINUOUS,
	ADC_DISCONTINUOUS
};

/* External trigger edge */
enum adc_trigger {
	ADC_SOFTWARE = (0 << 10),
	ADC_EXT_RISING = (1 << 10),
	ADC_EXT_FALLING = (2 << 10),
	ADC_EXT_BOTH = (3 << 10)
};

/* External trigger source */
enum adc_trigger_source {
	ADC_TRG0 = (0 << 6),
	ADC_TRG1 = (1 << 6),
	ADC_TRG2 = (2 << 6),
	ADC_TRG3 = (3 << 6),
	ADC_TRG4 = (4 << 6),
	ADC_TRG5 = (5 << 6),
	ADC_TRG6 = (6 << 6),
	ADC_TRG7 = (7 << 6),
	
	ADC_TIM6_TRGO = (0 << 6),
	ADC_TIM21_CH2 = (1 << 6),
	ADC_TIM2_TRGO = (2 << 6),
	ADC_TIM2_CH4 = (3 << 6),
	ADC_TIM22_TRGO = (4 << 6),
	ADC_TIM21_TRGO = (4 << 6),
	ADC_TIM2_CH3 = (5 << 6),
	ADC_TIM3_TRGO = (6 << 6),
	ADC_EXTI11 = (7 << 6),

	ADC_NONE = 0
};

/* Function */
enum {
	ADC_DMA_ENABLE = (1 << 0),
	ADC_DMA_CIRCULAR = (1 << 1),
	ADC_BACKWARD_SCAN = (1 << 2),
	ADC_LEFT_ALIGN = (1 << 5),
	ADC_OVERWRITE = (1 << 12),
	ADC_WAIT = (1 << 14),
	ADC_AUTO_OFF = (1 << 15)
};

/* Interrupt */
enum {
	ADC_READY = (1 << 0),
	ADC_END_OF_SAMPLING = (1 << 1),
	ADC_END_OF_CONVERSION = (1 << 2),
	ADC_END_OF_SEQUENCE = (1 << 3),
	ADC_OVERRUN = (1 << 4),
	ADC_ANALOG_WATCHDOG = (1 << 7),
	ADC_END_OF_CALIBRATION = (1 << 11)
};

int adc_calibration(void);
void adc_set_calfact(int calfact);
void adc_set_clock(enum adc_clock clock, int presc, bool low_freq);
void adc_set_resolution(enum adc_resolution res);
void adc_enable(void);
void adc_disable(void);
void adc_enable_voltage_regulator(void);
void adc_disable_voltage_regulator(void);
void adc_set_channel(int channel, bool backward);
void adc_set_sampling_time(enum adc_sampling_time smp);
void adc_set_conversion_mode(enum adc_conversion_mode mode);
void adc_start(void);
void adc_stop(void);
void adc_set_trigger(enum adc_trigger trigger, enum adc_trigger_source source);
int adc_get_data(void);
void adc_set_alignment(bool left_align);
void adc_set_overrun_mode(bool overwrite);
void adc_enable_dma(bool circular);
void adc_disable_dma(void);
void adc_enable_wait_mode(void);
void adc_disable_wait_mode(void);
void adc_enable_auto_off(void);
void adc_disable_auto_off(void);
void adc_init(int channel, enum adc_sampling_time smp,
	      enum adc_conversion_mode mode,
	      enum adc_trigger trigger, enum adc_trigger_source source,
	      int function);
void adc_init_analog_window_watchdog(int channel, int ht, int lt);
void adc_enable_oversampler(int n, bool trigger);
void adc_disable_oversampler(void);
void adc_set_oversampling_shift(int bit);
void adc_enable_temperature_sensor(void);
void adc_disable_temperature_sensor(void);
void adc_enable_vrefint(void);
void adc_disable_vrefint(void);
void adc_enable_interrupt(int interrupt);
void adc_disable_interrupt(int interrupt);
int adc_get_interrupt_mask(int interrupt);
int adc_get_interrupt_status(int interrupt);
void adc_clear_interrupt(int interrupt);
