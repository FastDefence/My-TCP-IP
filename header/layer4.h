#ifndef LAYER4_HEADER_H
#define LAYER4_HEADER_H

#include <stdint.h>

struct my_icmphdr {
    uint8_t  type;     // タイプ (8:Request, 0:Reply)
    uint8_t  code;     // コード (基本は0)
    uint16_t checksum; // チェックサム

    uint16_t id;       // 識別子
    uint16_t sequence; // シーケンス番号
} __attribute__((packed));

// 代表的なタイプの定数
#define ICMP_TYPE_ECHO_REPLY   0
#define ICMP_TYPE_ECHO_REQUEST 8

#endif