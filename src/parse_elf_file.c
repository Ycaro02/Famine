# include <famine.h>
# include <elf_getter.h>

/** 
 *	@brief check if c value is val1 or val 2
 *	@return bool 1 for true otherwise 0 
*/
static int check_identification_byte(char c, int val1, int val2) {
	return ((c == val1 || c == val2));
}

/** 
 *	@brief check if c value is between val1 and val2
 *	@return bool 1 for true otherwise 0 
*/
static int check_range_int8_val(char c, int val1, int val2) {
	return ((c >= val1 && c <= val2));
}

static int detect_os_abi(uint8_t os_abi) {
	/* 0 >= os_abi <= 3 || 0 >= os_abi <= 12 || special os case */
	if (check_range_int8_val(os_abi, ELFOSABI_NONE, ELFOSABI_GNU)\
		|| check_range_int8_val(os_abi, ELFOSABI_SOLARIS, ELFOSABI_OPENBSD)\
		|| check_identification_byte(os_abi, ELFOSABI_ARM_AEABI, ELFOSABI_ARM)\
		|| os_abi == ELFOSABI_STANDALONE) {
		return (os_abi);	
	}
	LOG(L_ERROR, "Unknow os ABI %d\n", os_abi);
	return (-1);
}

/**
 *	@brief Parse header identification field
 *	@param str file name to check
 *	@param elf_struct pointer on elf header struct
*/
static int header_identification_correct(char *str, void *file) {
	/* check magic number ELFMAG */
	if (ft_strncmp(((char *) ((Elf64_Ehdr *) file)->e_ident), ELFMAG, SELFMAG) != 0) {
        // LOG(L_ERROR, "field 0 %d\n", ELF_HFIELD(file, 0));
		LOG(L_ERROR, "Famine: %s: file format not recognized\n", str);
		return (FALSE);
	}
	/* get class 32 or 64 bits */
	char c = ELF_HFIELD(file, EI_CLASS);
	int ret = check_identification_byte(c, ELFCLASS32, ELFCLASS64);
	if (ret == FALSE) {
		LOG(L_ERROR, "Invalid class found: %d\n", c);
		return (ret);
	}
	/* get endian little or big */
	c = ELF_HFIELD(file, EI_DATA);
    ret = check_identification_byte(c, ELFDATA2LSB, ELFDATA2MSB);
	if (ret == FALSE) {
		LOG(L_ERROR, "Invalid endian found: %d\n", c);
		return (ret);
	}
	/* check version must be current version */
	if (((Elf64_Ehdr *) file)->e_ident[EI_VERSION] != EV_CURRENT) {
		LOG(L_ERROR, "Invalid version found: %d\n", ((Elf64_Ehdr *) file)->e_ident[EI_DATA]);
		return (FALSE);
	}
	/* detect os ABI */
	int os_abi = detect_os_abi(ELF_HFIELD(file, EI_OSABI));
	if (os_abi == -1) {
		return (FALSE);
	}

	s8 endian = ELF_HFIELD(file, EI_DATA) - local_endian_get();

	Elf64_Half type = Ehdr_type_get(file, endian);

	if (type != ET_EXEC && type != ET_DYN) {
		LOG(L_ERROR, "Invalid type found: %d\n", type);
		return (FALSE);
	}
	// int abi_version = ELF_HFIELD(file, EI_ABIVERSION);
	// (void)abi_version;
	LOG(L_INFO, GREEN"Valid elf header: %s\n"RESET, ((char *) ((Elf64_Ehdr *) file)->e_ident));
	
	return (TRUE);
}

/**
 * @brief Free the allocated memory of the ELF file
 * @param file The ELF file to free
*/
static void famine_elf_file_destroy(FamineElfFile *file) {
	munmap(file->ptr, file->size);
	free(file);
}

static FamineElfFile *elf_file_struct_init(void *file, u64 size) {
	FamineElfFile *f = NULL;
	
	if ((f = ft_calloc(1, sizeof(FamineElfFile))) == NULL) {
		LOG(L_ERROR, "Can't allocate memory for the ELF file\n");
		return (NULL);
	}
	f->ptr = file;
	f->size = size;

	/**
	 * Get the endianess and the class of the ELF file
	 * The f->endian field is 0 for same endianess and 1 for different endianess
	 * This used in READ_DATA macro to determine if we need to reverse the data
	*/
	f->endian = ELF_HFIELD(f->ptr, EI_DATA) - local_endian_get();
	f->is_64 = IS_ELF64(f->ptr);


	/* Check for bonus version for 32 bits handling */
	#ifndef FAMINE_BONUS
		if (!f->is_64) {
			LOG(L_ERROR, "32 bits ELF file are not supported\n");
			LOG(L_INFO, "Compile with make bonus to enable 32 bits support\n");
			famine_elf_file_destroy(f);
			return (NULL);
		}
	#endif

	return (f);
}

void destroy_famine_file(FamineFile *file) {
    if (file) {
        free(file->name);
        free(file);
    }
}

/** 
 * @brief Load an ELF file
 * @param path The path to the ELF file
 * @param size The size of the ELF file
 * @return The ELF file allocated in memory by mmap
 */
FamineFile *famine_elf_file_get(char *path) {
	FamineElfFile *f = NULL;
	char	*file = NULL;
	int 	fd = -1;
	u64		size = 0;
	
	if ((fd = open(path, O_RDONLY)) < 0) {
		LOG(L_ERROR, "Can't open the file: '%s'\n", path);
		return (NULL);
	}
	size = lseek(fd, 0, SEEK_END);
	if (size <= 0) {
		LOG(L_ERROR, "Can't get the size of the file: '%s'\n", path);
		close(fd);
		return (NULL);
	} else if ((file = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
		LOG(L_ERROR, "Mmap failed file: '%s'\n", path);
		close(fd);
		return (NULL);
	}
	close(fd); /* now we had data in void * we can close fd */
	if (header_identification_correct(path, file) == FALSE) {
		munmap(file, size);
		return (NULL);
	} if (!(f = elf_file_struct_init(file, size))) {
		munmap(file, size);
		return (NULL);
	}

    famine_elf_file_destroy(f);

    FamineFile *ff = ft_calloc(1, sizeof(FamineFile));
    if (!ff) {
        LOG(L_ERROR, "Can't allocate memory for FamineFile\n");
        return (NULL);
    }

    ff->name = ft_strdup(path);
    ff->size = size;
	LOG(L_INFO, YELLOW"ELF file loaded size : %lu\n"RESET, f->size);
	return (ff);
}
