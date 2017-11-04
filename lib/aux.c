#include "lib/aux.h"
#include "lib/common.h"
#include "lib/gpio.h"

typedef struct {
  uint32_t irq;
  uint32_t enables;
  uint32_t dummy1[14];
  uint32_t mu_io_reg;
  uint32_t mu_ier_reg;
  uint32_t mu_iir_reg;
  uint32_t mu_lcr_reg;
  uint32_t mu_mcr_reg;
  uint32_t mu_lsr_reg;
  uint32_t mu_msr_reg;
  uint32_t mu_scratch;
  uint32_t mu_cntl_reg;
  uint32_t mu_stat_reg;
  uint32_t mu_baud_reg;
  uint32_t dummy2[5];
  // SPI things not needed for now.
} Aux;

#define AUX_BASE (PERIPHERAL_BASE + 0x00215000)

volatile Aux *aux = (Aux *)AUX_BASE;

void aux_mu_init() {
  dmb();

  aux->enables = 1;
  aux->mu_ier_reg = 0;
  aux->mu_cntl_reg = 0;
  aux->mu_lcr_reg = 3;
  aux->mu_mcr_reg = 0;
  aux->mu_ier_reg = 0;
  aux->mu_iir_reg = 0xc6;
  aux->mu_baud_reg = 270;       // Baud rate: 115200

  gpio_configure(14, GPIO_ALT_5);
  gpio_configure(15, GPIO_ALT_5);

  aux->mu_cntl_reg = 3;

  dmb();
}

void aux_mu_send(char c) {
  dmb();

  WAIT_UNTIL(aux->mu_lsr_reg & 0x20);
  aux->mu_io_reg = c;

  dmb();
}

void aux_mu_send_string(char *str) {
  char c;
  while ((c = *(str++)) != '\0') {
    aux_mu_send(c);
  }
}

char aux_mu_receive() {
  dmb();

  WAIT_UNTIL(aux->mu_lsr_reg & 0x01);
  char received = aux->mu_io_reg;

  dmb();

  return received;
}

void aux_mu_flush(unsigned int c) {
  dmb();

  WAIT_UNTIL(aux->mu_lsr_reg & 0x40);

  dmb();
}
