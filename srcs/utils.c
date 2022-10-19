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

/*	<SUMMARY> Deletes char ** depending on the given type:
**	- if type == TAB_STR2: only the char ** (and not char *)
**	- if type == TAB_STRS/else: deletes char ** AND char*
*/

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

void	*ft_free_tabstr2(char **tab_str, int type)
{
	int	i;

	i = 0;
	if (tab_str != NULL)
	{
		if (type != TAB_STR2)
		{
			while (tab_str[i])
			{
				free(tab_str[i]);
				tab_str[i] = NULL;
				i++;
			}
		}
		free(tab_str);
		tab_str = NULL;
	}
	return (NULL);
}

void	*ft_free_tabstr_bin(char **tab_str, int type)
{
	int	i;

	i = 0;
	if (tab_str != NULL)
	{
		if (type != TAB_STR2)
		{
			while (tab_str[i])
			{
				if (tab_str[i])
					ft_handle_malloc(DELONE, tab_str[i], 0, NULL);
				i++;
			}
		}
		ft_handle_malloc(DELONE, tab_str, 0, NULL);
	}
	return (NULL);
}
