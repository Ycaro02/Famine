# include "linked_list.h" 

void list_sort(t_list **lst, int (*cmp)(void *, void *)) {
	t_list	*current;
	t_list	*next;
	void	*tmp;

	if (!lst || !*lst || !cmp)
		return ;
	current = *lst;
	while (current->next) {
		next = current->next;
		while (next) {
			if (cmp(current->content, next->content) <= 0) {
				tmp = current->content;
				current->content = next->content;
				next->content = tmp;
			}
			next = next->next;
		}
		current = current->next;
	}
}