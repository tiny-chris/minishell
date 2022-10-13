/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:29:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/13 16:34:07 by cgaillag         ###   ########.fr       */
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

int	ft_lstadd_token(t_token **tok, int type, char *token, t_data *data)
{
	t_token	*new;
	t_token	*last;

	ft_handle_malloc(ADD_M + TAB_STR1, token, 0, data);
	new = ft_handle_malloc(MALLOC_M + LST_TOK, NULL, 1, data);
	// new = malloc(sizeof(t_token));
	// if (!new)
	// {
	// 	ft_free_token(tok);
	// 	return (1);
	// }
	new->token = token;
	//dprintf(2, "new token %s, size = %ld\n", new->token, ft_strlen(new->token));
	new->type = type;
	//dprintf(2, "type %d\n", new->type);
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

// // ne semble plus nécessaire car malloc toujours fait pour le maillon tout seul
// // sans contenu
// void	ft_lstdelone_tok(t_token *node)
// {
// 	if (!node)
// 		return ;
// 	if (node->token != NULL)
// 	{
// 		free(node->token);
// 		node->token = NULL;
// 	}
// 	node->next = NULL;
// 	free(node);
// 	node = NULL;
// }

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

// ft_free_token et ft_lstclear_token sont presques semblables
// (param différents: ** vs *)


// !!!! voir si les 2 peuvent être regroupées selon les utilisations

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
		//dprintf(2, "token val = %s\n", (*token)->token);
		ft_lstdelone_tok_bin(todel);
		(*token) = tmp;
	}
	(*token) = NULL;
}

void	ft_lstclear_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token != NULL)
	{
		tmp = token->next;
		ft_lstdelone_tok_bin(token);
		token = tmp;
	}
}
