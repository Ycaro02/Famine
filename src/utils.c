#include <famine.h>

/**
 * @brief Redirects stdout and stderr to /dev/null to mute output.
 */
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
    if (fd < 0) {
        DBG("can't open %s\n", FLOCK_PATH);
        exit(0);
    }

    if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
        DBG("%s already locked\n", FLOCK_PATH);
        exit(0);
    }

    return fd;
}
