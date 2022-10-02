/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:35 by cvidon            #+#    #+#             */
/*   Updated: 2021/11/30 17:33:08 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!n)
		return (0);
	if (*str1 != *str2)
		return (*str1 - *str2);
	while (*str1 == *str2 && (n - 1))
	{
		str1++;
		str2++;
		n--;
	}
	if (*str1 != *str2 && n)
		return (*str1 - *str2);
	return (0);
}
