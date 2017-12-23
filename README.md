# pill\_blink

Blink an STM32F103C8 "blue pill" development board (LED on PC13) using various methods:

* [cubemx](./cubemx): using STMicroelectronics' [STM32CubeMX](http://www.st.com/content/st_com/en/products/ecosystems/stm32-open-development-environment.html) platform
* [opencm](./opencm): using [libopencm3](http://github.com/libopencm3/libopencm3-examples/) library function calls
* [opencm-registers](./opencm-registers): using [libopencm3](http://github.com/libopencm3/libopencm3-examples/), but only for register definitions

Size of each binary for comparison:

```sh
pill_blink $ find . -name '*.bin' -exec ls -l {} \;
-rwxr-xr-x  1 admin  staff  3496 Dec 22 20:58 ./cubemx/build/pill_blink.bin
-rwxr-xr-x  1 admin  staff  1088 Dec 22 22:43 ./opencm/pill_blink.bin
-rwxr-xr-x  1 admin  staff   608 Dec 22 23:00 ./opencm-registers/pill_blink.bin
```

