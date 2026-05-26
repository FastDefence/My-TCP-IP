#ifndef IPV4_H
#define IPV4_H

#include <stdint.h>

struct my_iphdr {
    uint8_t  version_ihl;
    uint8_t  tos;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_fragment_offset;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t header_checksum;
    uint32_t saddr;
    uint32_t daddr;
} __attribute__((packed));

#define MY_IPPROTO_ICMP 1
#define MY_IPPROTO_TCP  6
#define MY_IPPROTO_UDP  17

#endif