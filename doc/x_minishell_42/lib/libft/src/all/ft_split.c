/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 08:30:16 by cvidon            #+#    #+#             */
/*   Updated: 2021/12/02 14:23:50 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			count++;
			while (*s != c && *(s + 1))
				s++;
		}
		s++;
	}
	return (count);
}

static char	*ft_fill(char const *s, char c)
{
	size_t	size;
	char	*arr;
	int		index;

	size = 0;
	while (s[size] != c && s[size])
		size++;
	arr = malloc(sizeof(char) * (size + 1));
	index = 0;
	while (s[index] != c && s[index])
	{
		arr[index] = s[index];
		index++;
	}
	arr[index] = '\0';
	return (arr);
}

static void	*ft_backfree(char **tab, int i)
{
	while (i + 1)
	{
		free(tab[i]);
		i--;
	}
	free (tab);
	tab = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	if (!s)
		return (NULL);
	i = 0;
	tab = malloc (sizeof(char *) * (ft_count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s != c && *s)
		{
			tab[i] = ft_fill(s, c);
			if (!tab[i])
				return (ft_backfree(tab, i));
			i++;
			while (*s != c && *(s + 1))
				s++;
		}
		s++;
	}
	tab[i] = 0;
	return (tab);
}
