/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/18 18:24:21 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (ft_msg(1, ERRCWD, "", ""));
	}
	ft_handle_malloc(flag + TAB_STR1, data->cwd, 0, data);
	return (0);
}

static void	ft_handle_malloc_pwd(t_env *env, t_data *data, int flag)
{
	ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
	if (env->envp)
		ft_handle_malloc(DELONE, env->envp, 0, NULL);
	env->envp = ft_strjoin(env->var_equal, env->content);
	ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
}

static int	ft_new_pwd(t_env *env, t_data *data, t_token *token, int flag)
{
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", 4) == 0 && (ft_strlen(env->var_equal) == 4))
		{
			if (env->content)
			{
				data->tmp_oldpwd = ft_strdup(env->content);
				ft_handle_malloc(flag + TAB_STR1, data->tmp_oldpwd, 0, data);
				ft_handle_malloc(DELONE, env->content, 0, NULL);
			}
			if (token && ft_strncmp(token->token, "//", 2) == 0 && ft_strlen(token->token) == 2)
				env->content = ft_strdup(token->token);
			else
			{
				env->content = getcwd(NULL, 0);
				if (!env->content)
					return (ft_msg(1, ERRCWD, "", ""));
			}
			ft_handle_malloc_pwd(env, data, flag);
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	ft_update_pwd(t_cmd *cmd, t_data *data, int flag)
{
	t_env	*env;
	int		pwd_null;
	t_token	*token;

	env = data->env;
	pwd_null = 0;
	token = cmd->token->next;
	if (ft_update_cwd(token, data, flag))
		return (1);
	if (ft_new_pwd(env, data, token, flag))
		return (1);
	if (env == NULL)
	{
		data->tmp_oldpwd = NULL;
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
				if (!data->tmp_oldpwd)
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
					env->content = ft_strdup(data->tmp_oldpwd);
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
	if (data->tmp_oldpwd)
		ft_handle_malloc(DELONE, data->tmp_oldpwd, 0, NULL);
	return (0);
}

static int	ft_exec_cd(t_token *token, t_cmd *cmd, t_data *data, int flag)
{
	DIR		*directory;
	int		res;

	directory = NULL;
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

int	ft_cd(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;

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
		return (ft_exec_cd(token, cmd, data, flag));
	else
		return (ft_msg(1, token->token, ": ", strerror(errno)));
}
