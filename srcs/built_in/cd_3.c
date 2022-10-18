/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:47:22 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 22:26:34 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_malloc_pwd(t_env *env, t_data *data, int flag)
{
	ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
	if (env->envp)
		ft_handle_malloc(DELONE, env->envp, 0, NULL);
	env->envp = ft_strjoin(env->var_equal, env->content);
	ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
}

int	ft_pwd_content(t_env *env, t_data *data, t_token *token, int flag)
{
	if (env->content)
	{
		data->tmp_oldpwd = ft_strdup(env->content);
		ft_handle_malloc(flag + TAB_STR1, data->tmp_oldpwd, 0, data);
		ft_handle_malloc(DELONE, env->content, 0, NULL);
	}
	if (token && ft_strncmp(token->token, "//", 2) == 0
		&& ft_strlen(token->token) == 2)
		env->content = ft_strdup(token->token);
	else
	{
		env->content = getcwd(NULL, 0);
		if (!env->content)
			return (ft_msg(1, ERRCWD, "", ""));
	}
	return (0);
}

int	ft_new_pwd(t_env *env, t_data *data, t_token *token, int flag)
{
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", 4) == 0
			&& (ft_strlen(env->var_equal) == 4))
		{
			if (ft_pwd_content(env, data, token, flag))
				return (1);
			ft_handle_malloc_pwd(env, data, flag);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		return (-1);
	return (0);
}
