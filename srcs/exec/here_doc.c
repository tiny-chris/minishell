/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:09:15 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/10 18:22:01 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

t_env	*ft_check_env(t_data *data, char *line)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (ft_strncmp(env->var, line, ft_strlen(line)) == 0
			&& (ft_strlen(line) == ft_strlen(env->var)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_add_line(t_data *data, t_token *tok_redir, char *line)
{
	char	*expand_line;
	t_env	*tmp;

	expand_line = NULL;
	tmp = ft_check_env(data, line);
	if (tmp != NULL) // regarder si line est dans l'env
	{
		expand_line = ft_strdup(tmp->content);
		write(tok_redir->fd, expand_line, ft_strlen(expand_line));
		free(expand_line);
	}
	else
	{
		write(tok_redir->fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
}

char	*ft_get_prompt_line(void)
{
	char	*line;

	line = NULL;
	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	return (line);
}

void	ft_heredoc(t_data *data, t_cmd *cmd, t_token *tok_redir)
{
	char	*line;

	line = NULL;
	tok_redir = tok_redir->next;
	tok_redir->fd = open("/tmp/temp_heredoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (tok_redir->fd < 0)
	{
		cmd->file_err = 1;
		g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno)); // exit avec free
	}
	while (1)
	{
		line = ft_get_prompt_line();
		if (!line)
			break ; // exit + free
		if (ft_strncmp(line, tok_redir->token, ft_strlen(tok_redir->token)) == 0
			&& (ft_strlen(tok_redir->token) == (ft_strlen(line) - 1)))
			break ;
		ft_add_line(data, tok_redir, line);
		line = NULL;
	}
	cmd->infile = tok_redir->fd;
}
