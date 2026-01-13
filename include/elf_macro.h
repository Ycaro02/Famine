#ifndef _ELF_ENDIAN_H_DECLARE_
# define _ELF_ENDIAN_H_DECLARE_

#include <elf.h>
#include "../libft/basic_define.h"

/* From <byteswap.h> */
/* Swap bytes in 16-bit value.  */
# define SWAP_BYTE_16(x)					\
  ((u16) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))

/* Swap bytes in 32-bit value.  */
# define SWAP_BYTE_32(x)					\
  ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8)	\
   | (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24))

/* Swap bytes in 64-bit value.  */
# define SWAP_BYTE_64(x)			\
  ((((x) & 0xff00000000000000ull) >> 56)	\
   | (((x) & 0x00ff000000000000ull) >> 40)	\
   | (((x) & 0x0000ff0000000000ull) >> 24)	\
   | (((x) & 0x000000ff00000000ull) >> 8)	\
   | (((x) & 0x00000000ff000000ull) << 8)	\
   | (((x) & 0x0000000000ff0000ull) << 24)	\
   | (((x) & 0x000000000000ff00ull) << 40)	\
   | (((x) & 0x00000000000000ffull) << 56))

/** 
 *  @brief Simple detect endian function: https://www.embeddedsoft.net/simple-code-to-find-endianness-in-c
 *	@return (Elf define for LSB, MSB)
*/
FT_INLINE int local_endian_get() {
	int i = 1;
	/* just check value of lower byte */
	return ((*((char *)&i) == 1) ? ELFDATA2LSB : ELFDATA2MSB);
}

/* Start macro parse header ident */
/* Get ELF header field */
# define ELF_HFIELD(ptr, field)		(((Elf64_Ehdr *) ptr)->e_ident[field])
/* Alias to easy call ELF Hfield ptr, class*/
# define ELF_CLASS(ptr)				ELF_HFIELD(ptr, EI_CLASS)
/* is 64 bits format */
# define IS_ELF64(ptr)				ELF_CLASS(ptr) == ELFCLASS64
/* if size == 2 swap 16 bits, else: if size == 4 swap 32 bit, else swap 64*/
# define REVERSE_ENDIAN(x, size)	size == 2 ? SWAP_BYTE_16(x) : ((size == 4 ? SWAP_BYTE_32(x) : SWAP_BYTE_64(x)))
/* if endian = 0 || size data == 1, don't revese, else call reverse endian */
# define READ_DATA(data, endian)	(endian == 0 || sizeof(data) == 1) ? data : REVERSE_ENDIAN(data, sizeof(data))

# endif /* _ELF_ENDIAN_H_DECLARE_ */