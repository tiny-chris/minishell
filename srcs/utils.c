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

/*  Checks if there is a char 'c' is in the defined 'set' string
**	- if yes    --> return 1
**  - if no     --> return 0
*/
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

//


// A DEVELOPPER SELON BESOIN
void	ft_free_strs(char *str1, char *str2, char **str3)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	if (str3)
		ft_free_tabstr(str3);
}

/*	Frees each string of the table char** from the last line to the 1st one
**	and then free the table of strings 
*/
void	*ft_free_tabstr_rev(char **tab_str, int lines)
{
	while (lines >= 0)
	{
		free(tab_str[lines]);
		lines--;
	}
	free(tab_str);
	tab_str = NULL;
	return (NULL);
}