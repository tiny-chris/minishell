/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:07:43 by clem              #+#    #+#             */
/*   Updated: 2022/07/14 11:00:30 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Compare 2 tokids.
 */

int	ft_is_tokid(t_dlist *toklist, int tokid)
{
	if (toklist && ((t_tok *)toklist->content)->tokid == tokid)
		return (1);
	return (0);
}
