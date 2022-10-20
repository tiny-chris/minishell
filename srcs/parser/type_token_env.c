/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:45:43 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/20 16:57:49 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_env_4(t_data *data, t_cmd *cmd, t_token *token)
{
	t_token		*todel;
	t_token		*tmp;

	todel = NULL;
	tmp = NULL;
	if (ft_check_built_in(token->token, data, ft_strlen(token->token)))
		token->type = BUILTIN;
	else
		token->type = COMMAND;
	token->env = 1;
	todel = cmd->token;
	tmp = token;
	ft_lstdelone_tok_bin(todel);
	cmd->token = tmp;
}

void	ft_token_env_3(t_token *token)
{
	while (token)
	{
		if (ft_new_strchr(token->token, '='))
			token = token->next;
		else
			break ;
	}
	if (token)
		token->env = 1;
}

void	ft_token_env_2(t_cmd *cmd, t_token *token)
{
	t_token		*todel;
	t_token		*tmp;

	todel = NULL;
	tmp = NULL;
	while (token)
	{
		if (token && \
			ft_strncmp(token->token, "env", ft_strlen(token->token)) == 0)
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
