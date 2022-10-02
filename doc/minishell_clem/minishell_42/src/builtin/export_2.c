/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:45:04 by clem              #+#    #+#             */
/*   Updated: 2022/06/27 19:45:04 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Export the variable to 'explist'.
 **
 ** - ARG without '=' terminated KEY will be DECLARED only & exported to
 **   EXPLIST only.
 ** - EXPLIST saves variables from LEFT to RIGHT.
 **
 ** TODO:HELP On perd les pointeur si on mets les ft_free key/val dans
 ** ft_add_exp plutot qu'ici.
 */

static void
	ft_explist_export_2(t_data *data, char *cmd, t_dlist *temp, char **val)
{
	if (*val && cmd[ft_strlen (cmd) - ft_strlen (*val) - 2] == '+')
	{
		*val = ft_strjoin_free (((t_exp *) temp->content)->val, *val);
		((t_exp *) temp->content)->val = ft_w_strdup(data, *val);
	}
	else if (*val && ((t_exp *) temp->content)->val)
	{
		ft_free (((t_exp *) temp->content)->val);
		((t_exp *) temp->content)->val = ft_w_strdup(data, *val);
	}
	else if (*val && !**val && !((t_exp *) temp->content)->val)
	{
		ft_free (((t_exp *) temp->content)->val);
		((t_exp *) temp->content)->val = ft_w_strdup(data, *val);
	}
	else if (*val && !*val && !((t_exp *) temp->content)->val)
		((t_exp *) temp->content)->val = ft_w_strdup(data, *val);
}

static void	ft_explist_export_1(t_data *data, char *cmd, char **key, char **val)
{
	if (ft_strchr (cmd, '='))
	{
		*val = ft_w_strdup(data, ft_strchr (cmd, '=') + 1);
		*key = ft_w_substr(data, cmd, 0, ft_strlen (cmd) - ft_strlen (*val) - 1
				- (cmd[ft_strlen (cmd) - ft_strlen(*val) - 2] == '+'));
	}
	else
	{
		*val = NULL;
		*key = ft_w_strdup(data, cmd);
	}
}

void	ft_explist_export(t_data *data, char *cmd)
{
	char	*val;
	char	*key;
	t_dlist	*temp;

	temp = data->explist;
	val = NULL;
	key = NULL;
	ft_explist_export_1 (data, cmd, &key, &val);
	if (ft_check_exp_entry (data->explist, key))
	{
		while (temp)
		{
			if (ft_strncmp(((t_exp *) temp->content)->key, key, 3) == SUCCESS)
				ft_explist_export_2(data, cmd, temp, &val);
			temp = temp->next;
		}
	}
	else if (val == NULL)
		ft_add_exp (data, ft_w_strdup(data, key), ft_strdup(val));
	else
		ft_add_exp (data, ft_w_strdup(data, key), ft_w_strdup(data, val));
	ft_free (val);
	ft_free (key);
}

/*
 ** Export the variable to 'envlist'.
 **
 ** - ENVLIST saves variables from RIGHT to LEFT.
 */

static void
	ft_envlist_export_2(t_data *data, char *cmd, char **val, t_dlist *temp)
{
	if (*val && cmd[ft_strlen (cmd) - ft_strlen (*val) - 2] == '+')
	{
		*val = ft_strjoin_free (((t_env *) temp->content)->val, *val);
		((t_env *) temp->content)->val = ft_w_strdup(data, *val);
	}
	else if (*val && ((t_env *) temp->content)->val)
	{
		ft_free (((t_env *) temp->content)->val);
		((t_env *) temp->content)->val = ft_w_strdup(data, *val);
	}
}

void	ft_envlist_export(t_data *data, char *cmd)
{
	char	*val;
	char	*key;
	t_dlist	*temp;

	temp = data->envlist;
	val = ft_w_strdup(data, ft_strchr (cmd, '=') + 1);
	key = ft_w_substr(data, cmd, 0, ft_strlen (cmd) - ft_strlen (val) - 1
			- (cmd[ft_strlen (cmd) - ft_strlen(val) - 2] == '+'));
	if (ft_check_env_entry (data->envlist, key))
	{
		while (temp)
		{
			if (ft_strncmp(((t_env *) temp->content)->key, key, 3) == SUCCESS)
				ft_envlist_export_2(data, cmd, &val, temp);
			temp = temp->next;
		}
	}
	else
		ft_add_env (data, ft_w_strdup(data, key), ft_w_strdup(data, val));
	ft_free (val);
	ft_free (key);
}
