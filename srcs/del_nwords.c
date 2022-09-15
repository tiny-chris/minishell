/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_nwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:07:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/15 17:26:44 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_del_nword(t_cmd *cmd)
{
	t_token	*token;
	t_token	*todel;
	t_token	*tmp;

	token = cmd->token;
	todel = NULL;
	tmp = NULL;
	if (token && token->type == BUILTIN && (ft_strncmp(token->token, "echo", 4) == 0))
	{
		token = token->next;
		while (token && token->type == WORD_N)
		{
			if (token->next && token->next->type == WORD_N)
			{
				todel = token->next;
				tmp = token->next->next;
				todel->next = NULL;
				token->next = tmp;
				ft_lstdelone_tok(todel);
			}
			else
				return (0);
		}
	}
	return (0);
}