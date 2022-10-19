/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:23:10 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 18:25:00 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/*	Ajouter les handle malloc	*/

void	ft_heredoc_sigint(int sig)
{
	g_val_exit = 130;
	(void)sig;
	close(STDIN_FILENO);
}

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
			exit (EXIT_FAILURE);
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
	if (line[0] == '$' && tok_redir->hd_quotes != 1)
	{
		tmp = ft_check_env(data, line);
		if (tmp)
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
