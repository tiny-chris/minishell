/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:28:34 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/06 17:33:55 by lmelard          ###   ########.fr       */
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
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			status = 128 + WTERMSIG(status);
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
		if (WTERMSIG(status) == SIGINT)
		{
			status = 128 + WTERMSIG(status);
			write(1, "\n", 1);
		}
		status = EINTR;
	}
	ft_exit_exec(data);
	// i = 3;
	// while (i < 1000)
	// {
	// 	close(i);
	// 	i++;
	// }
	return (status);
}
