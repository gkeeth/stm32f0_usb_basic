// example based on libopencm3 miniblink/systick_blink/button examples

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/flash.h>

// LEDs are on PA0 and PA1
#define PORT_LED GPIOA
#define PIN_LED0 GPIO0
#define PIN_LED1 GPIO1

// user button is on PA2
#define PORT_BUT GPIOA
#define PIN_BUT GPIO2

volatile uint32_t counter = 0;

void sys_tick_handler(void) {
    ++counter;
}

uint32_t millis(void);
uint32_t millis(void) {
    return counter;
}

static void setup(void) {
    // use external 8MHz oscillator to derive 48MHz clock from PLL
    // this is an oscillator, not a crystal, so disable the builtin oscillator
    // circuit (enable oscillator bypass)
    rcc_osc_bypass_enable(RCC_HSE);
    rcc_clock_setup_in_hse_8mhz_out_48mhz();
    STK_CVR = 0; // clear systick current value to start immediately

    // every 1 ms (1000 Hz)
    systick_set_frequency(1000, rcc_ahb_frequency);
    systick_counter_enable();
    systick_interrupt_enable();

    // setup LED pins
    rcc_periph_clock_enable(RCC_GPIOA);
    // set LED pins to output push-pull
    gpio_mode_setup(PORT_LED, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED0 | PIN_LED1);

    // setup button pin
    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO2);

    // set PA8 to AF0 for MCO (main clock out)
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8);
    gpio_set_output_options(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO8);
    gpio_set_af(GPIOA, 0, GPIO8);
    rcc_set_mco(RCC_CFGR_MCO_SYSCLK);

    // set PF1 high now that bypass is enabled
    rcc_periph_clock_enable(RCC_GPIOF);
    gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
    gpio_set(GPIOF, GPIO1);
}



int main(void) {
    int i = 0;
    int button_armed = 0;
    uint32_t blink_delays[] = {100, 500, 1000};
    uint32_t last_flash_millis;

    setup();
    last_flash_millis = millis();

    while(1) {
        int button_pressed = !gpio_get(PORT_BUT, PIN_BUT);
        if (button_pressed && button_armed) {
            // disarm button (until button is released)
            button_armed = 0;

            // make LED blink faster
            i = (i + 1) % 3;
        } else if (!button_pressed) {
            button_armed = 1;
        }


        if ((millis() - last_flash_millis) > blink_delays[i]) {
            gpio_toggle(PORT_LED, PIN_LED0);
            gpio_toggle(PORT_LED, PIN_LED1);
            last_flash_millis = millis();
        }
    }

    return 0;
}

