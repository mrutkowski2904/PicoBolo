#ifndef __NETWORK_H
#define __NETWORK_H

#include "pico/cyw43_arch.h"

#define UDP_RX_PORT 2007U

void network_init(void);
void network_run(void);
void network_rx_register_cb(void (*cb)(const ip_addr_t *addr, uint16_t port, void *data, uint16_t len));

#endif /* __NETWORK_H */