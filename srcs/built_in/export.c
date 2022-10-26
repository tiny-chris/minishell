/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/26 02:05:46 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*	si export aaa
	alors dans t_env export
	si export aaa=b
	alors dans t_env env
	et supprimer de t_env export
*/



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

static int	ft_update_plus_token(t_token **tok, t_data *data, int flag)
{
	// char	*var_tmp;
	char	*tmp1;
	char	*tmp2;
	int		i;

	// var_tmp = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	i = ft_new_strchr((*tok)->token, '=');
	if ((*tok)->plus == 1)
	{
		tmp1 = ft_substr((*tok)->token, 0, i);
		ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
		if ((*tok)->token[i + 1] != '\0')
			tmp2 = ft_substr((*tok)->token, i + 1, ft_strlen((*tok)->token) - i);
		else
			tmp2 = ft_strdup("");
		ft_handle_malloc(flag + TAB_STR1, tmp2, 0, data);
		ft_handle_malloc(DELONE, (*tok)->token, 0, NULL);
		(*tok)->token = ft_strjoin(tmp1, tmp2);
		ft_handle_malloc(flag + TAB_STR1, (*tok)->token, 0, data);
		ft_handle_malloc(DELONE, tmp1, 0, NULL);
		tmp1 = NULL;
		ft_handle_malloc(DELONE, tmp2, 0, NULL);
		tmp2 = NULL;
		i = i - 1;
	}
	return (i);
	// var_tmp = ft_substr((*tok)->token, 0, i + 1);
	// ft_handle_malloc(flag + TAB_STR1, var_tmp, 0, data);
	// return (var_tmp);
}

int	ft_check_export(t_token *token, t_data *data, int flag)
{
	t_env	*env;
	char	*var_tmp;
	int		i;

	env = data->env;
	var_tmp = NULL;
	i = ft_update_plus_token(&token, data, flag);
	var_tmp = ft_substr(token->token, 0, i + 1);
	ft_handle_malloc(flag + TAB_STR1, var_tmp, 0, data);
	while (env)
	{
		if (ft_strncmp(env->var_equal, var_tmp, ft_strlen(env->var_equal)) == 0)
		{
			ft_is_in_env(env, token, data, flag);
			ft_is_in_export(data, token, flag);
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
// ft_check export :
/* 	si token->plus ==1
	 i = i - 1
	var_tmp ...
	while (env)
	{
		if ()
	}
*/


// check le name
// + verif signe + (modif var token->plus à 1)

static int	ft_get_export(t_data *data, t_token *token, int *res, int flag)
{
	int	i;

	i = 0;
	while (token->token[i] && (token->token[i] != '=' || token->token[i] != '+'))
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
	if (token->token[i] == '+')
	{
		if (token->token[i + 1] == '\0' \
			|| (token->token[i + 1] && token->token[i + 1] != '='))
			*res = ft_msg(1, token->token, ": ", ERRNAM);
		else
		{
			token->plus = 1;
			*res = ft_check_export(token, data, flag);
		}
	}
	else if (token->token[i] == '=')
		*res = ft_check_export(token, data, flag);
	else if (token->token[i] == '\0')
		*res = ft_add_export(token, data, flag);
	return (0);
}




// 	while (token->token[i] && token->token[i] != '=')
// 	{
// 		if ((ft_isalnum(token->token[i]) == 0))
// 		{
// 			*res = ft_msg(1, token->token, ": ", ERRNAM);
// 			break ;
// 		}
// 		else
// 		{
// 			i++;
// 			*res = 0;
// 		}
// 	}
// 	if (token->token[i] == '=')
// 		*res = ft_check_export(token, data, flag);
// 	else if (token->token[i] == '\0')
// 	{
// 		*res = ft_add_export(token, data, flag);
// 	}
// 	return (0);
// }

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
