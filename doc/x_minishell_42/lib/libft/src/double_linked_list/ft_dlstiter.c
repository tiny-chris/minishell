/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 09:34:01 by cvidon            #+#    #+#             */
/*   Updated: 2022/04/23 09:37:58 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	t_dlist	*cpy;

	cpy = lst;
	if (!lst || !f)
		return ;
	while (cpy)
	{
		f(cpy->content);
		cpy = cpy->next;
	}
}
