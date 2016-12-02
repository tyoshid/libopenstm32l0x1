/*
 * miniblink - Blink an LED.
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

#include <rcc.h>
#include <gpio.h>

volatile int dont_delete_loop;

/*
 * GPIO
 * PA0: output	LED
 */
static void gpio_setup(void)
{
	rcc_enable_clock(RCC_GPIOA);
	gpio_set_mode(GPIO_OUTPUT, GPIO_PA0);
}

/* Blink the LED. */
int main(void)
{
	int i;

	gpio_setup();

	while (1) {
		for (i = 0; i < 200000; i++)
			dont_delete_loop;
		gpio_toggle(GPIO_PA0);
	}

	return 0;
}
