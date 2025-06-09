#include "intr.h"

#include "timer.h"
#include "platform.h"


int main(void) {

    RCC->AHB1ENR |= 0x1UL << 5U;
    GPIOF->MODER |= 0x1UL << 12U;
    int a = 4;

    intr_init();

    timer_init(6);

    timer_configure_overflow_in_sec(TIM6, 5);

    intr_register(TIM6_DAC_IRQn, &TIM6_IRQHandler, (int *)&a);

    timer_enable(TIM6);

    while (1) {

    };

    return 0;

}
