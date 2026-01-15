#ifndef _WOODY_H_DECLARE_
#define _WOODY_H_DECLARE_

#include <elf.h>				/* Elf64/32 struct */
#include <fcntl.h>				/* open */
#include <sys/stat.h>
#include <sys/mman.h>			/* mmap */
#include "log.h"

/**
 * Elf header
 * Phdr table
 * SECTION
 * Shdr table
 */

/*----------------------------------------------------------------------------------*/
/*								Accepted bonus flag									*/
/*----------------------------------------------------------------------------------*/

typedef enum e_flag {
	FLAG_VERBOSE = 1U << 0,		/* Verbose flag, set log level to L_INFO */
	FLAG_HELP = 1U << 1U,		/* Help flag */
	FLAG_KEY = 1U << 2,			/* Custom key flag */
	FLAG_KEY_SIZE = 1U << 3,	/* Custom key size flag */
	FLAG_COMMAND = 1U << 4,		/* Command flag */
	FLAG_ARG = 1U << 5,			/* Argument flag */
} WoodyFlag;

/*----------------------------------------------------------------------------------*/
/*								Accepted bonus command								*/
/*----------------------------------------------------------------------------------*/

typedef enum e_command {
	CMD_NONE,					/* No command */
	CMD_EXEC,					/* Execute command with the sh interpreter (/bin/sh -c <command>) */
	CMD_CUSTOM_MSG,				/* Display custom message followed by a newline */
} WoodyCmd;


/*----------------------------------------------------------------------------------*/
/*								Structure declaration								*/
/*----------------------------------------------------------------------------------*/

typedef struct s_user_input {
	char 		*path;			/* Path to the file */
	char		*key;			/* Custom key */
	char		*arg;			/* Custom argument */
	u32			key_len;		/* Custom key length */
	u32			flag;			/* App Flag */
	u32			arg_len;		/* Custom argument length */
	WoodyCmd	command;		/* Command to execute */
} UserInput;

typedef struct s_woody_data {
	char		*ptr;			/* Pointer to the data */
	u64			size;			/* Size of the data */
	Elf64_Off	inject_off;		/* Inject code offset */
	Elf64_Off	encrypt_size;	/* Encrypt code offset */
	u8			*encrypt_key;	/* Encrypt key */
} WoodyData;

typedef struct s_payload {
	UserInput	*input;			/* User input */
	u8			*code;			/* The code */
	u8			*encrypt_key;	/* The key */
	u32			key_len;		/* The key length */
	u32			code_size;		/* Size of the code in byte */
} Payload;

typedef struct s_strtab {
	void		*strtab;		/* Pointer to the strtab */
	u32			size;			/* Size of the strtab */
} Strtab;

typedef struct s_text_data {
	void		*phdr; 			/* Pointer to the program header text */
	Elf64_Off	phdr_off;		/* Offset given in the phdr  */
	void		*shdr; 			/* Pointer to the section header (start of .init) */
	Elf64_Off	shdr_off;		/* Offset given in the shdr */
	Elf64_Off	encrypt_off;	/* Offset of the encryption start */
} TextData;

typedef struct s_elf_file {
	void		*ptr;			/* Pointer to the ELF file */
	void		*end;			/* Pointer to the end of the ELF file */
	void		*ph_data;		/* Pointer to the data program header */
	void		*ph_last;		/* Pointer to the last program header loaded (PT_LOAD) */
	TextData	*text_data;		/* Text data struct */
	Strtab		*shstrtab;		/* Section header string table struct */
	u64			size;			/* Size of the ELF file */
	Elf64_Xword	data_diff_sz;	/* Difference between memory and file size of the data segment */
	Elf64_Off	shdr_off;		/* Offset of the section header section */
	u32			total_shsize;	/* Total size of the section header */
	s8			data_is_last;	/* Data segment is the last segment */
	s8			is_64;			/* 64 bits or 32 bits */
	s8			endian;			/* Endianess of the ELF file */
} ElfFile;


/* typedef to function ptr used for find target segment */
typedef u8 (*LoadSegFunc)(void *phdr, s8 endian, s8 is_64);

/*----------------------------------------------------------------------------------*/
/*								ASM declaration										*/
/*----------------------------------------------------------------------------------*/

