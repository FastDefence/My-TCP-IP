#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <stdint.h>
#include <stddef.h>

// L2ハンドラ
void handle_ethernet(const uint8_t *data, size_t len);

// L3ディスパッチャ
void l3_dispatch(uint16_t eth_type, const uint8_t *data, size_t len);

// L3ハンドラ
void handle_arp(const uint8_t *data, size_t len);
void handle_ipv4(const uint8_t *data, size_t len);
//void handle_ipv6(const uint8_t *data, size_t len);

#endif