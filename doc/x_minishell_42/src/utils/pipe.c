/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:04:17 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 19:04:17 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_pipe(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, PP))
		{
			data->nb_pipes ++;
			while (ft_is_tokid(temp, PP))
				temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
	data->cmdcount = data->nb_pipes + 1;
}
