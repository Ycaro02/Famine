/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:13 by nfour             #+#    #+#             */
/*   Updated: 2024/04/18 11:29:09 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_VECTOR3_HEADER
#define DEFINE_VECTOR3_HEADER

#include "ft_math.h"

/*
 *	This header file provides macros and structures for handling 3D vectors of various data types.
 *	Here's a simplified explanation:
 *	The header file defines structures and macros to work with 3D vectors of various data types,
 *	including unsigned integers (u8, u16, u32, u64), signed integers (s8, s16, s32, s64), and floats (float).
 *	The macros provide functionalities like creating vectors, performing arithmetic operations:
 *	(addition, subtraction, multiplication, division), comparing vectors, and displaying vectors.
 *	The DISPLAY_VEC3 macro intelligently formats the output based on the data type of the vector,
 *	printing appropriate labels and using %u for unsigned integers, %f for floats, and %d for signed integers.
 *	This header file simplifies the process of working with 3D vectors of different data types,
 *	offering a consistent interface for vector operations across different data types
*/

 /********************************************************************
 *                        DATA STRUCTURES                           *
 ********************************************************************/

/*
 *	Data Structures:
 *	Defines a structure t_vec3_type for 3D vectors with x and y components of the specified data type
*/

/* Macro for write 3d point structure */
#define DEFINE_VEC3_STRUCT(type) \
typedef struct s_vec3_##type { \
    type x; \
    type y; \
	type z; \
} t_vec3_##type;

/* Define structure for unsigned int*/
DEFINE_VEC3_STRUCT(u8)
DEFINE_VEC3_STRUCT(u16)
DEFINE_VEC3_STRUCT(u32)
DEFINE_VEC3_STRUCT(u64)

/* Define structure for signed int*/
DEFINE_VEC3_STRUCT(s8)
DEFINE_VEC3_STRUCT(s16)
DEFINE_VEC3_STRUCT(s32)
DEFINE_VEC3_STRUCT(s64)

/* Define float/double structure */
DEFINE_VEC3_STRUCT(float)
DEFINE_VEC3_STRUCT(double)

 /********************************************************************
 *                        MACRO FUNCTION	                         *
 ********************************************************************/

/*
 *	Macros:
 *	DEFINE_VEC3_STRUCT(type): Defines a structure for 3D vectors with the specified data type.
 *	CREATE_VEC3(type, y_val, x_val, z_val): Creates a 3D vector of the specified data type with given x and y values.
 *	ADD_VEC3(type, a, b): Adds two 3D vectors of the specified data type.
 *	SUB_VEC3(type, a, b): Subtracts one 3D vector from another of the specified data type.
 *	MULT_VEC3(type, a, b): Multiplies two 3D vectors of the specified data type.
 *	DIV_VEC3(type, a, b): Divides one 3D vector by another of the specified data type.
 *	CMP_VEC3(type, a, b): Compares two 3D vectors of the specified data type.
 *	DISPLAY_VEC3(type, vec): Displays the 3D vector vec with appropriate formatting based on its data type.
*/

/* Macro for create vector */
#define CREATE_VEC3(type, x_val, y_val, z_val) ((t_vec3_##type){ .x = x_val, .y = y_val, .z = z_val})

/* Macro for add vector */
#define ADD_VEC3(type, a, b) ((t_vec3_##type){ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z})

/* Macro for sub vector */
#define SUB_VEC3(type, a, b) ((t_vec3_##type){ .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z})

/* Macro for multiply vector */
#define MULT_VEC3(type, a, b) ((t_vec3_##type){ .x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z})

/* Macro for divide vector */
#define DIV_VEC3(type, a, b) ((t_vec3_##type){ .x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z})

/* Macro for compare two vectors */
#define CMP_VEC3(a, b) (a.y == b.y && a.x == b.x && a.z == b.z)

/* Macro for display vector */
#define DISPLAY_VEC3(type, vec) \
{ \
    if (__builtin_types_compatible_p(type, u8) || \
        __builtin_types_compatible_p(type, u16) || \
        __builtin_types_compatible_p(type, u32) || \
        __builtin_types_compatible_p(type, u64)) { \
        ft_printf_fd(1, "Unsigned Vec3 x: %u, y: %u, z: %u\n", vec.x, vec.y, vec.z); \
    } else if (__builtin_types_compatible_p(type, float)) { \
        ft_printf_fd(1, "Float/Double Vec3 x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z); \
    } else { \
        ft_printf_fd(1, "Signed Vec3 x: %d, y: %d, z: %d\n", vec.x, vec.y, vec.z); \
    } \
}

/* Vec3 float manipulation*/

/* Dot product */
#define VEC3_DOT(type, a, b) (type)((a.x * b.x) + (a.y * b.y) + (a.z * b.z))

/* Dot on same target */
#define VEC3_NORM2(type, a) VEC3_DOT(type, a, a)

/* Vector norm */
#define VEC3_NORM(type, a)  sqrtf(VEC3_NORM2(type, a))


FT_INLINE void vec3_scale(t_vec3_f32 v, float s, t_vec3_f32 *dest) {
  dest->x = v.x * s;
  dest->y = v.y * s;
  dest->z = v.z * s;
}

/* Normalise the v vector */
FT_INLINE void vec3_normalise(t_vec3_f32 *v) {
    float norm = VEC3_NORM(float, ((t_vec3_f32)*v));
    if (norm < FT_EPSILON) {
        *v = CREATE_VEC3(float, 0.0f, 0.0f, 0.0f);
        return;
    }
    vec3_scale(*v, 1.0f / norm, v);
}

/*
    normalise(x) -> norm(x) -> sqrtf(norm2(x)) -> dot(x, x)
*/


# endif /* DEFINE_VECTOR3_HEADER */
