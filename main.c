#include <stdio.h>
#include <unistd.h>
#include "make_tap.h"
#include "protocols.h"

int main() {
    char dev_name[16] = "tap0";
    uint8_t buffer[1500];
    
    int fd = tun_alloc(dev_name);
    if (fd < 0) return 1;

    printf("Network Stack started on %s...\n", dev_name);
    
    while (1) {
        ssize_t nread = read(fd, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("read from tap");
            break;
        }

        ethii_dispatch(buffer, (size_t)nread);
    }

    close(fd);
    return 0;
}