#ifndef GPIO_H
#define GPIO_H

#include "platform.h"

/*
 * Initialize a given gpio as output
 */
void gpio_init_as_output(GPIO_TypeDef *gpio, int gpio_nr);

#endif /* GPIO_H */
