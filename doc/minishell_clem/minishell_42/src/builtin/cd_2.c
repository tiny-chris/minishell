/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:13 by cvidon            #+#    #+#             */
/*   Updated: 2022/07/14 15:15:05 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Update env and export PWD.
 ** As well as data->cwd.
 */

void	ft_update_pwd(t_data *data, char *newpwd)
{
	char	*str;
	char	**exportcmd;
	char	**unsetcmd;

	if (ft_check_exp_entry (data->explist, "PWD"))
	{
		if (newpwd)
		{
			str = ft_strjoin ("export PWD=", newpwd);
			exportcmd = ft_split(str, ' ');
			if (!exportcmd)
				ft_exitmsg (data, "malloc");
			ft_free (str);
		}
		else
			exportcmd = ft_split("export PWD", ' ');
		unsetcmd = ft_split("unset PWD", ' ');
		ft_unset (data, unsetcmd);
		ft_export (data, exportcmd);
		ft_free_tab (unsetcmd);
		ft_free_tab (exportcmd);
	}
	ft_free (data->cwd);
	data->cwd = ft_w_strdup(data, newpwd);
}

/*
 ** Update env and export OLDPWD.
 ** As well as data->oldcwd.
 */

static void	ft_update_oldpwd_2(t_data *data, char **exportcmd)
{
	char	**unsetcmd;

	unsetcmd = ft_split("unset OLDPWD", ' ');
	if (!unsetcmd)
		ft_exitmsg (data, "malloc");
	ft_unset (data, unsetcmd);
	ft_export (data, exportcmd);
	ft_free_tab (unsetcmd);
	ft_free_tab (exportcmd);
}

void	ft_update_oldpwd(t_data *data, char *oldpwd)
{
	char	*str;
	char	**exportcmd;

	if (ft_check_exp_entry (data->explist, "OLDPWD"))
	{
		if (*oldpwd)
		{
			str = ft_strjoin ("export OLDPWD=", oldpwd);
			exportcmd = ft_split(str, ' ');
			if (!exportcmd)
				ft_exitmsg (data, "malloc");
			ft_free (str);
		}
		else
		{
			exportcmd = ft_split("export OLDPWD", ' ');
			if (!exportcmd)
				ft_exitmsg (data, "malloc");
		}
		ft_update_oldpwd_2 (data, exportcmd);
	}
	ft_free (data->oldcwd);
	data->oldcwd = ft_w_strdup(data, oldpwd);
}
