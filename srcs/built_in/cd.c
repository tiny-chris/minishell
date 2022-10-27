/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/27 14:56:28 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_cwd(t_token *t, t_data *data, int flag)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (data->cwd)
	{
		tmp2 = ft_strdup(data->cwd);
		ft_handle_malloc(flag + TAB_STR1, tmp2, 0, data);
	}
	if (t && (ft_strncmp(t->token, "//", 2) == 0 && ft_strlen(t->token) == 2))
	{
		ft_handle_malloc(DELONE, data->cwd, 0, NULL);
		data->cwd = ft_strdup("//");
		ft_handle_malloc(flag + TAB_STR1, data->cwd, 0, data);
	}
	else
	{
		tmp1 = getcwd(NULL, 0);
		if (tmp1 == NULL || (data->cwd_err == 1 && t->token[0] != '/'))
		{
			if (tmp1)
				ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
			data->cwd_err = 1;
			ft_handle_malloc(DELONE, tmp1, 0, NULL);
			ft_handle_malloc(DELONE, tmp2, 0, NULL);
			return (ft_msg(1, ERRCWD, "", ""));
		}
		ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
		data->cwd_err = 0;
		ft_handle_malloc(DELONE, data->cwd, 0, NULL);
		data->cwd = ft_strdup(tmp1);
		ft_handle_malloc(flag + TAB_STR1, data->cwd, 0, data);
		ft_handle_malloc(DELONE, tmp1, 0, NULL);
	}
	if (data->oldpwd)
		ft_handle_malloc(DELONE, data->oldpwd, 0, NULL);
	data->oldpwd = ft_strdup(tmp2);
	ft_handle_malloc(flag + TAB_STR1, data->oldpwd, 0, data);
	ft_handle_malloc(DELONE, tmp2, 0, NULL);
	return (0);
}

int	ft_update_pwd(t_cmd *cmd, t_data *data, int flag)
{
	t_env	*env;
	int		pwd_null;
	t_token	*token;
	int		res;

	env = data->env;
	pwd_null = 0;
	token = cmd->token->next;
	if (ft_update_cwd(token, data, flag))
		return (1);
	res = ft_new_pwd(env, data, token, flag);
	if (res > 0)
		return (1);
	if (res == -1)
	{
		data->tmp_oldpwd = NULL;
		pwd_null = 1;
	}
	env = data->env;
	ft_new_oldpwd(env, data, flag, pwd_null);
	if (data->tmp_oldpwd)
		ft_handle_malloc(DELONE, data->tmp_oldpwd, 0, NULL);
	return (0);
}

int	ft_exec_cd(t_token *token, t_cmd *cmd, t_data *data, int flag)
{
	DIR		*directory;
	int		res;

	directory = NULL;
	if (access(token->token, F_OK))
		return (ft_msg(1, token->token, ": ", strerror(errno)));
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
	int		res;

	token = cmd->token;
	token = token->next;
	if (token == NULL)
	{
		ft_get_home(data, flag);
		if (data->home == NULL)
			return (ft_msg(1, cmd->token->token, ": ", ERRHOM));
		else if (data->home[0] == '\0')
			return (0);
		res = chdir(data->home);
		if (res == -1)
			return (ft_msg(errno, data->home, ": ", strerror(errno)));
		ft_update_pwd(cmd, data, flag);
		return (0);
	}
	if (token->next)
		return (ft_msg(1, cmd->token->token, ": ", ERRARG));
	if (token->type == SP_QUOTES)
		return (0);
	return (ft_exec_cd(token, cmd, data, flag));
}
