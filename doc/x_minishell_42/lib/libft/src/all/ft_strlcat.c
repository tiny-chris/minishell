/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:40:10 by cvidon            #+#    #+#             */
/*   Updated: 2021/11/29 16:09:01 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	len;

	len = 0;
	while (s[len] && len <= n)
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_len;
	size_t	d_len;
	size_t	offset;

	s_len = ft_strlen(src);
	d_len = ft_strnlen(dst, dstsize);
	offset = d_len;
	if (dstsize < d_len)
		return (s_len + dstsize);
	if (dstsize > d_len)
		while (*src && offset < dstsize - 1)
			dst[offset++] = *src++;
	dst[offset] = '\0';
	return (s_len + d_len);
}
