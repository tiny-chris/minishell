/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:40:01 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/24 15:46:43 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_built_in(char *token, t_data *data, int tok_len)
{
	int		len;
	int		j;
	char	**built_in;

	len = 0;
	j = 0;
	built_in = data->built_in;
	while (built_in[j])
	{
		len = ft_strlen(built_in[j]);
		if (len == tok_len)
		{
			if (ft_strncmp(token, built_in[j], len) == 0)
				return (1);
		}
		j++;
	}
	return (0);
}

static void	ft_token_echo(t_cmd *cmd, t_token *token)
{
	t_token		*n_token;

	n_token = NULL;
	n_token = ft_get_token_echo(&(cmd->token));
	if (n_token != NULL && n_token->next != NULL)
	{
		token = n_token;
		ft_echo_join_words_fill(token);
	}
}

void	ft_token_env(t_data *data, t_cmd *cmd, t_token *token)
{
	token = token->next;
	token = ft_token_env_2(cmd, token);
	if (token && ft_is_in_set(token->token, '='))
		ft_token_env_3(token);
	else if (token)
		ft_token_env_4(data, cmd, token);
}

static void	ft_token_unset(t_cmd *cmd, t_token *token)
{
	t_token		*todel;
	t_token		*tmp;

	todel = NULL;
	tmp = NULL;
	token = token->next;
	while (token)
	{
		if (token && ft_strncmp(token->token, "unset", \
			ft_strlen(token->token)) == 0)
		{
			todel = token;
			tmp = token->next;
			ft_lstdelone_tok_bin(todel);
			cmd->token->next = tmp;
			token = cmd->token->next;
		}
		else
			break ;
	}
}

int	ft_type_token(t_cmd *cmd, t_data *data)
{
	t_token		*token;

	token = cmd->token;
	if (ft_check_built_in(token->token, data, ft_strlen(token->token)))
		token->type = BUILTIN;
	else
		token->type = COMMAND;
	if (token && token->type == BUILTIN && \
		(ft_strncmp(token->token, "unset", 5) == 0))
		ft_token_unset(cmd, token);
	else if (token && token->type == BUILTIN && \
		(ft_strncmp(token->token, "env", 3) == 0))
		ft_token_env(data, cmd, token);
	token = cmd->token;
	if (token && token->type == BUILTIN && \
		(ft_strncmp(token->token, "echo", 4) == 0))
		ft_token_echo(cmd, token);
	return (0);
}
