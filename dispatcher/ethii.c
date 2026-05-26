#include "../header/parser.h"
#include "../pcthdr/ethii.h"

void ethii_dispatch(const uint8_t *data, size_t len)
{
    ParseResult result = parse_ethernet(data, len);

    while (result.next_proto != PROTO_NONE &&
           result.next_proto != PROTO_UNKNOWN) {
        switch (result.next_proto) {
            case PROTO_ARP:
                result = parse_arp(result.payload, result.payload_len);
                break;

            case PROTO_IPV4:
                result = parse_ipv4(result.payload, result.payload_len);
                break;

            default:
                result.next_proto = PROTO_UNKNOWN;
                break;
        }
    }
}