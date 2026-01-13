/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:15:01 by nfour             #+#    #+#             */
/*   Updated: 2024/12/09 19:05:46 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * Get abs value
*/
u32 abs_diff(u32 a, u32 b)
{
    s64 diff = (s64)a - (s64)b;

    /* if diff < 0 return (diff * -1) else return diff*/
    return (diff < 0 ? (diff * -1) : diff);
}

/**
 * Get max value, return first if ==
*/
u32 max_uint32(u32 a, u32 b)
{
    return (a >= b ? a : b);
}

/**
 * Get min value, return first if ==
*/
u32 min_uint32(u32 a, u32 b)
{
    return (a <= b ? a : b);
}


float percent(float from, float to, float current) 
{
    float div = to - from;
    if (div == 0.0f) {
        return (1.0f);
    }  
    return ((current - from) / div);
}