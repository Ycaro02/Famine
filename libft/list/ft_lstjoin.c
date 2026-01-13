#include "linked_list.h"

t_list *ft_lstjoin(t_list *first, t_list *second)
{
    t_list *current = second;
    while (current) {
        ft_lstadd_back(&first, ft_lstnew(current->content));
        current = current->next;
    }
    ft_lstclear_nodeptr(&second);
    return (first);
}