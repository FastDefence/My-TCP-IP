#include <stdio.h>
#include <arpa/inet.h>
#include "../pcthdr/arp.h"
#include "../pcthdr/ethii.h"
#include "../header/parser.h"
#include "../header/protocols.h"

static void disp_mac(const uint8_t mac[6])
{
    printf("%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2],
           mac[3], mac[4], mac[5]);
}

static void disp_ipv4_addr(uint32_t addr)
{
    const uint8_t *bytes = (const uint8_t *)&addr;

    printf("%u.%u.%u.%u",
           bytes[0],
           bytes[1],
           bytes[2],
           bytes[3]);
}

void disp_arp(const struct my_arphdr *arp)
{
    uint16_t htype = ntohs(arp->htype);
    uint16_t ptype = ntohs(arp->ptype);
    uint16_t oper = ntohs(arp->oper);

    printf("\n[ARP Header] -------------------------\n");

    printf("  Hardware Type : 0x%04x", htype);
    if (htype == MY_ARP_HTYPE_ETHERNET) {
        printf(" (Ethernet)");
    }
    printf("\n");

    printf("  Protocol Type : 0x%04x", ptype);
    if (ptype == MY_ETH_P_IP) {
        printf(" (IPv4)");
    }
    printf("\n");

    printf("  Hardware Len  : %u\n", arp->hlen);
    printf("  Protocol Len  : %u\n", arp->plen);

    printf("  Operation     : 0x%04x", oper);
    if (oper == MY_ARP_OPER_REQUEST) {
        printf(" (Request)");
    } else if (oper == MY_ARP_OPER_REPLY) {
        printf(" (Reply)");
    }
    printf("\n");

    printf("  Sender MAC    : ");
    disp_mac(arp->sha);
    printf("\n");

    printf("  Sender IP     : ");
    disp_ipv4_addr(arp->spa);
    printf("\n");

    printf("  Target MAC    : ");
    disp_mac(arp->tha);
    printf("\n");

    printf("  Target IP     : ");
    disp_ipv4_addr(arp->tpa);
    printf("\n");

    printf("--------------------------------------\n");
}

ParseResult parse_arp(const uint8_t *data, size_t len)
{
    ParseResult result = {
        .next_proto = PROTO_NONE,
        .payload = NULL,
        .payload_len = 0,
    };

    if (len < sizeof(struct my_arphdr)) {
        return result;
    }

    const struct my_arphdr *arp = (const struct my_arphdr *)data;

    uint16_t htype = ntohs(arp->htype);
    uint16_t ptype = ntohs(arp->ptype);

    if (htype != MY_ARP_HTYPE_ETHERNET) {
        result.next_proto = PROTO_UNKNOWN;
        return result;
    }

    if (ptype != MY_ETH_P_IP) {
        result.next_proto = PROTO_UNKNOWN;
        return result;
    }

    if (arp->hlen != 6 || arp->plen != 4) {
        result.next_proto = PROTO_UNKNOWN;
        return result;
    }

    disp_arp(arp);

    return result;
}