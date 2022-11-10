#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/watchdog.h"

#include "main.h"
#include "network.h"

static void init(void);
static void network_rx_callback(const ip_addr_t *addr, uint16_t port, void *data, uint16_t len);

/*
 * Core 0 entry
 * Runs network stack, handles communication
 */
int main()
{
    init();

    while (1)
    {
        watchdog_update();
        network_run();
    }
}

static void network_rx_callback(const ip_addr_t *addr, uint16_t port, void *data, uint16_t len)
{
    static char buff[128] = {0};
    if (len < (128 - 3))
    {
        memcpy(buff, data, len);
        buff[len] = '\r';
        buff[len + 1] = '\n';
        buff[len + 2] = '\0';
        printf(buff);
    }
}

static void init(void)
{
    stdio_init_all();
    watchdog_enable(2000, 1);

    network_init();
    network_rx_register_cb(network_rx_callback);

    multicore_reset_core1();
    multicore_launch_core1(core1_entry);
}