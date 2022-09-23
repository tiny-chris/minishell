/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/23 15:02:03 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_var_equal(t_data *data, t_token *token)
{
	t_env *env;

	env = data->env;
	while (env)
	{
		if ((ft_strncmp(token->token, env->var_equal, ft_strlen(env->var_equal)) == 0))
			return (1);
		env = env->next;
	}
	return (0);
}

int	ft_env(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	t_token	*tmp;
	t_env	*env;

	token = cmd->token;
	env = data->env;

	if (env == NULL)
	{
		if (token->next == NULL)
			return (0); //val_exit == 0
		return (ft_msg(127, token->token, ": ", ERRFOD));
	}
	if (token->next == NULL)
	{
		ft_display_env(data, token);
		return (0);
	}
	token = token->next;
	if (ft_new_strchr(token->token, '='))
	{
		tmp = token;
		while (ft_new_strchr(tmp->token, '='))
			tmp = tmp->next;
		if (tmp)
			return (ft_msg(127, tmp->token, ": ", ERRFOD));
		ft_display_env(data, token);
	}
	return (0);
}