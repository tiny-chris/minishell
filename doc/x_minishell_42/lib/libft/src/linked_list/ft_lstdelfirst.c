/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 09:44:56 by cvidon            #+#    #+#             */
/*   Updated: 2022/04/23 10:15:42 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** Delete the first Element of a list.
 */

void	ft_lstdelfirst(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	temp = *lst;
	if (!temp)
		return ;
	if (!temp->next)
	{
		ft_lstdelone(temp, del);
		return ;
	}
	*lst = (*lst)->next;
	ft_lstdelone(temp, del);
}
