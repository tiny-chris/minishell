/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/17 18:40:44 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	mettre à jour OLDPWD et PWD et data->cwd

	1 - nb arg: syntax
	2 - access
	3 - opendir :
		int et si ok close
	4 - chdir
*/

int	ft_update_cwd(t_token *t, t_data *data, int flag)
{
	if (data->oldpwd)
		ft_handle_malloc(DELONE, data->oldpwd, 0, NULL);
	data->oldpwd = ft_strdup(data->cwd);
	ft_handle_malloc(flag + TAB_STR1, data->oldpwd, 0, data);
	ft_handle_malloc(DELONE, data->cwd, 0, NULL);
	if (t && (ft_strncmp(t->token, "//", 2) == 0 && ft_strlen(t->token) == 2))
		data->cwd = ft_strdup("//");
	else
	{
		data->cwd = getcwd(NULL, 0);
		if (!data->cwd)
			return (ft_msg(1, "error retrieving current directory: ", "getcwd: ", "cannot access parent directories: No such file or directory"));//
	}
	ft_handle_malloc(flag + TAB_STR1, data->cwd, 0, data);
	return (0);
}

/*	t_env *env et env = data->env
	char *oldpwd = NULL
	int	pwd_null = 0

	- mise à jour des variables dans data : data->cwd et data->oldpwd
	puis
	1. mise à jour PWD
	  si PWD existe
		a)	si (env->content) existe
				--> var oldpwd = ft_strdup(env->content); avec protection malloc
			sinon
				--> var oldpwd == NULL
		b) mise à jour de PWD env->content :
			si (env->content) existe / n'est pas NULL
				--> on nettoie env->content : free(env->content)
					+ on alimente env->content : env->content = getcwd(NULL, 0)
			sinon
				--> on alimente env->content : env->content = getcwd(NULL, 0)
		c) mise à jour de PWD env->envp :
			si (env->envp) existe / n'est pas NULL
				--> on nettoie env->envp : free(env->envp)
					+ on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
			sinon
				--> on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
	  sinon (si PWD n'existe pas, i.e. unset)
		--> mettre var oldpwd == NULL (laisser à NULL)
			mettre var pwd = 1
			+ ne rien faire d'autre, i.e. le maillon est supprimé via unset PWD

	2. mise à jour OLDPWD
	  si OLDPWD existe
	  	si PWD existe
			a) mise à jour de OLPDWD env->content
				si (env->content) existe / n'est pas NULL
					--> on nettoie env->content : free(env->content)
						+ on alimente env->content : env->content = var oldpwd (NULL ou non)
				sinon
					--> on alimente env->content : env->content = var oldpwd (NULL ou non)
			b) mise à jour de OLDPWD env->envp
				i (env->envp) existe / n'est pas NULL
					--> on nettoie env->envp : free(env->envp)
						+ on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
				sinon
					--> on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
		sinon (si PWD n'existe pas, i.e. unset) : si var pwd_null = 1
			si OLDPWD == NULL et var pwd_null = 1
				--> on alimente env->content avec data->oldpwd : env->content = ft_strdup(data->oldpwd)
			sinon (si OLDPWD != NULL et pwd_null = 1)
				--> on nettoie env->content : free(env->content)
					mise à jour de OLDPWD env->content à NULL (vide)
	  sinon (OLDPWD n'existe pas = unset)
	  	si PWD existe
			--> on ne fait rien car le maillon est supprimé via unset PWD
		sinon (si PWD n'existe pas, i.e. unset) : si var pwd_null = 1
			--> on ne fait rien car le maillon est supprimé via unset PWD

*/
int	ft_update_pwd(t_cmd *cmd, t_data *data, int flag)
{
	t_env	*env;
	char	*oldpwd;
	int		pwd_null;
	t_token	*token;

	env = data->env;
	oldpwd = NULL;
	pwd_null = 0;
	token = cmd->token->next;
	if (ft_update_cwd(token, data, flag))
		return (1);
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", 4) == 0 && (ft_strlen(env->var_equal) == 4))
		{
			if (env->content)
			{
				oldpwd = ft_strdup(env->content);
				ft_handle_malloc(flag + TAB_STR1, oldpwd, 0, data);
				ft_handle_malloc(DELONE, env->content, 0, NULL);
			}
			if (token && ft_strncmp(token->token, "//", 2) == 0 && ft_strlen(token->token) == 2)
				env->content = ft_strdup(token->token);
			else
			{
				env->content = getcwd(NULL, 0);
				if (!env->content)
					return (ft_msg(1, "error retrieving current directory: ", "getcwd: ", "cannot access parent directories: No such file or directory"));//
			}
			ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
			if (env->envp)
				ft_handle_malloc(DELONE, env->envp, 0, NULL);
			env->envp = ft_strjoin(env->var_equal, env->content);
			ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		oldpwd = NULL;
		pwd_null = 1;
	}
	env = data->env;
	while (env)
	{
		if (ft_strncmp(env->var_equal, "OLDPWD=", 7) == 0 \
			&& (ft_strlen(env->var_equal) == 7))
		{
			if (pwd_null == 1)
			{
				if (env->content)
				{
					ft_handle_malloc(DELONE, env->content, 0, NULL);
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, NULL);
					env->envp = ft_strdup("OLDPWD=");
					ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
				}
				else
				{
					env->content = ft_strdup(data->oldpwd);
					ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, NULL);
					env->envp = ft_strjoin(env->var_equal, env->content);
					ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
				}
			}
			else
			{
				if (!oldpwd)
				{
					ft_handle_malloc(DELONE, env->content, 0, NULL);
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, NULL);
					env->envp = ft_strdup("OLDPWD=");
					ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
				}
				else
				{
					ft_handle_malloc(DELONE, env->content, 0, NULL);
					env->content = ft_strdup(oldpwd);
					ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, NULL);
					env->envp = ft_strjoin(env->var_equal, env->content);
					ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
				}
			}
			break ;
		}
		env = env->next;
	}
	if (oldpwd)
		ft_handle_malloc(DELONE, oldpwd, 0, NULL);
	return (0);
}

