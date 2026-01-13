#include "linked_list.h"

/*
	lst_remove_if : iter on list and delete targeted node
			args:
				list: addr of the head of linked list to iter on
				del: function ptr on the free_node function
					args:
						void *: lst content
				condition: function ptr return true for free node
					args:
						void *: node to check
*/
void	ft_lst_remove_if(t_list **list, void *ref, void (*del)(void *), int (*condition)(void *, void *))
{
	t_list	*tmp = NULL;
	t_list	*lst = NULL;

	if (list == NULL)
		return;
	lst = *list;
	if (lst && condition(lst->content, ref) == TRUE) {
		*list = (*list)->next;
		del(lst->content);
		free(lst);
		lst = *list;
	}
	while (lst) {
		if (lst->next && condition(lst->next->content, ref) == TRUE) {
			tmp = lst->next;
			lst->next = lst->next->next;
			del(tmp->content);
			free(tmp);
		}
		else
			lst = lst->next;
	}
}