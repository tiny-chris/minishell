/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:27:14 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/10 10:02:38 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_unset(t_token *token, t_data *data, int flag)
{
	t_env	*env;
	t_env	*todel;
	t_env	*tmp;

	env = data->env;
	tmp = data->env;
	todel = NULL;
	while (env)
	{
		if (ft_strncmp(env->var, token->token, ft_strlen(env->var)) == 0 && ft_strlen(env->var) == ft_strlen(token->token))
		{
			if (ft_strncmp(token->token, "PATH", 4) == 0 && ft_strlen(token->token) == 4)
			{
				if (data->env_path)
				{
					ft_free_env(&(data->env_path));
					data->env_path = NULL;
				}
				if (data->s_env_path)
				{
					ft_free_tabstr(data->s_env_path);
					data->s_env_path = NULL;
				}
			}
			else if (ft_strncmp(token->token, "HOME", 4) == 0 && ft_strlen(token->token) == 4)
			{
				printf("check le HOME unset\n");//
				if (data->home)
				{
					printf("data->home = %s\n", data->home);//
					free(data->home);
					data->home = NULL;
				}
			}
			if (env == data->env)
			{
				todel = env;
				tmp = env->next;
				ft_lstdelone_env(todel, flag);
				data->env = tmp;
				env = data->env;
			}
			else
			{
				todel = env;
				if (env->next)
					tmp->next = env->next;
				else
					tmp->next = NULL;
				ft_lstdelone_env(todel, flag);
				env = tmp;
			}
		}
		if (env != data->env || tmp != env)//ajout de la 2e condition
			tmp = tmp->next;
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;
	int		i;
	int		res;
	int		res2;

	token = cmd->token;
	i = 0;
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
				res = ft_check_unset(token, data, flag);
		}
		if (res == 0 && res2 == 0)
			res2 = 0;
		else
			res2 = 1;
		token = token->next;
		i = 0;
	}
	return (res2);
}
