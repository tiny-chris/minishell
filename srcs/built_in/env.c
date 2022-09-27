/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/28 01:20:18 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- while (env)
	parcourir
	verif si qch de correspondant dans le token
		while (token)
		si oui --> affiche token
		sinon affiche env et on ajoute lstaddback à une nouvelle liste 'new'

int	printed dans t_token;//pour env - init à 0 et passe à 1 si printé dans built-in env
si printed = 0 alors il faut display à la fin de env

hors loop:
si qch dans nouvelle liste 'new'
affiche le token
free la nouvelle liste 'new'
*/
void	ft_display_env(t_data *data, t_token *token)
{
	t_env	*env;
	t_token	*tmp;

	env = data->env;
	tmp = NULL;
	while (env)
	{
		tmp = token;
		while (tmp)
		{
			if (ft_strncmp(tmp->token, env->var_equal, ft_strlen(env->var_equal)) == 0)
			{
				printf("%s\n", tmp->token);
				tmp->printed = 1;
				break;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL)
			printf("%s\n", env->envp);
		env = env->next;
	}
	while (token)
	{
		if (token->printed == 0)
			printf("%s\n", token->token);
		token = token->next;
	}
}

int	ft_env(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	t_token	*tmp;
	t_env	*env;

	token = cmd->token;
	tmp = NULL;
	env = data->env;
	if (env == NULL)
	{
		if (token->next == NULL)
			return (0); //val_exit == 0
		return (ft_msg(127, token->token, ": ", ERRFOD));
	}
	if (token->next == NULL)
	{
		ft_display_env(data, NULL);
		return (0);
	}
	token = token->next;
	if (ft_new_strchr(token->token, '='))
	{
		tmp = token;
		while (tmp && ft_new_strchr(tmp->token, '='))
			tmp = tmp->next;
		if (tmp)
			return (ft_msg(127, tmp->token, ": ", ERRFOD));
		ft_display_env(data, token);
	}
	return (0);
}
