/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycaro <ycaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:09:23 by nfour             #+#    #+#             */
/*   Updated: 2024/03/14 16:15:01 by ycaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/* lst clear modular version, give null in del for don't free node */
void	lst_clear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*current;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	tmp = current;
	while (tmp != NULL)
	{
		tmp = current->next;
		if (del) {
			del(current->content);
		}
		free(current);
		current = tmp;
	}
	*lst = NULL;
}


void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*current;

	if (del == NULL || lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	tmp = current;
	while (tmp != NULL)
	{
		tmp = current->next;
		del(current->content);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}
