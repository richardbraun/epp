#include "gpio.h"

void gpio_init_as_output(GPIO_TypeDef *gpio, int gpio_nr)
{
    int gpio_moder_index = gpio_nr << 1;
    int gpio_rcc_index = gpio_nr - 1; 

    gpio->MODER |= 0x1UL << gpio_moder_index;
    RCC->AHB1ENR |= 0x1UL << gpio_rcc_index;
}
