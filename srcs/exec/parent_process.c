/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:28:34 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/16 19:10:53 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_parent_process(t_data *data)
{
	int		i;
	int		status;

	ft_close_fd(data);
	i = 0;
	while (i < data->nb_pipes + 1)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		if (status == 42)// A TESTER
			ft_free_data_child(1, data);
		status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			status = 128 + WTERMSIG(status);
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			status = 128 + WTERMSIG(status);
			write(1, "\n", 1);
		}
		else
			status = EINTR;
	}
	ft_clean_exec(data);
	return (status);
}

int	ft_parent_exit(t_data *data, int res)
{
	int		i;
	int		status;

	// (void) res;
	ft_close_fd(data);
	i = 0;
	ft_msg(g_val_exit, ERRMSG, "", strerror(g_val_exit));
	while (i < res + 1)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	g_val_exit = ft_free_data_child(1, data);
	return (g_val_exit);
}
