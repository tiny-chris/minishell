/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:01:17 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 22:01:45 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_new_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			if (i == 0 && s[i + 1] == '\0')
				return (1);
			return (i++);
		}
		i++;
	}
	if ((char)c == '\0' && s[i] == '\0')
		return (0);
	return (0);
}

int	ft_new_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == (char)c)
			return (i);
		i--;
	}
	return (0);
}

int	ft_is_in_set(const char *set, char c)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

int	ft_nb_word(char const *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			word++;
			while (str[i] != c && str[i])
				i++;
		}
		while (str[i] && str[i] == c)
			i++;
	}
	return (word);
}
