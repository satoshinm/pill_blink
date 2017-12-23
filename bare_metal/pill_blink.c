#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void) {
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

    while(1) {
        gpio_set(GPIOC, GPIO13);
        for (int i = 0; i < 1000000; ++i) __asm__("nop");
        gpio_clear(GPIOC, GPIO13);
        for (int i = 0; i <  500000; ++i) __asm__("nop");
    }
}
