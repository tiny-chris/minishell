/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:22 by cvidon            #+#    #+#             */
/*   Updated: 2022/07/14 15:15:55 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Note about PWD and OLDPWD behavior:
 **
 ** $		: command line
 **		>>>	: output
 **
 **	$ bash --posix
 **		$ export | grep PWD && env | grep PWD
 **		>>> declare -x OLDPWD="/mnt/nfs/homes/cvidon"
 **		>>> declare -x PWD="/mnt/nfs/homes/cvidon"
 **		>>> OLDPWD=/mnt/nfs/homes/cvidon
 **		>>> PWD=/mnt/nfs/homes/cvidon
 **
 ** Case: 3. unset OLDPWD PWD
 ** ---------------------
 **
 **		$ unset OLDPWD PWD
 **
 **		$ export | grep PWD && env | grep PWD
 **		>>>
 **		>>>
 **
 **		$ echo $OLDPWD && echo $PWD
 **		>>>
 **		$ cd ..
 **
 **		$ export | grep PWD && env | grep PWD
 **		>>>
 **		>>>
 **
 **		$ echo $OLDPWD && echo $PWD
 **		>>>
 **		>>> /mnt/nfs/homes
 **
 **		$ cd ..
 **
 **		$ export | grep PWD && env | grep PWD
 **		>>>
 **		>>>
 **
 **		$ echo $OLDPWD && echo $PWD
 **		>>> /mnt/nfs/homes
 **		>>> /mnt/nfs
 **
 **		Question: Why OLDPWD and PWD exist? if it is not in 'env' nor
 **		in 'export'.
 **
 **		Conclusion: It may be like $PATH that is set even tho it doesnt appear
 **		in 'env' nor in 'export' with 'env -i'.
 **
 **		Fix: We can set PWD and OLDPWD variables somewhere else than the
 **		'export' and 'env' lists, based on CWD. This way they stay accessible.
 */

/*
 ** Change the CWD if the given PATH is valid.
 **
 ** 'bash: cd: /mnt/nfs/homes/cvidon/U: No such file or directory'
 */

static int	ft_chdir(char *path)
{
	if (path)
	{
		if (!chdir(path) == SUCCESS)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(path, 1);
			ft_putstr_fd(": ", 1);
			ft_putstr_fd(strerror(errno), 1);
			ft_putstr_fd("\n", 1);
			return (FALSE);
		}
	}
	return (TRUE);
}

/*
 ** Set the CWD to the given path if valid.
 */

static int	ft_cd_path(t_data *data, char *cmd)
{
	char	*cwd;

	if (!ft_chdir (cmd))
		return (FAILURE);
	ft_update_oldpwd (data, data->cwd);
	cwd = ft_w_getcwd(data);
	ft_update_pwd (data, cwd);
	free (cwd);
	return (SUCCESS);
}

/*
 ** 'cd' is called with '-':
 **
 ** If OLPWD exist we swap current OLDPWD and PWD's values.
 ** Otherwise we throw an error, return 1, and do nothing.
 */

static int	ft_cd_hyphen(t_data *data)
{
	char	*swap;

	if (!data->oldcwd || !*data->oldcwd)
		return (ft_putstr_fd ("minishell: cd: OLDPWD not set\n", 2), FAILURE);
	if (!ft_chdir (data->oldcwd))
		return (FAILURE);
	swap = ft_w_strdup(data, data->oldcwd);
	ft_update_oldpwd (data, data->cwd);
	ft_update_pwd (data, swap);
	ft_free (swap);
	ft_pwd (data);
	return (SUCCESS);
}

/*
 ** Handle 'cd' call without arguments, set CWD to HOME.
 */

static int	ft_cd_alone(t_data *data)
{
	char	*homedir;

	homedir = ft_getexp (data, data->explist, "HOME");
	if (!ft_check_exp_entry (data->explist, "HOME") || !*homedir)
	{
		ft_free (homedir);
		return (ft_putstr_fd ("minishell: cd: HOME not set\n", 2), FAILURE);
	}
	if (!ft_chdir (homedir))
	{
		ft_free (homedir);
		return (FAILURE);
	}
	ft_update_oldpwd (data, data->cwd);
	ft_update_pwd (data, homedir);
	ft_free (homedir);
	return (SUCCESS);
}

/*
 ** Tiny 'cd' builtin.
 **
 ** - PWD and OLDPWD still exist elsewhere than 'export' or 'env' list, they are
 **   always updated according to the CWD, we will call them PWD and OLDPWD
 **   'persistent clones'.
 ** - If OLDPWD and PWD vars exist among 'export' or 'env' list they will be
 **   given the value of their persistent clone, if they dont exist they won't
 **   be created and their persistent clone will be used.
 ** - (Cf. 'Note about PWD and OLDPWD behavior' above)
 */

int	ft_cd(t_data *data, char **cmd)
{
	int	ret;

	ret = SUCCESS;
	if (!cmd[1])
		return (ft_cd_alone (data));
	if (cmd[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), FAILURE);
	if (ft_strncmp (cmd[1], "-", 2) == 0)
		return (ft_cd_hyphen (data));
	ret = ft_cd_path (data, cmd[1]);
	return (ret);
}
