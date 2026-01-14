#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
    printf("Program with name \"test\" is running with pid: %d\n", getpid());
    printf("ctrl + c to stop it\n");

    while (1)
        pause();
}
