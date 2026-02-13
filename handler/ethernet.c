#include <stdio.h>
#include <arpa/inet.h>
#include "../header/layer2.h"
#include "../protocols.h"

void disp_ethernet(struct my_ethhdr *eth) {
    printf("\n[Ethernet Header] --------------------\n");
    
    printf("  Dest MAC  : %02x:%02x:%02x:%02x:%02x:%02x\n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    printf("  Src  MAC  : %02x:%02x:%02x:%02x:%02x:%02x\n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    
    uint16_t type = ntohs(eth->h_proto);
    printf("  EtherType : 0x%04x ", type);
    if (type == MY_ETH_P_IP) printf("(IPv4)\n");
    else if (type == MY_ETH_P_ARP) printf("(ARP)\n");
    else if (type == MY_ETH_P_IPV6) printf("(IPv6)\n");
    else printf("(Unknown)\n");
    
    printf("--------------------------------------\n");
}

void handle_ethernet(int fd, const uint8_t *data, size_t len) {
    if (len < sizeof(struct my_ethhdr)) {
        return; 
    }

    struct my_ethhdr *eth = (struct my_ethhdr *)data;
    
    disp_ethernet(eth);

    uint16_t type = ntohs(eth->h_proto);
    const uint8_t *payload = data + sizeof(struct my_ethhdr);
    size_t payload_len = len - sizeof(struct my_ethhdr);

    l3_dispatch(fd, type, payload, payload_len);
}