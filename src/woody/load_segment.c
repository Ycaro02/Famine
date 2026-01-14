#include <elf_getter.h>
#include <woody.h>

/**
 * @brief Check if the segment is a text segment (if it's executable)
 * @param phdr The segment to check
 * @return 1 if the segment is a text segment, 0 otherwise
*/
static u8	is_ph_textment(void *phdr, s8 endian, s8 is_64) {
	return (Phdr_type_get(phdr, endian, is_64) == PT_LOAD && Phdr_flags_get(phdr, endian, is_64) & PF_X);
}

/**
 * @brief Check if the segment is a data segment (if it's writable)
 * @param phdr The segment to check
 * @return 1 if the segment is a data segment, 0 otherwise
*/
static u8	is_ph_datament(void *phdr, s8 endian, s8 is_64) {
	return (Phdr_type_get(phdr, endian, is_64) == PT_LOAD && (Phdr_flags_get(phdr, endian, is_64) & PF_W));
}

/**
 * @brief Check if the segment is a load segment
 * @param phdr The segment to check
 * @return 1 if the segment is a load segment, 0 otherwise
*/
static u8 is_load_segment(void *phdr, s8 endian, s8 is_64) {
	return (Phdr_type_get(phdr, endian, is_64) == PT_LOAD);
}

#include <stdio.h>

/**
 * @brief Display the segment information
 * @param ph The segment to display
 * @param name The name of the segment
 */
void phdr_info_display(void *ph, char *name, s8 is_elf64, s8 endian) {
	if (!ph) {
		LOG(L_INFO, "Segment not found\n");
		return;
	}
	u32 p_type = Phdr_type_get(ph, endian, is_elf64);
	u64 p_vaddr = Phdr_vaddr_get(ph, endian, is_elf64);
	u64 p_offset = Phdr_offset_get(ph, endian, is_elf64);
	u64 p_filesz = Phdr_filesz_get(ph, endian, is_elf64);
	u64 p_memsz = Phdr_memsz_get(ph, endian, is_elf64);
	u32 p_flags = Phdr_flags_get(ph, endian, is_elf64);


	LOG(L_INFO, "---------------------------------------------------------------------------------------------\n");
	LOG(L_INFO, ORANGE"Phdr Name: %s\n"RESET, name);
	LOG(L_INFO, YELLOW"Segment type: %d, vaddr: 0x%p, 0xoffset: %lx, filesz: 0x%lx, memsz: 0x%lx, flags: %x\n"RESET,
	   p_type, (void *)p_vaddr, p_offset, p_filesz, p_memsz, p_flags);
	LOG(L_INFO, "---------------------------------------------------------------------------------------------\n");
}


void shdr_info_display(void *sh, char *name, s8 is_elf64, s8 endian) {
	if (!sh) {
		LOG(L_INFO, "Section not found\n");
		return;
	}
	u32 sh_name = Shdr_name_get(sh, endian, is_elf64);
	u32 sh_type = Shdr_type_get(sh, endian, is_elf64);
	u64 sh_flags = Shdr_flags_get(sh, endian, is_elf64);
	u64 sh_addr = Shdr_addr_get(sh, endian, is_elf64);
	u64 sh_offset = Shdr_offset_get(sh, endian, is_elf64);
	u64 sh_size = Shdr_size_get(sh, endian, is_elf64);
	u32 sh_link = Shdr_link_get(sh, endian, is_elf64);
	u32 sh_info = Shdr_info_get(sh, endian, is_elf64);
	u64 sh_addralign = Shdr_addralign_get(sh, endian, is_elf64);
	u64 sh_entsize = Shdr_entsize_get(sh, endian, is_elf64);

	LOG(L_INFO, "---------------------------------------------------------------------------------------------\n");
	LOG(L_INFO, PINK"Shdr Name: %s\n"RESET, name);
	LOG(L_INFO, YELLOW"Section name: %u, type: %u, flags: 0x%lx, addr: 0x%p, offset: 0x%lx, size: 0x%lx, link: %u, info: %u, addralign: %lu, entsize: %lu\n"RESET,
	   sh_name, sh_type, sh_flags, (void *)sh_addr, sh_offset, sh_size, sh_link, sh_info, sh_addralign, sh_entsize);
	LOG(L_INFO, "---------------------------------------------------------------------------------------------\n");
}


