#include "../libft.h"

void display_double_char(char **array)
{
	u32 i = 0;
	while (array[i] != NULL) {
		ft_printf_fd(1, "%s\n", array[i]);
		i++;
	}
}

u32 double_char_size(char **array)
{
	u32 i = 0;

	while (array[i] != NULL) {
		i++;
	}
	return (i);

}

void free_double_char(char **array)
{
		int i = 0;
        
		while (array[i])
        {
			free(array[i]);
			i++;
        }
        free(array);
}