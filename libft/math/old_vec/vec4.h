/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:13 by nfour             #+#    #+#             */
/*   Updated: 2024/04/16 11:03:41 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_VECTOR4_HEADER
#define DEFINE_VECTOR4_HEADER

#include "ft_math.h"

/*
 *	This header file provides macros and structures for handling 3D vectors of various data types.
 *	Here's a simplified explanation:
 *	The header file defines structures and macros to work with 3D vectors of various data types,
 *	including unsigned integers (u8, u16, u32, u64), signed integers (s8, s16, s32, s64), and floats (float).
 *	The macros provide functionalities like creating vectors, performing arithmetic operations:
 *	(addition, subtraction, multiplication, division), comparing vectors, and displaying vectors.
 *	The DISPLAY_VEC4 macro intelligently formats the output based on the data type of the vector,
 *	printing appropriate labels and using %u for unsigned integers, %f for floats, and %d for signed integers.
 *	This header file simplifies the process of working with 3D vectors of different data types,
 *	offering a consistent interface for vector operations across different data types
*/

 /********************************************************************
 *                        DATA STRUCTURES                           *
 ********************************************************************/

/*
 *	Data Structures:
 *	Defines a structure t_vec4_type for 3D vectors with x and y components of the specified data type
*/

/* Macro for write 3d point structure */
#define DEFINE_VEC4_STRUCT(type) \
typedef struct s_vec4_##type { \
    type x; \
    type y; \
	type z; \
	type w; \
} t_vec4_##type;


/* Define structure for unsigned int*/
DEFINE_VEC4_STRUCT(u8)
DEFINE_VEC4_STRUCT(u16)
DEFINE_VEC4_STRUCT(u32)
DEFINE_VEC4_STRUCT(u64)

/* Define structure for signed int*/
DEFINE_VEC4_STRUCT(s8)
DEFINE_VEC4_STRUCT(s16)
DEFINE_VEC4_STRUCT(s32)
DEFINE_VEC4_STRUCT(s64) 

/* Define float/double structure */
DEFINE_VEC4_STRUCT(float)
DEFINE_VEC4_STRUCT(double)

 /********************************************************************
 *                        MACRO FUNCTION	                         *
 ********************************************************************/

/*
 *	Macros:
 *	DEFINE_VEC4_STRUCT(type): Defines a structure for 3D vectors with the specified data type.
 *	CREATE_VEC4(type, y_val, x_val, z_val): Creates a 3D vector of the specified data type with given x and y values.
 *	ADD_VEC4(type, a, b): Adds two 3D vectors of the specified data type.
 *	SUB_VEC4(type, a, b): Subtracts one 3D vector from another of the specified data type.
 *	MULT_VEC4(type, a, b): Multiplies two 3D vectors of the specified data type.
 *	DIV_VEC4(type, a, b): Divides one 3D vector by another of the specified data type.
 *	CMP_VEC4(type, a, b): Compares two 3D vectors of the specified data type.
 *	DISPLAY_VEC4(type, vec): Displays the 3D vector vec with appropriate formatting based on its data type.
*/

/* Macro for create vector */
#define CREATE_VEC4(type, x_val, y_val, z_val, w_val) ((t_vec4_##type){ .x = x_val, .y = y_val, .z = z_val, .w = w_val})

/* Macro for add vector */
#define ADD_VEC4(type, a, b) ((t_vec4_##type){ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z, .w = a.w + b.w})

/* Macro for sub vector */
#define SUB_VEC4(type, a, b) ((t_vec4_##type){ .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z, .w = a.w - b.w})

/* Macro for multiply vector */
#define MULT_VEC4(type, a, b) ((t_vec4_##type){ .x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z, .w = a.w * b.w})

/* Macro for divide vector */
#define DIV_VEC4(type, a, b) ((t_vec4_##type){ .x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z, .w = a.w / b.w})

/* Macro for compare two vectors */
#define CMP_VEC4(a, b) (a.y == b.y && a.x == b.x && a.z == b.z, a.w == b.w)

/* Macro for display vector */
#define DISPLAY_VEC4(type, vec) \
{ \
    if (__builtin_types_compatible_p(type, u8) || \
        __builtin_types_compatible_p(type, u16) || \
        __builtin_types_compatible_p(type, u32) || \
        __builtin_types_compatible_p(type, u64)) { \
        ft_printf_fd(1, "Unsigned Vec4 x: %u, y: %u, z: %u, w %u\n", vec.x, vec.y, vec.z, vec.w); \
    } else if (__builtin_types_compatible_p(type, float)) { \
        ft_printf_fd(1, "Float/Double Vec4 x: %f, y: %f, z: %f, w: %f\n", vec.x, vec.y, vec.z, vec.w); \
    } else { \
        ft_printf_fd(1, "Signed Vec4 x: %d, y: %d, z: %d\n, w: %d", vec.x, vec.y, vec.z, vec.w); \
    } \
}

# endif /* DEFINE_VECTOR4_HEADER */
