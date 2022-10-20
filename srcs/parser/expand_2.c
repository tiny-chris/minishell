/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:24:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 14:50:16 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

void	ft_fill_ex3(t_env *env, char *clean_cmd, t_int *var)
{
	int	l;

	l = 0;
	while (env->content[l])
	{
		if (env->content[l] == 34 || env->content[l] == 39)
			clean_cmd[var->j] = env->content[l] * (-1);
		else
			clean_cmd[var->j] = env->content[l];
		(var->j)++;
		l++;
	}
}

void	ft_fill_ex2(char *undoll_cmd, t_int *var, char *clean_cmd, t_data *data)
{
	t_env	*env;
	char	*var_to_expand;
	int		k;

	env = data->env;
	k = var->i;
	while (undoll_cmd[k] && (undoll_cmd[k] > 0) && ft_isalnum(undoll_cmd[k]))
		k++;
	var_to_expand = ft_substr(undoll_cmd, var->i, (k - var->i));
	ft_handle_malloc(ADD_M + TAB_STR1, var_to_expand, 0, NULL);
	while (env)
	{
		if ((ft_strlen(var_to_expand) == ft_strlen(env->var)) \
			&& (ft_strncmp(var_to_expand, env->var, (k - var->i)) == 0))
		{
			ft_fill_ex3(env, clean_cmd, var);
			break ;
		}
		env = env->next;
	}
	ft_handle_malloc(DELONE, var_to_expand, 0, NULL);
	var->i = k;
	return ;
}

void	ft_fill_normal(char *clean_cmd, char *undoll_cmd, int *i, int *j)
{
	clean_cmd[*j] = undoll_cmd[*i];
	(*i)++;
	(*j)++;
}

void	ft_fill_return_code(t_data *data, char *clean_cmd, int *j)
{
	int	k;

	k = 0;
	while (data->str_exit[k])
	{
		clean_cmd[*j] = data->str_exit[k];
		(*j)++;
		k++;
	}
}
