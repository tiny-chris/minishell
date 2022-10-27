/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/27 17:51:30 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_update_cwd2(t_token *t, char **tmp2, t_data *data, int flag)
{
	char	*tmp1;

	tmp1 = NULL;
	tmp1 = getcwd(NULL, 0);
	if (tmp1 == NULL || (t && data->cwd_err == 1 && t->token[0] != '/'))
	{
		if (tmp1)
			ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
		data->cwd_err = 1;
		ft_handle_malloc(DELONE, tmp1, 0, NULL);
		ft_handle_malloc(DELONE, (*tmp2), 0, NULL);
		return (ft_msg(1, ERRCWD, "", ""));
	}
	ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
	ft_handle_malloc(DELONE, data->cwd, 0, NULL);
	data->cwd = ft_strdup(tmp1);
	ft_handle_malloc(flag + TAB_STR1, data->cwd, 0, data);
	ft_handle_malloc(DELONE, tmp1, 0, NULL);
	return (0);
}

static void	ft_update_data_oldpwd(char **tmp2, t_data *data, int flag)
{
	data->cwd_err = 0;
	if (data->oldpwd)
		ft_handle_malloc(DELONE, data->oldpwd, 0, NULL);
	data->oldpwd = ft_strdup(*tmp2);
	ft_handle_malloc(flag + TAB_STR1, data->oldpwd, 0, data);
	ft_handle_malloc(DELONE, (*tmp2), 0, NULL);
}

int	ft_update_cwd(t_token *t, t_data *data, int flag)
{
	char	*tmp2;

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
		if (ft_update_cwd2(t, &tmp2, data, flag))
			return (1);
	}
	ft_update_data_oldpwd(&tmp2, data, flag);
	return (0);
}

int	ft_update_pwd(t_cmd *cmd, t_data *data, int flag)
{
	t_env	*env;
	t_token	*token;
	int		res;

	env = data->env;
	token = cmd->token->next;
	if (ft_update_cwd(token, data, flag))
		return (1);
	res = ft_new_pwd(env, data, token, flag);
	if (res > 0)
		return (1);
	if (res == -1)
	{
		data->tmp_oldpwd = NULL;
		data->pwd_null++;
	}
	env = data->env;
	ft_new_oldpwd(env, data, flag);
	if (data->tmp_oldpwd)
		ft_handle_malloc(DELONE, data->tmp_oldpwd, 0, NULL);
	return (0);
}
