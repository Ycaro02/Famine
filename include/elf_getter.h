#ifndef _ELF_GETTER_H_DECLARE_
#define _ELF_GETTER_H_DECLARE_

#include <elf.h>
#include "../libft/basic_define.h"
#include "elf_macro.h"

/* elf header getter */
Elf64_Half		Ehdr_type_get(void *ptr, s8 endian);
Elf64_Half		Ehdr_machine_get(void *ptr, s8 endian);
Elf64_Word		Ehdr_version_get(void *ptr, s8 endian);
Elf64_Addr		Ehdr_entry_get(void *ptr, s8 endian);
Elf64_Off		Ehdr_phoff_get(void *ptr, s8 endian);
Elf64_Off		Ehdr_shoff_get(void *ptr, s8 endian);
Elf64_Word		Ehdr_flags_get(void *ptr, s8 endian);
Elf64_Half		Ehdr_ehsize_get(void *ptr, s8 endian);
Elf64_Half		Ehdr_phentsize_get(void *ptr, s8 endian);
Elf64_Half		Ehdr_phnum_get(void *ptr, s8 endian);
Elf64_Half		Ehdr_shentsize_get(void *ptr, s8 endian);
Elf64_Half		Ehdr_shnum_get(void *ptr, s8 endian);
Elf64_Half		Ehdr_shstrndx_get(void *ptr, s8 endian);

/* elf header setter */
void			Ehdr_entry_set(void *ptr, s8 endian, Elf64_Addr new_entry);
void			Ehdr_shoff_set(void *ptr, s8 endian, Elf64_Off new_shoff);

/* program header getter */
Elf64_Word		Phdr_type_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Off		Phdr_offset_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Addr		Phdr_vaddr_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Addr		Phdr_paddr_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Xword		Phdr_filesz_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Xword		Phdr_memsz_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Word		Phdr_flags_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Xword		Phdr_align_get(void *ptr, s8 endian, s8 is_elf64);

/* program header setter */
void			Phdr_filesz_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Word new_size);
void			Phdr_memsz_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Xword new_size);
void			Phdr_flags_add(void *ptr, s8 endian, s8 is_elf64, Elf64_Word to_add);


/* section header getter */
Elf64_Word		Shdr_name_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Word		Shdr_type_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Xword		Shdr_flags_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Addr		Shdr_addr_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Off		Shdr_offset_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Xword		Shdr_size_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Word		Shdr_link_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Word		Shdr_info_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Xword		Shdr_addralign_get(void *ptr, s8 endian, s8 is_elf64);
Elf64_Xword		Shdr_entsize_get(void *ptr, s8 endian, s8 is_elf64);

/* section header setter */
void			Shdr_name_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Word new_name);
void			Shdr_offset_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Off new_offset);
void			Shdr_size_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Xword new_size);


#endif /* _ELF_GETTER_H_DECLARE_ */
