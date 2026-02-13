#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../header/layer2.h"
#include "../header/layer3.h"
#include "../header/layer4.h"
#include "../util/checksum.h"

void disp_icmp(struct my_icmphdr *icmp) {
    printf("\n[ICMP Header] ------------------------\n");
    
    printf("  Type     : %d ", icmp->type);
    if (icmp->type == ICMP_TYPE_ECHO_REQUEST) printf("(Echo Request)\n");
    else if (icmp->type == ICMP_TYPE_ECHO_REPLY) printf("(Echo Reply)\n");
    else printf("(Unknown)\n");

    printf("  Code     : %d\n", icmp->code);
    printf("  Checksum : 0x%04x\n", ntohs(icmp->checksum));
    printf("  ID       : 0x%04x\n", ntohs(icmp->id));
    printf("  Seq      : 0x%04x\n", ntohs(icmp->sequence));

    printf("--------------------------------------\n");
}

void send_icmp_echo_reply(int fd, const uint8_t *rx_data, size_t rx_len) {
    struct my_icmphdr *rx_icmp = (struct my_icmphdr *)rx_data;
    struct my_ipv4hdr *rx_ip = (struct my_ipv4hdr *)(rx_data - sizeof(struct my_ipv4hdr));
    struct my_ethhdr *rx_eth = (struct my_ethhdr *)((uint8_t *)rx_ip - sizeof(struct my_ethhdr));
    uint8_t tx_buffer[1500];
    struct my_ethhdr *tx_eth = (struct my_ethhdr *)tx_buffer;
    struct my_ipv4hdr *tx_ip = (struct my_ipv4hdr *)(tx_buffer + sizeof(struct my_ethhdr));
    struct my_icmphdr *tx_icmp = (struct my_icmphdr *)(tx_buffer + sizeof(struct my_ethhdr) + sizeof(struct my_ipv4hdr));
    
    size_t icmp_payload_len = rx_len - sizeof(struct my_icmphdr);
    uint8_t *tx_payload = (uint8_t *)tx_icmp + sizeof(struct my_icmphdr);

    memcpy(tx_eth->h_dest, rx_eth->h_source, 6);
    memcpy(tx_eth->h_source, rx_eth->h_dest, 6);
    tx_eth->h_proto = htons(MY_ETH_P_IP);

    tx_ip->version = 4;
    tx_ip->ihl = 5;
    tx_ip->tos = 0;

    tx_ip->tot_len = htons(sizeof(struct my_ipv4hdr) + sizeof(struct my_icmphdr) + icmp_payload_len);
    tx_ip->id = htons(0);
    tx_ip->frag_off = htons(0x4000);
    tx_ip->ttl = 64;
    tx_ip->protocol = 1;
    tx_ip->check = 0;
    
    tx_ip->saddr = rx_ip->daddr;
    tx_ip->daddr = rx_ip->saddr;
    
    tx_ip->check = calculate_checksum(tx_ip, sizeof(struct my_ipv4hdr));

    tx_icmp->type = ICMP_TYPE_ECHO_REPLY;
    tx_icmp->code = 0;
    tx_icmp->checksum = 0;
    tx_icmp->id = rx_icmp->id;
    tx_icmp->sequence = rx_icmp->sequence;

    if (icmp_payload_len > 0) {
        memcpy(tx_payload, rx_data + sizeof(struct my_icmphdr), icmp_payload_len);
    }

    size_t icmp_total_len = sizeof(struct my_icmphdr) + icmp_payload_len;
    tx_icmp->checksum = calculate_checksum(tx_icmp, icmp_total_len);

    size_t packet_len = sizeof(struct my_ethhdr) + sizeof(struct my_ipv4hdr) + icmp_total_len;
    
    printf("[ICMP] Sending Echo Reply...\n");
    write(fd, tx_buffer, packet_len);
}

void handle_icmp(int fd, const uint8_t *data, size_t len) {
    if (len < sizeof(struct my_icmphdr)) {
        return;
    }

    struct my_icmphdr *icmp = (struct my_icmphdr *)data;

    disp_icmp(icmp);

    uint16_t sum = calculate_checksum(data, len);
    
    if (sum != 0) {
        printf("[ICMP] Checksum Error! (Result: 0x%04x)\n", sum);
    } else {
        printf("[ICMP] Checksum Valid\n");
    }

    if (icmp->type == ICMP_TYPE_ECHO_REQUEST) {
        send_icmp_echo_reply(fd, data, len);
    }
}