/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:36:07 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/08 11:37:55 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = (unsigned char)c;
	while (n > 0)
	{
		if (*str == i)
			return (str);
		n--;
		str++;
	}
	return (0);
}
