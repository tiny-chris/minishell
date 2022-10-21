/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:29:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/22 00:20:21 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_lstadd_tok(t_token **tok, int type, char *token, t_data *data)
{
	t_token	*new;
	t_token	*last;

	ft_handle_malloc(ADD_M + TAB_STR1, token, 0, data);
	new = ft_handle_malloc(MALLOC_M + LST_TOK, NULL, 1, data);
	new->token = token;
	new->type = type;
	new->fd = -1;
	new->env = 0;
	new->printed = 0;
	new->hd_quotes = -1;
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

/*	<SUMMARY> Deletes the t_token node ONLY (not its content) and removes it
**	from the garbage collector at the same time
**	<REMARK>	a malloc of t_token node is always done without content
**				(on the contrary of char **, e.g. ft_split function)
*/
void	ft_lstdelone_tok(t_token *node)
{
	if (!node)
		return ;
	node->next = NULL;
	free(node);
	node = NULL;
}

/*	<SUMMARY> Deletes the whole t_token node and removes all 'malloc'
**	elements from the garbage collector at the same time:
**	- its content (char * token) if not NULL
**	- the node itself
*/
void	ft_lstdelone_tok_bin(t_token *node)
{
	if (!node)
		return ;
	if (node->token != NULL)
		ft_handle_malloc(DELONE, node->token, 0, NULL);
	ft_handle_malloc(DELONE, node, 0, NULL);
}

void	ft_free_token(t_token **token)
{
	t_token	*tmp;
	t_token	*todel;

	tmp = NULL;
	todel = NULL;
	if (!*token)
		return ;
	while ((*token) != NULL)
	{
		todel = (*token);
		tmp = (*token)->next;
		ft_lstdelone_tok_bin(todel);
		(*token) = tmp;
	}
	(*token) = NULL;
}
