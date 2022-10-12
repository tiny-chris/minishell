/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:27:14 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/12 05:25:01 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_unset(t_token *token, t_data *data)
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
				// {
					ft_free_env(&(data->env_path));
				printf("val env path unset = %p\n", data->env_path);//
				// 	data->env_path = NULL;
				// }
				if (data->s_env_path)
				// {
					ft_free_tabstr_bin(data->s_env_path, TAB_STRS);
				// 	data->s_env_path = NULL;
				// }
			}
			else if (ft_strncmp(token->token, "HOME", 4) == 0 && ft_strlen(token->token) == 4)
			{
				printf("check le HOME unset\n");//
				if (data->home)
				{
					printf("data->home = %s\n", data->home);//
					ft_handle_malloc(DELONE, data->home, 0, 0);
					//free(data->home);
					data->home = NULL;// ne pas enleve pour le moment - prb de leak sinon...
					printf("data->home h= %p\n", data->home);//
				}
			}
			if (env == data->env)
			{
				todel = env;
				tmp = env->next;
				ft_lstdelone_env_bin(todel);
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
				ft_lstdelone_env_bin(todel);
				env = tmp;
			}
		}
		if (env != data->env || tmp != env)
			tmp = tmp->next;
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_data *data)
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
				res = ft_check_unset(token, data);
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
