/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:52:36 by athirion          #+#    #+#             */
/*   Updated: 2022/07/13 09:53:53 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Free a char 2D array.
 */

void	ft_free_tab(char **tab)
{
	char	**temp;

	if (tab)
	{
		temp = tab;
		while (*tab)
		{
			free(*tab);
			*tab = NULL;
			tab++;
		}
		free(temp);
		temp = NULL;
	}
}

/*
 ** Free and set to NULL.
 */

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	ft_free_all(t_data *data)
{
	int	fd;

	ft_free (data->cwd);
	ft_free (data->oldcwd);
	ft_free_tab (data->cmd_path);
	ft_free_tab (data->envtab);
	ft_clearlist_env (&data->envlist, ft_free);
	ft_clearlist_cmd (&data->cmdlist, ft_free);
	ft_clearlist_exp (&data->explist, ft_free);
	ft_clearlist_red (&data->redlist, ft_free);
	ft_clearlist_tok (&data->toklist, ft_free);
	fd = 3;
	while (fd < OPEN_MAX)
		close (fd++);
}

/*
 ** Print a common error message, clear and exit.
 */

void	ft_exitmsg(t_data *data, char *str)
{
	extern int	g_sig_status;

	if (str && *str)
	{
		g_sig_status = EXIT_FAILURE;
		write(2, "minishell: ", 12);
		write(2, str, ft_strlen (str));
		write(2, " error\n", 7);
	}
	ft_free_all(data);
	rl_clear_history ();
	exit(g_sig_status);
}
