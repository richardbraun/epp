#include "platform.h"

/*!< Peripheral memory map */
#define PERIPH_BASE         0x40000000UL
#define AHB1PERIPH_BASE     (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE     PERIPH_BASE

#define GPIOB_BASE          (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOF_BASE          (AHB1PERIPH_BASE + 0x1400UL)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)

#define RCC_BASE            (AHB1PERIPH_BASE + 0x3800UL)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)

#define TIM6_BASE           (APB1PERIPH_BASE + 0x1000UL)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)


void TIM6_IRQHandler(void) __attribute__ ((used, section(".tim6_irq_handler")));

__attribute__ ((used, section(".tim6_irq_handler")))
void TIM6_IRQHandler(void)
{
    if (TIM6->SR & 0x1UL) {
        GPIOF->ODR ^= 0x1UL << 6U;
    }

    TIM6->SR = 0x0UL;
}

int main(void) {

    RCC->AHB1ENR |= 0x1UL << 5U;
    RCC->APB1ENR |= 0x1UL << 4U;
    GPIOF->MODER |= 0x1UL << 12U;

    TIM6->PSC |= 0x3E8UL; //Prescaler value = 1000.
    TIM6->ARR |= 0x5UL; //Auto-reload value = 5.
    TIM6->DIER |= 0x1UL; // update interrupt enabled.

    __NVIC_EnableIRQ(TIM6_DAC_IRQn);
    TIM6->CR1 |= 0x5UL; //enable counter + URS.

    while (1) {
      __asm volatile ("nop");
    };

    return 0;

}
