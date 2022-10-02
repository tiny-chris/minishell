/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:25:15 by clem              #+#    #+#             */
/*   Updated: 2022/06/27 18:25:15 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Unset data->cwd and data->oldcwd.
 */

static void	ft_data_unset(t_data *data, char *cmd)
{
	if (ft_strlen(cmd) == 3 && ft_strcmp (cmd, "PWD") == SUCCESS)
	{
		ft_free (data->cwd);
		data->cwd = ft_w_strdup(data, "");
	}
	if (ft_strlen(cmd) == 6 && ft_strcmp (cmd, "OLDPWD") == SUCCESS)
	{
		ft_free (data->oldcwd);
		data->oldcwd = ft_w_strdup(data, "");
	}
}

/*
 ** Update the exp list of variables.
 */

static void	ft_explist_unset(t_data *data, char *key)
{
	char	*expkey;
	size_t	expkeylen;
	t_dlist	*temp;
	t_dlist	*freetemp;

	temp = data->explist;
	while (temp)
	{
		expkey = ((t_exp *)temp->content)->key;
		expkeylen = ft_strlen (expkey);
		if (ft_strlen (key) == expkeylen
			&& !ft_strncmp (expkey, key, expkeylen))
		{
			freetemp = temp;
			data->explist = ft_remove_exp (data->explist, temp);
			temp = temp->next;
			ft_free (freetemp);
		}
		else
			temp = temp->next;
	}
}

static void	ft_envlist_unset(t_data *data, char *key)
{
	char	*envkey;
	size_t	envkeylen;
	t_dlist	*temp;
	t_dlist	*freetemp;

	temp = data->envlist;
	while (temp)
	{
		envkey = ((t_env *)temp->content)->key;
		envkeylen = ft_strlen (envkey);
		if (ft_strlen (key) == envkeylen
			&& !ft_strncmp (envkey, key, envkeylen))
		{
			freetemp = temp;
			data->envlist = ft_remove_env (data->envlist, temp);
			temp = temp->next;
			ft_free (freetemp);
		}
		else
			temp = temp->next;
	}
}

/*
 ** Check the given arguments validity.
 */

static int	ft_is_valid_unset(char *key)
{
	if (!ft_isdigit (*key))
	{
		while (*key && (ft_isalnum (*key) || *key == '_'))
			key++;
		if (*key == '\0')
			return (TRUE);
	}
	return (FALSE);
}

/*
 ** Tiny 'unset' builtin.
 */

int	ft_unset(t_data *data, char **cmd)
{
	int		i;
	int		ret;

	ret = SUCCESS;
	i = 1;
	while (cmd[i])
	{
		if (!ft_is_valid_unset (cmd[i]))
			ret = SUCCESS;
		else
		{
			ft_data_unset (data, cmd[i]);
			ft_envlist_unset (data, cmd[i]);
			ft_explist_unset (data, cmd[i]);
		}
		i++;
	}
	return (ret);
}
