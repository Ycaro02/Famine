
#include <woody.h>
#include <elf_getter.h>

/** 
 * @brief Save data to a file
 * @param data The data to save
 * @param size The size of the data
 */
void file_save(void *data, u64 size) {
	int fd = open("woody", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0) {
		return;
	}
	if (write(fd, data, size) < 0) {
		return;
	}
	close(fd);
	LOG(L_INFO, YELLOW"Save file 'woody' with %lu size\n"RESET, size);
}

/**
 * @brief Compute the size of the new ELF file store in woody
 * @param file The ELF file struct
 * @param payload The payload struct
 * @return The size of the new ELF file
 */
u64 woody_size_compute(ElfFile *file, Payload *payload) {
	u64			size = 0;
	Elf64_Off	off = 0;
	/* Calculate the size of the new ELF file */
	if (file->data_is_last) {
		off = Phdr_offset_get(file->ph_data, file->endian, file->is_64);
		size = off + Phdr_filesz_get(file->ph_data, file->endian, file->is_64) + file->data_diff_sz + payload->code_size;
	} else {
		off = Phdr_offset_get(file->ph_last, file->endian, file->is_64);
		size = off + Phdr_filesz_get(file->ph_last, file->endian, file->is_64) + payload->code_size;
	}
	return (size);
}

// void check_elf_integrity(void *ptr) {
// 	if (ft_strncmp(((char *) ((Elf64_Ehdr *) ptr)->e_ident), ELFMAG, SELFMAG) != 0) {
// 		LOG(L_ERROR, RED"woody_woodpacker: %s: file format not recognized\n"RESET, ((char *) ((Elf64_Ehdr *) ptr)->e_ident), ELFMAG, SELFMAG);
// 	}
// }