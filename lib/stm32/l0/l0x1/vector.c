/*
 * Vector table
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

extern char _stack[];

extern void nmi(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void hardfault(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void svcall(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void pendsv(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void systick_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));

extern void wwdg_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void pvd_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void rtc_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void flash_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void rcc_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void exti0_1_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void exti2_3_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void exti4_15_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void dma_ch1_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void dma_ch2_3_isr(void) __attribute__ ((weak, alias ("_dummy_isr")));
extern void dma_ch4_7_isr(void) __attribute__ ((weak, alias ("_dummy_isr")));
extern void adc_comp_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void lptim1_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void usart4_5_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void tim2_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void tim3_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void tim6_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void tim7_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void tim21_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void i2c3_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void tim22_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void i2c1_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void i2c2_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void spi1_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void spi2_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void usart1_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void usart2_isr(void)	__attribute__ ((weak, alias ("_dummy_isr")));
extern void lpuart1_aes_isr(void)
	__attribute__ ((weak, alias ("_dummy_isr")));

void _reset(void)	__attribute__ ((naked, section (".startup")));
void _dummy_isr(void)	__attribute__ ((section (".startup")));

void _reset(void)
{
	int i;
	extern char _data_start[];
	extern char _data_load_start[];
	extern char _data_size[];
	extern char _bss_start[];
	extern char _bss_size[];
	extern int main(void);

	for (i = 0; i < (int)_data_size; i++)
		_data_start[i] = _data_load_start[i];
	for (i = 0; i < (int)_bss_size; i++)
		_bss_start[i] = 0;
	main();
	while (1)
		;
}

void _dummy_isr(void)
{
	while (1)
		;
}

void (* const _vector[]) (void) __attribute__ ((section (".vector"))) = {
	(void *)_stack,
	_reset,
	nmi,
	hardfault,
	0, 0, 0, 0, 0, 0, 0,
	svcall,
	0, 0,
	pendsv,
	systick_isr,
	wwdg_isr,
	pvd_isr,
	rtc_isr,
	flash_isr,
	rcc_isr,
	exti0_1_isr,
	exti2_3_isr,
	exti4_15_isr,
	0,
	dma_ch1_isr,
	dma_ch2_3_isr,
	dma_ch4_7_isr,
	adc_comp_isr,
	lptim1_isr,
	usart4_5_isr,
	tim2_isr,
	tim3_isr,
	tim6_isr,
	tim7_isr,
	0,
	tim21_isr,
	i2c3_isr,
	tim22_isr,
	i2c1_isr,
	i2c2_isr,
	spi1_isr,
	spi2_isr,
	usart1_isr,
	usart2_isr,
	lpuart1_aes_isr,
	0, 0
};
