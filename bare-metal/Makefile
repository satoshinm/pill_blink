CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
CPUFLAGS = -mcpu=cortex-m3 -mthumb
CFLAGS = -Wall -Wextra -g3 -O0 -MD $(CPUFLAGS)
LDFLAGS = $(CPUFLAGS) -nostartfiles -Wl,-T,bluepill.ld
LDLIBS = -lc -lnosys

CSRC = pill_blink.c
OBJ = $(CSRC:.c=.o)

pill_blink.elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

.PHONY: clean
clean:
	-rm -rf *.o *.bin *.elf *.map -include *.d

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

all: pill_blink.bin
