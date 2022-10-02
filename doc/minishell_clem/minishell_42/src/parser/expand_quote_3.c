/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:43:29 by cvidon            #+#    #+#             */
/*   Updated: 2022/07/14 17:46:20 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_emptyquote(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if ((ft_is_tokid(temp, DQ) || ft_is_tokid(temp, QT))
			&& (!ft_strcmp(((t_tok *)temp->content)->tok, "")
				|| !ft_strcmp(((t_tok *)temp->content)->tok, "\' ")
				|| !ft_strcmp(((t_tok *)temp->content)->tok, "\" ")))
		{
			if (!temp->next)
			{
				ft_remove_tok(data->toklist, temp);
				break ;
			}
			else
			{
				if (temp)
					temp = temp->next;
				ft_remove_tok(data->toklist, temp->prev);
			}
		}
		if (temp)
			temp = temp->next;
	}
}
/*
 ** Concatenate the given QUOTED WORDS.
 */

char	*ft_concat_quoted_words(t_data *data, t_dlist *toklist)
{
	t_dlist	*temp;
	char	*str;

	if (!toklist || !toklist->next)
		return (ft_w_strdup(data, ""));
	temp = toklist;
	if (!ft_is_tokid (temp->next, QT) && !ft_is_tokid (temp->next, DQ))
		str = ft_strjoin (((t_tok *)temp->content)->tok,
				((t_tok *)temp->next->content)->tok);
	else
		return (ft_w_strdup(data, ((t_tok *)temp->content)->tok));
	temp = temp->next->next;
	while (temp && !ft_is_tokid (temp, QT) && !ft_is_tokid (temp, DQ))
	{
		str = ft_strjoin_free_s1(str, ((t_tok *)temp->content)->tok);
		temp = temp->next;
	}
	return (str);
}
