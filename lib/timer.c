#include "lib/timer.h"

typedef struct {
  uint32_t cs;
  uint32_t clo;
  uint32_t chi;
  uint32_t c[4];
} Timer;

#define TIMER_BASE (PERIPHERAL_BASE + 0x00003000)

volatile Timer *timer = (Timer *)TIMER_BASE;

void timer_init() {}

uint32_t timer_get() {
  dmb();
  return timer->clo;
}

void timer_set(int timer, int us, int type) {}
