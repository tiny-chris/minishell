/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:40:24 by cvidon            #+#    #+#             */
/*   Updated: 2021/12/01 08:23:38 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_matchset(char c1, const char *set)
{
	while (*set)
	{
		if (c1 == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_allocsize(char const *s1, char const *set)
{
	size_t	len;

	len = 0;
	while (ft_matchset(*s1, set))
		s1++;
	while (s1[len + 1])
		len++;
	while (ft_matchset(s1[len], set))
		len--;
	return (len + 1);
}

static int	ft_shield(char const *s1, char const *set)
{
	if (!s1 || !set)
		return (1);
	while (*s1 && ft_matchset(*s1, set))
		s1++;
	if (*s1 == '\0')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;

	if (ft_shield(s1, set))
		return (ft_strdup(""));
	str = malloc(sizeof(char) * ft_allocsize(s1, set) + 1);
	if (!str)
		return (0);
	i = 0;
	while (ft_matchset(*s1, set))
		s1++;
	while (s1[i + 1])
		i++;
	while (ft_matchset(s1[i], set))
		i--;
	str[i + 1] = '\0';
	while (i)
	{
		str[i] = s1[i];
		i--;
	}
	str[i] = s1[i];
	return (str);
}
