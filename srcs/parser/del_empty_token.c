/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_empty_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:55:53 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/21 11:55:36 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	<SUMMARY> Deletes empty token trough a loop that restarts from the beginning
**	of the command each time there is a deletion, 2 cases:
**	 1. tok->token[0] == '\0' --> move head to token->next and delete 1st token
**	 2. tok->token[0] != '\0' --> check next token(s)
*/
static t_token	*ft_del_first_empty_tok(t_cmd *cmd, t_token *tok)
{
	t_token	*todel;
	t_token	*tmp;

	todel = NULL;
	tmp = NULL;
	if (tok->token[0] == '\0')
	{
		if (tok->next != NULL)
		{
			todel = tok;
			tmp = tok->next;
			todel->next = NULL;
			ft_lstdelone_tok_bin(todel);
			cmd->token = tmp;
			tok = tmp;
		}
		else
		{
			ft_lstdelone_tok_bin(tok);
			cmd->token = NULL;
			return (NULL);
		}
	}
	return (tok);
}

static t_token	*ft_del_next_empty_token(t_cmd *cmd, t_token *tok)
{
	t_token	*todel;
	t_token	*tmp;

	todel = NULL;
	tmp = NULL;
	if (tok->next != NULL && tok->next->token[0] == '\0')
	{
		if (tok->next->next != NULL)
		{
			todel = tok->next;
			tmp = tok->next->next;
			todel->next = NULL;
			tok->next = tmp;
			ft_lstdelone_tok_bin(todel);
			tok = cmd->token;
		}
		else
		{
			todel = tok->next;
			tok->next = NULL;
			ft_lstdelone_tok_bin(todel);
			return (NULL);
		}
	}
	return (tok);
}

int	ft_del_empty_token(t_cmd *cmd, t_data *data)
{
	t_token	*tok;

	(void) data;
	if (cmd->token == NULL)
		return (1);
	tok = cmd->token;
	while (tok)
	{
		if (tok->token[0] == '\0')
			tok = ft_del_first_empty_tok(cmd, tok);
		else
		{
			if (tok->next == NULL)
				return (0);
			else if (tok->next != NULL && tok->next->token[0] == '\0')
				tok = ft_del_next_empty_token(cmd, tok);
			else
				tok = tok->next;
		}
	}
	return (0);
}
