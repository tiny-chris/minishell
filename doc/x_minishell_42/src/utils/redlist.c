/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:42:42 by athirion          #+#    #+#             */
/*   Updated: 2022/06/30 11:42:55 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Init a redir list or add command to it.
 */

void	ft_create_redlist(t_data *data)
{
	t_dlist	*temp;
	int		nb_cmd;

	temp = data->toklist;
	nb_cmd = 0;
	while (temp)
	{
		if (ft_is_tokid(temp, PP))
			nb_cmd ++;
		if (ft_is_tokid(temp, GT) || ft_is_tokid(temp, LS)
			|| ft_is_tokid(temp, DG) || ft_is_tokid(temp, DL))
			ft_add_red (data, temp, nb_cmd);
		temp = temp->next;
	}
}

/*
 ** Init a redir list or add command to it.
 */

void	ft_add_red(t_data *data, t_dlist *token, int nb_cmd)
{
	t_redir	*redir;

	redir = ft_w_malloc (data, sizeof(t_redir));
	redir->type = ((t_tok *)token->content)->tokid;
	redir->cmdid = nb_cmd;
	if (token->next)
		redir->file = ft_w_strdup(data, ((t_tok *)token->next->content)->tok);
	else
		redir->file = NULL;
	ft_dlstadd_back(&data->redlist, ft_dlstnew(redir));
}

/*
 ** Print redir list.
 */

void	ft_printlist_redir(t_dlist *lst)
{
	t_dlist	*temp;

	temp = lst;
	while (temp)
	{
		ft_printf(" [ cmdid: '%i', type: '%i', file '%s' ]\n",
			((t_redir *)temp->content)->cmdid,
			((t_redir *)temp->content)->type,
			((t_redir *)temp->content)->file);
		temp = temp->next;
	}
}

/*
 ** Clear a redir list.
 */

void	ft_clearlist_red(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*ptr;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (ptr)
	{
		*lst = (*lst)->next;
		del(((t_redir *)ptr->content)->file);
		del(ptr->content);
		del(ptr);
		ptr = *lst;
	}
}
