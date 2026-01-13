#include "../include/elf_macro.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Ehdr/Elf32_Ehdr                           //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/* @brief Get header type  */ 
Elf64_Half Ehdr_type_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_type, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_type, endian));
}

/* @brief Get machine */
Elf64_Half Ehdr_machine_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_machine, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_machine, endian));
}

/* @brief Get version */
Elf64_Word Ehdr_version_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_version, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_version, endian));
}

/* @brief Get addr entry point */
Elf64_Addr Ehdr_entry_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_entry, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_entry, endian));
}

/* @brief Get Program header table file offset */
Elf64_Off Ehdr_phoff_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phoff, endian));
}

/* @brief Get Section header table file offset */
Elf64_Off Ehdr_shoff_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shoff, endian));
}

/* @brief Get Processor-specific flags */
Elf64_Word Ehdr_flags_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_flags, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_flags, endian));
}

/* @brief ELF header size in bytes */
Elf64_Half Ehdr_ehsize_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_ehsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_ehsize, endian));
}

/* @brief Program header table entry size */
Elf64_Half Ehdr_phentsize_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phentsize, endian));
}

/* @brief Program header table entry count */
Elf64_Half Ehdr_phnum_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phnum, endian));
}

/* @brief Section header table entry size */
Elf64_Half Ehdr_shentsize_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shentsize, endian));
}

/* @brief Section header table entry count */
Elf64_Half Ehdr_shnum_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shnum, endian));
}

/* @brief Section header string table index */
Elf64_Half Ehdr_shstrndx_get(void *ptr, s8 endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shstrndx, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shstrndx, endian));
}

/**
 * Setter
*/
void Ehdr_entry_set(void *ptr, s8 endian, Elf64_Addr new_entry) {
	if (IS_ELF64(ptr)) {
		((Elf64_Ehdr *) ptr)->e_entry = READ_DATA(new_entry, endian);
	} else {
		((Elf32_Ehdr *) ptr)->e_entry = READ_DATA(new_entry, endian);
	}
}

void Ehdr_shoff_set(void *ptr, s8 endian, Elf64_Off new_shoff) {
	if (IS_ELF64(ptr)) {
		((Elf64_Ehdr *) ptr)->e_shoff = READ_DATA(new_shoff, endian);
	} else {
		((Elf32_Ehdr *) ptr)->e_shoff = READ_DATA(new_shoff, endian);
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Phdr/Elf32_Phdr                           //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/* @brief get Segment type */
Elf64_Word Phdr_type_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_type, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_type, endian));
}

/* @brief get Segment file offset */
Elf64_Off Phdr_offset_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_offset, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_offset, endian));
}
/* @brief get Segment virtual address */
Elf64_Addr Phdr_vaddr_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_vaddr, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_vaddr, endian));
}
/* @brief get Segment physical address */
Elf64_Addr Phdr_paddr_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_paddr, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_paddr, endian));
}
/* @brief get Segment size in file */
Elf64_Xword Phdr_filesz_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_filesz, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_filesz, endian));
}

/* @brief get Segment size in memory */
Elf64_Xword Phdr_memsz_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_memsz, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_memsz, endian));
}

/* @brief get Segment flags */
Elf64_Word Phdr_flags_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_flags, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_flags, endian));
}

/* @brief get Segment alignment */
Elf64_Xword Phdr_align_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_align, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_align, endian));
}

/**
 * Setter
*/

/* @brief set a new memory size */
void Phdr_memsz_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Xword new_size) {
	if (is_elf64) {
		((Elf64_Phdr *) ptr)->p_memsz = READ_DATA(new_size, endian);
	} else {
		((Elf32_Phdr *) ptr)->p_memsz = READ_DATA(new_size, endian);
	}
}

/* @brief set a new file size */
void Phdr_filesz_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Xword new_size) {
	if (is_elf64) {
		((Elf64_Phdr *) ptr)->p_filesz = READ_DATA(new_size, endian);
	} else {
		((Elf32_Phdr *) ptr)->p_filesz = READ_DATA(new_size, endian);
	}
}

/* @brief Add flags to a program header */
void Phdr_flags_add(void *ptr, s8 endian, s8 is_elf64, Elf64_Word to_add) {
	Elf64_Word curr_flags = Phdr_flags_get(ptr, endian, is_elf64);

	curr_flags |= to_add;
	if (is_elf64) {
		((Elf64_Phdr *) ptr)->p_flags = READ_DATA(curr_flags, endian);
	} else {
		((Elf32_Phdr *) ptr)->p_flags = READ_DATA(curr_flags, endian);
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Shdr/Elf32_Shdr                           //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/**
 * Getter value for section header table (Elf64/32_Shdr) structure array
*/

/* @brief Section name (string tbl index) */
Elf64_Word Shdr_name_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_name, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_name, endian));
}

/* @brief Section type */
Elf64_Word Shdr_type_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_type, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_type, endian));
}

/* @brief Section flags */
Elf64_Xword Shdr_flags_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_flags, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_flags, endian));
}

/* @brief Section virtual address at execution */
Elf64_Addr Shdr_addr_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_addr, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_addr, endian));
}

/* @brief Section file offset */
Elf64_Off Shdr_offset_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_offset, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_offset, endian));
}

/* @brief Section size in bytes */
Elf64_Xword Shdr_size_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_size, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_size, endian));
}

/* @brief Link to another section */
Elf64_Word Shdr_link_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_link, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_link, endian));
}

/* @brief Additional section information */
Elf64_Word Shdr_info_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_info, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_info, endian));
}

/* @brief Section alignment */
Elf64_Xword Shdr_addralign_get(void *ptr, s8 endian, s8 is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_addralign, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_addralign, endian));
}

/* @brief Entry size if section holds table */
Elf64_Xword Shdr_entsize_get(void *ptr, s8 endian, s8 is_elf64)
{
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_entsize, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_entsize, endian));
}

/**
 * Setter value for section header table (Elf64/32_Shdr) structure array
*/

/* @brief Set section offset */

void Shdr_name_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Word new_name) {
	if (is_elf64) {
		((Elf64_Shdr *) ptr)->sh_name = READ_DATA(new_name, endian);
	} else {
		((Elf32_Shdr *) ptr)->sh_name = READ_DATA(new_name, endian);
	}
}

void Shdr_offset_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Off new_offset) {
	if (is_elf64) {
		((Elf64_Shdr *) ptr)->sh_offset = READ_DATA(new_offset, endian);
	} else {
		((Elf32_Shdr *) ptr)->sh_offset = READ_DATA(new_offset, endian);
	}
}

void Shdr_size_set(void *ptr, s8 endian, s8 is_elf64, Elf64_Xword new_size) {
	if (is_elf64) {
		((Elf64_Shdr *) ptr)->sh_size = READ_DATA(new_size, endian);
	} else {
		((Elf32_Shdr *) ptr)->sh_size = READ_DATA(new_size, endian);
	}
}