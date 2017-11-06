#pragma once

#define INTR_TIMER_1 1
#define INTR_TIMER_2 3

void intr_enable();
void intr_disable();
void intr_enable_irq(int irq_no);
void intr_disable_irq(int irq_no);
void intr_register_handler(int irq_no, void (*handler)(void));
