/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/27 17:47:05 by cgaillag         ###   ########.fr       */
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

void	ft_update_pwd(t_cmd *cmd, t_data *data)
{
	t_env	*env;
//	t_token	*token;
	char	*oldpwd;

	(void) cmd;// voir si on enlève le paramètre
	env = data->env;
//	token = cmd->token->next;
	oldpwd = NULL;
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", ft_strlen(env->var_equal)) == 0)
		{
			oldpwd = ft_strdup(env->content);
			if (!oldpwd)
				return ; //free malloc!!
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
	env = data->env;
	while (env)
	{
		if (ft_strncmp(env->var_equal, "OLDPWD=", ft_strlen(env->var_equal)) == 0)
		{
			free(env->content);
			env->content = ft_strdup(oldpwd);
			free(env->envp);
			env->envp = ft_strjoin(env->var_equal, env->content);
			if (!env->envp)
				return ; //free malloc !!
			break ;
		}
		env = env->next;
	}
	if (oldpwd)
		free(oldpwd);
	if (data->oldpwd)
		free(data->oldpwd);
	data->oldpwd = ft_strdup(data->cwd);
	if (!data->oldpwd)
		return ;//free malloc !!
	free(data->cwd);
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return ;//free malloc !!
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
		if (chdir("/mnt/nfs/homes/lmelard/") == -1)
			return (ft_msg(errno, ERRMSG, "", strerror(errno)));
		printf("cd tout seul\n");
		ft_update_pwd(cmd, data);
		return (0);
	}
	if (token->next)
		return (ft_msg(1, "cd: ", "", ERRARG));
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
		return (ft_msg(errno, ERRMSG, "", strerror(errno)));
}
