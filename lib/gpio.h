#pragma once

#define GPIO_INPUT  0b000
#define GPIO_OUTPUT 0b001
#define GPIO_ALT_0  0b100
#define GPIO_ALT_1  0b101
#define GPIO_ALT_2  0b110
#define GPIO_ALT_3  0b111
#define GPIO_ALT_4  0b011
#define GPIO_ALT_5  0b010

void gpio_configure(int pin, int type);
void gpio_set(int pin);
void gpio_clear(int pin);
