/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:09:23 by nfour             #+#    #+#             */
/*   Updated: 2022/10/01 18:42:36 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/** safe_reverse_lst
 * Classic reverse lst content
*/
void reverse_lst(t_list **lst)
{
    t_list *prev = NULL, *next = NULL, *current = *lst;

    while (current) {
        next = current->next; /* save next ptr */
        current->next = prev; /* reverse */
        /* move ptr */
        prev = current;
        current = next;
    }
    *lst = prev;
    return ;
}