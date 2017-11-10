#include "lib/aux.h"
#include "lib/gpio.h"
#include "lib/i2c.h"
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
  i2c_enable();
  intr_enable();
  timer_init();

  aux_mu_send_string("Hello, world!\r\n");
  aux_mu_flush();

  // gpio_configure(PIN_OUTPUT, GPIO_OUTPUT);
  timer_set(TIMER_1, 1000 * 1000, TIMER_PERIODIC, toggle_pin_output);

  int r = i2c_write(0x48, (byte[]) {0b00000001, 0b10000100, 0b10000011}, 3);
  assert(r == I2C_SUCCESS);
  r = i2c_write(0x48, (byte[]) {0b00000000}, 1);
  assert(r == I2C_SUCCESS);

  byte buf[2];
  while (1) {
    int r = i2c_read(0x48, buf, 2);
    assert(r == I2C_SUCCESS);

    count ++;
    aux_mu_send_int(256 * buf[0] + buf[1]);
    aux_mu_send_newline();
  }

  return 0;
}
