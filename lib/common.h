#pragma once

typedef unsigned int mem_t;

typedef int uint32_t;

#define PERIPHERAL_BASE 0x20000000

inline void dmb() {
    __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 5" : : "r" (0) : "memory");
}
