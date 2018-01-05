#include "lib/aux.h"
#include "lib/gpio.h"
#include "lib/i2c.h"
#include "lib/spi.h"
#include "lib/intr.h"
#include "lib/timer.h"

#define PIN_LED 47
#define PIN_OUTPUT 12

static int count = 0;

void toggle_pin_output() {
  aux_mu_send_uint(count);
  count = 0;
  aux_mu_send_newline();
}

int notmain(void) {
  aux_mu_init();
  // intr_enable();
  spi_enable();
  // timer_init();

  aux_mu_send_string("Hello, world!\r\n");
  aux_mu_flush();

  // gpio_configure(PIN_OUTPUT, GPIO_OUTPUT);
  // timer_set(TIMER_1, 1000 * 1000, TIMER_PERIODIC, toggle_pin_output);

  return 0;
}
