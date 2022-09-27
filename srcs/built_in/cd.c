/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/27 12:34:22 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	mettre à jour OLDPWD et PWD et data->cwd

	1 - nb arg: syntax
	2 - opendir :
		int et si ok close
	3 - access
	4 - chdir
*/

void	ft_update_pwd(t_cmd *cmd, t_data *data)
{
	t_env	*env;
	t_token	*token;
	char	*oldpwd;

	env = data->env;
	token = cmd->token->next;
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", ft_strlen(env->var_equal)) == 0)
		{	
			oldpwd = ft_strdup(env->content);
			if (!oldpwd)
				return ;//free malloc !!
			free(env->content);
			if (token)
			{
				env->content = ft_strdup(token->token);
				if (!env->content)
					return ;//free malloc !!
			}
			else
			{
				env->content = ft_strdup("/mnt/nfs/homes/lmelard/");
				if (!env->content)
					return ;//free malloc !!
			}
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
			env->content = oldpwd;
			break ;
		}
		env = env->next;
	}
	if (data->oldpwd)
		free(data->oldpwd);
	data->oldpwd = ft_strdup(data->cwd);
	if (!data->oldpwd)
		return ;//free malloc !!
	free(data->cwd);
	if (token)
	{
		data->cwd = ft_strdup(token->token);
		if (!data->cwd)
			return ;//free malloc !!
	}
	else
		data->cwd = ft_strdup("/mnt/nfs/homes/lmelard/");
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	int		res;
	DIR		*directory;

	res = 0;
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
