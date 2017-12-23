# pill\_blink, libopencm3 version

To build this project:

1. Ensure you have the ARM GCC compiler installed (e.g. install [Homebrew](https://brew.sh), run `brew cask install gcc-arm-embedded`)
2. `make all`
3. The binary should now be available for flashing in `pill_blink.bin`

Uses the popular [libopencm3](https://github.com/libopencm3/libopencm3) library.

References:
* [examples/stm32/stm32-h103/miniblink](https://github.com/libopencm3/libopencm3-examples/tree/master/examples/stm32/f1/stm32-h103/miniblink).
* [Open-Source Cortex-M Demo](https://github.com/gsmcmullin/embedded-demo)

