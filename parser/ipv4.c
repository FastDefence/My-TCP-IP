#include <stdio.h>
#include <arpa/inet.h>
#include "../pcthdr/ipv4.h"
#include "../header/parser.h"
#include "../header/protocols.h"

static void disp_ipv4_addr(uint32_t addr)
{
    const uint8_t *bytes = (const uint8_t *)&addr;

    printf("%u.%u.%u.%u",
           bytes[0],
           bytes[1],
           bytes[2],
           bytes[3]);
}

void disp_ipv4(const struct my_iphdr *ip)
{
    uint8_t version = ip->version_ihl >> 4;
    uint8_t ihl = ip->version_ihl & 0x0f;
    uint16_t total_length = ntohs(ip->total_length);

    printf("\n[IPv4 Header] ------------------------\n");

    printf("  Version      : %u\n", version);
    printf("  IHL          : %u bytes\n", ihl * 4);
    printf("  Total Length : %u\n", total_length);
    printf("  TTL          : %u\n", ip->ttl);

    printf("  Protocol     : %u ", ip->protocol);
    if (ip->protocol == MY_IPPROTO_ICMP) {
        printf("(ICMP)\n");
    } else if (ip->protocol == MY_IPPROTO_TCP) {
        printf("(TCP)\n");
    } else if (ip->protocol == MY_IPPROTO_UDP) {
        printf("(UDP)\n");
    } else {
        printf("(Unknown)\n");
    }

    printf("  Src IP       : ");
    disp_ipv4_addr(ip->saddr);
    printf("\n");

    printf("  Dst IP       : ");
    disp_ipv4_addr(ip->daddr);
    printf("\n");

    printf("--------------------------------------\n");
}

ParseResult parse_ipv4(const uint8_t *data, size_t len)
{
    ParseResult result = {
        .next_proto = PROTO_NONE,
        .payload = NULL,
        .payload_len = 0,
    };

    if (len < sizeof(struct my_iphdr)) {
        return result;
    }

    const struct my_iphdr *ip = (const struct my_iphdr *)data;

    uint8_t version = ip->version_ihl >> 4;
    uint8_t ihl = ip->version_ihl & 0x0f;
    size_t header_len = ihl * 4;

    if (version != 4) {
        result.next_proto = PROTO_UNKNOWN;
        return result;
    }

    if (ihl < 5) {
        result.next_proto = PROTO_UNKNOWN;
        return result;
    }

    if (len < header_len) {
        result.next_proto = PROTO_NONE;
        return result;
    }

    uint16_t total_length = ntohs(ip->total_length);

    if (total_length < header_len) {
        result.next_proto = PROTO_UNKNOWN;
        return result;
    }

    if (len < total_length) {
        result.next_proto = PROTO_NONE;
        return result;
    }

    disp_ipv4(ip);

    result.payload = data + header_len;
    result.payload_len = total_length - header_len;

    switch (ip->protocol) {
        case MY_IPPROTO_ICMP:
            result.next_proto = PROTO_ICMP;
            break;

        case MY_IPPROTO_TCP:
            result.next_proto = PROTO_TCP;
            break;

        case MY_IPPROTO_UDP:
            result.next_proto = PROTO_UDP;
            break;

        default:
            result.next_proto = PROTO_UNKNOWN;
            break;
    }

    return result;
}