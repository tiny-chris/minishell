/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:20:28 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 18:20:28 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Init an export list or add a variable to it.
 */

void	ft_add_exp(t_data *data, char *key, char *val)
{
	t_exp	*var;

	var = ft_w_malloc (data, sizeof(t_exp));
	var->key = key;
	var->val = val;
	ft_dlstadd_back(&data->explist, ft_dlstnew(var));
}

/*
 ** Print the variable attached to the given 'key' within minishel exp.
 */

void	ft_printlist_elem_exp(t_data *data, t_dlist *explist, char *key)
{
	char	*val;

	if (ft_check_exp_entry (explist, key))
	{
		val = ft_getexp (data, explist, key);
		ft_putstr_fd("declare -x ", 1);
		if (!val)
		{
			ft_putstr_fd(key, 1);
			ft_putstr_fd("\n", 1);
		}
		else if (!*val)
		{
			ft_putstr_fd(key, 1);
			ft_putstr_fd("=\"\"\n", 1);
		}
		else if (val && *val)
		{
			ft_putstr_fd(key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(val, 1);
			ft_putstr_fd("\"\n", 1);
		}
		ft_free (val);
	}
}

/*
 ** Print export list
 */

void	ft_printlist_exp_2(t_dlist *temp)
{
	ft_putstr_fd("declare -x ", 1);
	if (!((t_exp *)temp->content)->val)
	{
		ft_putstr_fd(((t_exp *)temp->content)->key, 1);
		ft_putstr_fd("\n", 1);
	}
	else if (!*((t_exp *)temp->content)->val)
	{
		ft_putstr_fd(((t_exp *)temp->content)->key, 1);
		ft_putstr_fd("=\"\"\n", 1);
	}
	else
	{
		ft_putstr_fd(((t_exp *)temp->content)->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(((t_exp *)temp->content)->val, 1);
		ft_putstr_fd("\"\n", 1);
	}
}

void	ft_printlist_exp(t_data *data, t_dlist *explist)
{
	t_dlist	*temp;

	ft_sort_exp (data, explist);
	temp = explist;
	while (temp)
	{
		ft_printlist_exp_2 (temp);
		temp = temp->next;
	}
}

/*
 ** Clear an exp list
 */

void	ft_clearlist_exp(t_dlist **explist, void (*del)(void *))
{
	t_dlist	*ptr;

	if (!explist || !del)
		return ;
	ptr = *explist;
	while (ptr != NULL)
	{
		*explist = (*explist)->next;
		del(((t_exp *)ptr->content)->val);
		del(((t_exp *)ptr->content)->key);
		del(ptr->content);
		del(ptr);
		ptr = *explist;
	}
}
