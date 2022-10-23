/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:21:40 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/23 16:21:47 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}