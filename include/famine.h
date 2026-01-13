#ifndef FAMINE_H
#define FAMINE_H

#include <sys/mman.h>
#include <sys/stat.h>
#include "../libft/libft.h"
#include "../include/log.h"

#define SIGNATURE "Famine version 1.0 (c)oded by nfour-kbutor-b\n"
#define SIGNATURE_LEN (sizeof(SIGNATURE))

typedef struct s_elf_file {
	void		*ptr;			/* Pointer to the ELF file */
	u64			size;			/* Size of the ELF file */
	s8			is_64;			/* 64 bits or 32 bits */
	s8			endian;			/* Endianess of the ELF file */
} FamineElfFile;

typedef struct FamineFile {
    char        *name;          /* Name of the section */
    u64         size;          /* Size of the section */
} FamineFile;

/* Famine file handling parse elf and get file structure */
FamineFile  *elf_file_get(char *path);
void        destroy_famine_file(FamineFile *file);

/* Signature injection */
void        inject_signature(FamineFile *elf);
#endif /* FAMINE_H */