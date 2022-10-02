/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 09:34:24 by cvidon            #+#    #+#             */
/*   Updated: 2022/04/23 10:18:34 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*first;

	first = malloc(sizeof(t_dlist));
	if (!first)
		return (NULL);
	first->content = content;
	first->next = NULL;
	first->prev = NULL;
	return (first);
}
