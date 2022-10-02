/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explist_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:20:23 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 18:20:23 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Remove the given entry from explist.
 */

t_dlist	*ft_remove_exp(t_dlist *explist, t_dlist *entry)
{
	if (explist && entry)
	{
		if (explist == entry)
			explist = entry->next;
		if (entry->next)
			entry->next->prev = entry->prev;
		if (entry->prev)
			entry->prev->next = entry->next;
		free(((t_exp *) entry->content)->key);
		free(((t_exp *) entry->content)->val);
		free(entry->content);
		return (explist);
	}
	return (NULL);
}

/*
 ** Set the minimal export, in case there is no env in the parent shell.
 **
 ** $ env -i bash
 ** $ export
 **
 **		declare -x OLDPWD
 **		declare -x PWD="/mnt/nfs/homes/cvidon/git/minishell_42"
 **		declare -x SHLVL="1"
 */

void	ft_init_minimal_exp(t_data *data)
{
	ft_add_exp (data, ft_w_strdup(data, "OLDPWD"), NULL);
	ft_add_exp (data, ft_w_strdup(data, "PWD"), ft_w_getcwd(data));
	ft_add_exp (data, ft_w_strdup(data, "SHLVL"), ft_w_strdup(data, "1"));
}

/*
 ** Initialize export.
 **
 ** Generate export according to 'environ' except for:
 ** - '_' var from 'environ' that is ignored.
 ** - Set PWD to CWD if it is unset.
 ** - SHELL is set to 'minishell'.
 */

void	ft_init_exp_2(t_data *data, unsigned int i, unsigned int j)
{
	char	*key;
	char	*val;

	key = ft_w_substr (data, data->environ[i], 0, j);
	if (ft_strncmp(key, "_", 2) != SUCCESS)
	{
		if (ft_strncmp (key, "PWD", 3) == SUCCESS)
			val = getcwd (NULL, PATH_MAX);
		else if (ft_strncmp(key, "SHELL", 3) == SUCCESS && !key[5])
			val = ft_w_strdup(data, "minishell");
		else
			val = ft_w_substr (data, data->environ[i],
					j + 1, ft_strlen (data->environ[i]) - j);
		if (val == NULL)
			ft_add_exp (data, ft_w_strdup(data, key), ft_strdup(val));
		else
			ft_add_exp (data,
				ft_w_strdup(data, key), ft_w_strdup(data, val));
		ft_free(val);
		ft_free(key);
	}
	else
		ft_free (key);
}

void	ft_init_exp(t_data *data)
{
	unsigned int	i;
	unsigned int	j;

	if (!data->environ)
		ft_exitmsg (data, "malloc");
	i = 0;
	if (*data->environ == NULL)
	{
		ft_init_minimal_exp(data);
		return ;
	}
	while (data->environ[i] != NULL)
	{
		j = 0;
		while (data->environ[i][j] != '=')
			j++;
		ft_init_exp_2 (data, i, j);
		i++;
	}
	ft_sort_exp(data, data->explist);
}
