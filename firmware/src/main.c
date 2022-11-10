#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main()
{
    stdio_init_all();

    while (1)
    {
        puts("Hello from pico");
        sleep_ms(100);
    }
    return 0;
}
