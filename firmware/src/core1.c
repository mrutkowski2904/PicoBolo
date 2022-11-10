#include "pico/stdlib.h"

#include "main.h"

static void core1_init(void);

/*
 * Core 1 entry
 * Controls robot movement
 */
void core1_entry(void)
{
    core1_init();

    while (1)
    {
        tight_loop_contents();
    }
}

static void core1_init(void)
{
}