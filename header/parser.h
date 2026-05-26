#ifndef MYNET_PARSER_H
#define MYNET_PARSER_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    PROTO_NONE,
    PROTO_UNKNOWN,
    PROTO_IPV4,
    PROTO_IPV6,
    PROTO_ARP,
    PROTO_VLAN,
    PROTO_TCP,
    PROTO_UDP,
    PROTO_ICMP,
    PROTO_ICMPV6
} ProtoType;

typedef struct {
    ProtoType next_proto;
    const uint8_t *payload;
    size_t payload_len;
} ParseResult;

#endif