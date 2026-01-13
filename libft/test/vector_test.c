/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:04:07 by nfour             #+#    #+#             */
/*   Updated: 2024/04/18 11:29:09 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void basic_vec2_test()
{
	t_vec2_float vec2_float = CREATE_VEC2(float, 1.0, 2.0);
	t_vec2_float vec2_float2 = CREATE_VEC2(float, 3.0, 4.0);

	t_vec2_float vec2_float_add = ADD_VEC2(float, vec2_float, vec2_float2);
	if (vec2_float_add.x == 4.0 && vec2_float_add.y == 6.0)
		ft_printf_fd(1, GREEN"Addition of vec2_float and vec2_float2 is correct\n"RESET);
	else {
		DISPLAY_VEC2(float, vec2_float_add);
		ft_printf_fd(1, RED"Addition of vec2_float and vec2_float2 is incorrect\n"RESET);
	}

	t_vec2_float vec2_float_sub = SUB_VEC2(float, vec2_float, vec2_float2);
	if (vec2_float_sub.x == -2.0 && vec2_float_sub.y == -2.0)
		ft_printf_fd(1, GREEN"Subtraction of vec2_float and vec2_float2 is correct\n"RESET);
	else {
		DISPLAY_VEC2(float, vec2_float_sub);
		ft_printf_fd(1, RED"Subtraction of vec2_float and vec2_float2 is incorrect\n"RESET);
	}

	t_vec2_float vec2_float_mult = MULT_VEC2(float, vec2_float, vec2_float2);
	if (vec2_float_mult.x == 3.0 && vec2_float_mult.y == 8.0)
		ft_printf_fd(1, GREEN"Multiplication of vec2_float and vec2_float2 is correct\n"RESET);
	else {
		DISPLAY_VEC2(float, vec2_float_mult);
		ft_printf_fd(1, RED"Multiplication of vec2_float and vec2_float2 is incorrect\n"RESET);
	}

	vec2_float = CREATE_VEC2(float, 4.0, 6.0);
	vec2_float2 = CREATE_VEC2(float, 2.0, 2.0);
	t_vec2_float vec2_float_div = DIV_VEC2(float, vec2_float, vec2_float2);	
	if (vec2_float_div.x == 2.0f && vec2_float_div.y == 3.0f)
		ft_printf_fd(1, GREEN"Division of vec2_float and vec2_float2 is correct\n"RESET);
	else {
		DISPLAY_VEC2(float, vec2_float_div);
		ft_printf_fd(1, RED"Division of vec2_float and vec2_float2 is incorrect\n"RESET);
	}

	if (CMP_VEC2(vec2_float, vec2_float))
		ft_printf_fd(1, GREEN"Comparison of vec2_float and vec2_float is correct\n"RESET);
	else
		ft_printf_fd(1, RED"Comparison of vec2_float and vec2_float is incorrect\n"RESET);

	if (CMP_VEC2(vec2_float, vec2_float2))
		ft_printf_fd(1, RED"Comparison of vec2_float and vec2_float2 is incorrect\n"RESET);
	else
		ft_printf_fd(1, GREEN"Comparison of vec2_float and vec2_float2 is correct\n"RESET);

}

static void basic_test_vec3() 
{
	t_vec3_f32 vec3_f32 = CREATE_VEC3(float, 1.0, 2.0, 3.0);
	t_vec3_f32 vec3_f322 = CREATE_VEC3(float, 4.0, 5.0, 6.0);

	t_vec3_f32 vec3_f32_add = ADD_VEC3(float, vec3_f32, vec3_f322);
	if (vec3_f32_add.x == 5.0 && vec3_f32_add.y == 7.0 && vec3_f32_add.z == 9.0)
		ft_printf_fd(1, GREEN"Addition of vec3_f32 and vec3_f322 is correct\n"RESET);
	else {
		ft_printf_fd(1, RED"Addition of vec3_f32 and vec3_f322 is incorrect\n"RESET);
		DISPLAY_VEC3(float, vec3_f32_add);
	}

	t_vec3_f32 vec3_f32_sub = SUB_VEC3(float, vec3_f32, vec3_f322);
	if (vec3_f32_sub.x == -3.0 && vec3_f32_sub.y == -3.0 && vec3_f32_sub.z == -3.0)
		ft_printf_fd(1, GREEN"Subtraction of vec3_f32 and vec3_f322 is correct\n"RESET);
	else {
		ft_printf_fd(1, RED"Subtraction of vec3_f32 and vec3_f322 is incorrect\n"RESET);
		DISPLAY_VEC3(float, vec3_f32_sub);
	}

	t_vec3_f32 vec3_f32_mult = MULT_VEC3(float, vec3_f32, vec3_f322);
	if (vec3_f32_mult.x == 4.0 && vec3_f32_mult.y == 10.0 && vec3_f32_mult.z == 18.0)
		ft_printf_fd(1, GREEN"Multiplication of vec3_f32 and vec3_f322 is correct\n"RESET);
	else {
		ft_printf_fd(1, RED"Multiplication of vec3_f32 and vec3_f322 is incorrect\n"RESET);
		DISPLAY_VEC3(float, vec3_f32_mult);
	}

	vec3_f32 = CREATE_VEC3(float, 4.0, 6.0, 8.0);
	vec3_f322 = CREATE_VEC3(float, 2.0, 2.0, 2.0);
	t_vec3_f32 vec3_f32_div = DIV_VEC3(float, vec3_f32, vec3_f322);
	if (vec3_f32_div.x == 2.0f && vec3_f32_div.y == 3.0f && vec3_f32_div.z == 4.0f)
		ft_printf_fd(1, GREEN"Division of vec3_f32 and vec3_f322 is correct\n"RESET);
	else {
		DISPLAY_VEC3(float, vec3_f32_div);
		ft_printf_fd(1, RED"Division of vec3_f32 and vec3_f322 is incorrect\n"RESET);
	}

	if (CMP_VEC3(vec3_f32, vec3_f32))
		ft_printf_fd(1, GREEN"Comparison of vec3_f32 and vec3_f32 is correct\n"RESET);
	else
		ft_printf_fd(1, RED"Comparison of vec3_f32 and vec3_f32 is incorrect\n"RESET);

	if (CMP_VEC3(vec3_f32, vec3_f322))
		ft_printf_fd(1, RED"Comparison of vec3_f32 and vec3_f322 is incorrect\n"RESET);
	else
		ft_printf_fd(1, GREEN"Comparison of vec3_f32 and vec3_f322 is correct\n"RESET);
}

int main(int argc, char **argv)
{
	basic_vec2_test();
	basic_test_vec3();
	return (0);
}

