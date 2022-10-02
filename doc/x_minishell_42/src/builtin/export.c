/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:44:04 by clem              #+#    #+#             */
/*   Updated: 2022/07/14 15:20:36 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Export data->cwd and data->oldcwd.
 **
 ** If   cmd has    '=' then 'key=value'
 ** Else cmd = 'key' and value is NULL
 **
 ** If 'key' == "PWD"
 **   If   cmd has '+' -> concate
 **   Else             -> replace
 ** If 'key' == "OLDPWD"
 **   If   cmd has '+' -> concate
 **   Else             -> replace
 */

static void	ft_data_export_pwd(t_data *data, char *cmd, char **val)
{
	if (cmd[ft_strlen (cmd) - ft_strlen (*val) - 2] == '+')
		data->cwd = ft_strjoin_free_s1 (data->cwd, *val);
	else
	{
		ft_free (data->cwd);
		data->cwd = ft_w_strdup(data, *val);
	}
}

static void	ft_data_export_oldpwd(t_data *data, char *cmd, char **val)
{
	if (cmd[ft_strlen (cmd) - ft_strlen (*val) - 2] == '+')
		data->oldcwd = ft_strjoin_free_s1 (data->oldcwd, *val);
	else
	{
		ft_free (data->oldcwd);
		data->oldcwd = ft_w_strdup(data, *val);
	}
}

static void	ft_data_export(t_data *data, char *cmd)
{
	char	*val;
	char	*key;

	if (ft_strchr (cmd, '='))
	{
		val = ft_w_strdup(data, ft_strchr (cmd, '=') + 1);
		key = ft_w_substr(data, cmd, 0, ft_strlen (cmd) - ft_strlen (val) - 1
				- (cmd[ft_strlen (cmd) - ft_strlen(val) - 2] == '+'));
	}
	else
	{
		val = NULL;
		key = ft_w_strdup(data, cmd);
	}
	if (ft_strlen(key) == 3 && ft_strcmp (key, "PWD") == SUCCESS)
		ft_data_export_pwd(data, cmd, &val);
	if (ft_strlen(key) == 6 && ft_strcmp (key, "OLDPWD") == SUCCESS)
		ft_data_export_oldpwd(data, cmd, &val);
	ft_free (val);
	ft_free (key);
}

/*
 ** Check the given arguments validity.
 **
 ** - KEY can only start with an ALPHA or an '_'.
 ** - KEY can only be ALPHANUMERIC or '_'.
 */

static int	ft_is_valid_export(char *key)
{
	char	*keyptr;

	keyptr = key;
	if (ft_isalpha (*key) || *key == '_')
	{
		while (*key && (ft_isalnum (*key) || *key == '_'))
			key++;
		if (*key == '\0')
			return (1);
		if ((*key == '=') || (*key == '+' && *(key + 1) == '='))
			return (2);
	}
	ft_putstr_fd ("minishell: export: `", 2);
	ft_putstr_fd (keyptr, 2);
	ft_putstr_fd ("': not a valid identifier\n", 2);
	return (FALSE);
}

/*
 ** Tiny 'export' builtin.
 **
 ** - Multiple export at once possible.
 ** - Each wrong ARG print an ERRMSG, set return value to 1 but doesnt interrupt
 **   the command execution. No ERRMSG sets return value to 0.
 **
 **   export [key[=val]] ...
 **
 ** - ARG are SPACE SEPARATED. (so `export KEY = VAL` -> ERROR)
 ** - ARG without '=' terminated KEY will be DECLARED only & exported to
 **   EXPLIST only.
 ** - EXPLIST saves variables from LEFT to RIGHT. TODO:?
 ** - ENVLIST saves variables from RIGHT to LEFT. TODO:?
 ** - ARG with '=' terminated KEY will be DEFINED & exported to ENVLIST AND
 **   EXPLIST.
 */

int	ft_export(t_data *data, char **cmd)
{
	int		i;
	int		ret;
	int		valid;

	ret = SUCCESS;
	if (!cmd[1])
		ft_printlist_exp(data, data->explist);
	i = 1;
	while (cmd[i])
	{
		valid = ft_is_valid_export (cmd[i]);
		if (!valid)
			ret = FAILURE;
		else if (valid == 1)
			ft_explist_export (data, cmd[i]);
		else if (valid == 2)
		{
			ft_data_export (data, cmd[i]);
			ft_explist_export (data, cmd[i]);
			ft_envlist_export (data, cmd[i]);
		}
		i++;
	}
	return (ret);
}
