/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_nwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:07:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/21 10:35:54 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_del_nword(t_cmd *cmd)
{
	t_token	*tok;
	t_token	*todel;
	t_token	*tmp;

	tok = cmd->token;
	todel = NULL;
	tmp = NULL;
	if (tok && tok->type == BUILTIN && (ft_strncmp(tok->token, "echo", 4) == 0))
	{
		tok = tok->next;
		while (tok && tok->type == WORD_N)
		{
			if (tok->next && tok->next->type == WORD_N)
			{
				todel = tok->next;
				tmp = tok->next->next;
				todel->next = NULL;
				ft_lstdelone_tok_bin(todel);
				tok->next = tmp;
			}
			else
				return (0);
		}
	}
	return (0);
}
