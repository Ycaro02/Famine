#include "linked_list.h"

/**
 * Basic get file lst content
 * Args:    lst: linked list pointer
 *          cmp: function to compare content (return 0 if equal)
 *          value_to_find: Value to find must be casted to void * and adapted to cmp function
 * return:  Ptr on wanted lst->content if found, otherwise NULL
*/
void *get_lst_node(t_list *lst,  int(*cmp)(void *, void *), void *value_to_find)
{
	t_list *current = lst;

	while (current) {
		if (cmp(current->content, value_to_find) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}