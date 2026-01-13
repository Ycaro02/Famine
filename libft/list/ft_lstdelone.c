/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:49:46 by nfour             #+#    #+#             */
/*   Updated: 2022/10/01 18:07:38 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*current;

	if (lst == NULL || del == NULL)
		return ;
	current = lst;
	del(current->content);
	free(current);
}
