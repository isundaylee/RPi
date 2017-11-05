#include "lib/aux.h"
#include "lib/gpio.h"
#include "lib/timer.h"

#define PIN_LED 47

int notmain(void) {
  aux_mu_init();

  aux_mu_send_string("Hello, world!\r\n");
  aux_mu_flush();

  gpio_configure(PIN_LED, GPIO_OUTPUT);

  while (1) {
    char c = aux_mu_receive();

    switch (c) {
    case '0':
      gpio_set(PIN_LED);
      break;
    case '1':
      gpio_clear(PIN_LED);
      break;
    case 't':
      aux_mu_send_int(timer_get());
      aux_mu_send_newline();
      aux_mu_flush();
      break;
    }
  }

  return 0;
}
