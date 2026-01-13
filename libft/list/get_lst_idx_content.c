#include "linked_list.h"

/**
 * Basic get file lst content
 * Args:    lst: linked list pointer
 *          index: wanted node index
 * return:  Ptr on wanted lst->content if found, otherwise NULL
*/
void *get_lst_index_content(t_list *lst, int index)
{
    int     i = 0;
    t_list  *current = lst;

    while (current) {
        if (i == index)
            return (current->content);
        ++i;
        current = current->next;
    }
    return (NULL);
}