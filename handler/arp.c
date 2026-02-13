#include <stdio.h>
#include <arpa/inet.h>
#include "../header/layer3.h"   // 構造体の定義
#include "../protocols.h"        // プロトタイプ宣言

void disp_arp(struct my_arphdr *arp){
    printf("\n[ARP Header] --------------------------\n");
    
    printf("  Hardware Type  : 0x%04x (Ethernet=1)\n", ntohs(arp->hw_type));
    printf("  Protocol Type  : 0x%04x (IPv4=0x0800)\n", ntohs(arp->proto_type));
    printf("  HW Addr Len    : %d\n", arp->hw_len); 
    printf("  Proto Addr Len : %d\n", arp->proto_len);

    uint16_t op = ntohs(arp->opcode);
    if (op == 1) {
        printf("  Operation      : Request (Who has?)\n");
    } else if (op == 2) {
        printf("  Operation      : Reply (I am!)\n");
    } else {
        printf("  Operation      : Unknown (%u)\n", op);
    }
    
    struct in_addr src_ip, dst_ip;
    src_ip.s_addr = arp->sender_ip;
    dst_ip.s_addr = arp->target_ip;
    printf("  Sender MAC     : %02x:%02x:%02x:%02x:%02x:%02x\n", arp->sender_mac[0], arp->sender_mac[1], arp->sender_mac[2], arp->sender_mac[3], arp->sender_mac[4], arp->sender_mac[5]);
    printf("  Sender IP      : %s\n", inet_ntoa(src_ip));
    printf("  Target MAC     : %02x:%02x:%02x:%02x:%02x:%02x\n", arp->target_mac[0], arp->target_mac[1], arp->target_mac[2], arp->target_mac[3], arp->target_mac[4], arp->target_mac[5]);
    printf("  Target IP      : %s\n", inet_ntoa(dst_ip));
    
    printf("--------------------------------------\n");
}

void handle_arp(int fd, const uint8_t *data, size_t len) {
    if (len < sizeof(struct my_arphdr)) {
        return;
    }

    struct my_arphdr *arp = (struct my_arphdr *)data;

    disp_arp(arp);
}