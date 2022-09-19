/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:29:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/19 13:54:52 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_tok(t_token *node)
{
	if (!node)
		return ;
	free(node->token);
	node->token = NULL;
	node->next = NULL;
	free(node);
}

void	ft_free_token(t_token **token)
{
	t_token	*tmp;

	if (!*token)
		return ;
	while (*token != NULL)
	{
		tmp = (*token)->next;
		//dprintf(2, "token val = %s\n", (*token)->token);
		ft_lstdelone_tok(*token);
		(*token) = tmp;
	}
	(token) = NULL;
}

t_token	*ft_lstlast_tok(t_token *lst)
{
	t_token	*node;

	if (!lst)
		return (0);
	node = lst;
	while (node->next)
		node = node->next;
	return (node);
}

int	ft_lstadd_token(t_token **tok, int type, char *token)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		ft_free_token(tok);
		return (1);
	}
	new->token = token;
	//dprintf(2, "new token %s, size = %ld\n", new->token, ft_strlen(new->token));
	new->type = type;
	//dprintf(2, "type %d\n", new->type);
	new->fd = -1;
	new->next = NULL;
	if (ft_lstlast_tok(*tok) == 0)
	{
		*tok = new;
		return (0);
	}
	last = ft_lstlast_tok(*tok);
	last->next = new;
	return (0);
}

void	ft_lstclear_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token != NULL)
	{
		tmp = token->next;
		ft_lstdelone_tok(token);
		token = tmp;
	}
}
