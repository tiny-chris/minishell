/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:09:15 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 18:35:35 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/*	Ajouter les handle malloc	*/

char	*ft_get_prompt_line(t_data *data)
{
	char	*line;

	line = NULL;
	write(1, "> ", 2);
	ft_signal(data, SIGINT, ft_heredoc_sigint);
	if (g_val_exit == 0)
		line = get_next_line(STDIN_FILENO);
	return (line);
}

void	ft_end_of_file(t_token *tok_redir)
{
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-line (wanted `", 2);
	ft_putstr_fd(tok_redir->token, 2);
	ft_putendl_fd("')", 2);
}

void	ft_exec_hd(t_data *data, t_token *tok_redir, char *line, int stdin_dup)
{
	while (1)
	{
		line = ft_get_prompt_line(data);
		if (g_val_exit)
		{
			dup2(stdin_dup, STDIN_FILENO);
			free(line);
			break ;
		}
		if (!line)
		{
			ft_end_of_file(tok_redir);
			break ;
		}
		if (ft_strncmp(line, tok_redir->token, ft_strlen(tok_redir->token)) == 0
			&& (ft_strlen(tok_redir->token) == (ft_strlen(line) - 1)))
		{
			free(line);
			break ;
		}
		ft_add_line(data, tok_redir, line);
		line = NULL;
		ft_init_signals(data);
	}
}

void	ft_heredoc(t_data *data, t_cmd *cmd, t_token *tok_redir)
{
	char	*line;
	int		stdin_dup;

	line = NULL;
	tok_redir = tok_redir->next;
	tok_redir->fd = open(cmd->heredoc_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	g_val_exit = 0;
	if (tok_redir->fd < 0)
	{
		cmd->file_err = 1;
		g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
	}
	stdin_dup = dup(STDIN_FILENO);
	ft_exec_hd(data, tok_redir, line, stdin_dup);
	close(stdin_dup);
	close(tok_redir->fd);
	tok_redir->fd = open(cmd->heredoc_path, O_RDONLY);
	cmd->infile = tok_redir->fd;
	unlink(cmd->heredoc_path);
}
