CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
CPUFLAGS = -mcpu=cortex-m3 -mthumb
CFLAGS = -Wall -Wextra -g3 -O0 -MD $(CPUFLAGS) -DSTM32F1 -Ilibopencm3/include
LDFLAGS = $(CPUFLAGS) -nostartfiles -Llibopencm3/lib -Wl,-T,bluepill.ld
LDLIBS = -lopencm3_stm32f1 -lc -lnosys

CSRC = pill_blink.c
OBJ = $(CSRC:.c=.o)

pill_blink.elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

.PHONY: libopencm3
libopencm3:
	if [ ! -f libopencm3/Makefile ]; then \
		git submodule init; \
		git submodule update; \
	fi
	$(MAKE) -C libopencm3 lib/stm32/f1

.PHONY: clean
clean:
	-rm -rf *.o *.bin *.elf *.map -include *.d
	#-$(MAKE) -C libopencm3 clean

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

all: pill_blink.bin
