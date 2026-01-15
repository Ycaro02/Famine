#include "../include/famine.h"

void mute_output() {
    int fd = open("/dev/null", O_WRONLY);
    if (fd == -1)
        exit(1);

    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
}
