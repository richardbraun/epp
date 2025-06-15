#ifndef TIMER_H
#define TIMER_H

#include "platform.h"

/*
 * Initialize a timer.
 */
void timer_init(int timer_nr);

/*
 * Configure the amount of time in second a given timer will overflow.
 */
void timer_configure_overflow_in_sec(TIM_TypeDef *timer, int nr_sec);

/*
 * Start the timer counter.
 */
void timer_enable(TIM_TypeDef *timer);

#endif /* TIMER_H */
