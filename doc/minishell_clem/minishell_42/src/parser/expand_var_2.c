/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:37:39 by athirion          #+#    #+#             */
/*   Updated: 2022/07/14 16:39:48 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple_quote_2(t_data *data, t_dlist **temp, char *str)
{
	str = ft_strjoin(((t_tok *)(*temp)->content)->tok,
			((t_tok *)(*temp)->next->content)->tok);
	free(((t_tok *)(*temp)->next->content)->tok);
	((t_tok *)(*temp)->next->content)->tok = str;
	((t_tok *)(*temp)->next->content)->tokid = WD;
	*temp = (*temp)->next;
	ft_remove_tok(data->toklist, (*temp)->prev);
}

void	ft_simple_quote(t_data *data)
{
	t_dlist	*temp;
	char	*str;

	str = NULL;
	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, QT))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid(temp, QT))
			{
				if (temp->next && ft_is_tokid(temp, DO)
					&& ft_is_tokid(temp->next, WD))
					ft_simple_quote_2(data, &temp, str);
				temp = temp->next;
			}
			if (temp && ft_is_tokid(temp, QT))
				temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
}

t_dlist	*ft_expand_dollar_2(t_dlist *temp)
{
	if (temp->prev && ft_is_tokid(temp, DO)
		&& ft_is_tokid(temp->prev, WD) && !ft_is_tokid(temp->next, WD))
		((t_tok *)temp->content)->tokid = WD;
	else if (temp->next && ft_is_tokid(temp, DO)
		&& !ft_is_tokid(temp->next, WD))
	{
		if (temp->next && ft_is_tokid(temp, DO)
			&& (ft_is_tokid(temp->next, QT) || ft_is_tokid(temp->next, DQ)))
		{
			if (!temp->prev || (temp->prev && ((ft_is_tokid(temp->next, QT)
							&& !ft_is_tokid(temp->prev, QT))
						|| (ft_is_tokid(temp->next, DQ)
							&& !ft_is_tokid(temp->prev, DQ)))))
			{
				temp = temp->next;
				return (temp);
			}
		}
		((t_tok *)temp->content)->tokid = WD;
	}
	else if (!temp->next && ft_is_tokid(temp, DO))
		((t_tok *)temp->content)->tokid = WD;
	else if (!temp->next && !temp->prev && ft_is_tokid(temp, DO))
		((t_tok *)temp->content)->tokid = WD;
	return (temp);
}

void	ft_expand_dollar(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		temp = ft_expand_dollar_2 (temp);
		if (temp == temp->next)
			continue ;
		temp = temp->next;
	}
}

void	ft_var_exit_status(t_data *data)
{
	t_dlist		*temp;
	char		*str;
	extern int	g_sig_status;

	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, RV))
		{
			if (g_sig_status)
				str = ft_itoa(g_sig_status);
			else
				str = ft_itoa(g_sig_status);
			free(((t_tok *)temp->content)->tok);
			((t_tok *)temp->content)->tok = str;
		}
		if (temp)
			temp = temp->next;
	}
	g_sig_status = 0;
}
