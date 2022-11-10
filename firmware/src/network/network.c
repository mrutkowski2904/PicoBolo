#include <stdint.h>
#include "pico/stdlib.h"

#include "secret.h" // tmp
#include "network.h"

static uint8_t connection_active = 0;
struct udp_pcb *udp_rx_proc;
static void (*user_udp_rx_cb)(const ip_addr_t *addr, uint16_t port, void *data, uint16_t len) = NULL;

static void on_udp_rx(void *arg, struct udp_pcb *pcb,
                      struct pbuf *p, const ip_addr_t *addr,
                      u16_t port);

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

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, connection_active);

    if (connection_active)
        cyw43_arch_poll();
}

void network_rx_register_cb(void (*cb)(const ip_addr_t *addr, uint16_t port, void *data, uint16_t len))
{
    user_udp_rx_cb = cb;
    udp_rx_proc = udp_new();
    udp_bind(udp_rx_proc, IP_ADDR_ANY, UDP_RX_PORT);
    udp_recv(udp_rx_proc, on_udp_rx, NULL);
}

static void on_udp_rx(void *arg, struct udp_pcb *pcb,
                      struct pbuf *p, const ip_addr_t *addr,
                      u16_t port)
{
    if (user_udp_rx_cb != NULL)
        user_udp_rx_cb(addr, port, p->payload, p->len);
    pbuf_free(p);
}