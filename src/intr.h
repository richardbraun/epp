#ifndef INTR_H
#define INTR_H

#include "typedef.h"

#define INTR_VECTOR_RAM_BASE         0x20000000UL
#define INTR_VECTOR_RAM              ((volatile uint32_t *) INTR_VECTOR_RAM_BASE)

void intr_init(void);
void TIM6_IRQHandler(void *arg);
int intr_register(int intr_nr, intr_handler_fn_t intr_handler_fn, void *arg);

#endif /* INTR_H */
