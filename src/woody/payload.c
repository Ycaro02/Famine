#include <woody.h>
#include <elf_getter.h>
#include <parse_flag.h>
#include <32_bits_payload.h>

/**
 * This is used to get the opcodes of the function dynamically
 * We need to use this hack because the 32 bit function is not linked in the final binary 
 * so we can't get the opcodes of the function at runtime
 * Use as follow:
 * 	run: ./rsc/test_32bit_entry.sh
 * @note This function exist only for the testing purpose,
 * in the final version the 32 bit function is defined in brut array  
*/
u8 *get_optcode32(u32 *opcode_count) {
    char	buffer[1024];
    FILE	*fp = NULL;
    u8		*opcodes = NULL;

	ft_bzero(buffer, sizeof(buffer));
    opcodes = ft_calloc(1024, sizeof(u8));
    if (opcodes == NULL) {
        perror("calloc failed");
        return (NULL);
    }

    fp = popen("./get_opcode32", "r");
    if (!fp) {
        perror("popen failed");
        free(opcodes);
        return (NULL);
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        opcodes[(*opcode_count)++] = (u8)ft_atoi(buffer);
    }

    if (pclose(fp) == -1) {
        perror("pclose failed");
        free(opcodes);
		return (NULL);
    }

    printf("Opcodes: size %u\n", *opcode_count);
    for (size_t i = 0; i < (*opcode_count); i++) {
        printf("0x%02x, ", opcodes[i]);
    }
    printf("\n");
    return (opcodes);
}


s8 load_32_bit_entry(Payload *payload) {
	static u8 opcode32[] = PAYLOAD_32_EXEC;
	u64 		real_len = 0;
	payload->code_size = sizeof(opcode32) / sizeof(u8);
	real_len = payload->code_size - 16U + payload->input->key_len;
	payload->code = ft_calloc(real_len, 1);
	if (payload->code == NULL) {
		LOG(L_INFO, "Error: Can't allocate memory for the opcode\n");
		return (FALSE);
	}
	ft_memcpy(payload->code, opcode32, payload->code_size);
	payload->code_size = real_len;
	return (TRUE);
}

s8 payload_32bits_handling(Payload *payload) {

	#ifdef DYNAMIC_32_BITS_ENTRY
		/* Dynamic load 32 bit */
		LOG(L_INFO, ORANGE"Dynamic load 32 bit\n"RESET);
		if (!(payload->code = get_optcode32(&payload->code_size))) {
			return (FALSE);
		}
	#else
		/* Static load 32 bit (production version) */
		LOG(L_INFO, CYAN"Static load 32 bit\n"RESET);
		if (!load_32_bit_entry(payload)) {
			return (FALSE);
		}
	#endif
	return (TRUE);
}

/**
 * @brief Build the payload
 * @param payload The payload to build
 */
s8 payload_build(Payload *payload, s8 is_64) {
	// opcode end are the end of the func here is the string declaration in the last label
	if (is_64) {
		u8 opcode_end[] = {'.' ,'.' ,'.' ,'.' ,'E' ,'N' ,'D' ,'O' ,'C' ,'.' ,'.' ,'.' ,'.' ,'\n'};
		u8 size_opcode_end = sizeof(opcode_end) / sizeof(u8);
		u64 real_len = 0;

		/* Get the size of the function */
		payload->code_size = function_size_get(DECRYPT_FUNCTION_64, opcode_end, size_opcode_end);
		real_len = payload->code_size - 16U + payload->input->key_len;
		if (!(payload->code = opcodes_get(DECRYPT_FUNCTION_64, payload->code_size, real_len))) {
			LOG(L_INFO, "Error: Can't get the opcodes of the function\n");
			return (FALSE);
		}
		payload->code_size = real_len;
		LOG(L_INFO, "64: Payload code size: %u\n", payload->code_size);
		// opcodes_print(payload->code, payload->code_size, is_64);
		return (TRUE);
	} else {
		if (payload_32bits_handling(payload)) {
			return (TRUE);
		}
	}
	return (FALSE);
}

/**
 * @brief Set the variable for decrypt routine in the injected code
 * @param payload The payload struct
 * @param f The ELF file struct
 * @param woody The WoodyData struct
 * @param base_entry The base entry point of the ELF file
 */
