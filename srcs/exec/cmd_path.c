/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:23:33 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 21:43:28 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static char	*ft_get_parent3(char *cwd_update, char *tmp_cwd, t_data *data)
{
	int		i;
	char	*new_cwd;

	new_cwd = NULL;
	i = ft_new_strrchr(tmp_cwd, '/');
	ft_handle_malloc(DELONE, tmp_cwd, 0, NULL);
	if (i == 0)
	{
		new_cwd = ft_strdup("/");
		ft_handle_malloc(ADD_C + TAB_STR1, new_cwd, 0, data);
	}
	else
	{
		new_cwd = ft_substr(cwd_update, 0, i);
		ft_handle_malloc(ADD_C + TAB_STR1, new_cwd, 0, data);
	}
	return (new_cwd);
}

static char	*ft_get_parent2(char *cwd_update, char *tmp_cwd, t_data *data)
{
	char	*new_cwd;
	int		i;

	i = ft_strlen(cwd_update) - 1;
	new_cwd = NULL;
	if (cwd_update[i] == '/')
	{
		tmp_cwd = ft_substr(cwd_update, 0, i);
		ft_handle_malloc(ADD_C + TAB_STR1, tmp_cwd, 0, data);
	}
	else
	{
		tmp_cwd = ft_strdup(cwd_update);
		ft_handle_malloc(ADD_C + TAB_STR1, tmp_cwd, 0, data);
	}
	new_cwd = ft_get_parent3(cwd_update, tmp_cwd, data);
	return (new_cwd);
}

char	*ft_get_path_parent(char *cwd_update, t_data *data)
{
	char	*new_cwd;
	char	*tmp_cwd;

	new_cwd = NULL;
	tmp_cwd = NULL;
	if (ft_strlen(cwd_update) == 1 && cwd_update[0] == '/')
	{
		new_cwd = ft_strdup(cwd_update);
		ft_handle_malloc(ADD_C + TAB_STR1, new_cwd, 0, data);
	}
	else
		new_cwd = ft_get_parent2(cwd_update, tmp_cwd, data);
	return (new_cwd);
}
