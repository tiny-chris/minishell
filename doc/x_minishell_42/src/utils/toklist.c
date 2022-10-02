/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:31:15 by clem              #+#    #+#             */
/*   Updated: 2022/07/14 11:47:08 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Update the index.
 */

void	ft_update_tokpos(t_dlist *toklist)
{
	t_dlist	*temp;
	int		i;

	temp = toklist;
	i = 0;
	while (temp)
	{
		((t_tok *)temp->content)->tokpos = i;
		temp = temp->next;
		i ++;
	}
}

/*
 ** Remove the given token from toklist.
 */

void	ft_remove_tok(t_dlist *toklist, t_dlist *token)
{
	if (toklist && token)
	{
		if (toklist == token)
			toklist = token->next;
		if (token->next)
			token->next->prev = token->prev;
		if (token->prev)
			token->prev->next = token->next;
		free(((t_tok *) token->content)->tok);
		free(token->content);
		free(token);
	}
}

/*
 ** Init a tok list or add token to it.
 */

void	ft_add_tok(t_data *data, int tokid, int tokpos, char *token)
{
	t_tok	*tok;

	tok = ft_w_malloc (data, sizeof(t_tok));
	tok->tokid = tokid;
	tok->tokpos = tokpos;
	tok->tok = token;
	ft_dlstadd_back (&data->toklist, ft_dlstnew(tok));
}

/*
 ** Print tok list.
 */

void	ft_printlist_tok(t_dlist *toklist)
{
	t_dlist	*temp;

	temp = toklist;
	while (temp)
	{
		ft_printf(" [ id: '%i', po: '%i', tk: '%s' ]\n",
			((t_tok *)temp->content)->tokid,
			((t_tok *)temp->content)->tokpos,
			((t_tok *)temp->content)->tok
			);
		temp = temp->next;
	}
	ft_printf(" (NULL / list back)\n");
	temp = toklist;
	ft_printf(">> '");
	while (temp)
	{
		ft_printf("%s", ((t_tok *)temp->content)->tok);
		temp = temp->next;
	}
	ft_printf("'\n");
	ft_printf("\n");
}

/*
 ** Clear a token list.
 */

void	ft_clearlist_tok(t_dlist **toklist, void (*del)(void *))
{
	t_dlist	*ptr;

	if (!toklist || !del)
		return ;
	ptr = *toklist;
	while (ptr != NULL)
	{
		*toklist = (*toklist)->next;
		del(((t_tok *)ptr->content)->tok);
		del(ptr->content);
		del(ptr);
		ptr = *toklist;
	}
}
