/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/23 16:21:52 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_is_in_env(t_env *env, t_token *token, t_data *data, int flag)
{
	int		i;
	size_t	size_content;

	i = ft_new_strchr(token->token, '=');
	size_content = ft_strlen(token->token) - i + 1;
	ft_handle_malloc(DELONE, env->content, 0, NULL);
	env->content = ft_substr(token->token, i + 1, size_content);
	ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
	ft_handle_malloc(DELONE, env->envp, 0, NULL);
	env->envp = ft_strdup(token->token);
	ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
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

int	ft_check_export(t_token *token, t_data *data, int flag)
{
	t_env	*env;
	char	*var_tmp;
	int		i;

	env = data->env;
	var_tmp = NULL;
	i = ft_new_strchr(token->token, '=');
	var_tmp = ft_substr(token->token, 0, i + 1);
	ft_handle_malloc(flag + TAB_STR1, var_tmp, 0, data);
	while (env)
	{
		if (ft_strncmp(env->var_equal, var_tmp, ft_strlen(env->var_equal)) == 0)
		{
			ft_is_in_env(env, token, data, flag);
			ft_handle_malloc(DELONE, var_tmp, 0, NULL);
			ft_export_path_home(env, data, flag);
			return (0);
		}
		env = env->next;
	}
	if (env == NULL)
		ft_lstadd_env(&(data->env), token->token, data, flag);
	env = data->env;
	ft_handle_malloc(DELONE, var_tmp, 0, NULL);
	return (0);
}

static int	ft_get_export(t_data *data, t_token *token, int *res, int flag)
{
	int	i;

	i = 0;
	while (token->token[i] && token->token[i] != '=')
	{
		if ((ft_isalnum(token->token[i]) == 0))
		{
			*res = ft_msg(1, token->token, ": ", ERRNAM);
			break ;
		}
		else
		{
			i++;
			*res = 0;
		}
	}
	if (token->token[i] == '=')
		*res = ft_check_export(token, data, flag);
	return (0);
}

int	ft_export(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;
	int		res;
	int		res2;

	token = cmd->token;
	res = 0;
	res2 = 0;
	if (token->next == NULL)
		return (ft_display_export(data, flag), 0);
	token = token->next;
	while (token)
	{
		if ((ft_isalpha(token->token[0]) == 0) && (token->token[0] != '_'))
			res = ft_msg(1, token->token, ": ", ERRNAM);
		else if ((token->token[0] == '_') && (token->token[1] == '='))
			res = 0;
		else
			ft_get_export(data, token, &res, flag);
		if (res == 0 && res2 == 0)
			res2 = 0;
		else
			res2 = 1;
		token = token->next;
	}
	return (res2);
}
