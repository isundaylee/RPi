#pragma once

#include <stdint.h>

typedef unsigned int mem_t;

#define PERIPHERAL_BASE 0x20000000

inline void dmb() {
    __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 5" : : "r" (0) : "memory");
}

#define WAIT_UNTIL(cond)    \
    do {                    \
    } while (!(cond))
