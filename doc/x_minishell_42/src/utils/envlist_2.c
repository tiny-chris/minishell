/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:48:39 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 17:48:39 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Convert envlist to envtab
 */

char	**ft_update_envtab(t_data *data)
{
	t_dlist	*temp;
	char	**envtab;
	int		i;

	temp = data->envlist;
	envtab = ft_w_malloc
		(data, sizeof (char *)
			* (long unsigned int)(ft_dlstsize(data->envlist) + 1));
	i = 0;
	while (temp)
	{
		envtab[i] = ft_strjoin (((t_env *)temp->content)->key, "=");
		envtab[i] = ft_strjoin_free_s1
			(envtab[i], ((t_env *)temp->content)->val);
		i++;
		temp = temp->next;
	}
	envtab[i] = NULL;
	return (envtab);
}

/*
 ** Return 1 if the entry key is defined in envlist.
 */

int	ft_check_env_entry(t_dlist *envlist, char *key)
{
	t_dlist	*temp;
	char	*envkey;
	size_t	keylen;
	size_t	envkeylen;

	temp = envlist;
	keylen = ft_strlen(key);
	while (temp)
	{
		envkey = ((t_env *)temp->content)->key;
		envkeylen = ft_strlen (envkey);
		if (keylen == envkeylen && !ft_strncmp (key, envkey, envkeylen))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

/*
 ** Return the 'value' attached to the given 'key' within minishel env.
 */

char	*ft_getenv(t_data *data, t_dlist *envlist, char *key)
{
	t_dlist	*temp;
	char	*envkey;
	size_t	keylen;
	size_t	envkeylen;

	temp = envlist;
	keylen = ft_strlen(key);
	while (temp)
	{
		envkey = ((t_env *)temp->content)->key;
		envkeylen = ft_strlen (envkey);
		if (keylen == envkeylen && !ft_strncmp (envkey, key, envkeylen))
			return (ft_w_strdup(data, ((t_env *)temp->content)->val));
		temp = temp->next;
	}
	return (NULL);
}

/*
 ** Set the minimal env, in case there is no env in the parent shell.
 **
 ** $ env -i bash
 ** $ env
 **
 **		PWD=/mnt/nfs/homes/cvidon/git/minishell_42
 **		SHLVL=1
 **		_=/usr/bin/env
 */

void	ft_init_minimal_env(t_data *data)
{
	ft_add_env (data, ft_w_strdup(data, "PWD"), ft_w_getcwd(data));
	ft_add_env (data, ft_w_strdup(data, "SHLVL"), ft_w_strdup(data, "1"));
	ft_add_env (data, ft_w_strdup(data, "_"), ft_w_getcwd(data));
}

/*
 ** Initialize the env.
 **
 ** - Generate the env based on 'environ' the parent shell 'env'.
 ** - Set PWD to CWD if it is unset.
 ** - SHELL is set to 'minishell'.
 */

void	ft_init_env(t_data *data)
{
	char			*key;
	char			*val;
	int				i;
	unsigned int	j;

	if (!data->environ)
		ft_exitmsg (data, "env");
	i = -1;
	if (*data->environ == NULL)
		return (ft_init_minimal_env(data));
	while (data->environ[++i] != NULL)
	{
		j = 0;
		while (data->environ[i][j] != '=')
			j++;
		key = ft_w_substr (data, data->environ[i], 0, j);
		if (ft_strncmp(key, "PWD", 3) == SUCCESS && !key[3])
			val = ft_w_getcwd(data);
		else if (ft_strncmp(key, "SHELL", 3) == SUCCESS && !key[5])
			val = ft_w_strdup(data, "minishell");
		else
			val = ft_w_substr(data, data->environ[i], j + 1,
					ft_strlen(data->environ[i]) - j);
		ft_add_env (data, key, val);
	}
}
