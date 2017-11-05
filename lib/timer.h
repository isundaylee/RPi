#pragma once

#include "lib/common.h"

#define TIMER_1 1
#define TIMER_2 3

#define TIMER_ONCE 0
#define TIMER_PERIODIC 1

#define TIMER_BASE (PERIPHERAL_BASE + 0x00003000)

void timer_init();

uint32_t timer_get();
void timer_set(int timer, int us, int type);
