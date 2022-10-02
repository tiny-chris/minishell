/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:38:24 by clem              #+#    #+#             */
/*   Updated: 2022/07/10 10:30:11 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_redir(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if (temp->next
			&& (ft_is_tokid(temp, GT) || ft_is_tokid(temp, DG)
				|| ft_is_tokid(temp, LS)))
				((t_tok *)temp->next->content)->tokid = FI;
		if (temp->next && ft_is_tokid(temp, DL))
			((t_tok *)temp->next->content)->tokid = SW;
		temp = temp->next;
	}
}
