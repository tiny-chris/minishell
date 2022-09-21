/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:09:32 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/21 04:03:36 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_exec(t_data *data)//, int val_exit)
{
	if (data != NULL)
	{
		if (data->pid != NULL)
			free (data->pid);
		if (data->pipe_fd != NULL)
			ft_free_tabint(data->pipe_fd, data->nb_pipes);
		if (data->s_env_path != NULL)
			ft_free_tabstr(data->s_env_path);
		// if (val_exit != -1)
		// 	data->val_exit = val_exit;
	}
}

void	ft_free_data_child(t_data *data)
{
	if (data->line != NULL)
		free(data->line);
	if (data->prompt != NULL)
		free(data->prompt);
	if (data->env != NULL)
		ft_free_env(&(data->env));
	if (data->str_exit != NULL)
		free(data->str_exit);
	if (data->cmd != NULL)
		ft_free_cmd(&(data->cmd));
	if (data->built_in != NULL)
		ft_free_tabstr(data->built_in);
	if (data->pid != NULL)
		free (data->pid);
	if (data->pipe_fd != NULL)
		ft_free_tabint(data->pipe_fd, data->nb_pipes);
	if (data->env_path != NULL)
		ft_free_env(&(data->env_path));
	if (data->s_env_path != NULL)
		ft_free_tabstr(data->s_env_path);
}

void	ft_close_fd(t_data *data)
{
	t_cmd	*cmd;
	t_token	*token;
	int		i;

	cmd = data->cmd;
	token = NULL;
	i = 0;
	while (cmd)
	{
		token = cmd->tok_redir;
		while (token)
		{
			if (token->fd != -1)
				close(token->fd);
			token = token->next;
		}
		cmd = cmd->next;
	}
	while (i < data->nb_pipes)
	{
		if (data->pipe_fd[i][0] != -1)
			close(data->pipe_fd[i][0]);
		if (data->pipe_fd[i][1] != -1)
			close(data->pipe_fd[i][1]);
		i++;
	}
}

int	ft_msg(int val_exit, char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(msg2, 2);
	ft_putendl_fd(msg3, 2);
	return (val_exit);
}
