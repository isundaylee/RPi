#pragma once

#define GPIO_INPUT 0b000
#define GPIO_OUTPUT 0b001

void gpio_configure(int pin, int type);
void gpio_set(int pin);
void gpio_clear(int pin);
