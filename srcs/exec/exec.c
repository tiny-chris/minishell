/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/19 12:05:58 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_redirect_inout(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
	{
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
		else
		{
			if (dup2(data->pipe_fd[i][1], STDOUT_FILENO) == -1)
				return (-1);
		}
	}
	else if (i == data->nb_pipes)
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

}

int	ft_exec(t_data *data)
{
	int	i;

	data->pipe_fd = ft_init_pipe(data);
	data->pid = ft_init_pid(data);
	ft_get_files_io(data);
	i = 0;
	while (i < (data->nb_pipes + 1))
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			printf("pid error\n"); // modif val_exit free + exit
		else if (data->pid[i] == 0)
			ft_child_process(data, i);
	}
	//data->val_exit = ft_parent_process(data);
	return (0);
}

//Test echo
// int	ft_exec(t_data *data)
// {
// 	t_cmd	*cmd;

// 	cmd = data->cmd;
// 	while (cmd)
// 	{
// 		if (cmd->token->type == BUILTIN && (ft_strncmp(cmd->token->token, "echo", 4) == 0))
// 			printf("%s", ft_echo(cmd, data));
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }
