#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "secret.h" // tmp
#include "network.h"

static uint8_t connection_active = 0;

void network_init(void)
{
    if (cyw43_arch_init())
    {
        while (1)
            printf("CYW43 init failed\n");
    }

    cyw43_arch_enable_sta_mode();
    cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK);
}

void network_run(void)
{
    if (cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA) == CYW43_LINK_JOIN)
        connection_active = 1;
    else
        connection_active = 0;

    if (connection_active)
        cyw43_arch_poll();
}