/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:21:40 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/26 12:47:26 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_export(t_token *token, t_data *data, int flag, int len)
{
	t_env	*env;
	t_env	*exp;

	env = data->env;
	exp = data->export;
	while (env)
	{
		if (ft_strncmp(env->var, token->token, len) == 0 \
			&& len == (int) ft_strlen(env->var))
			break ;
		env = env->next;
	}
	if (env == NULL)
	{
		while (exp)
		{
			if (ft_strncmp(exp->content, token->token, len) == 0 \
				&& len == (int) ft_strlen(exp->content))
				break ;
			exp = exp->next;
		}
		if (exp == NULL)
			ft_lstadd_env2(&(data->export), token->token, data, flag);
	}
	return (0);
}

static void	ft_display_export_lst(t_data *data, int flag)
{
	t_env	*export;
	char	*tmp;

	tmp = NULL;
	export = data->export;
	if (export)
	{
		while (export)
		{
			tmp = ft_strjoin("export ", export->content);
			ft_handle_malloc(flag + TAB_STR1, tmp, 0, data);
			ft_putendl_fd(tmp, STDOUT_FILENO);
			ft_handle_malloc(DELONE, tmp, 0, NULL);
			tmp = NULL;
			export = export->next;
		}
	}
}

void	ft_display_export(t_data *data, int flag)
{
	char	*tmp;
	t_env	*env;

	tmp = NULL;
	env = data->env;
	while (env)
	{
		tmp = ft_strjoin("export ", env->envp);
		ft_handle_malloc(flag + TAB_STR1, tmp, 0, data);
		ft_putendl_fd(tmp, STDOUT_FILENO);
		ft_handle_malloc(DELONE, tmp, 0, NULL);
		tmp = NULL;
		env = env->next;
	}
	ft_display_export_lst(data, flag);
}
