/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 09:33:43 by cvidon            #+#    #+#             */
/*   Updated: 2022/04/23 10:21:19 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*ptr;

	ptr = *lst;
	while (ptr != NULL)
	{
		*lst = (*lst)->next;
		ft_dlstdelone(ptr, del);
		ptr = *lst;
	}
}