/**
 * @brief Encrypt the given data with the given key
 * @param data The data to encrypt
 * @param data_len The length of the data
 * @param key The key to use for encryption
 * @param key_len The length of the key
*/
extern void encrypt_data(char *data, u32 data_len, u8 *key, u32 key_len);

/**
 * @brief Decrypt the data, argument are given by replace the associated 
 * offset in the opcode of the function
*/
extern void decrypt_data();

/**
 * @brief Decrypt the data bonus exec version
*/
extern void decrypt_data_exec();

/* Key len default min/max accepted */
#define KEY_LEN				(16U)
#define KEY_LEN_MIN			(16U)
#define KEY_LEN_MAX			(256U)

/* The len of end str and woody str in decrypt func */
#define WOODY_STR_LEN		(14U)
#define END_STR_LEN			(14U)

/* The len of the argument 1 for command or custom string */
#define ARG1_SIZE			(256U)
#define ARG1_ACCEPTED_SIZE	(256U - 16U)

/*----------------------------------------------------------------------------------*/
/*								64 bits offset										*/
/*----------------------------------------------------------------------------------*/

#ifdef WOODY_BONUS
	#define DECRYPT_FUNCTION_64					decrypt_data_exec
	#define DATA_PTR_OFF_64						((u32)16U)
	// exec version
	#define KEY_OFF_64(code_size, klen)			((u32)((code_size) - END_STR_LEN - ARG1_SIZE - klen))
	//exec version
	#define INJECT_JUMP_OFF_64(code_size, klen)	((u32)(code_size - END_STR_LEN - ARG1_SIZE - klen - WOODY_STR_LEN - 4U))
#else
	#define DECRYPT_FUNCTION_64					decrypt_data
	#define DATA_PTR_OFF_64						((u32)17U)
	/* Offset is the end of code size - strlen woody_str - key_len */
	#define KEY_OFF_64(code_size, klen)			((u32)((code_size) - END_STR_LEN - klen))
	/* Offset is the end of code size - strlen woody_str - key_len - jmp_var_len (4u) */
	#define INJECT_JUMP_OFF_64(code_size, klen)	((u32)(code_size - WOODY_STR_LEN - klen - END_STR_LEN - 4U))
#endif

#define DATA_LEN_OFF_64					((u32)(DATA_PTR_OFF_64 + sizeof(u32) + 1))
#define KEY_LEN_OFF_64					((u32)(DATA_LEN_OFF_64 + sizeof(u32) + 1))
#define BOOL_OFF_64						((u32)(KEY_LEN_OFF_64 + sizeof(u32) + 13))

/* Offset where the argument is injected */
#define INJEC_ARG1_OFF_64(code_size)		((u32)(code_size - END_STR_LEN - ARG1_SIZE))

/*----------------------------------------------------------------------------------*/
/*								32 bits offset										*/
/*----------------------------------------------------------------------------------*/

/* The offset of the data and key in the new entry (decrypt_data_32) code */
#define DATA_PTR_OFF_32						((u32)13U)
#define DATA_LEN_OFF_32						((u32)(DATA_PTR_OFF_32 + sizeof(u32) + 1))
#define KEY_LEN_OFF_32						((u32)(DATA_LEN_OFF_32 + sizeof(u32) + 1))
#define BOOL_OFF_32							((u32)(KEY_LEN_OFF_32 + sizeof(u32) + 2))

/* Offset is the end of code size - strlen woody_str - key_len */
#define KEY_OFF_32(code_size, klen)			((u32)((code_size) - ARG1_SIZE - END_STR_LEN - klen))

/* Offset is the end of code size - strlen woody_str - key_len - jmp_var_len (4u) - get_eip label size (4u) */
#define INJECT_JUMP_OFF_32(code_size, klen)	((u32)(code_size - ARG1_SIZE - WOODY_STR_LEN - klen - END_STR_LEN - 4U - 4U))

#define INJEC_ARG1_OFF_32(code_size) INJEC_ARG1_OFF_64(code_size)
/*----------------------------------------------------------------------------------*/
/*								General offset										*/
/*----------------------------------------------------------------------------------*/

