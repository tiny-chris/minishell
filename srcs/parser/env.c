/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:27:05 by marvin            #+#    #+#             */
/*   Updated: 2022/08/18 11:27:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* <SUMMARY> Gets char **envp (from main) and saves it in a linked list 'env'
** <REMARK>	flag is equal to ADD_M (add main) as this function is only called
**			once at the start of the program
*/
t_env	*ft_get_env(char **envp, t_data *data)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_lstadd_env(&env, envp[i], data, ADD_M);
		i++;
	}
	return (env);
}

static int	ft_check_env_size(t_data *data)
{
	t_env	*env;
	int		i;

	env = data->env;
	i = 0;
	if (env == NULL || env->var[0] == '\0')
		return (-1);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static int	ft_s_env_null(t_data *data)
{
	int	i;

	i = 0;
	if (data->s_env != NULL)
	{
		ft_handle_malloc(DELONE, data->s_env, 0, NULL);
		data->s_env = NULL;
	}
	i = ft_check_env_size(data);
	return (i);
}

char	**ft_get_s_env(t_data *data)
{
	t_env	*env;
	char	**s_env;
	int		i;

	env = data->env;
	s_env = NULL;
	i = ft_s_env_null(data);
	if (i == -1)
		return (NULL);
	s_env = ft_handle_malloc(MALLOC_M + TAB_STR2, NULL, (i + 1), NULL);
	i = 0;
	while (env)
	{
		if (env->envp)
		{
			s_env[i] = ft_strdup(env->envp);
			ft_handle_malloc(ADD_M + TAB_STR1, s_env[i], 0, NULL);
		}
		else
			s_env[i] = NULL;
		i++;
		env = env->next;
	}
	s_env[i] = NULL;
	return (s_env);
}
