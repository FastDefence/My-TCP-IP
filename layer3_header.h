#ifndef LAYER3_HEADER_H
#define LAYER3_HEADER_H

#include <stdint.h>

struct my_arphdr {
    uint16_t hw_type;
    uint16_t proto_type;
    uint8_t  hw_len;
    uint8_t  proto_len;
    uint16_t opcode;
    uint8_t  sender_mac[6];
    uint32_t sender_ip;
    uint8_t  target_mac[6];
    uint32_t target_ip;
} __attribute__((packed));

struct my_ipv4hdr {
    uint8_t  ihl:4,        // ヘッダ長
             version:4;    // バージョン(4)
    uint8_t  tos;          // サービス型
    uint16_t tot_len;      // 全長
    uint16_t id;           // 識別子
    uint16_t frag_off;     // フラグメント情報
    uint8_t  ttl;          // 生存時間
    uint8_t  protocol;     // 次のプロトコル(1=ICMP, 6=TCP, 17=UDP)
    uint16_t check;        // チェックサム
    uint32_t saddr;        // 送信元IP
    uint32_t daddr;        // 宛先IP
} __attribute__((packed));

struct my_ipv6hdr {
    uint32_t v_tc_fl;      // Version(4bit), Traffic Class(8bit), Flow Label(20bit)
    uint16_t payload_len;  // ペイロード（中身）の長さ
    uint8_t  next_header;  // 次のヘッダの種類 (IPv4のprotocolと同じ。TCP=6など)
    uint8_t  hop_limit;    // ホップリミット (IPv4のTTLと同じ)
    uint8_t  saddr[16];    // 送信元IPv6アドレス (128bit)
    uint8_t  daddr[16];    // 宛先IPv6アドレス (128bit)
} __attribute__((packed));

#endif