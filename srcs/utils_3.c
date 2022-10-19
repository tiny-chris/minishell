/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:03:31 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 22:04:14 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	*ft_free_tabint2(int **tab_int, int size, int type)
{
	int	i;

	i = 0;
	if (tab_int == NULL)
		return (NULL);
	if (type != TAB_INT2)
	{
		while (i < size)
		{
			free(tab_int[i]);
			tab_int[i] = NULL;
			i++;
		}
	}
	free(tab_int);
	tab_int = NULL;
	return (NULL);
}

void	*ft_free_tabint_bin(int **tab_int, int size, int type)
{
	int	i;

	i = 0;
	if (tab_int == NULL)
		return (NULL);
	if (type != TAB_INT2)
	{
		while (i < size)
		{
			ft_handle_malloc(DELONE, tab_int[i], 0, NULL);
			i++;
		}
	}
	ft_handle_malloc(DELONE, tab_int, 0, NULL);
	return (NULL);
}

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
