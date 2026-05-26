#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <stdint.h>
#include <stddef.h>
#include "./parser.h"

void dispatch_ethii(const uint8_t *data, size_t len);
void dispatch_ipv4(const uint8_t *data, size_t len);

ParseResult parse_ethii(const uint8_t *data, size_t len);
ParseResult parse_arp(const uint8_t *data, size_t len);
ParseResult parse_ipv4(const uint8_t *data, size_t len);
ParseResult parse_icmp(const uint8_t *data, size_t len);

#endif