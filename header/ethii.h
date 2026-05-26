#ifndef ETHII_H
#define ETHII_H

#include <stdint.h>

struct my_ethhdr {
    uint8_t  h_dest[6];
    uint8_t  h_source[6];
    uint16_t h_proto;
} __attribute__((packed));

#define MY_ETH_HLEN   14

#define MY_ETH_P_IP   0x0800
#define MY_ETH_P_ARP  0x0806
#define MY_ETH_P_IPV6 0x86dd
#define MY_ETH_P_VLAN 0x8100

#endif
