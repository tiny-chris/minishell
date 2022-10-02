/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 09:34:17 by cvidon            #+#    #+#             */
/*   Updated: 2022/04/23 10:26:12 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*cpy;
	t_dlist	*new;
	t_dlist	*tmp;

	cpy = lst;
	if (!lst || !f)
		return (NULL);
	new = 0;
	while (cpy)
	{
		tmp = ft_dlstnew((*f)(cpy->content));
		if (!tmp)
		{
			ft_dlstclear(&tmp, del);
			ft_dlstclear(&new, del);
			return (NULL);
		}
		ft_dlstadd_back(&new, tmp);
		cpy = cpy->next;
	}
	return (new);
}
