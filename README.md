# Libopenstm32l0x1

Libopenstm32l0x1 is a peripheral library for STMicroelectronics STM32L0x1
  (STM32L011, STM32L021, STM32L031, STM32L041, STM32L051, STM32L071,
  STM32L081) microcontrollers.
The STM32L0x1 microcontroller family are based on the ARM Cortex-M0+ core.

This library is used with ARM GCC, ARM binutils, and newlib C library.
They form a toolchain for the STM32L0x1.

This package includes a in-system programming utility (`usart-util`)
and some examples.

## Build

You need to install the ARM bare-metal (no OS) toolchain ([GNU ARM Embedded
Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm)).
GCC 5.2 (or later) is recommended.

To build libopenstm32l0x1, use the following sequence of commands:
```
$ git clone https://github.com/tyoshid/libopenstm32l0x1.git
$ cd libopenstm32l0x1
$ make
```
The `make` step will build the target library
(`lib/stm32/l0/l0x1/libstm32l0x1.a`) and the host utility
(`tools/stm32/usart-util/usart-util`).

## License

### Software

The software is released under the terms of GNU General Public License (GPL),
 version 3 or later.

See http://www.gnu.org/licenses/ or COPYING.

### Hardware

The hardware is released under the Creative Commons Attribution-ShareAlike 4.0
International License.

See http://creativecommons.org/licenses/by-sa/4.0/.
