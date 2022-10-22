/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_inout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:40:01 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/22 15:33:20 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static int	ft_redir_first_2(t_data *data, t_cmd *cmd, int i)
{
	if (cmd->outfile != 1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(data->pipe_fd[i][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_redirect_first_cmd(t_data *data, t_cmd *cmd, int i)
{
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (-1);
	}
	if (data->nb_pipes > 0)
	{
		if (ft_redir_first_2(data, cmd, i) == -1)
			return (-1);
	}
	else
	{
		if (cmd->outfile != 1)
		{
			if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
				return (-1);
		}
	}
	return (0);
}

static int	ft_redirect_last_cmd(t_data *data, t_cmd *cmd, int i)
{
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(data->pipe_fd[i - 1][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmd->outfile != 1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_redirect_middle_cmd(t_data *data, t_cmd *cmd, int i)
{
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(data->pipe_fd[i - 1][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmd->outfile != 1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(data->pipe_fd[i][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	ft_redirect_inout(t_data *data, t_cmd *cmd, int i)
{
	if (cmd->file_err != 1)
	{
		if (i == 0)
		{
			if (ft_redirect_first_cmd(data, cmd, i) == -1)
				return (-1);
		}
		else if (i > 0 && i == data->nb_pipes)
		{
			if (ft_redirect_last_cmd(data, cmd, i) == -1)
				return (-1);
		}
		else
		{
			if (ft_redirect_middle_cmd(data, cmd, i) == -1)
				return (-1);
		}
	}
	return (0);
}
