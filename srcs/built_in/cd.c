/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/28 01:28:23 by cgaillag         ###   ########.fr       */
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

void	ft_update_cwd(t_data *data)
{
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
	data->oldpwd = ft_strdup(data->cwd);
	if (!data->oldpwd)
		return ;//free malloc !!
	free(data->cwd);
	data->cwd = NULL;
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return ;//free malloc !!
	dprintf(2, "val de cwd updated = %s\n", data->cwd);//
}

void	ft_update_pwd(t_cmd *cmd, t_data *data)
{
	t_env	*env;
	char	*oldpwd;

	(void) cmd;// voir si on enlève le paramètre
	env = data->env;
	oldpwd = NULL;
	ft_update_cwd(data);
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", ft_strlen(env->var_equal)) == 0)
		{
			oldpwd = ft_strdup(env->content);
			if (!oldpwd)
			{
				printf("pwd est vide\n");
				return ; //free malloc!!
			}
			if (env->content)
				free(env->content);
			env->content = NULL;
			env->content = getcwd(NULL, 0);
			if (!env->content)
				return ; //free malloc!!
			free(env->envp);
			env->envp = ft_strjoin(env->var_equal, env->content);
			if (!env->envp)
				return ;//free malloc !!
			break ;
		}
		env = env->next;
	}
	//ajout d'une condition si oldpwd == NULL
	env = data->env;
	while (env)
	{
		if (ft_strncmp(env->var_equal, "OLDPWD=", ft_strlen(env->var_equal)) == 0)
		{
			if (env->content)
			{
				free(env->content);
				env->content = NULL;
			}
			if (oldpwd)
			{
				env->content = ft_strdup(oldpwd);
				if (!env->content)
					return ; //free malloc !!
			}
			if (env->envp)
				free(env->envp);
			printf("env car equal %s\n", env->var_equal);
			env->envp = ft_strjoin(env->var_equal, env->content);
			printf("env envp de OLDPWD qd pwd est vide %s\n", env->envp);
			if (!env->envp)
				return ; //free malloc !!
			break ;
		}
		env = env->next;
	}
	if (oldpwd)
		free(oldpwd);
	return ;
	// if (data->oldpwd)
	// 	free(data->oldpwd);
	// data->oldpwd = ft_strdup(data->cwd);
	// if (!data->oldpwd)
	// 	return ;//free malloc !!
	// free(data->cwd);
	// data->cwd = getcwd(NULL, 0);
	// if (!data->cwd)
	// 	return ;//free malloc !!
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	DIR		*directory;

	directory = NULL;
	token = cmd->token;
	token = token->next;
	if (token == NULL)
	{
		ft_get_home(data);
		if (data->home == NULL)
			return (ft_msg(1, cmd->token->token, ": ", ERRHOM));
		if (chdir(data->home) == -1)
			return (ft_msg(errno, data->home, ": ", strerror(errno)));
		printf("cd tout seul\n");
		ft_update_pwd(cmd, data);
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
		if (chdir(token->token) == -1)
			return (ft_msg(errno, ERRMSG, "", strerror(errno)));
		ft_update_pwd(cmd, data);
		return (0);
	}
	else
		return (ft_msg(errno, token->token, ": ", strerror(errno)));
}
