/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:51:05 by cvidon            #+#    #+#             */
/*   Updated: 2022/03/18 12:12:38 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy;
	t_list	*new;
	t_list	*tmp;

	cpy = lst;
	if (!lst || !f)
		return (NULL);
	new = 0;
	while (cpy)
	{
		tmp = ft_lstnew((*f)(cpy->content));
		if (!tmp)
		{
			ft_lstclear(&tmp, del);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tmp);
		cpy = cpy->next;
	}
	return (new);
}
