#include "../../libft/libft.h"
#include "../../include/woody.h"

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
		if (ft_memcmp(byte_ptr + size, to_find, opcode_nb) == 0) {
			return (size + opcode_nb); // maybe + 1 here
		}
		size++;
	}
	return (0);
}

/**
 * @brief Get the opcodes of a function
 * @param func_ptr The pointer to the function
 * @param length The length of the function in bytes
 * @return The allocated opcodes array of the function or NULL if an error occured
 */
u8 *opcodes_get(void *func_ptr, u64 code_len, u64 total_len) {
	u8 *byte_ptr = (u8 *)func_ptr;
	u8 *opcode = NULL;

	if (!(opcode = ft_calloc(total_len, 1))) {
		LOG(L_INFO, "Error: Can't allocate memory for the opcode\n");		
		return (NULL);
	}
	ft_memcpy(opcode, byte_ptr, code_len);
	return (opcode);
}

/**
 * @brief Print the opcodes of a function
 * @param opcodes The opcodes
 * @param length The length of the opcodes
 */
void opcodes_print(uint8_t *opcodes, u64 length, u32 key_len, s8 is_64) {

	u32 current_size = 0;
	u32 line_size_max = 0;
	char *data_size = "data size";
	char *key_size = "key size";
	char *data_ptr = "data ptr";
	char *key_ptr = "key ptr";
	char *str = NULL;


	u32 data_ptr_off = DATA_PTR_OFF(is_64);
	u32 data_len_off = DATA_LEN_OFF(is_64);
	u32 key_len_off = KEY_LEN_OFF(is_64);
	u32 key_off = KEY_OFF(is_64, length, key_len);



	for (u64 i = 0; i < length; i++) {
		if (i == data_ptr_off || i == data_len_off || i == key_off || i == key_len_off) {
			current_size = 0;
			if (i == data_len_off || i == key_len_off) {
				line_size_max = 4;
				str = i == data_len_off ? data_size : key_size;
			} else if (i == data_ptr_off) {
				line_size_max = 4;
				str = data_ptr;
			} else if (i == key_off) {
				line_size_max = key_len;
				str = key_ptr;
			}
			printf(YELLOW"|\nline: %s|", str);
		}
		printf("0x%x ", opcodes[i]);
		current_size++;
		if (current_size >= line_size_max && line_size_max != 0) {
			printf("|\n"RESET);
			line_size_max = 0;
			current_size = 0;
		}
	}
	printf("\n");
}
