/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:27:14 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/25 12:10:14 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_path_home(t_token *tok, t_data *data)
{
	if (ft_strncmp(tok->token, "PATH", 4) == 0 && ft_strlen(tok->token) == 4)
	{
		if (data->env_path)
		{
			ft_free_env(&(data->env_path));
			data->env_path = NULL;
		}
		if (data->s_env_path)
		{
			ft_free_tabstr_bin(data->s_env_path, TAB_STRS);
			data->s_env_path = NULL;
		}
	}
	else if (ft_strncmp(tok->token, "HOME", 4) == 0 \
		&& ft_strlen(tok->token) == 4)
	{
		if (data->home)
		{
			ft_handle_malloc(DELONE, data->home, 0, NULL);
			data->home = NULL;
		}
	}
}	

static t_env	*ft_unset_var(t_env *env, t_env **tmp, t_data *data)
{
	t_env	*todel;

	todel = NULL;
	if (env == data->env)
	{
		todel = env;
		(*tmp) = env->next;
		todel->next = NULL;
		ft_lstdelone_env_bin(todel);
		data->env = (*tmp);
		env = data->env;
	}
	else
	{
		todel = env;
		if (env->next)
			(*tmp)->next = env->next;
		else
			(*tmp)->next = NULL;
		ft_lstdelone_env_bin(todel);
		env = (*tmp);
	}
	return (env);
}

static t_env	*ft_unset_var2(t_env *env, t_env **tmp, t_env **data_env)
{
	t_env	*todel;

	todel = NULL;
	if (env == (*data_env))
	{
		todel = env;
		(*tmp) = env->next;
		todel->next = NULL;
		ft_lstdelone_env_bin(todel);
		(*data_env) = (*tmp);
		env = (*tmp);
	}
	else
	{
		todel = env;
		if (env->next)
			(*tmp)->next = env->next;
		else
			(*tmp)->next = NULL;
		ft_lstdelone_env_bin(todel);
		env = (*tmp);
	}
	return (env);
}

static int	ft_check_unset_in_export(t_token *token, t_data *data)
{
	t_env	*exp;
	t_env	*tmp;

	exp = data->export;
	tmp = data->export;
	while (exp)
	{
		if (ft_strncmp(exp->content, token->token, ft_strlen(exp->var)) == 0 \
			&& ft_strlen(exp->content) == ft_strlen(token->token))
		{
			exp = ft_unset_var2(exp, &tmp, &(data->export));
			return (1);
		}
		if (exp == NULL)
			break ;
		if (exp != data->export || tmp != exp)
			tmp = tmp->next;
		exp = exp->next;
	}
	return (0);
}

int	ft_check_unset(t_token *token, t_data *data)
{
	t_env	*env;
	t_env	*tmp;

	env = data->env;
	tmp = data->env;
	if (data->export)
	{
		if (ft_check_unset_in_export(token, data) == 1)
			return (0);
	}
	while (env)
	{
		if (ft_strncmp(env->var, token->token, ft_strlen(env->var)) == 0 \
			&& ft_strlen(env->var) == ft_strlen(token->token))
		{
			ft_unset_path_home(token, data);
			env = ft_unset_var(env, &tmp, data);
		}
		if (env == NULL)
			break ;
		if (env != data->env || tmp != env)
			tmp = tmp->next;
		env = env->next;
	}
	return (0);
}
