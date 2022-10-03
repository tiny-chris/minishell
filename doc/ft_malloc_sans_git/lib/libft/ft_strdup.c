/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:41:32 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/08 12:04:58 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		s1len;

	s1len = ft_strlen(s1);
	str = malloc(sizeof(char) * (s1len + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	return (str);
}
