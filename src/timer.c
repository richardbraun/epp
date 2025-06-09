#include "timer.h"

void 
timer_init(int timer_nr) 
{
    if (timer_nr >1 && timer_nr < 15) {
        RCC->APB1ENR |= 0x1UL << (timer_nr - 2);
    }
}

void 
timer_configure_overflow_in_sec(TIM_TypeDef *timer, int nr_sec)
{
    timer->PSC |= 0x3E8UL; //Prescaler value = 1000.
    timer->ARR |= nr_sec; //Auto-reload value
    timer->DIER |= 0x1UL; // update interrupt enabled.
}

void timer_enable(TIM_TypeDef *timer)
{
    timer->CR1 |= 0x5UL; //enable counter + URS.
}
