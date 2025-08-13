#ifndef INTR_H
#define INTR_H

typedef void (*intr_isr_fn_t)(void);
typedef void (*intr_handler_fn_t)(void *arg);

/*
 * Initialize interrupts.
 *
 * Relocate interrupt to ram.
 */
void intr_init(void);


void TIM6_IRQHandler(void *arg);

/*
 * Register an interrupt with an associated interrupt handler function and argument.
 */
int intr_register(int intr_nr, intr_handler_fn_t intr_handler_fn, void *arg);

#endif /* INTR_H */
