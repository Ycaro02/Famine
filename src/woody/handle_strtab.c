#include <elf_getter.h>
#include <woody.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Strtab_handling		                          //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/**
 * @brief Check if strtab is valid
 * @param strtab strtab pointer
 * @param end_of_file end of file pointer
 * @return 1 if invalid 0 if valid
*/
static u8 invalid_strtab(char *strtab, void* end_of_file)
{
	while (strtab != end_of_file) {
		if (*strtab == '\0') {
			break;
		}
		++strtab;
	}
	return ((void *)strtab == end_of_file);
}

/** 
 *	@brief Get section header strtab
 *	@param ptr pointer on elf struct
 *	@param endian endian value
 *	@param is_elf64 1 for 64 bits 0 for 32 bits
 *	@return shstrtab pointer
*/
void *shstrtab_get(ElfFile *file, s8 endian, s8 is_elf64, u32 *shstrtab_size)
{
	void		*ptr = file->ptr;
	u16			sh_size = Ehdr_shentsize_get(ptr, endian);
	/* section header ptr, base pointer + section header offset */
	void		*section_header = (ptr + Ehdr_shoff_get(ptr, endian));
	/* section_header_strtab, sectionheader[idx], section header str index */
	Elf64_Half shstrtab_idx = Ehdr_shstrndx_get(ptr, endian);
	if (shstrtab_idx > Ehdr_shnum_get(ptr, endian)) {
		LOG(L_ERROR, "No shstrtab found, bad index %d, max: %d\n", shstrtab_idx, Ehdr_shnum_get(ptr, endian));
		return (NULL);
	}
	void *section_shstrtab = section_header + (sh_size * shstrtab_idx);
	void *shstrtab = ptr + Shdr_offset_get(section_shstrtab, endian, is_elf64);

	if (invalid_strtab(shstrtab, file->ptr + file->size)) {
		LOG(L_ERROR, "Invalid format no valid shstrtab\n");
		return (NULL);
	}
	*shstrtab_size = Shdr_size_get(section_shstrtab, endian, is_elf64);
	return (shstrtab);
}

/**
 * @brief Get the index of the shstrtab section header
 * @param ptr pointer to the elf file
 * @param endian endian value
 * @return index of the shstrtab section
*/
Elf64_Half Shdr_idx_shstrab_get(void *ptr, s8 endian) {
	return (Ehdr_shstrndx_get(ptr, endian));
}

/**
 * @brief Get the index of the strtab section header
 * @param file pointer to the elf file
 * @return index of the strtab section, -1 if not found
*/
int Shdr_idx_strtab_get(ElfFile *file) {
	void *shdr = file->ptr + file->shdr_off;
	u32 size = 0;
	int shnum = Ehdr_shnum_get(file->ptr, file->endian);
	char *shstrtab = shstrtab_get(file, file->endian, file->is_64, &size);

	for (int i = 0; i < shnum; i++) {
		/* here we need to change the section header strtab/shstrtab offset */
		Elf64_Word name_idx = Shdr_name_get(shdr, file->endian, file->is_64); /* need to check idx here, get shstrtab len todo that */
		void *section_name = shstrtab + name_idx;
		if (Shdr_type_get(shdr, file->endian, file->is_64) == SHT_STRTAB) {
			if (ft_strcmp(((char *) section_name), ".strtab") == 0) {
				return (i);
			}
		}
		shdr += Ehdr_shentsize_get(file->ptr, file->endian);
	}
	return (-1);
}

/**
 * @brief Change the size of the strtab section to avoid objdump warning
 * @param woody The WoodyData struct
 * @param f The ELF file struct
 * @param sh_size The size of the section header
 */
static void strtab_size_fix(WoodyData *woody, ElfFile *f, u32 sh_size) {
	int strtab_idx = Shdr_idx_strtab_get(f);
	if (strtab_idx > 0) {
		Elf64_Off shoff = Ehdr_shoff_get(woody->ptr, f->endian);
		void *sh_strtab = woody->ptr + shoff + (sh_size * strtab_idx);
		Shdr_size_set(sh_strtab, f->endian, f->is_64, 0);
	}
}

/**
 * @brief Add the shstrtab and the section header at the end of the file
 * @param f The ELF file struct
 * @param woody The WoodyData struct
 * @param payload The payload struct
 */
void shstrab_woody_add(ElfFile *f, WoodyData *woody, Payload *payload) {
	/* Calculate the offset of the section header */
	Elf64_Off shoff = woody->inject_off + payload->code_size + f->shstrtab->size;
	
	/* Copy the section header string table section */
	ft_memcpy(woody->ptr + woody->inject_off + payload->code_size,
	 f->shstrtab->strtab, f->shstrtab->size);

	/* Copy the section header at the end of file to make objdump working */
	ft_memcpy(woody->ptr + shoff, f->ptr + f->shdr_off, f->total_shsize);

	/* Update the ELF header shoff */
	Ehdr_shoff_set(woody->ptr, f->endian, shoff);

	Elf64_Half	sh_shstrtab_idx = Shdr_idx_shstrab_get(f->ptr, f->endian);
	Elf64_Off	shstrtab_off = woody->inject_off + payload->code_size;
	Elf64_Off	shdr_off = Ehdr_shoff_get(woody->ptr, f->endian);
	u32			sh_size = Ehdr_shentsize_get(woody->ptr, f->endian);


	void *sh_shstrtab = woody->ptr + shdr_off + (sh_size * sh_shstrtab_idx);
	Shdr_offset_set(sh_shstrtab, f->endian, f->is_64, shstrtab_off); 

	/* Fix the size of the strtab to avoid obdump warning */
	strtab_size_fix(woody, f, sh_size);
}