static void payload_setup_info(Payload *payload, ElfFile *f, WoodyData *woody, Elf64_Addr base_entry) {
	/* Set the jump offset */
	char	custom_message[ARG1_ACCEPTED_SIZE] = {0};
	u32		jump_addr = 0;
	u32		injec_jmp_off = INJECT_JUMP_OFF(f->is_64, payload->code_size, payload->input->key_len);
	u32		entry_addr = Ehdr_entry_get(woody->ptr, f->endian);

	/* Set the text start offset */
    u32	text_start = 0 ;

	Elf64_Off diff_off = f->text_data->encrypt_off - f->text_data->phdr_off;

	// opcodes_print(payload->code, payload->code_size, payload->input->key_len, f->is_64);

	if (f->is_64) {
		text_start = Phdr_vaddr_get(f->text_data->phdr, f->endian, f->is_64)
			- (entry_addr + DATA_PTR_OFF(f->is_64) + 4);
	} else { /* is 32 bits */
		text_start = entry_addr + DATA_PTR_OFF(f->is_64) - 2
			- Phdr_vaddr_get(f->text_data->phdr, f->endian, f->is_64) - diff_off;
	}


	/* Calculate the jump offset and update the injected code */
	jump_addr = base_entry - (Ehdr_entry_get(woody->ptr, f->endian) + injec_jmp_off + sizeof(u32));

	// LOG(L_INFO, "base_entry %lu ", base_entry);
	// LOG(L_INFO, "etry get woody %lu ", Ehdr_entry_get(woody->ptr, f->endian));
	
	ft_memcpy(payload->code + injec_jmp_off, &jump_addr, sizeof(u32));
	LOG(L_INFO, PURPLE"Jump back: |%x|\n"RESET, jump_addr);
	
	/* Set the text start, text size and key size in the injected code */
	ft_memcpy(payload->code + DATA_PTR_OFF(f->is_64), &text_start, sizeof(u32));
	ft_memcpy(payload->code + DATA_LEN_OFF(f->is_64), &woody->encrypt_size, sizeof(u32));
	ft_memcpy(payload->code + KEY_LEN_OFF(f->is_64), &payload->input->key_len, sizeof(u32));


	if (has_flag(payload->input->flag, FLAG_COMMAND)) {
		/* Copy the arg1 in custom message buff */
		ft_memcpy(custom_message, payload->input->arg, payload->input->arg_len);
		/* Add a new line at the end of the custom message */
		if (payload->input->command == CMD_CUSTOM_MSG) {
			custom_message[payload->input->arg_len] = '\n';
		}
		/* Set the boolean for the command */
		ft_memcpy(payload->code + BOOL_OFF(f->is_64), &payload->input->command, sizeof(s8));
		ft_memcpy(payload->code + INJEC_ARG1_OFF(f->is_64, payload->code_size), custom_message, ARG1_ACCEPTED_SIZE);
	}

	/* Set the key in the injected code */
	ft_memcpy(payload->code + KEY_OFF(f->is_64, payload->code_size, payload->input->key_len), woody->encrypt_key, payload->input->key_len);

	LOG(L_DEBUG, GREEN"Text start: %x\n"RESET, text_start);
	LOG(L_DEBUG, GREEN"Inject code at offset: %lu\n"RESET, woody->inject_off);

	/* Inject the payload in file */
	ft_memcpy(woody->ptr + woody->inject_off, payload->code, payload->code_size);
	// opcodes_print(payload->code, payload->code_size, payload->input->key_len, f->is_64);
}

/**
 * @brief Inject the payload in the new ELF file
 * @param f The ELF file struct
 * @param woody The WoodyData struct
 * @param payload The payload struct
 */
void inject_payload(ElfFile *f, WoodyData *woody, Payload *payload) {
	/* Save the base entry point */
	Elf64_Addr	base_entry = Ehdr_entry_get(f->ptr, f->endian);
	Elf64_Addr	new_entry = 0;
	

	LOG(L_INFO, GREEN"Injecting payload, key_len: %u\n"RESET, payload->input->key_len);

	/* Calculate initial injection offset based on the end of the data segment */
	woody->inject_off = Phdr_offset_get(f->ph_data, f->endian, f->is_64)
		+ Phdr_filesz_get(f->ph_data, f->endian, f->is_64);

	/* Copy everything up to the end of the data segment from the original ELF file */
	ft_memcpy(woody->ptr, f->ptr, woody->inject_off);

	/* Handle the data segment and the last segment data */
	data_and_last_segment_handling(f, woody);


	new_entry = Phdr_vaddr_get(f->ph_last, f->endian, f->is_64) + Phdr_memsz_get(f->ph_last, f->endian, f->is_64);
	
	/* Update entry here to the end of the last segment (injected code) */
	Ehdr_entry_set(woody->ptr, f->endian, new_entry);

	/* Set the size of the text section to encrypt */
 	woody->encrypt_size	= Phdr_filesz_get(f->text_data->phdr, f->endian, f->is_64);

	/* Set the offset of the text section to encrypt */
	f->text_data->encrypt_off = f->text_data->phdr_off;

	/* Check if the text section offset is valid, if the exec section is starting before the 
	 * .init section , it means that the text section can't be encrypted entirely
	 * cause she contain the elf header, the program header or the INTERP section
	 * To avoir this we store .init section offset in the text_data struct and we use 
	 * the section header to find only the text section and encrypt it
	*/
	if (f->text_data->phdr_off < f->text_data->shdr_off) {
		LOG(L_INFO, RED"Error: Can't encrypt the entire text section\n"RESET);
		woody->encrypt_size = Shdr_size_get(f->text_data->shdr, f->endian, f->is_64);
		f->text_data->encrypt_off = f->text_data->shdr_off;
	}

	/* Setup the payload info */
	payload_setup_info(payload, f, woody, base_entry);

	/* Update last segment size and perm to make it executable */
	Phdr_memsz_set(f->ph_last, f->endian, f->is_64, Phdr_memsz_get(f->ph_last, f->endian, f->is_64) + payload->code_size);
	Phdr_filesz_set(f->ph_last, f->endian, f->is_64, Phdr_filesz_get(f->ph_last, f->endian, f->is_64) + payload->code_size);
	Phdr_flags_add(f->ph_last, f->endian, f->is_64, PF_X);

	/* Add the shstrtab and the section header at the end of the file */
	shstrab_woody_add(f, woody, payload);


	LOG(L_INFO, ORANGE"Start encrypt at offset: %lu, On [%lu] size\n"RESET, f->text_data->encrypt_off, woody->encrypt_size);

	/* Encrypt the text section */
	encrypt_data(woody->ptr + f->text_data->encrypt_off, 
		woody->encrypt_size,
		woody->encrypt_key, payload->input->key_len);

	/* Save the new ELF file */
	file_save(woody->ptr, woody->size);
}