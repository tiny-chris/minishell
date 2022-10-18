/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:21:17 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 22:21:55 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_check_heredoc(t_data *data)
{
	t_cmd	*cmd;
	t_token	*tok_redir;

	cmd = data->cmd;
	if (!cmd)
		return (0);
	tok_redir = cmd->tok_redir;
	while (cmd != NULL)
	{
		if (tok_redir)
		{
			while (tok_redir)
			{
				if (tok_redir->type == D_LESS)
					return (1);
				tok_redir = tok_redir->next;
			}
		}
		cmd = cmd->next;
		if (cmd)
			tok_redir = cmd->tok_redir;
	}
	return (0);
}

int	ft_check_sigint_heredoc(t_data *data)
{
	ft_close_fd(data);
	ft_clean_exec(data);
	write(1, "\n", 1);
	return (g_val_exit);
}

int	ft_no_pipe_no_token(t_data *data)
{
	if (data->cmd->file_err == 1)
		g_val_exit = EXIT_FAILURE;
	else
		g_val_exit = EXIT_SUCCESS;
	ft_close_fd(data);
	ft_clean_exec(data);
	return (g_val_exit);
}
