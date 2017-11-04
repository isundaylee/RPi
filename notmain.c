#include "lib/aux.h"
#include "lib/gpio.h"
#include "lib/timer.h"

int notmain(void) {
  aux_mu_init();

  aux_mu_send_string("Hello, world!\r\n");
  aux_mu_flush();

  while (1) {
      aux_mu_send(aux_mu_receive());
      aux_mu_flush();
  }

  return 0;
}
