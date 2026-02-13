#include <stdint.h> // uint8_t, uint16_t, uint32_t を使うために必要

// __attribute__((packed)) は「コンパイラに隙間(パディング)を空けさせるな」という命令
// これがないと、パケットのデータと構造体の位置がズレることがあります。
struct my_arphdr {
    uint16_t hw_type;      // Hardware Type (Ethernet = 1)
    uint16_t proto_type;   // Protocol Type (IPv4 = 0x0800)
    uint8_t  hw_len;       // Hardware Address Length (MACアドレスの長さ = 6)
    uint8_t  proto_len;    // Protocol Address Length (IPアドレスの長さ = 4)
    uint16_t opcode;       // Operation Code (Request=1, Reply=2)
    
    // --- ここから下は可変長ですが、Ethernet+IPv4なら固定でこの形です ---
    uint8_t  sender_mac[6]; // 送信元MACアドレス
    uint32_t sender_ip;     // 送信元IPアドレス (32bit整数)
    uint8_t  target_mac[6]; // ターゲットMACアドレス
    uint32_t target_ip;     // ターゲットIPアドレス
} __attribute__((packed));

struct my_iphdr {
    // リトルエンディアン(x86)環境での定義
    uint8_t  ihl:4,        // ヘッダ長
             version:4;    // バージョン(4)
    uint8_t  tos;          // サービス型
    uint16_t tot_len;      // パケット全長
    uint16_t id;           // 識別子
    uint16_t frag_off;     // フラグメント情報
    uint8_t  ttl;          // 生存時間
    uint8_t  protocol;     // 次のプロトコル(1=ICMP, 6=TCP, 17=UDP)
    uint16_t check;        // チェックサム
    uint32_t saddr;        // 送信元IP
    uint32_t daddr;        // 宛先IP
} __attribute__((packed));