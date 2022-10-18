/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:30:46 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/18 23:20:39 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

char	**ft_init_cmd_opt(t_cmd *cmd, t_data *data)
{
	char	**cmd_opt;
	t_token	*token;
	int		i;

	(void) data;
	token = cmd->token;
	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	cmd_opt = ft_handle_malloc(MALLOC_C + TAB_STR2, NULL, (i + 1), data);
	i = 0;
	token = cmd->token;
	while (token)
	{
		cmd_opt[i] = ft_strdup(token->token);
		ft_handle_malloc(ADD_C + TAB_STR1, cmd_opt[i], 0, data);
		i++;
		token = token->next;
	}
	cmd_opt[i] = NULL;
	return (cmd_opt);
}

int	**ft_init_pipe(t_data *data)
{
	int	**tab_int;
	int	i;

	tab_int = ft_handle_malloc(MALLOC_M + TAB_INT2, NULL, data->nb_pipes, data);
	i = 0;
	while (i < data->nb_pipes)
	{
		tab_int[i] = ft_handle_malloc(MALLOC_M + TAB_INT1, NULL, 2, data);
		tab_int[i][0] = -1;
		tab_int[i][1] = -1;
		i++;
	}
	return (tab_int);
}

int	*ft_init_pid(t_data *data)
{
	int	*pid;
	int	i;

	i = 0;
	pid = ft_handle_malloc(MALLOC_M + TAB_INT1, NULL, (data->nb_pipes + 1), data);
	while (i < (data->nb_pipes + 1))
	{
		pid[i] = -1;
		i++;
	}
	return (pid);
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
		while (tok_redir)
		{
			if (tok_redir->type == GREAT)
			{
				tok_redir = tok_redir->next;
				if (cmd->file_err != 1)
				{
					tok_redir->fd = open(tok_redir->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
			else if (tok_redir->type == D_GREAT)
			{
				tok_redir = tok_redir->next;
				if (cmd->file_err != 1)
				{
					tok_redir->fd = open(tok_redir->token, O_CREAT | O_RDWR | O_APPEND, 0644);
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
			else if (tok_redir->type == LESS)
			{
				tok_redir = tok_redir->next;
				if (cmd->file_err != 1)
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
			else if (tok_redir->type == D_LESS)
				ft_heredoc(data, data->cmd, tok_redir);
			tok_redir = tok_redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
