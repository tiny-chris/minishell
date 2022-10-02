/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelfirst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:25:23 by cvidon            #+#    #+#             */
/*   Updated: 2022/04/23 10:25:23 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** Delete the first Element of a list.
 */

void	ft_dlstdelfirst(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*temp;

	temp = *lst;
	if (!temp)
		return ;
	if (!temp->next)
	{
		ft_dlstdelone(temp, del);
		return ;
	}
	*lst = (*lst)->next;
	(*lst)->prev = NULL;
	ft_dlstdelone(temp, del);
}
