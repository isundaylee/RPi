#include "lib/spi.h"
#include "lib/common.h"
#include "lib/gpio.h"

#define SPI_PIN_CE0 8
#define SPI_PIN_CE1 7
#define SPI_PIN_CE2 16
#define SPI_PIN_MISO 9
#define SPI_PIN_MOSI 10
#define SPI_PIN_SCLK 11

#define SPI_CS_CS_MASK (BIT(0) | BIT(1))
#define SPI_CS_CS_0 (0)
#define SPI_CS_CS_1 (BIT(0))
#define SPI_CS_CS_2 (BIT(1))
#define SPI_CS_CPHA (BIT(2))
#define SPI_CS_CPOL (BIT(3))
#define SPI_CS_CLEAR (BIT(4) | BIT(5))
#define SPI_CS_CSPOL (BIT(6))
#define SPI_CS_TA (BIT(7))
#define SPI_CS_DMAEN (BIT(8))
#define SPI_CS_INTD (BIT(9))
#define SPI_CS_INTR (BIT(10))
#define SPI_CS_ADCS (BIT(11))
#define SPI_CS_REN (BIT(12))
#define SPI_CS_LEN (BIT(13))
#define SPI_CS_LMONO (BIT(14))
#define SPI_CS_TE_EN (BIT(15))
#define SPI_CS_DONE (BIT(16))
#define SPI_CS_RXD (BIT(17))
#define SPI_CS_TXD (BIT(18))
#define SPI_CS_RXR (BIT(19))
#define SPI_CS_RXF (BIT(20))
#define SPI_CS_CSPOL0 (BIT(21))
#define SPI_CS_CSPOL1 (BIT(22))
#define SPI_CS_CSPOL2 (BIT(23))
#define SPI_CS_DMA_LEN (BIT(24))
#define SPI_CS_LEN_LONG (BIT(25))

typedef struct {
  uint32_t cs;
  uint32_t fifo;
  uint32_t clk;
  uint32_t dlen;
  uint32_t ltoh;
  uint32_t dc;
} SPI;

#define SPI_BASE (PERIPHERAL_BASE + 0x204000)
volatile SPI *spi = (volatile SPI *)SPI_BASE;

int c;

void spi_enable() {
  gpio_configure(SPI_PIN_CE0, GPIO_ALT_0);
  gpio_configure(SPI_PIN_CE1, GPIO_ALT_0);
  gpio_configure(SPI_PIN_CE2, GPIO_ALT_0);
  gpio_configure(SPI_PIN_MISO, GPIO_ALT_0);
  gpio_configure(SPI_PIN_MOSI, GPIO_ALT_0);
  gpio_configure(SPI_PIN_SCLK, GPIO_ALT_0);

  spi->clk = 65536;
  spi->cs |= SPI_CS_CPOL;
  spi->cs = (spi->cs & (~SPI_CS_CS_MASK)) | SPI_CS_CS_0;

  gpio_configure(17, GPIO_OUTPUT);
  gpio_clear(17);
  gpio_set(17);

  dmb();

  spi->cs |= SPI_CS_CLEAR;
  spi->cs |= SPI_CS_TA;

  WAIT_UNTIL(spi->cs & SPI_CS_TXD);
  spi->fifo = 0b01100000;

  WAIT_UNTIL(spi->cs & SPI_CS_DONE);
  spi->cs &= ~SPI_CS_TA;

  dmb();
}

void spi_disable() {
  gpio_configure(SPI_PIN_CE0, GPIO_INPUT);
  gpio_configure(SPI_PIN_CE1, GPIO_INPUT);
  gpio_configure(SPI_PIN_CE2, GPIO_INPUT);
  gpio_configure(SPI_PIN_MISO, GPIO_INPUT);
  gpio_configure(SPI_PIN_MOSI, GPIO_INPUT);
  gpio_configure(SPI_PIN_SCLK, GPIO_INPUT);
}
