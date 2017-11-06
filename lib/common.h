#pragma once

#include <stdint.h>

typedef unsigned int mem_t;

#define PERIPHERAL_BASE 0x20000000

inline void dmb() {
  __asm__ __volatile__("mcr p15, 0, %0, c7, c10, 5" : : "r"(0) : "memory");
}

inline uint32_t read_cpsr_c() {
  uint32_t val;
  __asm__ __volatile__("mrs %0, cpsr" : "=r"(val));
  return val;
}

inline void write_cpsr_c(uint32_t val) {
  __asm__ __volatile__("msr cpsr_c, %0" : : "r"(val));
}

#define WAIT_UNTIL(cond)                                                       \
  do {                                                                         \
  } while (!(cond))
