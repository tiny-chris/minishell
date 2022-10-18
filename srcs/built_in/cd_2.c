/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:40:51 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 18:47:08 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_oldpwd_nopwd(t_env *env, t_data *data, int flag)
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

void	ft_oldpwd_pwd(t_env *env, t_data *data, int flag)
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

void	ft_new_oldpwd(t_env *env, t_data *data, int flag, int pwd_null)
{
	while (env)
	{
		if (ft_strncmp(env->var_equal, "OLDPWD=", 7) == 0 \
			&& (ft_strlen(env->var_equal) == 7))
		{
			if (pwd_null == 1)
				ft_oldpwd_nopwd(env, data, flag);
			else
				ft_oldpwd_pwd(env, data, flag);
			break ;
		}
		env = env->next;
	}
}
