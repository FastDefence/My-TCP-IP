#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h>
#include <stddef.h>

uint16_t calculate_checksum(const void *data, size_t len);

#endif