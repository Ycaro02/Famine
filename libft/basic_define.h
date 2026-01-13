/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:03:53 by nfour             #+#    #+#             */
/*   Updated: 2024/08/25 13:57:50 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_DEF_TYPE_HEADER
#define BASIC_DEF_TYPE_HEADER

/* Push from vox */
#include <stdint.h>
#include <sys/types.h>

/********************************************************************
 *                        DEFINE		                            *
 ********************************************************************/
/* bool */
#define		FALSE  	0
#define		TRUE 	1

/* pointer size */
#define		PTR_SIZE	    sizeof(void *)

/* ANSI COLOR */

# ifndef CHESS_WINDOWS_VERSION
#define		RED     			"\x1b[31m"
#define		GREEN   			"\x1b[32m"
#define		YELLOW  			"\x1b[33m"
#define		BLUE    			"\x1b[34m"
#define		PURPLE  			"\x1b[35m"
#define		CYAN    			"\x1b[36m"
#define		PINK    			"\x1b[38;5;200m"
#define		ORANGE  			"\x1b[38;5;208m"
#define		RESET   			"\x1b[0m"
#define		FILL_GREEN			"\033[7;32m"
#define		FILL_YELLOW			"\033[7;33m"
#define		FILL_RED			"\033[7;31m"
#define		FILL_YELBLACK		"\033[40;33m"
# else
#define		RED     			""
#define		GREEN   			""
#define		YELLOW  			""
#define		BLUE    			""
#define		PURPLE  			""
#define		CYAN    			""
#define		PINK    			""
#define		ORANGE  			""
#define		RESET   			""
#define		FILL_GREEN			""
#define		FILL_YELLOW			""
#define		FILL_RED			""
#define		FILL_YELBLACK		""
#endif

#define		RESET_LINE			"\r\033[K"

/* Inline function */
#define		FT_INLINE   static inline __attribute((always_inline))

/* Packed struct */
#define		PACKED_STRUCT __attribute__((packed))

/* Typedef for integet type */
typedef		uint8_t	 	u8;			/* Unsigned int 8 bits */
typedef		uint16_t 	u16;		/* Unsigned int 16 bits */	
typedef		uint32_t 	u32;		/* Unsigned int 32 bits */
typedef		uint64_t 	u64;		/* Unsigned int 64 bits */
typedef		int8_t	 	s8;			/* Signed int 8 bits */
typedef		int16_t	 	s16;		/* Signed int 16 bits */
typedef		int32_t	 	s32;		/* Signed int 32 bits */
typedef		int64_t	 	s64;		/* Signed int 64 bits */

/* Typedef for float type */
typedef		float		f32;		/* Float 32 bits */
typedef		double		f64;		/* Float 64 bits */

/* Macro for min max */
#define		GET_MAX(a, b) ((a) >= (b) ? (a) : (b))
#define		GET_MIN(a, b) ((a) <= (b) ? (a) : (b))

/* Macro for ABS diff */
#define		MINUS_IN_S64(a, b) ((s64)((s64)(a) - (s64)(b)))
#define		INT_ABS_DIFF(a, b) (MINUS_IN_S64(a, b) < 0 ? MINUS_IN_S64(a, b) * -1 : MINUS_IN_S64(a, b))

 #endif /* BASIC_DEF_TYPE_HEADER */
