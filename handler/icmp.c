#include <stdio.h>
#include <arpa/inet.h>
#include "../header/layer4.h"
#include "../util/checksum.h" // チェックサム計算用

// ICMPヘッダの表示担当
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

// ICMPパケットの処理担当
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

    // ★ここに将来「Echo Reply送信処理」を追加します
    /*
    if (icmp->type == ICMP_TYPE_ECHO_REQUEST) {
        send_echo_reply(...);
    }
    */
}