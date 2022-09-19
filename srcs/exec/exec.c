/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/19 17:24:30 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect_inout(t_data *data, t_cmd *cmd, int i)
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

char	**ft_init_cmd_opt(t_cmd *cmd, t_data *data)
{
	char	**cmd_opt;
	t_token	*token;
	int		i;

	token = cmd->token;
	i = 0;
	while (token->next)
	{
		token = token->next;
		i++;
	}
	cmd_opt = malloc(sizeof(char *) * (i + 1));
	if (!cmd_opt)
		return (NULL);
	i = 0;
	token = cmd->token->next;
	while (token)
	{
		cmd_opt[i] = ft_strdup(token->token);
		if (!cmd_opt[i])
		{
			ft_free_tabstr(cmd_opt);
			return (NULL);
		}
		i++;
		token = token->next;
	}
	cmd_opt[i] = ft_strdup("\0");
	return (cmd_opt);
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
		ft_exit_exec(data, 1);
		return ;
	}
	if (cmd->token->type == BUILTIN)
		ft_exec_built_in(cmd, data); // A CREER
	else
	{
		if (cmd->token->type == SP_QUOTES)
		{
			ft_exit_exec(data, ft_msg(127, "''", ": ", ERRCMD));
			return ;
		}
		cmd->cmd_opt = ft_init_cmd_opt(cmd, data);
		if (cmd->cmd_opt == NULL)
		{
			ft_exit_exec(data, ft_msg(1, "", "", ERRMAL));
			return ;
		}
		cmd->cmd_path = ft_find_cmd_path(cmd, data);
		if (!cmd->cmd_path)
		{
			ft_exit_exec(data, -1);
			return ;
		}
		data->s_env_path = ft_get_str_env_path(data);
		if (!data->s_env_path)
		{
			ft_exit_exec(data, ft_msg(1, "", "", ERRMAL));
			return ;
		}
		if (execve(cmd->cmd_path, cmd->cmd_opt, data->s_env_path) == -1)
		{
			ft_exit_exec(data, ft_msg(126, cmd->token->token, ": ", strerror(errno)));
			return ;
		}
	}
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
			data->val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
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
