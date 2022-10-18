/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:01:13 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 22:33:31 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_redirect_builtin(t_cmd *cmd)
{
	cmd->stin = dup(STDIN_FILENO);
	if (cmd->stin == -1)
		return (-1);
	cmd->stout = dup(STDOUT_FILENO);
	if (cmd->stout == -1)
		return (-1);
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmd->outfile != 1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	ft_redirect_std(t_cmd *cmd)
{
	if (dup2(cmd->stin, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(cmd->stout, STDOUT_FILENO) == -1)
		return (-1);
	close(cmd->stin);
	close(cmd->stout);
	return (0);
}

void	ft_handle_ub_fd(t_data *data)
{
	int	res;

	res = -1;
	res = ft_redirect_builtin(data->cmd);
	ft_close_fd(data);
	if (res == -1)
	{
		g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
		ft_redirect_std(data->cmd);
		ft_clean_exec(data);
		exit(g_val_exit);
	}
}

int	ft_unique_builtin(t_data *data)
{
	if (data->cmd->file_err == 1)
			g_val_exit = 1;
	else
	{
		if (data->cmd->tok_redir)
			ft_handle_ub_fd(data);
		g_val_exit = ft_exec_built_in(data->cmd, data, ADD_M);
		if (data->cmd->tok_redir)
		{
			if (ft_redirect_std(data->cmd) == -1)
			{
				g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
				ft_clean_exec(data);
				exit(g_val_exit);
			}
		}
		ft_clean_exec(data);
	}
	return (g_val_exit);
}
