/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:33:12 by lmelard           #+#    #+#             */
/*   Updated: 2022/06/25 20:44:42 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(const char *s, char c)
{
	size_t	w;
	size_t	i;

	w = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			w++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (w);
}

static char	*ft_malloc_str(const char *s, char c)
{
	char		*str;
	size_t		i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	while (i > 0)
	{
		str[i] = s[i];
		i--;
	}
	str[i] = s[i];
	return (str);
}

static void	*ft_free(char **str, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	str = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!str)
		return (NULL);
	j = (ft_wordcount(s, c) + 1);
	i = 0;
	while (*s && i < j)
	{
		while (*s && *s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			str[i] = ft_malloc_str(s, c);
			if (!str[i])
				return (ft_free(str, i));
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (str[i] = 0, str);
}