/* Macro to abstract the offset between 32 and 64 bits */

/* The offset of the data and key in the new entry (decrypt_data) code */
#define DATA_PTR_OFF(is_64) 					((is_64) ? DATA_PTR_OFF_64 : DATA_PTR_OFF_32)
#define DATA_LEN_OFF(is_64) 					((is_64) ? DATA_LEN_OFF_64 : DATA_LEN_OFF_32)
#define KEY_LEN_OFF(is_64)						((is_64) ? KEY_LEN_OFF_64 : KEY_LEN_OFF_32)
#define KEY_OFF(is_64, code_size, klen)			((is_64) ? KEY_OFF_64(code_size, klen) : KEY_OFF_32(code_size, klen))

/* Offset where the addr of jump to restore the code is injected */
#define INJECT_JUMP_OFF(is_64, code_size, klen)	((is_64) ? INJECT_JUMP_OFF_64(code_size, klen) : INJECT_JUMP_OFF_32(code_size, klen))

/* Offset of the boolean for running command or display custom message */
#define BOOL_OFF(is_64)							((is_64) ? BOOL_OFF_64 : BOOL_OFF_32)

/* Offset where the argument is injected */
#define INJEC_ARG1_OFF(is_64, code_size)		((is_64) ? INJEC_ARG1_OFF_64(code_size) : INJEC_ARG1_OFF_32(code_size))

/*----------------------------------------------------------------------------------*/
/*								woody_woodpacker.c									*/
/*----------------------------------------------------------------------------------*/

s8			woody_woodpacker(UserInput *input);
void		input_destroy(UserInput *input);

/*----------------------------------------------------------------------------------*/
/*								parse_elf_header.c									*/
/*----------------------------------------------------------------------------------*/

ElfFile		*elf_file_get(char *path);
void		elf_file_destroy(ElfFile *file);

/*----------------------------------------------------------------------------------*/
/*								function_to_opcode.c								*/
/*----------------------------------------------------------------------------------*/

u64			function_size_get(void *func_ptr, u8 *to_find, u8 opcode_nb);
void		opcodes_print(uint8_t *opcodes, u64 length, u32 key_len, s8 is_64);
u8			*opcodes_get(void *func_ptr, u64 code_len, u64 total_len);


/*----------------------------------------------------------------------------------*/
/*								load_segment.c										*/
/*----------------------------------------------------------------------------------*/

s8			segment_load(ElfFile *file);
void 		data_and_last_segment_handling(ElfFile *file, WoodyData *woody);
s8          search_interp_phdr(ElfFile *file);

/*----------------------------------------------------------------------------------*/
/*								handle_strtab.c										*/
/*----------------------------------------------------------------------------------*/

void		*shstrtab_get(ElfFile *file, s8 endian, s8 is_elf64, u32 *shstrtab_size);
Elf64_Half	Shdr_idx_shstrab_get(void *ptr, s8 endian);
int			Shdr_idx_strtab_get(ElfFile *file);
void		shstrab_woody_add(ElfFile *f, WoodyData *woody, Payload *payload);

/*----------------------------------------------------------------------------------*/
/*								payload.c											*/
/*----------------------------------------------------------------------------------*/

s8		    inject_payload(ElfFile *f, WoodyData *woody, Payload *payload);
s8			payload_build(Payload *payload, s8 is_64);

/*----------------------------------------------------------------------------------*/
/*								woody_utils.c										*/
/*----------------------------------------------------------------------------------*/

void		file_save(void *data, u64 size);
u64			woody_size_compute(ElfFile *file, Payload *payload);

/*----------------------------------------------------------------------------------*/
/*								encrypy_keygen.c									*/
/*----------------------------------------------------------------------------------*/

u8			*keygen(u32 key_len);
u8			*fill_hexa_buff(char *data, u32 size);

/*----------------------------------------------------------------------------------*/
/*								bonus_init.c										*/
/*----------------------------------------------------------------------------------*/
s8			woody_bonus_init(char **argv, UserInput *input, int argc);

/*----------------------------------------------------------------------------------*/
/*								main.c												*/
/*----------------------------------------------------------------------------------*/
int         process_woody(int argc, char **argv);

#endif /* _WOODY_H_DECLARE_ */