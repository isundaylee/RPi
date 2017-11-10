#pragma once

#include "lib/aux.h"

#include <stdint.h>

typedef unsigned int mem_t;
typedef unsigned char byte;

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

inline void assert(int condition) {
  if (!condition) {
    aux_mu_send_string("!!!!! Assertion failed! !!!!!!\r\n");
    aux_mu_flush();

    while (1) {}
  }
}

#define WAIT_UNTIL(cond)                                                       \
  do {                                                                         \
  } while (!(cond))

#define BIT(n) (1 << (n))
