#include "lib/aux.h"
#include "lib/gpio.h"
#include "lib/intr.h"
#include "lib/timer.h"

#define PIN_LED 47

void handle_timer() {
  static int state = 0;

  aux_mu_send('.');
  aux_mu_flush();

  state = 1 - state;

  if (state) {
    gpio_set(PIN_LED);
  } else {
    gpio_clear(PIN_LED);
  }
}

int notmain(void) {
  intr_enable();
  aux_mu_init();

  aux_mu_send_string("Hello, world!\r\n");
  aux_mu_flush();

  gpio_configure(PIN_LED, GPIO_OUTPUT);

  timer_init();
  timer_set(TIMER_1, 100 * 1000, TIMER_PERIODIC, handle_timer);

  return 0;
}
