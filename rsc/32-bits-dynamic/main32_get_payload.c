#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>

#include "../../libft/basic_define.h"


extern void decrypt_data_32();


// void opcodes_print(uint8_t *opcodes, u64 length	);

typedef struct s_payload {
	u8 *code;
	u32 code_size;
} Payload;

void formated_output(u64 i, u64 length) {
	if (i < length - 1) {
		printf(", ");
	}
	if ((i + 1) % 10 == 0) {
		printf("\\\n\t");
	}
}

/**
 * @brief Print the opcodes of a function
 * @param opcodes The opcodes
 * @param length The length of the opcodes
 */
void opcodes_print(uint8_t *opcodes, u64 length, u8 format) {
	char *classic_format = "%d\n";
	char *formated_str =  "0x%02x";

	char *f;

	if (format) {
		f = formated_str;
		printf("{ \\\n\t");
	} else {
		f = classic_format;
	}


	for (u64 i = 0; i < length; i++) {
		printf(f, opcodes[i]);
		if (format) {
			formated_output(i, length);
		}
	}

	if (format) {
		printf(" \\\n} \\\n");
	}
}
/** 
 * @brief Get the size of a function
 * @param func_ptr The pointer to the function
 * @param opcode_to_find The opcode to find
 * @param opcode_nb The number of opcode to find
 * @return The size of the function in bytes
 * @note This function will perform a memcmp(current_opcode, to_find, opcode_nb)
 * until it finds the given opcodes pattern
*/
u64 function_size_get(void *func_ptr, u8 *to_find, u8 opcode_nb) {
	u8		*byte_ptr = (u8 *)func_ptr;
	u64		size = 0;

	while (1) {
		if (memcmp(byte_ptr + size, to_find, opcode_nb) == 0) {
			return (size + opcode_nb); // maybe + 1 here
		}
		size++;
	}
	printf("Error: Can't find the end of the function\n");
	return (0);
}

/**
 * @brief Get the opcodes of a function
 * @param func_ptr The pointer to the function
 * @param length The length of the function in bytes
 * @return The allocated opcodes array of the function or NULL if an error occured
 */
u8 *opcodes_get(void *func_ptr, u64 length) {
	u8 *byte_ptr = (u8 *)func_ptr;
	u8 *opcode = NULL;

	opcode = mmap(NULL, 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
	if (opcode == MAP_FAILED) {
		printf("Error: Can't allocate memory for the opcode\n");
		return (NULL);
	}
	bzero(opcode, 4096);

	// memcpy(opcode, op, length);
	memcpy(opcode, byte_ptr, length);
	return (opcode);
}

/**
 * @brief Build the payload
 * @param payload The payload to build
 */
s8 payload_build(Payload *payload, u8 format) {
	// opcode end are the end of the func here is the string declaration in the last label
	// u8 opcode_end[] = {0x2e ,0x2e ,0x2e ,0x2e ,0x57 ,0x4f ,0x4f ,0x44 ,0x59 ,0x2e ,0x2e ,0x2e ,0x2e ,0x0a};
	u8 opcode_end[] = {'.' ,'.' ,'.' ,'.' ,'E' ,'N' ,'D' ,'O' ,'C' ,'.' ,'.' ,'.' ,'.' ,'\n'}; // ...WOODY....\n
	u8 size_opcode_end = sizeof(opcode_end) / sizeof(u8);
	
	payload->code_size = function_size_get(decrypt_data_32, opcode_end, size_opcode_end);
	
	if (!(payload->code = opcodes_get(decrypt_data_32, payload->code_size))) {
		printf("Error: Can't get the opcodes of the function\n");
		return (FALSE);
	}
	opcodes_print(payload->code, payload->code_size, format);
	return (TRUE);
}

int main (int argc, char **argv) {
	Payload payload;
	u8 format = 0;

	if (argc == 2 && argv[1]) {
			if (strcmp(argv[1], "-f") == 0) {
			format = 1;
		} else {
			return (1);
		}
	}

	payload_build(&payload, format);

	return (0);
}


