/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:37:49 by clem              #+#    #+#             */
/*   Updated: 2022/07/10 10:48:43 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_convert_wd(t_dlist *toklist)
{
	t_dlist	*temp;

	temp = toklist;
	while (temp)
	{
		if (ft_is_tokid (temp, RV))
			((t_tok *)temp->content)->tokid = WD;
		temp = temp->next;
	}
}
/*
 ** Remove unnecessary spaces.
 */

static void	ft_remove_spaces(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	ft_convert_wd (data->toklist);
	while (temp)
	{
		if (temp->prev && temp && ft_is_tokid (temp, WS))
		{
			temp = temp->prev;
			ft_remove_tok (data->toklist, temp->next);
		}
		temp = temp->next;
	}
}

void	ft_parse_space_2(t_data *data)
{
	t_dlist	*temp;

	temp = ft_dlstlast(data->toklist);
	while (temp && temp != data->toklist && ft_is_tokid (temp, WS))
	{
		temp = temp->prev;
		ft_remove_tok (data->toklist, temp->next);
	}
}

void	ft_parse_space(t_data *data)
{
	t_dlist	*temp;

	ft_parse_space_2 (data);
	temp = data->toklist;
	while (temp)
	{
		if (temp->prev && ft_is_tokid (temp, WS) && !ft_is_tokid(temp->prev, DQ)
			&& !ft_is_tokid(temp->prev, QT) && !ft_is_tokid(temp->prev, RV))
		{
			while (temp->prev && temp->next && ft_is_tokid (temp, WS))
			{
				if (ft_is_tokid(temp->next, RV))
					break ;
				temp = temp->next;
				ft_remove_tok (data->toklist, temp->prev);
			}
		}
		if (temp)
			temp = temp->next;
	}
	ft_remove_spaces (data);
}
