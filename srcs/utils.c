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

#include "../includes/minishell.h"

int	ft_new_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i++);
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
