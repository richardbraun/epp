#include "gpio.h"
#include "intr.h"
#include "platform.h"
#include "timer.h"


int main(void) {

    int a = 4;

    intr_init();

    gpio_init_as_output(GPIOF, 6);

    timer_init(6);

    timer_configure_overflow_in_sec(TIM6, 5);

    intr_register(TIM6_DAC_IRQn, &TIM6_IRQHandler, (int *)&a);

    timer_enable(TIM6);

    while (1) {

    };

    return 0;

}
