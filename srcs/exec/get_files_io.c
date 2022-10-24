/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:12:28 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/24 17:37:13 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static void	ft_redir_outfile(t_data *data, t_cmd *cmd, t_token *tok_redir)
{
	tok_redir = tok_redir->next;
	if (cmd->file_err != 1 && data->sigint_hd != 1)
	{
		tok_redir->fd = open(tok_redir->token, \
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (tok_redir->fd < 0)
		{
			cmd->file_err = 1;
			g_val_exit = ft_msg(errno, tok_redir->token, ": ", strerror(errno));
		}
	}
	else
		tok_redir->fd = -1;
	cmd->outfile = tok_redir->fd;
}

static void	ft_redir_append(t_data *data, t_cmd *cmd, t_token *tok_redir)
{
	tok_redir = tok_redir->next;
	if (cmd->file_err != 1 && data->sigint_hd != 1)
	{
		tok_redir->fd = open(tok_redir->token, \
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (tok_redir->fd < 0)
		{
			cmd->file_err = 1;
			g_val_exit = ft_msg(errno, tok_redir->token, ": ", strerror(errno));
		}
	}
	else
		tok_redir->fd = -1;
	cmd->outfile = tok_redir->fd;
}

static void	ft_redir_infile(t_data *data, t_cmd *cmd, t_token *tok_redir)
{
	tok_redir = tok_redir->next;
	if (cmd->file_err != 1 && data->sigint_hd != 1)
	{
		tok_redir->fd = open(tok_redir->token, O_RDONLY);
		if (tok_redir->fd < 0)
		{
			cmd->file_err = 1;
			g_val_exit = ft_msg(errno, tok_redir->token, ": ", strerror(errno));
		}
	}
	else
		tok_redir->fd = -1;
	cmd->infile = tok_redir->fd;
}

static void	ft_get_files_io_token(t_data *data, t_cmd *cmd, t_token *tok_redir)
{
	while (tok_redir)
	{
		if (tok_redir->type == GREAT)
			ft_redir_outfile(data, cmd, tok_redir);
		else if (tok_redir->type == D_GREAT)
			ft_redir_append(data, cmd, tok_redir);
		else if (tok_redir->type == LESS)
			ft_redir_infile(data, cmd, tok_redir);
		else if (tok_redir->type == D_LESS)
			ft_heredoc(data, data->cmd, tok_redir);
		tok_redir = tok_redir->next;
	}
}

int	ft_get_files_io(t_data *data)
{
	t_cmd	*cmd;
	t_token	*tok_redir;

	cmd = data->cmd;
	tok_redir = NULL;
	while (cmd)
	{
		tok_redir = cmd->tok_redir;
		ft_get_files_io_token(data, cmd, tok_redir);
		cmd = cmd->next;
	}
	return (0);
}
