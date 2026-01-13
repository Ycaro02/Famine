#include "../libft.h"

/**
 * @brief Check if the size of a struct is the same as the wanted size
 * @param str_test name of the struct
 * @param struct_size size of the struct
 * @param wanted_size wanted size of the struct
*/
void check_struct_size(char *str_test, u32 struct_size, u32 wanted_size)
{
	if (struct_size == wanted_size) {
		ft_printf_fd(1, GREEN"sizeof(%s) == %u)\n"RESET, str_test, wanted_size);
	} else {
		ft_printf_fd(1, RED"sizeof(%s) != %u)\n"RESET, str_test, wanted_size);
	}
}