// for "stale file handle"
/* 

When the directory is deleted, the inode for that directory (and the inodes for its contents) are recycled. The pointer your shell has to that directory's inode (and its contents's inodes) are now no longer valid. When the directory is restored from backup, the old inodes are not (necessarily) reused; the directory and its contents are stored on random inodes. The only thing that stays the same is that the parent directory reuses the same name for the restored directory (because you told it to).

Now if you attempt to access the contents of the directory that your original shell is still pointing to, it communicates that request to the file system as a request for the original inode, which has since been recycled (and may even be in use for something entirely different now). So you get a stale file handle message because you asked for some nonexistent data.

When you perform a cd operation, the shell reevaluates the inode location of whatever destination you give it. Now that your shell knows the new inode for the directory (and the new inodes for its contents), future requests for its contents will be valid.

*/
// https://stackoverflow.com/questions/20105260/what-does-stale-file-handle-in-linux-mean
// 

int	ft_cd(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;
	DIR		*directory;
	int		res;

	directory = NULL;
	token = cmd->token;
	token = token->next;
	if (token == NULL)
	{
		ft_get_home(data, flag);
		if (data->home == NULL)
			return (ft_msg(1, cmd->token->token, ": ", ERRHOM));
		else if (data->home[0] == '\0')
			return (0);
		if (chdir(data->home) == -1)
			return (ft_msg(errno, data->home, ": ", strerror(errno)));
		ft_update_pwd(cmd, data, flag);
		return (0);
	}
	if (token->next)
		return (ft_msg(1, cmd->token->token, ": ", ERRARG));
	if (access(token->token, F_OK) == 0)
	{
		directory = opendir(token->token);
		if (directory == NULL)
			return (ft_msg(1, token->token, ": ", ERRNDR));
		closedir(directory);
		res = chdir(token->token);
		if (res != 0)
			return (ft_msg(1, token->token, ": ", strerror(errno)));
		if (ft_update_pwd(cmd, data, flag))
			return (1);
		return (0);
	}
	else
		return (ft_msg(1, token->token, ": ", strerror(errno)));
}
