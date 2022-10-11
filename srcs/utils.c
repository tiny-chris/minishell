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
			tab_str[i] = NULL;
			i++;
		}
		free(tab_str);
		tab_str = NULL;
	}
	return (NULL);
}

/*	<SUMMARY> Deletes only the char** (not the char*)
*/
void	*ft_free_tabstr2(char **tab_str)
{
	int	i;

	i = 0;
	if (tab_str == NULL)
		return (NULL);
	free(tab_str);
	tab_str = NULL;
	return (NULL);
}

void	*ft_free_tabint(int **tab_int, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab_int[i]);
		tab_int[i] = NULL;
		i++;
	}
	free(tab_int);
	tab_int = NULL;
	return (NULL);
}

void	*ft_free_tabint2(int **tab_int, int size)
{
	int	i;

	i = 0;
	if (tab_int == NULL)
		return ;
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


void	ft_free_strs(char *str1, char *str2, char *str3)
{
	if (str1 != NULL)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2 != NULL)
	{
		free(str2);
		str2 = NULL;
	}
	if (str3 != NULL)
	{
		free(str3);
		str3 = NULL;
	}
}

void	ft_free_ints(int *t_int1, int *t_int2, int *t_int3)
{
	if (t_int1 != NULL)
	{
		free(t_int1);
		t_int1 = NULL;
	}
	if (t_int2 != NULL)
	{
		free(t_int2);
		t_int2 = NULL;
	}
	if (t_int3 != NULL)
	{
		free(t_int3);
		t_int3 = NULL;
	}
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