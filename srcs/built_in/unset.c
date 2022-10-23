/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:27:14 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/23 15:47:20 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_spec_var(t_token *tok, t_data *data)
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

int	ft_check_unset(t_token *token, t_data *data)
{
	t_env	*env;
	t_env	*tmp;

	env = data->env;
	tmp = data->env;
	while (env)
	{
		if (ft_strncmp(env->var, token->token, ft_strlen(env->var)) == 0 \
			&& ft_strlen(env->var) == ft_strlen(token->token))
		{
			ft_unset_spec_var(token, data);
			env = ft_unset_var(env, &tmp, data);
		}
		if (env != data->env || tmp != env)
			tmp = tmp->next;
		env = env->next;
	}
	return (0);
}

static int	ft_check_token_token(t_token *token, t_data *data)
{
	int	res;
	int	i;

	i = 0;
	if ((ft_isalpha(token->token[0]) == 0) && (token->token[0] != '_'))
			res = ft_msg(1, token->token, ": ", ERRNAM);
	else
	{
		while (token->token[i])
		{
			if (ft_isalnum(token->token[i]) == 0)
			{
				res = ft_msg(1, token->token, ": ", ERRNAM);
				break ;
			}
			else
			{
				i++;
				res = 0;
			}
		}
		if (token->token[i] == '\0')
			res = ft_check_unset(token, data);
	}
	return (res);
}

/* <SUMMARY> Unsets tokens that are in the env 
** <REMARKS>	- Previous check of name validity
**				- Additional cleaning for PATH & HOME
*/
int	ft_unset(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	int		res;
	int		res2;

	token = cmd->token;
	res = 0;
	res2 = 0;
	if (token->next == NULL)
		return (0);
	token = token->next;
	while (token)
	{
		res = ft_check_token_token(token, data);
		if (res == 0 && res2 == 0)
			res2 = 0;
		else
			res2 = 1;
		token = token->next;
	}
	return (res2);
}
