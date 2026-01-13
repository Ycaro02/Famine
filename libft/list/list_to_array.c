#include "linked_list.h"

void	*list_to_array(t_list *lst, u32 lst_size, u32 type_size) 
{
	u32		i = 0;
	void	*array = ft_calloc(type_size, lst_size);

	if (!array) {
		return (NULL);
	}
	for (t_list *current = lst; current; current = current->next) {
		ft_memcpy(array + (i * type_size), current->content, type_size);
		i++;
	}
	return (array);
}
