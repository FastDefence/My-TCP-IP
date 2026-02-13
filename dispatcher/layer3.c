#include <stdio.h>
#include "../protocols.h"
#include "../header/layer2.h"

void l3_dispatch(int fd, uint16_t eth_type, const uint8_t *data, size_t len) {
    switch (eth_type) {
        case MY_ETH_P_ARP:
            handle_arp(fd, data, len);
            break;
        case MY_ETH_P_IP:
            handle_ipv4(fd, data, len);
            break;
        /*case MY_ETH_P_IPV6:
            handle_ipv6(fd, data, len);
            break;
        */

        default:
            break;
    }
}