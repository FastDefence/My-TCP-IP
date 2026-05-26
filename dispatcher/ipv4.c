#include "../header/parser.h"
#include "../header/protocols.h"
#include "../pcthdr/ipv4.h"

void dispatch_ipv4(const uint8_t *data, size_t len)
{
    ParseResult result = parse_ipv4(data, len);

    /* 時期尚早
    while (result.next_proto != PROTO_NONE &&
           result.next_proto != PROTO_UNKNOWN) {
        switch (result.next_proto) {
            case PROTO_ICMP:
                result = parse_icmp(result.payload, result.payload_len);
                break;

            case PROTO_TCP:
                result = parse_tcp(result.payload, result.payload_len);
                break;

            case PROTO_UDP:
                result = parse_udp(result.payload, result.payload_len);
                break;

            default:
                result.next_proto = PROTO_UNKNOWN;
                break;
        }
    }
    */
}