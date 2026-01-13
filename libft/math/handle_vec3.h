/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_vec3.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:14:33 by nfour             #+#    #+#             */
/*   Updated: 2024/04/24 12:21:56 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_VEC3_H
#define HANDLE_VEC3_H 1

#include "vector_template.h"

/* Vec3 float manipulation*/

/**
 *	@brief add vec3_f32
 *	@param a first operand vector
 *	@param b second operand vector
 *	@param dest Destination vector
*/
FT_INLINE void vec3_add(vec3_f32 a, vec3_f32 b, vec3_f32 dest) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
}

/**
 *	@brief sub vec3_f32
 *	@param a first operand vector
 *	@param b second operand vector
 *	@param dest Destination vector
*/
FT_INLINE void vec3_sub(vec3_f32 a, vec3_f32 b, vec3_f32 dest) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
}


/**
 *	@brief dot product of vec3
 *	@param a first operand vector
 *	@param b second operand vector
 *	@return dot product
*/
#define VEC3_DOT(a, b) (float)((a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]))

/**
 *	@brief dot product of vec3 and itself
 *	@param a first operand vector
 *	@return dot product
*/
#define VEC3_NORM2(a) VEC3_DOT(a, a)

/**
 *	@brief norm of vec3
 *	@param a vector
 *	@return norm (sqrf of dot product of vector with itself)
*/
#define VEC3_NORM(a)  sqrtf(VEC3_NORM2(a))

/**
 *	@brief scale vec3_f32
 *	@param v vector
 *	@param s scale
 *	@param dest Destination vector
*/
FT_INLINE void vec3_scale(vec3_f32 v, float s, vec3_f32 dest) {
  dest[0] = v[0] * s;
  dest[1] = v[1] * s;
  dest[2] = v[2] * s;
}

/**
 *	@brief scale vec3_f32
 *	@param v vector
 *	@param s scale
*/
FT_INLINE void vec3_normalize(vec3_f32 v) {
    float norm = VEC3_NORM(v);
    if (norm <= FT_EPSILON) {
        ft_vec_zero(v, sizeof(vec3_f32));
        return;
    }
    vec3_scale(v, (1.0f / norm), v);
}

/**
 *	@brief scale vec3_f32
 *	@param v vector
 *	@param dest Destination vector
 *  @param s scale
*/
FT_INLINE void vec3_normalize_to(vec3_f32 v, vec3_f32 dest) {
    float norm = VEC3_NORM(v);
    if (norm <= FT_EPSILON) {
        ft_vec_zero(dest, sizeof(vec3_f32));
        return;
    }
    vec3_scale(v, (1.0f / norm), dest);
}


/**
 * @brief cross product of two vec3
 * @param a[in] first operand vector
 * @param b[in] second operand vector
 * @param dest[out] Destination vector
*/
FT_INLINE void vec3_cross(vec3_f32 a, vec3_f32 b, vec3_f32 dest) {
    dest[0] = a[1] * b[2] - a[2] * b[1];
    dest[1] = a[2] * b[0] - a[0] * b[2];
    dest[2] = a[0] * b[1] - a[1] * b[0];
}


/**
 * @brief Negate a vector
 * @param dest destination vector
 * @param vec vector to negate
*/
FT_INLINE void vec3_negate(vec3_f32 dest, vec3_f32 vec) {
	dest[0] = -vec[0];
	dest[1] = -vec[1];
	dest[2] = -vec[2];
}

#define RED_VEC3F (vec3_f32){1.0f, 0.0f, 0.0f}
#define GREEN_VEC3F (vec3_f32){0.0f, 1.0f, 0.0f}
#define BLUE_VEC3F (vec3_f32){0.0f, 0.0f, 1.0f} 

#endif /* HANDLE_VEC3_H */