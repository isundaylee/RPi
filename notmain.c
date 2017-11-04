#include "lib/timer.h"
#include "lib/gpio.h"

int notmain ( void )
{
    gpio_configure(12, GPIO_OUTPUT);

    while(1)
    {
        gpio_clear(12);
        
        gpio_set(12);
    }

    return(0);
}
