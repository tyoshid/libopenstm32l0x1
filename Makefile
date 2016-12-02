# Makefile for libopenstm32l0x1

# Copyright 2016 Toshiaki Yoshida <yoshida@mpc.net>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

LIBS		= lib/stm32/l0/l0x1
TOOLS		= tools/stm32/usart-util

EXAMPLES	= examples/stm32/l0/l0x1/stm32l011d3p/miniblink \
		  examples/stm32/l0/l0x1/stm32l011d3p/fancyblink \
		  examples/stm32/l0/l0x1/stm32l011d3p/button \
		  examples/stm32/l0/l0x1/stm32l011d3p/exti \
		  examples/stm32/l0/l0x1/stm32l011d3p/tim \
		  examples/stm32/l0/l0x1/stm32l011d3p/tim_delay \
		  examples/stm32/l0/l0x1/stm32l011d3p/tim_pwm \
		  examples/stm32/l0/l0x1/stm32l011d3p/tim_encoder \
		  examples/stm32/l0/l0x1/stm32l011d3p/lptim \
		  examples/stm32/l0/l0x1/stm32l011d3p/lptim_delay \
		  examples/stm32/l0/l0x1/stm32l011d3p/lptim_pwm \
		  examples/stm32/l0/l0x1/stm32l011d3p/lptim_encoder \
		  examples/stm32/l0/l0x1/stm32l011d3p/usart \
		  examples/stm32/l0/l0x1/stm32l011d3p/usart_irq \
		  examples/stm32/l0/l0x1/stm32l011d3p/usart_printf \
		  examples/stm32/l0/l0x1/stm32l011d3p/usart_getchar \
		  examples/stm32/l0/l0x1/stm32l011d3p/lpuart \
		  examples/stm32/l0/l0x1/stm32l011d3p/lpuart_irq \
		  examples/stm32/l0/l0x1/stm32l011d3p/lpuart_printf \
		  examples/stm32/l0/l0x1/stm32l011d3p/lpuart_getchar \
		  examples/stm32/l0/l0x1/stm32l011d3p/rtc \
		  examples/stm32/l0/l0x1/stm32l011d3p/crc \
		  examples/stm32/l0/l0x1/stm32l011d3p/1wire_temp \
		  examples/stm32/l0/l0x1/stm32l011d3p/potentiometer \
		  examples/stm32/l0/l0x1/stm32l011d3p/comp \
		  examples/stm32/l0/l0x1/stm32l011d3p/i2c_rom \
		  examples/stm32/l0/l0x1/stm32l011d3p/i2c_proximity \
		  examples/stm32/l0/l0x1/stm32l011d3p/spi_rom \
		  examples/stm32/l0/l0x1/stm32l011d3p/spi_barometer \
		  examples/stm32/l0/l0x1/stm32l011d3p/iwdg \
		  examples/stm32/l0/l0x1/stm32l011d3p/wwdg

ifeq ($(MAKECMDGOALS), clean_example)
EXAMPLEGOAL	= clean
endif

.PHONY: all clean $(LIBS) $(TOOLS)

all clean: $(LIBS) $(TOOLS)

$(LIBS) $(TOOLS):
	@echo "-- $@ --"
	@$(MAKE) -C $@ -s $(MAKECMDGOALS)

.PHONY: example clean_example $(EXAMPLES)

example clean_example: $(EXAMPLES)

$(EXAMPLES):
	@echo "-- $@ --"
	@$(MAKE) -C $@ -s $(EXAMPLEGOAL)
