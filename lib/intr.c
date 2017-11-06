#include "lib/intr.h"
#include "lib/common.h"

#define INTR_NUM 64

typedef struct {
  uint32_t basic_pending;
  uint32_t pendings[2];
  uint32_t fiq_control;
  uint32_t enables[2];
  uint32_t enable_basic;
  uint32_t disables[2];
  uint32_t disable_basic;
} Intr;

#define INTR_BASE (PERIPHERAL_BASE + 0x0000B200)
volatile Intr *intr = ((volatile Intr *)INTR_BASE);

void intr_enable() {
  uint32_t cpsr_c = read_cpsr_c();
  cpsr_c &= ~(1 << 7);
  write_cpsr_c(cpsr_c);
}

void intr_disable() {
  uint32_t cpsr_c = read_cpsr_c();
  cpsr_c |= (1 << 7);
  write_cpsr_c(cpsr_c);
}

void intr_enable_irq(int irq_no) {
  dmb();
  intr->enables[irq_no / 32] |= (1 << (irq_no % 32));
  dmb();
}

void intr_disable_irq(int irq_no) {
  dmb();
  intr->enables[irq_no / 32] &= ~(1 << (irq_no % 32));
  dmb();
}

void (*handlers[INTR_NUM])(void);

void intr_register_handler(int irq_no, void (*handler)(void)) {
  handlers[irq_no] = handler;
}

void intr_entry() {
  dmb();

  for (int i = 0; i < INTR_NUM; i++) {
    if (intr->pendings[i / 32] & (1 << (i % 32))) {
      handlers[i]();
      break;
    }
  }

  dmb();
}
