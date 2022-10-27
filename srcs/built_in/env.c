/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/27 17:09:58 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_env_lst(t_env *env, t_token *token)
{
	t_token	*tmp;
	size_t	size_var_equal;

	tmp = NULL;
	size_var_equal = ft_strlen(env->var_equal);
	while (env)
	{
		tmp = token;
		while (tmp)
		{
			if (ft_strncmp(tmp->token, env->var_equal, size_var_equal) == 0)
			{
				ft_putendl_fd(tmp->token, STDOUT_FILENO);
				tmp->printed = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL)
		{
			if (env->envp)
				ft_putendl_fd(env->envp, STDOUT_FILENO);
		}
		env = env->next;
	}
}

void	ft_display_env(t_data *data, t_token *token)
{
	t_env	*env;
	t_token	*tmp;

	env = data->env;
	tmp = NULL;
	ft_print_env_lst(env, token);
	while (token)
	{
		if (token->printed == 0)
			ft_putendl_fd(token->token, STDOUT_FILENO);
		token = token->next;
	}
	tmp = token;
	while (tmp)
	{
		tmp->printed = 0;
		tmp = tmp->next;
	}
}

static int	ft_env_equal(t_token *token, t_data *data)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && ft_is_in_set(tmp->token, '='))
		tmp = tmp->next;
	if (tmp)
		return (ft_msg(127, tmp->token, ": ", ERRFOD));
	ft_display_env(data, token);
	return (0);
}

int	ft_env(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	t_env	*env;

	token = cmd->token;
	env = data->env;
	if (env == NULL)
	{
		if (token->next == NULL)
			return (0);
		return (ft_msg(127, token->token, ": ", ERRFOD));
	}
	if (token->next == NULL)
	{
		ft_display_env(data, NULL);
		return (0);
	}
	token = token->next;
	if (ft_is_in_set(token->token, '='))
	{
		if (ft_env_equal(token, data))
			return (127);
	}
	return (0);
}
