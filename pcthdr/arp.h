#ifndef ARP_H
#define ARP_H

#include <stdint.h>

struct my_arphdr {
    uint16_t htype;
    uint16_t ptype;
    uint8_t  hlen;
    uint8_t  plen;
    uint16_t oper;

    uint8_t  sha[6];
    uint32_t spa;
    uint8_t  tha[6];
    uint32_t tpa;
} __attribute__((packed));

#define MY_ARP_HTYPE_ETHERNET 0x0001

#define MY_ARP_OPER_REQUEST   0x0001
#define MY_ARP_OPER_REPLY     0x0002

#endif