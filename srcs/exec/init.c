/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:30:46 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/16 18:02:17 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**ft_init_pipe(t_data *data)
{
	int	**tab_int;
	int	i;

	tab_int = (int **) malloc(sizeof(int *) * data->nb_pipes);
	if (tab_int == NULL)
		return (free(tab_int), NULL);
	i = 0;
	while (i < data->nb_pipes)
	{
		tab_int[i] = (int *) malloc(sizeof(int) * 2);
		if (!tab_int[i])
		{
			ft_free_tabint(tab_int, i - 1);
			break ;
		}
		tab_int[i][0] = -1;
		tab_int[i][1] = -1;
		i++;
	}
	return (tab_int);
}

int	*ft_init_pid(t_data *data)
{
	int	*pid;
	int	i;

	i = 0;
	pid = malloc(sizeof(int) * (data->nb_pipes + 1));
	if (!pid)
		return (NULL);//FREE TOUT ET EXIT
	while (i < (data->nb_pipes + 1))
	{
		pid[i] = -1;
		i++;
	}
	return (pid);
}

