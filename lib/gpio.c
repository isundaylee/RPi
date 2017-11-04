#include "lib/gpio.h"
#include "lib/common.h"

typedef struct {
    uint32_t fsel[6];
    uint32_t dummy1;
    uint32_t set[2];
    uint32_t dummy2;
    uint32_t clr[2];
    uint32_t dummy3;
    uint32_t lev[2];
    uint32_t dummy4;
    uint32_t eds[2];
    uint32_t dummy5;
    uint32_t ren[2];
    uint32_t dummy6;
    uint32_t fen[2];
    uint32_t dummy7;
    uint32_t hen[2];
    uint32_t dummy8;
    uint32_t len[2];
    uint32_t dummy9;
    uint32_t aren[2];
    uint32_t dummy10;
    uint32_t afen[2];
    uint32_t dummy11;
    uint32_t gppud;
    uint32_t gppudclk[2];
    uint32_t dummy12;
} GPIO;


#define GPIO_BASE  (PERIPHERAL_BASE + 0x00200000)

volatile GPIO *gpio = (GPIO *) GPIO_BASE;

void gpio_configure(int pin, int type) {
    dmb();
    int sel = gpio->fsel[pin / 10];
    sel &= ~(0b111 << (3 * (pin % 10)));
    sel |= type << (3 * (pin % 10));
    gpio->fsel[pin / 10] = sel;
    dmb();
}

void gpio_set(int pin) {
    dmb();
    gpio->set[(pin / 32)] = 1 << (pin % 32);
    dmb();
}

void gpio_clear(int pin) {
    dmb();
    gpio->clr[(pin / 32)] = 1 << (pin % 32);
    dmb();
}
