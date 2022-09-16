/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:21:45 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/14 13:16:52 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	slen;

	i = 0;
	j = 0;
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	while (dst[i] != '\0' && (i < dstsize))
		i++;
	while (src[j] != '\0' && ((i + j) < dstsize - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + slen);
}
