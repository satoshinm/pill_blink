# pill\_blink

Blink an STM32F103C8 "blue pill" development board (LED on PC13) using various methods:

* [cubemx](./cubemx): using STMicroelectronics' [STM32CubeMX](http://www.st.com/content/st_com/en/products/ecosystems/stm32-open-development-environment.html) platform
* [opencm](./opencm): using [libopencm3](http://github.com/libopencm3/libopencm3-examples/) library function calls
* [opencm-registers](./opencm-registers): using [libopencm3](http://github.com/libopencm3/libopencm3-examples/), but only for register definitions
* [bare-metal](./bare-metal): using no libraries

Size of each binary for comparison:

```sh
pill_blink $ find . -name '*.bin' -exec ls -l {} \;
-rwxr-xr-x  1 admin  staff  3496 Dec 22 20:58 ./cubemx/build/pill_blink.bin
-rwxr-xr-x  1 admin  staff  1088 Dec 22 22:43 ./opencm/pill_blink.bin
-rwxr-xr-x  1 admin  staff   608 Dec 22 23:00 ./opencm-registers/pill_blink.bin
-rwxr-xr-x  1 admin  staff   440 Dec 23 00:10 ./bare-metal/pill_blink.bin
```

![Blinking example](https://user-images.githubusercontent.com/26856618/34317330-2e0485f2-e761-11e7-9bad-5e27cae52735.png)

*How to build these examples?* First, install an ARM compiler, I use the [GNU ARM Embedded Toolchain](https://launchpad.net/gcc-arm-embedded/)
installed via [Homebrew](https://brew.sh) as follows: `brew cask install gcc-arm-embedded`. See each individual project directory for
additional instructions; all are using the `make` tool for building.

*Where to acquire a blue pill?* Search on Aliexpress or eBay for "stm32", look for the cheapest. I use these:

* [STM32F103C8T6 ARM STM32 Minimum System Development Board Module](https://www.aliexpress.com/item/STM32F103C8T6-ARM-STM32-Minimum-System-Development-Board-Module/32656040083.html), ~$1.70
* [Free Shipping STM32F103C8T6 ARM STM32 Minimum System Development Board Module Forarduino](https://www.aliexpress.com/item/Free-Shipping-STM32F103C8T6-ARM-STM32-Minimum-System-Development-Board-Module-Forarduino/32525208361.html), $1.85

*How to flash the firmwares?* You can use any USB-to-serial adapter, but for development I prefer to flash
another blue pill as a [Black Magic Probe](https://github.com/blacksphere/blackmagic/) since it can be used
both for uploading via serial and debugging via SWD, see:
*[Converting an STM32F103 board to a Black Magic Probe](https://medium.com/@paramaggarwal/converting-an-stm32f103-board-to-a-black-magic-probe-c013cf2cc38c)*.
Assuming you want to do this too, connect the Black Magic Probe blue pill to the target blue pill as follows:

| Black Magic Probe blue pill | target blue pill |
| ----------------- | ------ |
| A2 (TX) | A10 |
| A3 (RX) | A9 |
| A5 (SWCLK) | SWD header CK |
| B14 (SWDIO) | SWD header O |
| GND | GND |
| 5V | 5V |

If using a regular USB-to-serial adapter, connect only A10 and A9 and ground. For flashing the firmware I
use [stm32loader](https://medium.com/@paramaggarwal/converting-an-stm32f103-board-to-a-black-magic-probe-c013cf2cc38c), example:

```sh
python stm32loader.py -p /dev/cu.usbmodemE3C896E3 -e -w -v bare-metal/pill_blink.bin
```

*How to debug?* Use a dongle capable of the [Serial Wire Debug](https://en.wikipedia.org/wiki/JTAG#Serial_Wire_Debug) protocol, connect to
the right-angle header on the blue pill board, assuming you're using a BMP (see above), connect using GDB:

```sh
arm-none-eabi-gdb -ex "target extended-remote /dev/cu.usbmodemE3C896E1" -ex "monitor swdp_scan"
```

then attach with `att 1` and you should be able to continue, examine registers and memory, and step through as usual. To load symbols, build
with `make CFLAGS+=-g` and load the elf with `file`. 

```sh
+ arm-none-eabi-gdb -ex 'target extended-remote /dev/cu.usbmodemE3C896E1' -ex 'monitor swdp_scan'
Available Targets:
No. Att Driver
 1      STM32F1 medium density
(gdb) att 1
Attaching to Remote target
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x08000194 in ?? ()
(gdb) file pill_blink/bare-metal/pill_blink.elf
A program is being debugged already.
Are you sure you want to change the file? (y or n) y
Reading symbols from pill_blink/bare-metal/pill_blink.elf...done.
(gdb) c
Continuing.
^C
Program received signal SIGINT, Interrupt.
0x0800017e in reset_handler () at pill_blink.c:9
9	        for (int i = 0; i < 1000000; ++i) __asm__("nop");
(gdb)

```

*Any simpler?* Yes, see also [Arduino for STM32 at stm32duino.com](http://www.stm32duino.com), for a friendlier
[Arduino](https://www.arduino.cc)-compatible STM32 platform where `digitalWrite()` can toggle the LED, but these
examples are primarily intended as experiments in lower-level embedded programming without Arduino, for background see also:
*[STM32 Blue Pill ARM development board first look: from Arduino to bare metal programming](https://satoshinm.github.io/blog/171212_stm32_blue_pill_arm_development_board_first_look_bare_metal_programming.html)*.

---

See also accompanying blog post: *[JTAG/SWD debugging via Black Magic Probe on an STM32 blue pill and blinking a LED using STM32CubeMX, libopencm3, and bare metal C](https://satoshinm.github.io/blog/171223_jtagswdpillblink_jtagswd_debugging_via_black_magic_probe_on_an_stm32_blue_pill_and_blinking_a_led_using_stm32cubemx_libopencm3_and_bare_metal_c.html)*

--

**[Comments?](https://www.reddit.com/r/stm32f4/comments/7lnosf/pill_blink_examples_of_blinking_the_stm32f103c8/)**
