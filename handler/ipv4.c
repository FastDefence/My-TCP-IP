#include <stdio.h>
#include <arpa/inet.h>
#include "../header/layer3.h"
#include "../protocols.h"

void disp_ipv4(struct my_ipv4hdr *ip) {
    struct in_addr src, dst;
    src.s_addr = ip->saddr;
    dst.s_addr = ip->daddr;

    printf("\n[IPv4 Header] --------------------------\n");

    printf("  Version   : %d\n", ip->version);
    printf("  IHL       : %d (%d bytes)\n", ip->ihl, ip->ihl * 4);
    printf("  TOS       : 0x%02x\n", ip->tos);
    printf("  Total Len : %d bytes\n", ntohs(ip->tot_len));
    printf("  ID        : 0x%04x (%d)\n", ntohs(ip->id), ntohs(ip->id));

    uint16_t frag = ntohs(ip->frag_off);
    uint16_t flags = frag & 0xE000; // 上位3ビット
    uint16_t offset = frag & 0x1FFF; // 下位13ビット
    printf("  Flag Info : 0x%04x (Flags: ", frag);
    if (flags & 0x4000) printf("DF "); // Don't Fragment (分割禁止)
    if (flags & 0x2000) printf("MF "); // More Fragments (続きあり)
    printf("| Offset: %d)\n", offset);

    printf("  TTL       : %d\n", ip->ttl);

    printf("  Protocol  : %d ", ip->protocol);
    if (ip->protocol == 1) printf("(ICMP)\n");
    else if (ip->protocol == 6) printf("(TCP)\n");
    else if (ip->protocol == 17) printf("(UDP)\n");
    else printf("(Unknown)\n");

    printf("  Checksum  : 0x%04x\n", ntohs(ip->check));
    printf("  Source    : %s\n", inet_ntoa(src));
    printf("  Dest      : %s\n", inet_ntoa(dst));

    printf("--------------------------------------\n");
}

void handle_ipv4(int fd, const uint8_t *data, size_t len) {
    if (len < sizeof(struct my_ipv4hdr)) return;

    struct my_ipv4hdr *ip = (struct my_ipv4hdr *)data;
    disp_ipv4(ip);

    int hlen = ip->ihl * 4;
    const uint8_t *payload = data + hlen;
    size_t payload_len = len - hlen;

    l4_dispatch(fd, ip->protocol, payload, payload_len);
}