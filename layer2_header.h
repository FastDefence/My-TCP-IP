#ifndef LAYER2_HEADER_H
#define LAYER2_HEADER_H

#include <stdint.h>

struct my_ethhdr {
    uint8_t  h_dest[6];   // 宛先MACアドレス (Destination)
    uint8_t  h_source[6]; // 送信元MACアドレス (Source)
    uint16_t h_proto;     // プロトコルタイプ (ARP: 0x0806, IP: 0x0800)
} __attribute__((packed));

#define MY_ETH_P_IP   0x0800 // IPv4
#define MY_ETH_P_ARP  0x0806 // ARP
#define MY_ETH_P_IPV6 0x86dd // IPv6

#endif
