#include <stdio.h>
#include "../protocols.h"
#include "../header/layer3.h"

void l4_dispatch(int fd, uint16_t protocol, const uint8_t *data, size_t len) {
    switch (protocol) {
        case MY_L3_P_ICMP:
            handle_icmp(fd, data, len);
            break;
    }
}