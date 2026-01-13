/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:26 by nfour             #+#    #+#             */
/*   Updated: 2024/04/16 10:21:11 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_VECTOR2_HEADER
#define DEFINE_VECTOR2_HEADER

#include "ft_math.h"

/*
 *	This header file provides macros and structures for handling 2D vectors of various data types.
 *	Here's a simplified explanation:
 *	The header file defines structures and macros to work with 2D vectors of various data types,
 *	including unsigned integers (u8, u16, u32, u64), signed integers (s8, s16, s32, s64), and floats (float).
 *	The macros provide functionalities like creating vectors, performing arithmetic operations:
 *	(addition, subtraction, multiplication, division), comparing vectors, and displaying vectors.
 *	The DISPLAY_VEC2 macro intelligently formats the output based on the data type of the vector,
 *	printing appropriate labels and using %u for unsigned integers, %f for floats, and %d for signed integers.
 *	This header file simplifies the process of working with 2D vectors of different data types,
 *	offering a consistent interface for vector operations across different data types
*/

 /********************************************************************
 *                        DATA STRUCTURES                           *
 ********************************************************************/

/*
 *	Data Structures:
 *	Defines a structure t_vec2_type for 2D vectors with x and y components of the specified data type
*/

/* Macro for write 2d point structure */
#define DEFINE_VEC2_STRUCT(type) \
typedef struct s_vec2_##type { \
    type x; \
    type y; \
} t_vec2_##type;

/* Define structure for unsigned int*/
DEFINE_VEC2_STRUCT(u8)
DEFINE_VEC2_STRUCT(u16)
DEFINE_VEC2_STRUCT(u32)
DEFINE_VEC2_STRUCT(u64)

/* Define structure for signed int*/
DEFINE_VEC2_STRUCT(s8)
DEFINE_VEC2_STRUCT(s16)
DEFINE_VEC2_STRUCT(s32)
DEFINE_VEC2_STRUCT(s64)

/* Define float/double structure */
DEFINE_VEC2_STRUCT(float)
DEFINE_VEC2_STRUCT(double)


 /********************************************************************
 *                        MACRO FUNCTION	                         *
 ********************************************************************/

/*
 *	Macros:
 *	DEFINE_VEC2_STRUCT(type): Defines a structure for 2D vectors with the specified data type.
 *	CREATE_VEC2(type, y_val, x_val): Creates a 2D vector of the specified data type with given x and y values.
 *	ADD_VEC2(type, a, b): Adds two 2D vectors of the specified data type.
 *	SUB_VEC2(type, a, b): Subtracts one 2D vector from another of the specified data type.
 *	MULT_VEC2(type, a, b): Multiplies two 2D vectors of the specified data type.
 *	DIV_VEC2(type, a, b): Divides one 2D vector by another of the specified data type.
 *	CMP_VEC2(type, a, b): Compares two 2D vectors of the specified data type.
 *	DISPLAY_VEC2(type, vec): Displays the 2D vector vec with appropriate formatting based on its data type.
*/

/* Macro for create vector */
#define CREATE_VEC2(type, x_val, y_val) ((t_vec2_##type){ .x = x_val, .y = y_val })

/* Macro for add vector */
#define ADD_VEC2(type, a, b) ((t_vec2_##type){ .x = a.x + b.x, .y = a.y + b.y })

/* Macro for sub vector */
#define SUB_VEC2(type, a, b) ((t_vec2_##type){ .x = a.x - b.x, .y = a.y - b.y })

/* Macro for multiply vector */
#define MULT_VEC2(type, a, b) ((t_vec2_##type){ .x = a.x * b.x, .y = a.y * b.y })

/* Macro for divide vector */
#define DIV_VEC2(type, a, b) ((t_vec2_##type){ .x = a.x / b.x, .y = a.y / b.y })

/* Macro for compare two vectors */
#define CMP_VEC2(a, b) (a.y == b.y && a.x == b.x)

/* Macro for display vector */
#define DISPLAY_VEC2(type, vec) \
{ \
    if (__builtin_types_compatible_p(type, u8) || \
        __builtin_types_compatible_p(type, u16) || \
        __builtin_types_compatible_p(type, u32) || \
        __builtin_types_compatible_p(type, u64)) { \
        ft_printf_fd(1, "Unsigned Vec2 x: %u, y: %u\n", vec.x, vec.y); \
    } else if (__builtin_types_compatible_p(type, float)) { \
        ft_printf_fd(1, "Float/Double Vec2 x: %f, y: %f\n", vec.x, vec.y); \
    } else { \
        ft_printf_fd(1, "Signed Vec2 x: %d, y: %d\n", vec.x, vec.y); \
    } \
}

# endif /* DEFINE_VECTOR2_HEADER */
