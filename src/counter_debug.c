#include "../include/famine.h"

void anti_debug() {
    char buf[256];
    int fd = open("/proc/self/status", O_RDONLY);
    if (fd < 0)
        return;

    int n = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (n <= 0)
        return;

    buf[n] = 0;

    for (int i = 0; i < n - 10; i++)
        if (buf[i] == 'T' &&
            buf[i+1] == 'r' &&
            buf[i+2] == 'a' &&
            buf[i+3] == 'c' &&
            buf[i+4] == 'e' &&
            buf[i+5] == 'r' &&
            buf[i+6] == 'P' &&
            buf[i+7] == 'i' &&
            buf[i+8] == 'd' &&
            buf[i+9] == ':')
            if (buf[i+11] != '0')
                _exit(0);
}
