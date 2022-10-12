/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:09:15 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/12 13:17:46 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

t_env	*ft_check_env(t_data *data, char *line)
{
	t_env	*env;
	char	*tmp;

	env = data->env;
	tmp = NULL;
	while (env)
	{
		tmp = ft_strjoin("$", env->var);
		if (!tmp)
			exit (EXIT_FAILURE); // et free tout;
		if (ft_strncmp(tmp, line, ft_strlen(tmp)) == 0
			&& (ft_strlen(line) - 1 == ft_strlen(tmp)))
		{
			free(tmp);
			return (env);
		}
		free(tmp);
		tmp = NULL;
		env = env->next;
	}
	return (NULL);
}

void	ft_add_line(t_data *data, t_token *tok_redir, char *line)
{
	char	*expand_line;
	t_env	*tmp;

	expand_line = NULL;
	if (line[0] == '$')
	{
		tmp = ft_check_env(data, line);
		if (tmp) // regarder si line est dans l'env
		{
			expand_line = ft_strjoin(tmp->content, "\n");
			write(tok_redir->fd, expand_line, ft_strlen(expand_line));
			free(expand_line);
		}
	}
	else
		write(tok_redir->fd, line, ft_strlen(line));
	free(line);
	line = NULL;
}

void	ft_heredoc_sigint(int sig)
{
	g_val_exit = 130;
	(void)sig;
	close(STDIN_FILENO);
}

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

void	ft_heredoc(t_data *data, t_cmd *cmd, t_token *tok_redir)
{
	char	*line;
	int		stdin_dup;

	line = NULL;
	tok_redir = tok_redir->next;
	tok_redir->fd = open("/tmp/temp_heredoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	g_val_exit = 0;
	if (tok_redir->fd < 0)
	{
		cmd->file_err = 1;
		g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno)); // exit avec free
	}
	stdin_dup = dup(STDIN_FILENO);
	while (1)
	{
		line = ft_get_prompt_line(data);
		if (g_val_exit)
		{
			dup2(stdin_dup, STDIN_FILENO);
			break ;
		}
		if (!line)
		{
			ft_end_of_file(tok_redir);
			break ;
		}
		if (ft_strncmp(line, tok_redir->token, ft_strlen(tok_redir->token)) == 0
			&& (ft_strlen(tok_redir->token) == (ft_strlen(line) - 1)))
			break ;
		ft_add_line(data, tok_redir, line);
		line = NULL;
		ft_init_signals(data);
	}
	if (line)
		free(line);
	close(stdin_dup);
	close(tok_redir->fd);
	tok_redir->fd = open("/tmp/temp_heredoc", O_RDONLY);
	cmd->infile = tok_redir->fd;
	unlink("/tmp/temp_heredoc");
}
