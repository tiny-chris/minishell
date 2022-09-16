/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:29:39 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/16 10:33:33 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{	
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1 && ft_isinset(s1[i], set) == 1)
		i++;
	if (i != j)
	{
		j--;
		while ((j > i) && ft_isinset(s1[j], set) == 1)
			j--;
	}
	if (j != ft_strlen(s1))
		j++;
	str = ft_substr(s1, i, (j - i));
	if (!str)
		return (NULL);
	return (str);
}
