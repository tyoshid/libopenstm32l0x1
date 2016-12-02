# Makefile for libstm32l0x1.a

# Copyright 2015 Toshiaki Yoshida <yoshida@mpc.net>

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

LIB		= libstm32l0x1.a
OBJS		= vector.o flash.o crc.o fw.o pwr.o rcc.o gpio.o \
		  syscfg.o dma.o nvic.o exti.o adc.o comp.o aes.o \
		  tim.o lptim.o iwdg.o wwdg.o rtc.o i2c.o usart.o \
		  lpuart.o spi.o dbg.o misc.o stk.o scb.o mpu.o
VPATH		= ..

CC		= arm-none-eabi-gcc
AR		= arm-none-eabi-ar
CFLAGS		= -MMD -Os \
		  -Wall -Wextra -Wredundant-decls -Wmissing-prototypes \
		  -Wstrict-prototypes -Wundef -Wshadow \
		  -I../../../../include -I../../../../include/stm32/l0 \
		  -I../../../../include/stm32/l0/l0x1 \
		  -ffreestanding -fno-common \
		  -ffunction-sections -fdata-sections \
		  -fsigned-char \
		  -mthumb -mcpu=cortex-m0plus
ARFLAGS		= rcs

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	echo "  $(@F)"
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	echo "  $(<F)"
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(LIB) $(OBJS) $(OBJS:.o=.d)

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJS:.o=.d)
endif