static void* shdr_get(ElfFile *file, char *section_name) {
	void	*section_header = NULL;
	u32		idx = 0;
	u32		shnum = Ehdr_shnum_get(file->ptr, file->endian);
	u32 	shsize = Ehdr_shentsize_get(file->ptr, file->endian);
	char 	*name = NULL;


	section_header = Ehdr_shoff_get(file->ptr, file->endian) + file->ptr;
	while (idx < shnum) {
		if ((section_header + (idx * shsize)) > file->end || section_header + (idx * shsize) < file->ptr) {
			LOG(L_ERROR, RED"Section header offset out of range\n"RESET);
			break;
		}
		name = (char *)file->shstrtab->strtab + Shdr_name_get(section_header + (idx * shsize), file->endian, file->is_64);
		if (ft_strcmp(name, section_name) == 0) {
			LOG(L_DEBUG, GREEN"Section [%s] == [%s] found at index: %u\n"RESET, section_name,name,idx);
			shdr_info_display(section_header + (idx * shsize), name, file->is_64, file->endian);
			
			return (section_header + (idx * shsize));
		}
		idx++;
	}
	LOG(L_ERROR, RED"Section header offset out of range\n"RESET);
	return (NULL);
}

/**
 * @brief Get the offset of a segment (start iterating from the end of the file)
 * @param file The ELF file
 * @param func The function to check the segment
 * @return The segment offset
*/
static void	*phdr_get(ElfFile *file, LoadSegFunc func, s8 start_from_end) {
	void	*program_header = NULL;
	u32		idx = 0;
	u32 	phsize = Ehdr_phentsize_get(file->ptr, file->endian);

	if (start_from_end) {
		idx = Ehdr_phnum_get(file->ptr, file->endian) - 1;
	}


	program_header = Ehdr_phoff_get(file->ptr, file->endian) + file->ptr;
	while ((void *)(program_header + (idx * phsize)) < file->end) {
		if ((program_header + (idx * phsize)) > file->end || program_header + (idx * phsize) < file->ptr) {
			LOG(L_ERROR, RED"Segment offset out of range\n"RESET);
			break;
		}
		if (func(program_header + (idx * phsize), file->endian, file->is_64)) {
			LOG(L_DEBUG, GREEN"Segment found at index: %u\n"RESET, idx);
			return (program_header + (idx * phsize));
		}
		/* Increment or decrement the index */
		start_from_end ? idx-- : idx++;
	}
	LOG(L_ERROR, RED"Segment offset out of range\n"RESET);
	return (NULL);
}

/**
 * @brief Compute the difference between the memory and file size of the data segment
 * @param file The ELF file struct
 * @return The difference between the memory and file size of the data segment
 */
static Elf64_Xword ph_data_diff_size_compute(ElfFile *file) {
	/* If the data segment has a different memory and file size get the difference */
	Elf64_Xword data_memsize = Phdr_memsz_get(file->ph_data, file->endian, file->is_64);
	Elf64_Xword data_filesize = Phdr_filesz_get(file->ph_data, file->endian, file->is_64);
	Elf64_Xword	diff_size = 0;

	if (data_memsize != data_filesize) {
		diff_size = data_memsize - data_filesize;
		if (diff_size < 0) {
			LOG(L_INFO, "Error: Data segment memory size is smaller than file size\n");
			diff_size = 0;
		}
	}
	return (diff_size);
}

/**
 * @brief Load the segments of the ELF file
 * @param file The ELF file
 */
