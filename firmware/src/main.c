#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "hardware/watchdog.h"

#include "config.h"
#include "network.h"

static void core0_init(void);
static void core1_init(void);
static void core1_entry(void);

/*
 * Core 0 entry
 * Runs network stack, handles communication
 */
int main()
{
    core0_init();

    while (1)
    {
        watchdog_update();
        network_run();
    }
}

/*
 * Core 1 entry
 * Controls robot movement
 */
static void core1_entry(void)
{
    core1_init();

    while (1)
    {
        __wfi();
    }
}

static void core0_init(void)
{
    stdio_init_all();

    if (watchdog_caused_reboot())
    {
        printf("Rebooted by watchdog\n");
    }
    watchdog_enable(1000, 1);

    network_init();

    multicore_reset_core1();
    multicore_launch_core1(core1_entry);
}

static void core1_init(void)
{
}