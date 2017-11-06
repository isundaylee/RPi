#include "lib/timer.h"
#include "lib/intr.h"

typedef struct {
  uint32_t cs;
  uint32_t clo;
  uint32_t chi;
  uint32_t c[4];
} Timer;

#define TIMER_BASE (PERIPHERAL_BASE + 0x00003000)

volatile Timer *timer = (Timer *)TIMER_BASE;

void (*timer_handlers[TIMER_COUNT])(void);
int timer_enabled[TIMER_COUNT];
uint32_t timer_period[TIMER_COUNT];

void timer_handle_timer(int timer_id) {
  dmb();

  if (timer->cs & (1 << timer_id)) {
    if (timer_enabled[timer_id]) {
      timer_handlers[timer_id]();

      if (timer_period[timer_id]) {
        uint32_t now = timer_get();
        timer->c[timer_id] = now + timer_period[timer_id];
      } else {
        timer_enabled[timer_id] = 0;
      }
    }

    timer->cs = (1 << timer_id);
  }

  dmb();
}

void timer_1_interrupt_handler() {
  timer_handle_timer(TIMER_1);
}

void timer_2_interrupt_handler() {
  timer_handle_timer(TIMER_2);
}

void timer_init() {
  intr_register_handler(INTR_TIMER_1, timer_1_interrupt_handler);
  intr_register_handler(INTR_TIMER_2, timer_2_interrupt_handler);

  intr_enable_irq(INTR_TIMER_1);
  intr_enable_irq(INTR_TIMER_2);
}

uint32_t timer_get() {
  dmb();
  return timer->clo;
}

void timer_set(int timer_id, uint32_t us, int type, void (*handler)(void)) {
  uint32_t now = timer_get();
  timer->c[timer_id] = now + us;
  dmb();

  timer_handlers[timer_id] = handler;
  timer_enabled[timer_id] = 1;
  timer_period[timer_id] = (type == TIMER_PERIODIC ? us : 0);
}