s8 segment_load(ElfFile *file) {
	/* Get the section header */
	file->shdr_off = Ehdr_shoff_get(file->ptr, file->endian);
	
	/* Get the section header array total size */
	file->total_shsize = Ehdr_shnum_get(file->ptr, file->endian) * Ehdr_shentsize_get(file->ptr, file->endian);
	if (!(file->shstrtab = ft_calloc(1, sizeof(Strtab)))) {
		LOG(L_INFO, RED"Error: Can't allocate memory for the shstrtab\n"RESET);
		return (FALSE);
	}

	/* Get the shstrtab */
	file->shstrtab->strtab = shstrtab_get(file, file->endian, file->is_64, &file->shstrtab->size);
	
	/* get the text segment */
	file->text_data->phdr = phdr_get(file, is_ph_textment, FALSE);
	phdr_info_display(file->text_data->phdr, "Text segment", file->is_64, file->endian);
	/* add write permission to the text segment */
	Phdr_flags_add(file->text_data->phdr, file->endian, file->is_64, PF_W);

	/* get the .init section header */
	file->text_data->shdr = shdr_get(file, ".init");

	/* get the offset in phdr and shdr */
	file->text_data->phdr_off = Phdr_offset_get(file->text_data->phdr, file->endian, file->is_64);
	file->text_data->shdr_off = Shdr_offset_get(file->text_data->shdr, file->endian, file->is_64);

	/* get the end segment */
	file->ph_last = phdr_get(file, is_load_segment, TRUE);
	
	/* get the data segment */
	file->ph_data = phdr_get(file, is_ph_datament, TRUE);
	if (!file->ph_data) {
		LOG(L_INFO, "No data segment found data == end\n");
		file->ph_data = file->ph_last;
	} 

	/* Check if the data segment is the last segment */
	file->data_is_last = file->ph_data == file->ph_last;

	if (file->data_is_last) {
		phdr_info_display(file->ph_data, "Data/End segment", file->is_64, file->endian);
		LOG(L_INFO, CYAN"Data segment is the last segment\n"RESET);
	} else {
		LOG(L_INFO, CYAN"Data and End are different\n"RESET);
		phdr_info_display(file->ph_data, "Data segment", file->is_64, file->endian);
		phdr_info_display(file->ph_last, "End segment", file->is_64, file->endian);
	}

	/* Compute the difference between the memory and file size of the data segment */
	file->data_diff_sz = ph_data_diff_size_compute(file);
	return (TRUE);
}

/**
 * @brief Handle the data segment and the last segment data
 * @param file The ELF file
 * @param woody The WoodyData struct
 */
void data_and_last_segment_handling(ElfFile *file, WoodyData *woody) {
		/* Track where the copying process currently is */
	Elf64_Off copy_off = woody->inject_off;

	/* If there is a difference between the segment's memory size and file size */
	if (file->data_diff_sz > 0) {
		/* 
		* If the memory size (p_memsz) is larger than the file size,
		* it means that there are extra uninitialized data like .bss section
		* We need to add update the size of the injected offset to represent the new size
		* we don't need to copy the extra data, we just need to update the size of the data segment
		*/
		woody->inject_off += file->data_diff_sz;
		/* Adjust the data segment pointer to reflect its new location */
		file->ph_data = woody->ptr + (file->ph_data - file->ptr);
		/* Update segment file size to match its memory size	*/
		Phdr_filesz_set(file->ph_data, file->endian, file->is_64, Phdr_memsz_get(file->ph_data, file->endian, file->is_64));
	}

	/* If the data segment is not the last segment, handle the remaining segments */
	if (!file->data_is_last) {
		LOG(L_INFO, RED"Copy last segment\n"RESET);
		/*
		* Calculate the size of the last segment then substract the copy offset
		* to ensure we are only copying the remaining part of the ELF file->
		*/
		Elf64_Off last_seg_size = Phdr_offset_get(file->ph_last, file->endian, file->is_64) \
			+ Phdr_filesz_get(file->ph_last, file->endian, file->is_64) - copy_off;
		LOG(L_INFO, ORANGE"Last segment size: %lu\n"RESET, last_seg_size);
		/* Update injection offset to account for the size of the last segment */
		woody->inject_off += last_seg_size;
		/* Copy the last segment from the original ELF file to the new file */
		ft_memcpy(woody->ptr + woody->inject_off, file->ptr + copy_off, last_seg_size);
	}
	/* Update the last segment pointer to point to its new location in the modified ELF */
	file->ph_last = woody->ptr + (file->ph_last - file->ptr);
}
