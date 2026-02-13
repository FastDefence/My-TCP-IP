#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <stdint.h>
#include <stddef.h>

// ディスパッチャ
void l3_dispatch(int fd, uint16_t eth_type, const uint8_t *data, size_t len);
void l4_dispatch(int fd, uint16_t eth_type, const uint8_t *data, size_t len);

// L2ハンドラ
void handle_ethernet(int fd, const uint8_t *data, size_t len);

// L3ハンドラ
void handle_arp(int fd, const uint8_t *data, size_t len);
void handle_ipv4(int fd, const uint8_t *data, size_t len);
//void handle_ipv6(const uint8_t *data, size_t len);

// L4ハンドラ
void handle_icmp(int fd, const uint8_t *data, size_t len);

#endif