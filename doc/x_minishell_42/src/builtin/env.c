/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:42:14 by cvidon            #+#    #+#             */
/*   Updated: 2022/06/27 15:54:55 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Tiny 'env' builtin.
 */

int	ft_env(t_dlist *envlist)
{
	t_dlist	*temp;

	temp = envlist;
	while (temp)
	{
		ft_putstr_fd(((t_env *)temp->content)->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(((t_env *)temp->content)->val, 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}
	return (SUCCESS);
}
