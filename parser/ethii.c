#include <stdio.h>
#include <arpa/inet.h>
#include "../header/ethii.h"
#include "../header/parser.h"
#include "../protocols.h"

void disp_ethernet(const struct my_ethhdr *eth) {
    printf("\n[Ethernet Header] --------------------\n");
    
    printf("  Dest MAC  : %02x:%02x:%02x:%02x:%02x:%02x\n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    printf("  Src  MAC  : %02x:%02x:%02x:%02x:%02x:%02x\n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    
    uint16_t type = ntohs(eth->h_proto);
    printf("  EtherType : 0x%04x ", type);
    if (type == MY_ETH_P_IP) printf("(IPv4)\n");
    else if (type == MY_ETH_P_ARP) printf("(ARP)\n");
    else if (type == MY_ETH_P_VLAN) printf("(VLAN)\n");
    else if (type == MY_ETH_P_IPV6) printf("(IPv6)\n");
    else printf("(Unknown)\n");
    
    printf("--------------------------------------\n");
}

ParseResult parse_ethernet(const uint8_t *data, size_t len) {
    ParseResult result = {
        .next_proto = PROTO_NONE,
        .payload = NULL,
        .payload_len = 0,
    };
    
    if (len < sizeof(struct my_ethhdr)) {
        return result; 
    }

    const struct my_ethhdr *eth = (const struct my_ethhdr *)data;
    
    disp_ethernet(eth);

    uint16_t ether_type = ntohs(eth->h_proto);

    result.payload = data + sizeof(struct my_ethhdr);
    result.payload_len = len - sizeof(struct my_ethhdr);

    switch (type) {
        case MY_ETH_P_IP:
            result.next_proto = PROTO_IPV4;
            break;
        case MY_ETH_P_ARP:
            result.next_proto = PROTO_ARP;
            break;
        case MY_ETH_P_IPV6:
            result.next_proto = PROTO_IPV6;
            break;
        default:
            result.next_proto = PROTO_UNKNOWN;
            break;
    }

    return result;
}