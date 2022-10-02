/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:06 by cvidon            #+#    #+#             */
/*   Updated: 2021/11/29 15:39:06 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			len;

	ptr = NULL;
	ptr = malloc(count * size);
	if (ptr)
	{
		len = count * size;
		while (len--)
			ptr[len] = 0;
	}
	return (ptr);
}
