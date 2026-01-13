/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_template.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:07 by nfour             #+#    #+#             */
/*   Updated: 2024/05/12 12:15:44 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TEMPLATE_HEADER
#define VECTOR_TEMPLATE_HEADER 1

#include "ft_math.h"

/*
 *	This header file provides macros and structures for handling 2D, 3D, and 4D vectors of various data types.
 *	Here's a simplified explanation:
 *	The header file defines structures and macros to work with 2D, 3D, and 4D vectors of various data types,
 *	including unsigned integers (u8, u16, u32, u64), signed integers (s8, s16, s32, s64), and floating point numbers (float, double).
 *	The macros provide functionalities like creating vectors, performing arithmetic operations:
 *	(addition, subtraction, multiplication, division), and displaying vectors.
 *	This header file simplifies the process of working with 2D, 3D, and 4D vectors of different data types,
 *	offering a consistent interface for vector operations across different data types.
 */

#define DEFINE_VECTOR_STRUCT(type, nb) typedef type vec##nb##_##type[nb];

/* Define vec structure for unsigned int*/
DEFINE_VECTOR_STRUCT(u8, 2)
DEFINE_VECTOR_STRUCT(u8, 3)
DEFINE_VECTOR_STRUCT(u8, 4)

DEFINE_VECTOR_STRUCT(u16, 2)
DEFINE_VECTOR_STRUCT(u16, 3)
DEFINE_VECTOR_STRUCT(u16, 4)

DEFINE_VECTOR_STRUCT(u32, 2)
DEFINE_VECTOR_STRUCT(u32, 3)
DEFINE_VECTOR_STRUCT(u32, 4)

DEFINE_VECTOR_STRUCT(u64, 2)
DEFINE_VECTOR_STRUCT(u64, 3)
DEFINE_VECTOR_STRUCT(u64, 4)

/* Define vec structure for signed int*/
DEFINE_VECTOR_STRUCT(s8, 2)
DEFINE_VECTOR_STRUCT(s8, 3)
DEFINE_VECTOR_STRUCT(s8, 4)

DEFINE_VECTOR_STRUCT(s16, 2)
DEFINE_VECTOR_STRUCT(s16, 3)
DEFINE_VECTOR_STRUCT(s16, 4)

DEFINE_VECTOR_STRUCT(s32, 2)
DEFINE_VECTOR_STRUCT(s32, 3)
DEFINE_VECTOR_STRUCT(s32, 4)

DEFINE_VECTOR_STRUCT(s64, 2) 
DEFINE_VECTOR_STRUCT(s64, 3) 
DEFINE_VECTOR_STRUCT(s64, 4) 

/* Define vec float structure */
DEFINE_VECTOR_STRUCT(f32, 2)
DEFINE_VECTOR_STRUCT(f32, 3)
DEFINE_VECTOR_STRUCT(f32, 4)

/* Define vec double structure */
DEFINE_VECTOR_STRUCT(f64, 2)
DEFINE_VECTOR_STRUCT(f64, 3)
DEFINE_VECTOR_STRUCT(f64, 4)

/**
 * @brief Copy vector
 * @param dest Destination vector
 * @param src Source vector
 * @param size Size of vector (type * nb_field)
*/
FT_INLINE void ft_vec_copy(void *dest, void *src, u32 size) {
	ft_memcpy(dest, src, size);
}

/**
 * @brief Zero vector
 * @param vec Vector to zero
 * @param size Size of vector (type * nb_field)
*/
FT_INLINE void ft_vec_zero(void *vec, u32 size) {
	ft_bzero(vec, size);
}

#define CREATE_VEC2(x_val, y_val, vec)					{vec[0] = x_val; vec[1] = y_val} 
#define CREATE_VEC3(x_val, y_val, z_val, vec)			{vec[0] = x_val; vec[1] = y_val; vec[2] = z_val;}
#define CREATE_VEC4(x_val, y_val, z_val, w_val, vec)	{vec[0] = x_val; vec[1] = y_val; vec[2] = z_val; vec[3] = w_val;}


/**
 * @brief Add two vectors
 * @param type Type of vector
 * @param nb_field Size of vector (nb_field)
 * @param a First vector [output]
 * @param b Second vector
*/
#define VECTOR_ADD(type, nb_field, a, b) \
{ \
	u32 idx = 0; \
	while (idx < nb_field) { \
		((type *)a)[idx] += ((type *)b)[idx]; \
		++idx; \
	} \
}

/**
 * @brief Subtract two vectors
 * @param type Type of vector
 * @param nb_field Size of vector (nb_field)
 * @param a First vector [output]
 * @param b Second vector
*/
#define VECTOR_SUB(type, nb_field, a, b) \
{ \
	u32 idx = 0; \
	while (idx < nb_field) { \
		((type *)a)[idx] -= ((type *)b)[idx]; \
		++idx; \
	} \
}

/**
 * @brief Multiply two vectors
 * @param type Type of vector
 * @param nb_field Size of vector (nb_field)
 * @param a First vector [output]
 * @param b Second vector
*/
#define VECTOR_MUL(type, nb_field, a, b) \
{ \
	u32 idx = 0; \
	while (idx < nb_field) { \
		((type *)a)[idx] *= ((type *)b)[idx]; \
		++idx; \
	} \
}

/**
 * @brief Divide two vectors
 * @param type Type of vector
 * @param nb_field Size of vector (nb_field)
 * @param a First vector [output]
 * @param b Second vector
*/
#define VECTOR_DIV(type, nb_field, a, b) \
{ \
	u32 idx = 0; \
	while (idx < nb_field) { \
		((type *)a)[idx] /= ((type *)b)[idx]; \
		++idx; \
	} \
}


/**
 * @brief Display float vector
 * @param nb_field Size of vector (nb_field)
 * @param vec Vector to display
*/
#define VECTOR_FLOAT_DISPLAY(nb_field, vec) \
{ \
	u32 idx = 0; \
	ft_printf_fd(1, "vec float: "); \
	while (idx < nb_field) { \
		ft_printf_fd(1, "%f, ", vec[idx]); \
		++idx; \
	} \
	ft_printf_fd(1, "\n"); \
}

/**
 * @brief Display int vector
 * @param nb_field Size of vector (nb_field)
 * @param vec Vector to display
*/
#define VECTOR_INT_DISPLAY(nb_field, vec) \
{ \
	u32 idx = 0; \
	ft_printf_fd(1, "vec int: "); \
	while (idx < nb_field) { \
		ft_printf_fd(1, "%d, ", vec[idx]); \
		++idx; \
	} \
	ft_printf_fd(1, "\n"); \
}

/**
 * @brief Display unsigned int vector
 * @param nb_field Size of vector (nb_field)
 * @param vec Vector to display
*/
#define VECTOR_UINT_DISPLAY(nb_field, vec) \
{ \
	u32 idx = 0; \
	ft_printf_fd(1, "vec uint: "ORANGE); \
	while (idx < nb_field) { \
		ft_printf_fd(1, "%u, ", vec[idx]); \
		++idx; \
	} \
	ft_printf_fd(1, RESET"\n"); \
}

#endif /* VECTOR_TEMPLATE_HEADER */