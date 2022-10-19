/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:09:32 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 21:28:20 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

void	ft_clean_exec(t_data *data)
{
	int	i;

	i = 0;
	if (data != NULL)
	{
		if (data->pid != NULL)
			ft_handle_malloc(DELONE, data->pid, 0, NULL);
		if (data->pipe_fd != NULL)
		{
			i = 0;
			while (i < data->nb_pipes)
			{
				ft_handle_malloc(DELONE, data->pipe_fd[i], 0, NULL);
				i++;
			}
			ft_handle_malloc(DELONE, data->pipe_fd, 0, NULL);
		}
	}
}

int	ft_free_data_child(int res, t_data *data)
{
	(void) data;
	rl_clear_history();
	ft_handle_malloc(0, NULL, 0, NULL);
	ft_close_std();
	return (res);
}

int	ft_msg(int val_exit, char *msg1, char *msg2, char *msg3)
{
	char	*tmp;
	char	*tmp2;
	char	*msg;

	tmp = ft_strjoin(msg1, msg2);
	if (!tmp)
		return (1);
	tmp2 = ft_strjoin(tmp, msg3);
	if (!tmp2)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	msg = ft_strjoin(tmp2, "\n");
	if (!msg)
	{
		free(tmp2);
		return (1);
	}
	free(tmp2);
	ft_putstr_fd(msg, 2);
	free(msg);
	return (val_exit);
}
