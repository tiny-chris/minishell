/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:25:45 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/06 17:33:34 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_redirect_inout(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
	{
		if (cmd->infile != 0)
		{
			if (dup2(cmd->infile, STDIN_FILENO) == -1)
				return (-1);
		}
		if (data->nb_pipes > 0)
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
		}
		else
		{
			if (cmd->outfile != 1)
			{
				if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
					return (-1);
			}
		}
	}
	else if (i > 0 && i == data->nb_pipes)
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
	}
	else
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
	}
	return (0);
}

void	ft_child_process(t_data *data, int i)
{
	t_cmd	*cmd;
	int		j;
	int		res;

	cmd = data->cmd;
	j = i;
	while (j > 0)
	{
		cmd = cmd->next;
		j--;
	}
	res = ft_redirect_inout(data, cmd, i);
	ft_close_fd(data);
	if (res == -1)
	{
		ft_exit_exec(data);
		ft_free_data_child(data);
		ft_close_std();
		exit(EXIT_FAILURE);
	}
	if (cmd->token == NULL)
	{
		ft_free_data_child(data);
		ft_close_std();
		exit(EXIT_SUCCESS);
	}
//	dprintf(2, "child %d: res(redirect inout) = %d\n", i, res);
	if (cmd->token->type == BUILTIN)
	{
		dprintf(2, "passe dans les builtin\n");
		g_val_exit = ft_exec_built_in(cmd, data);
		ft_free_data_child(data);
		exit(g_val_exit);// A CORRIGER
	}
	else
	{
		if (cmd->token->type == SP_QUOTES)
		{
			//ft_exit_exec(data);
			res = ft_msg(127, "''", ": ", ERRCMD);
			ft_free_data_child(data);
			ft_close_std();
			exit(res);
		}
		cmd->cmd_opt = ft_init_cmd_opt(cmd, data);
		// printf("cmd_opt = %s\n", cmd->cmd_opt[0]);
		// printf("cmd_opt = %s\n", cmd->cmd_opt[1]);
		if (cmd->cmd_opt == NULL)
		{
			//ft_exit_exec(data);
			res = ft_msg(1, "", "", ERRMAL);
			ft_free_data_child(data);
			ft_close_std();
			exit(res);
		}
	//	printf("cmd->cmd_opt = %s\n", cmd->cmd_opt[0]);
		cmd->cmd_path = ft_find_cmd_path(cmd, data);
		//printf("cmd_path = %s\n", cmd->cmd_path);
		if (!cmd->cmd_path)
		{
			//ft_exit_exec(data);
			res = ft_msg(EXIT_FAILURE, "", "", ERRMAL);
			ft_free_data_child(data);
			ft_close_std();
			exit(res);
		}
		printf("val cmd path = %s\n", cmd->cmd_path);
		if (execve(cmd->cmd_path, cmd->cmd_opt, data->s_env_path) == -1)
		{
			//ft_exit_exec(data);
			res = ft_msg(126, cmd->token->token, ": ", strerror(errno));
			ft_free_data_child(data);
			ft_close_std();
			exit(res);
		}
		ft_close_std();
	}
	ft_close_std();
}
