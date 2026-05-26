#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <stdint.h>
#include <stddef.h>
#include "./parser.h"

// ディスパッチャ
void dispatch_ethii(const uint8_t *data, size_t len);

// パーサー
ParseResult parse_ethii(const uint8_t *data, size_t len);

#endif