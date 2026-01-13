#include "linked_list.h"

void ft_lstclear_nodeptr(t_list **lst)
{
	t_list	*tmp;
	t_list	*current;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	tmp = current;
	while (tmp != NULL) {
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*lst = NULL;
}