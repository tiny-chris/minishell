/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:37:41 by athirion          #+#    #+#             */
/*   Updated: 2022/07/14 16:39:46 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_to_word(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if (temp && ft_is_tokid(temp, EX))
			((t_tok *)temp->content)->tokid = WD;
		temp = temp->next;
	}
}

void	ft_concat_expand(t_data *data)
{
	t_dlist	*temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		if (temp && ft_is_tokid(temp, EX))
		{
			while (temp && temp->next && ft_is_tokid(temp, EX)
				&& ft_is_tokid(temp->next, EX))
			{
				str = ft_strjoin(((t_tok *)temp->content)->tok,
						((t_tok *)temp->next->content)->tok);
				free(((t_tok *)temp->content)->tok);
				((t_tok *)temp->content)->tok = ft_w_strdup(data, str);
				free(str);
				ft_remove_tok(data->toklist, temp->next);
			}
		}
		if (temp)
			temp = temp->next;
	}
}

/*
 ** Remove DOLLAR from toklist.
 */

void	ft_remove_dollar(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*ptrcpy[2];
	t_dlist	*new;

	temp = data->toklist;
	ptrcpy[0] = temp;
	new = ft_w_malloc(data, sizeof(t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	while (temp)
	{
		if (!ft_is_tokid(temp, DO))
			ft_dlst_elem_dup(data, &new, temp);
		temp = temp->next;
	}
	data->toklist = new;
	ft_clearlist_tok(&ptrcpy[0], ft_free);
	ft_free(ptrcpy[1]);
}

void	ft_heredoc_dollar_2(t_dlist **temp)
{
	*temp = (*temp)->next;
	if (*temp && ft_is_tokid(*temp, WS))
		*temp = (*temp)->next;
	if (*temp && ft_is_tokid(*temp, DQ))
		*temp = (*temp)->next;
}

void	ft_heredoc_dollar(t_data *data)
{
	t_dlist	*temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		if (temp && ft_is_tokid(temp, DL))
		{
			ft_heredoc_dollar_2(&temp);
			if (temp && temp->next && ft_is_tokid(temp, DO)
				&& ft_is_tokid(temp->next, WD))
			{
				str = ft_strjoin(((t_tok *)temp->content)->tok,
						((t_tok *)temp->next->content)->tok);
				free(((t_tok *)temp->next->content)->tok);
				((t_tok *)temp->next->content)->tok = str;
				temp = temp->next;
				ft_remove_tok(data->toklist, temp->prev);
			}
		}
		if (temp)
			temp = temp->next;
	}
}
