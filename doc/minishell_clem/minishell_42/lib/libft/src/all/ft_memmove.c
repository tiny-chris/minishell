/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:40 by cvidon            #+#    #+#             */
/*   Updated: 2021/11/29 15:39:40 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d > s)
		while (len--)
			d[len] = s[len];
	else if (d < s)
		while (len--)
			*d++ = *s++;
	return (dst);
}
