/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:21:40 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/26 15:31:01 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clean_var_tmp(char **var_tmp, char **var_name)
{
	ft_handle_malloc(DELONE, (*var_tmp), 0, NULL);
	(*var_tmp) = NULL;
	ft_handle_malloc(DELONE, (*var_name), 0, NULL);
	(*var_name) = NULL;
}

static void	ft_is_in_env(t_env **env, t_token *token, t_data *data, int flag)
{
	int		i;
	size_t	size_content;
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	if (token->plus == 1)
	{
		tmp1 = ft_strdup((*env)->content);
		ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
	}
	i = ft_new_strchr(token->token, '=');
	size_content = ft_strlen(token->token) - i + 1;
	tmp2 = ft_substr(token->token, i + 1, size_content);
	ft_handle_malloc(flag + TAB_STR1, tmp2, 0, data);
	ft_handle_malloc(DELONE, (*env)->content, 0, NULL);
	ft_handle_malloc(DELONE, (*env)->envp, 0, NULL);
	(*env)->content = ft_strjoin(tmp1, tmp2);
	ft_handle_malloc(flag + TAB_STR1, (*env)->content, 0, data);
	ft_clean_var_tmp(&tmp1, &tmp2);
	tmp1 = ft_substr(token->token, 0, i + 1);
	ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
	(*env)->envp = ft_strjoin(tmp1, (*env)->content);
	ft_handle_malloc(flag + TAB_STR1, (*env)->envp, 0, data);
	ft_handle_malloc(DELONE, tmp1, 0, NULL);
}

static void	ft_export_path_home(t_env *env, t_data *data, int flag)
{
	size_t	size_var_equal;

	size_var_equal = ft_strlen(env->var_equal);
	if (ft_strncmp(env->var_equal, "PATH=", size_var_equal) == 0)
		ft_get_env_path(data, flag);
	else if (ft_strncmp(env->var_equal, "HOME=", size_var_equal) == 0)
		ft_get_home(data, flag);
}

int	ft_check_export(t_token *token, t_data *data, int flag, char *var_name)
{
	t_env	*env;
	char	*var_tmp;

	env = data->env;
	var_tmp = ft_strjoin(var_name, "=");
	ft_handle_malloc(flag + TAB_STR1, var_tmp, 0, data);
	while (env)
	{
		if (ft_strncmp(env->var_equal, var_tmp, ft_strlen(env->var_equal)) == 0)
		{
			ft_is_in_env(&env, token, data, flag);
			ft_check_unset_in_export(var_name, data);
			ft_clean_var_tmp(&var_tmp, &var_name);
			ft_export_path_home(env, data, flag);
			return (0);
		}
		env = env->next;
	}
	if (env == NULL)
	{
		ft_lstadd_env(&(data->env), token->token, data, flag);
		ft_check_unset_in_export(var_name, data);
	}
	ft_clean_var_tmp(&var_tmp, &var_name);
	return (0);
}
