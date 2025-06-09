#ifndef TIMER_H
#define TIMER_H

#include "platform.h"

void timer_init(int timer_nr);

void timer_configure_overflow_in_sec(TIM_TypeDef *timer, int nr_sec);

void timer_enable(TIM_TypeDef *timer);

#endif /* TIMER_H */
