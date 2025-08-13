#include <stdbool.h>
#include <stddef.h>

#include "intr.h"
#include "macro.h"
#include "platform.h"
#include "typedef.h"

#define INTR_TABLE_SIZE 15
#define INTR_NR_INTR 97

extern intr_isr_fn_t vectors[];

struct intr_handler_fn_attributes {
    void (*myfunc)(void *arg);
    int intr_nr;
    void *arg;
};

struct intr_handler_fn_attributes intr_handler_fn_table[INTR_TABLE_SIZE];

static void
intr_handler_fn_attributes_set_fn_and_arg(struct intr_handler_fn_attributes *intr_handler, void (*myFunc)(void *arg), void *arg)
{
    intr_handler->arg = arg;
    intr_handler->myfunc = myFunc;
}

static void
intr_handler_fn_attributes_init(struct intr_handler_fn_attributes *intr_handler) {
    intr_handler->intr_nr = -1;
}

static int
intr_handler_fn_get_intr_nr(struct intr_handler_fn_attributes *intr_handler)
{
    return intr_handler->intr_nr;
}

static bool
intr_handler_fn_is_enabled(struct intr_handler_fn_attributes *intr_handler)
{
    return (intr_handler->intr_nr != -1);
}

static struct intr_handler_fn_attributes *
intr_handler_fn_find(int intr_nr)
{
    for (size_t i = 0; i < ARRAY_SIZE(intr_handler_fn_table); i++) {
        struct intr_handler_fn_attributes *intr_handler = &intr_handler_fn_table[i];

        if (!intr_handler_fn_is_enabled(intr_handler)) {
            continue;
        }

        if (intr_handler_fn_get_intr_nr(intr_handler) == intr_nr) {
            return intr_handler;
        }
    }

    return NULL;
}

static void
intr_handler_fn_enable(struct intr_handler_fn_attributes *intr_handler, int intr_nr)
{
    intr_handler->intr_nr = intr_nr;
}

static struct intr_handler_fn_attributes *
intr_alloc_intr_handler_fn(int intr_nr)
{
    for (size_t i = 0; i < ARRAY_SIZE(intr_handler_fn_table); i++) {
        struct intr_handler_fn_attributes *intr_handler = &intr_handler_fn_table[i];

        if (!intr_handler_fn_is_enabled(intr_handler)) {
            intr_handler_fn_enable(intr_handler, intr_nr);
            return intr_handler;
        }
    }

    return NULL;
}

void TIM6_IRQHandler(void *arg)
{
    if (TIM6->SR & 0x1UL) {
        GPIOF->ODR ^= 0x1UL << 6U;
    }

    TIM6->SR = 0x0UL;
}

static void 
intr_handler(void)
{
    uint32_t regIPSR;

    __asm__ volatile ("mrs %0, ipsr" : "=r" (regIPSR));

    struct intr_handler_fn_attributes *intr_handler = intr_handler_fn_find(regIPSR - 16);

    (*intr_handler->myfunc)(intr_handler->arg);
}

int
intr_register(int intr_nr, intr_handler_fn_t intr_handler_fn, void *arg)
{
    struct intr_handler_fn_attributes *intr_handler;

    intr_handler = intr_alloc_intr_handler_fn(intr_nr);

    if (!intr_handler) {
        return 1;
    }

    __NVIC_EnableIRQ(intr_nr);

    intr_handler_fn_attributes_set_fn_and_arg(intr_handler, intr_handler_fn, arg);
    return 0;
}

void
intr_init(void)
{
    SCB->VTOR = INTR_VECTOR_RAM_BASE; // Point at RAM copy

    for(int i = 0; i < INTR_NR_INTR; i++) {
        *(INTR_VECTOR_RAM + i) = (uintptr_t) intr_handler;
    }

    for(size_t i = 0; i < ARRAY_SIZE(intr_handler_fn_table); i++) {
        struct intr_handler_fn_attributes *intr_handler = &intr_handler_fn_table[i];
        intr_handler_fn_attributes_init(intr_handler);
    }
}
