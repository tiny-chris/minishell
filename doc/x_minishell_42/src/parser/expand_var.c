/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:37:27 by athirion          #+#    #+#             */
/*   Updated: 2022/07/14 14:42:25 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** if $0something -> return to join('minishell' + 'something')
 **
 **			echo $0tray
 **				 bashtray
 **
 ** if $+1 == digit -> substr(key, 1, strlend(key - 1));
 **
 **			echo $100
 **				 00
 **
 ** if $+1 = !alpha_ -> return join('$', key);
 **
 **			echo $=42
 **				 $=42
 **
 ** while alphanum_ until !alphanum_ -> join (getenv_var + after !alphanum_)
 **
 **			echo 1. "$t=TEST" 2. $USER=USER
 **				 1. =TEST	  2. cvidon=USER
 **
 ** if all alphanum_ -> return getenv_var
 **
 **			echo $USERR
 */

void	ft_multiple_dollar_2(t_data *data, t_dlist **temp, t_dlist **new)
{
	while (*temp)
	{
		if ((*temp)->next && ft_is_tokid(*temp, DO)
			&& ft_is_tokid((*temp)->next, DO))
		{
			while ((*temp)->next && ft_is_tokid(*temp, DO)
				&& ft_is_tokid((*temp)->next, DO))
				*temp = (*temp)->next;
		}
		else
		{
			ft_dlst_elem_dup(data, new, *temp);
			*temp = (*temp)->next;
		}
	}
}

void	ft_multiple_dollar(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*freetemp;
	t_dlist	*new;
	t_dlist	*newfree;

	new = ft_w_malloc(data, sizeof(t_dlist *));
	newfree = new;
	new = NULL;
	temp = data->toklist;
	freetemp = temp;
	ft_multiple_dollar_2(data, &temp, &new);
	ft_clearlist_tok(&freetemp, ft_free);
	free(freetemp);
	data->toklist = new;
	ft_free(newfree);
}

void	ft_expand_vars_2(t_data *data, t_dlist **temp)
{
	char	*str;

	data->toggle = 0;
	str = ft_expand_var (data, ((t_tok *)(*temp)->content)->tok);
	if (!ft_strcmp(str, ""))
	{
		if (!(*temp)->next)
		{
			ft_remove_tok(data->toklist, *temp);
			ft_free(str);
			data->toggle = 1;
			return ;
		}
		*temp = (*temp)->next;
		if ((*temp)->prev)
			ft_remove_tok(data->toklist, (*temp)->prev);
		*temp = (*temp)->prev;
	}
	else
	{
		free (((t_tok *)(*temp)->content)->tok);
		((t_tok *)(*temp)->content)->tok = ft_w_strdup(data, str);
		((t_tok *)(*temp)->content)->tokid = EX;
	}
	ft_free(str);
}

void	ft_expand_vars(t_data *data)
{
	t_dlist	*temp;

	ft_multiple_dollar(data);
	ft_simple_quote(data);
	ft_var_exit_status(data);
	ft_expand_dollar(data);
	ft_heredoc_dollar(data);
	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid (temp, DO) && ft_is_tokid (temp->next, WD))
		{
			temp = temp->next;
			if (ft_strcmp(((t_tok *)temp->content)->tok, "$?"))
				ft_expand_vars_2(data, &temp);
			if (data->toggle)
				break ;
		}
		if (temp)
			temp = temp->next;
	}
	ft_remove_dollar (data);
	ft_concat_expand(data);
	ft_expand_to_word(data);
}
