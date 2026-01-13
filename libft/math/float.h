/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:15:06 by nfour             #+#    #+#             */
/*   Updated: 2024/12/09 19:06:09 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLOAT_HEADER_H
#define FT_FLOAT_HEADER_H 1

#include "ft_math.h"

/* Check float eqauel without epsilon */
FT_INLINE s8 float_equal(float a, float b) {
	return (fabs(a - b) < FT_EPSILON);
}

FT_INLINE s8 float_greater(float a, float b) {
	return (a - b > FT_EPSILON);
}

FT_INLINE s8 float_less(float a, float b) {
	return (a - b < -FT_EPSILON);
}

FT_INLINE s8 float_greater_equal(float a, float b) {
	return (a - b > -FT_EPSILON);
}

FT_INLINE s8 float_less_equal(float a, float b) {
	return (a - b < FT_EPSILON);
}

/* Convert degres to radian  */
FT_INLINE float deg_to_rad(float deg) {
	return (float)(deg * (float)FT_PI / 180.0f);
}

/* Convert radian to degres */
FT_INLINE float rad_to_deg(float rad) {
	return (float)(rad * 180.0f / (float)FT_PI);
}

#endif /* FT_FLOAT_HEADER_H */