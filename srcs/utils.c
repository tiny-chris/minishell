/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:06:37 by marvin            #+#    #+#             */
/*   Updated: 2022/08/18 12:06:37 by marvin           ###   ########.fr       */
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

void	*ft_free_tabstr(char **tab_str)
{
	int	i;

	i = 0;
	if (tab_str != NULL)
	{
		while (tab_str[i])
		{
			free(tab_str[i]);
			i++;
		}
		free(tab_str);
		tab_str = NULL;
	}
	return (NULL);
}

void	*ft_free_tabint(int **tab_int, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab_int[i]);
		i++;
	}
	free(tab_int);
	tab_int = NULL;
	return (NULL);
}
