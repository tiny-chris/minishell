/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:24:16 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 21:30:10 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_path(t_data *data)
{
	if (data->env_path)
		ft_free_env(&(data->env_path));
	if (data->s_env_path)
		ft_free_tabstr_bin(data->s_env_path, TAB_STRS);
}

void	ft_unset_home(t_data *data)
{
	if (data->home)
	{
		ft_handle_malloc(DELONE, data->home, 0, NULL);
		data->home = NULL;
	}
}

void	ft_unset_first(t_env *env, t_env *tmp, t_data *data)
{
	t_env	*todel;

	todel = env;
	tmp = env->next;
	ft_lstdelone_env_bin(todel);
	data->env = tmp;
	env = data->env;
}

void	ft_unset_var(t_env *env, t_env *tmp)
{
	t_env	*todel;

	todel = env;
	if (env->next)
		tmp->next = env->next;
	else
		tmp->next = NULL;
	ft_lstdelone_env_bin(todel);
	env = tmp;
}
