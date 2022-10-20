/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:26:02 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/20 15:31:55 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static void	ft_close_tokfd(t_data *data)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = data->cmd;
	token = NULL;
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
}

static void	ft_close_pipefd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipes)
	{
		if (data->pipe_fd[i][0] != -1)
			close(data->pipe_fd[i][0]);
		if (data->pipe_fd[i][1] != -1)
			close(data->pipe_fd[i][1]);
		i++;
	}
}

void	ft_close_fd(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd)
		ft_close_tokfd(data);
	if (data->pipe_fd)
		ft_close_pipefd(data);
}

void	ft_close_std(void)
{
	if (STDIN_FILENO != -1)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != -1)
		close(STDOUT_FILENO);
	if (STDERR_FILENO != -1)
		close(STDERR_FILENO);
}
