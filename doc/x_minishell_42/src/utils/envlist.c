/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:48:30 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 17:48:30 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Remove the given entry from envlist.
 */

t_dlist	*ft_remove_env(t_dlist *envlist, t_dlist *entry)
{
	if (envlist && entry)
	{
		if (envlist == entry)
		{
			envlist = entry->next;
		}
		if (entry->next)
			entry->next->prev = entry->prev;
		if (entry->prev)
			entry->prev->next = entry->next;
		free(((t_env *) entry->content)->key);
		free(((t_env *) entry->content)->val);
		free(entry->content);
		return (envlist);
	}
	return (NULL);
}

/*
 ** Init an env list or add variable to it
 **
 ** Les vars viennent de environ donc de la stack.
 */

void	ft_add_env(t_data *data, char *key, char *val)
{
	t_env	*env;

	env = ft_w_malloc (data, sizeof(t_env));
	env->key = key;
	env->val = val;
	ft_dlstadd_back(&data->envlist, ft_dlstnew(env));
}

/*
 ** Print the variable attached to the given 'key' within minishel env.
 */

void	ft_printlist_elem_env(t_data *data, t_dlist *envlist, char *key)
{
	char	*val;

	val = ft_getenv (data, envlist, key);
	if (val && *val)
	{
		ft_printf("%s=%s\n", key, val);
	}
	ft_free (val);
}

/*
 ** Print env list
 */

void	ft_printlist_env(t_dlist *envlist)
{
	t_dlist	*temp;

	temp = envlist;
	while (temp)
	{
		ft_printf ("%s=%s\n",
			((t_env *)temp->content)->key,
			((t_env *)temp->content)->val);
		temp = temp->next;
	}
}

/*
 ** Clear an env list
 */

void	ft_clearlist_env(t_dlist **envlist, void (*del)(void *))
{
	t_dlist	*ptr;

	if (!envlist || !del)
		return ;
	ptr = *envlist;
	while (ptr != NULL)
	{
		*envlist = (*envlist)->next;
		del(((t_env *)ptr->content)->val);
		del(((t_env *)ptr->content)->key);
		del(ptr->content);
		del(ptr);
		ptr = *envlist;
	}
}
