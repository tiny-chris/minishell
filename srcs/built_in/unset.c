/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:27:14 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 21:30:28 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_var_in_env(t_token *token, t_env *env, t_env *tmp, t_data *data)
{
	if (ft_strncmp(token->token, "PATH", 4) == 0
		&& ft_strlen(token->token) == 4)
		ft_unset_path(data);
	else if (ft_strncmp(token->token, "HOME", 4) == 0
		&& ft_strlen(token->token) == 4)
		ft_unset_home(data);
	if (env == data->env)
		ft_unset_first(env, tmp, data);
	else
		ft_unset_var(env, tmp);
}

int	ft_check_unset(t_token *token, t_data *data)
{
	t_env	*env;
	t_env	*tmp;

	env = data->env;
	tmp = data->env;
	while (env)
	{
		if (ft_strncmp(env->var, token->token, ft_strlen(env->var)) == 0
			&& ft_strlen(env->var) == ft_strlen(token->token))
			ft_var_in_env(token, env, tmp, data);
		if (env != data->env || tmp != env)
			tmp = tmp->next;
		env = env->next;
	}
	return (0);
}

void	ft_check_token_token(t_data *data, t_token *token, int *res)
{
	int	i;

	i = 0;
	while (token->token[i])
	{
		if (ft_isalnum(token->token[i]) == 0)
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
	if (token->token[i] == '\0')
		*res = ft_check_unset(token, data);
}

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
		if ((ft_isalpha(token->token[0]) == 0) && (token->token[0] != '_'))
			res = ft_msg(1, token->token, ": ", ERRNAM);
		else
			ft_check_token_token(data, token, &res);
		if (res == 0 && res2 == 0)
			res2 = 0;
		else
			res2 = 1;
		token = token->next;
	}
	return (res2);
}
