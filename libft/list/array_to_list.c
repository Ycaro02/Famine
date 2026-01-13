#include "linked_list.h"

t_list *array_to_list(void *arr, u16 size, u16 size_of_elem) {
	t_list	*lst = NULL;
	void	*node = NULL;

	for (int i = 0; i < size; i++) {
		node = ft_calloc(1, size_of_elem);
		ft_memcpy(node, arr +(i * size_of_elem), size_of_elem);
		ft_lstadd_back(&lst, ft_lstnew(node));
	}
	return (lst);
}
