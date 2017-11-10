#include "lib/i2c.h"
#include "lib/aux.h"
#include "lib/common.h"
#include "lib/gpio.h"

typedef struct {
  uint32_t c;    // Control
  uint32_t s;    // Status
  uint32_t dlen; // Data length
  uint32_t a;    // Slave address
  uint32_t fifo; // Data FIFO
  uint32_t div;  // Clock divider
  uint32_t del;  // Data delay
  uint32_t clkt; // Clock stretch timeout
} I2C;

#define I2C_BASE (PERIPHERAL_BASE + 0x205000)
volatile I2C *i2c = (volatile I2C *)I2C_BASE;

#define I2C_PIN_SDA 0
#define I2C_PIN_CLK 1

#define I2C_C_I2CEN BIT(15)
#define I2C_C_INTR BIT(10)
#define I2C_C_INTT BIT(9)
#define I2C_C_INTD BIT(8)
#define I2C_C_ST BIT(7)
#define I2C_C_CLEAR (BIT(4) | BIT(5))
#define I2C_C_READ BIT(0)

#define I2C_S_TA BIT(0)
#define I2C_S_DONE BIT(1)
#define I2C_S_TXW BIT(2)
#define I2C_S_RXR BIT(3)
#define I2C_S_TXD BIT(4)
#define I2C_S_RXD BIT(5)
#define I2C_S_TXE BIT(6)
#define I2C_S_RXF BIT(7)
#define I2C_S_ERR BIT(8)
#define I2C_S_CLKT BIT(9)

void i2c_enable() {
  gpio_configure(I2C_PIN_SDA, GPIO_ALT_0);
  gpio_configure(I2C_PIN_CLK, GPIO_ALT_0);
}

void i2c_disable() {
  gpio_configure(I2C_PIN_SDA, GPIO_INPUT);
  gpio_configure(I2C_PIN_CLK, GPIO_INPUT);
}

int i2c_write(int addr, byte *buf, int len) {
  byte *end = buf + len;

  dmb();
  i2c->a = addr;
  i2c->dlen = len;
  i2c->s = I2C_S_ERR | I2C_S_CLKT | I2C_S_DONE;
  i2c->c = I2C_C_CLEAR | I2C_C_ST | I2C_C_I2CEN;

  while (buf != end) {
    WAIT_UNTIL(i2c->s & I2C_S_TXD);
    i2c->fifo = *buf;
    buf++;
  }

  WAIT_UNTIL(i2c->s & I2C_S_DONE);

  dmb();

  i2c->s = I2C_S_DONE;

  if (i2c->s & I2C_S_ERR) {
    dmb();
    return I2C_ERROR;
  }

  if (i2c->s & I2C_S_CLKT) {
    dmb();
    return I2C_ERROR;
  }

  dmb();
  return I2C_SUCCESS;
}

int i2c_read(int addr, byte *buf, int len) {
  byte *end = buf + len;

  dmb();
  i2c->a = addr;
  i2c->dlen = len;
  i2c->s = I2C_S_ERR | I2C_S_CLKT | I2C_S_DONE;
  i2c->c = I2C_C_I2CEN | I2C_C_ST | I2C_C_CLEAR | I2C_C_READ;

  while (!(i2c->s & I2C_S_DONE)) {
    while (i2c->s & I2C_S_RXD) {
      *buf = i2c->fifo;
      buf++;
    }
  }

  while ((buf < end) && (i2c->s & I2C_S_RXD)) {
    *buf = i2c->fifo;
    buf++;
  }

  if (buf != end) {
    dmb();
    return I2C_ERROR;
  }

  if (i2c->s & I2C_S_ERR) {
    dmb();
    return I2C_ERROR;
  }

  if (i2c->s & I2C_S_CLKT) {
    dmb();
    return I2C_ERROR;
  }

  dmb();
  return I2C_SUCCESS;
}
