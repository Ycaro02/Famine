#include "../include/famine.h"

void exit_if_process_running() {
    const char *name = "test";
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    char path[256];
    char comm[256];
    FILE *f;

    if (!dir) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!ft_isdigit(entry->d_name[0])) {
            continue;
        }

        snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
        f = fopen(path, "r");
        if (!f) {
            continue;
        }

        if (fgets(comm, sizeof(comm), f)) {
            comm[strcspn(comm, "\n")] = 0;
            if (!ft_strcmp(comm, name)) {
                fclose(f);
                closedir(dir);
                exit(0);
            }
        }
        fclose(f);
    }
    closedir(dir);
}
