/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_empty_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:55:53 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/14 18:18:42 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_del_empty_token(t_cmd *cmd, t_data *data)
{
	t_token	*tok;
	t_token	*tmp1;
	t_token	*tmp2;

	(void) data;
	tok = cmd->token;
	tmp1 = NULL;
	tmp2 = NULL;
	if (tok && tok->token[0] == '\0')
	{
		if (tok->next)
		{
			dprintf(2, "y'a kekchose ici\n");
			tmp1 = tok;
			tmp2 = tok->next;
			tok = tmp2;
			ft_lstdelone_tok(tmp1);
		}
		else
		{
			dprintf(2, "passe ici\n");
			ft_lstdelone_tok(tok);
			cmd->token = NULL;
			dprintf(2, "passe là\n");
			return (0);
		}
	}
	cmd->token = tok;
	while (tok->next)
	{
		dprintf(2, "y'a kekchose la suite\n");
		if (tok->next->token[0] == '\0')
		{
			if (tok->next->next)
			{
				tmp1 = tok->next;
				tmp2 = tok->next->next;
				tok->next = tmp2;
				ft_lstdelone_tok(tmp1);
			}
			else
			{
				tmp1 = tok->next;
				tok->next = NULL;
				ft_lstdelone_tok(tok->next);
				return (0);
			}
		}
		tok = tok->next;
	}
	return (0);
}
