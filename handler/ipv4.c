#include <stdio.h>
#include <arpa/inet.h>
#include "../header/layer3.h"
#include "../protocols.h"

void disp_ipv4(struct my_ipv4hdr *ip) {
    struct in_addr src, dst;
    src.s_addr = ip->saddr;
    dst.s_addr = ip->daddr;

    printf("\n[IPv4 Header] ------------------------\n");
    printf("  Version: %d\n", ip->version);
    printf("  IHL: %d (%d bytes)\n", ip->ihl, ip->ihl * 4);
    printf("  TTL: %d\n", ip->ttl);

    printf("  Protocol: %d ", ip->protocol);
    if (ip->protocol == 1) printf("(ICMP)\n");
    else if (ip->protocol == 6) printf("(TCP)\n");
    else if (ip->protocol == 17) printf("(UDP)\n");
    else printf("(Unknown)\n");

    printf("  Source: %s\n", inet_ntoa(src));
    printf("  Dest: %s\n", inet_ntoa(dst));

    printf("--------------------------------------\n");
}

void handle_ipv4(const uint8_t *data, size_t len) {
    if (len < sizeof(struct my_ipv4hdr)) return;

    struct my_ipv4hdr *ip = (struct my_ipv4hdr *)data;
    disp_ipv4(ip);

    //int hlen = ip->ihl * 4;
    //const uint8_t *payload = data + hlen;
    //size_t payload_len = len - hlen;

    // TODO: l4_dispatch(ip->protocol, payload, payload_len);
}