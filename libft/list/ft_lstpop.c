#include "linked_list.h"

void ft_lstpop(t_list **lst, void (*del)(void *)) {
	t_list *tmp = *lst;

	if (!lst || !(*lst))
		return ;
	*lst = (*lst)->next;
	del(tmp->content);
	free(tmp);
}

