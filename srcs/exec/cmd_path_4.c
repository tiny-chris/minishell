/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:42:17 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 21:43:16 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/*	<SUMMARY> Updates the cmd_path
	Next step will be to check it (rigths/access & directory)
*/

static char	*ft_update_path_tmppath(char *cwd_update, char *check, t_data *data)
{
	char	*tmp_path;
	char	*tmp_path2;

	tmp_path = NULL;
	tmp_path2 = NULL;
	if (cwd_update[ft_strlen(cwd_update) - 1] != '/')
	{
		tmp_path2 = ft_strjoin(cwd_update, "/");
		ft_handle_malloc(ADD_C + TAB_STR1, tmp_path2, 0, data);
		tmp_path = ft_strjoin(tmp_path2, check);
		ft_handle_malloc(ADD_C + TAB_STR1, tmp_path, 0, data);
		ft_handle_malloc(DELONE, tmp_path2, 0, NULL);
	}
	else
	{
		tmp_path = ft_strjoin(cwd_update, check);
		ft_handle_malloc(ADD_C + TAB_STR1, tmp_path, 0, data);
	}
	return (tmp_path);
}

void	ft_update_path(t_cmd *cmd, t_data *data, int i, int j)
{
	char	*tmp_path;
	char	*cwd_update;
	char	*check;

	tmp_path = NULL;
	cwd_update = ft_strdup(cmd->cmd_path);
	ft_handle_malloc(ADD_C + TAB_STR1, cwd_update, 0, data);
	check = ft_substr(cmd->token->token, i, (j - i + 1));
	ft_handle_malloc(ADD_C + TAB_STR1, check, 0, data);
	if (ft_strncmp(check, "./", ft_strlen(check)) == 0)
	{
		ft_handle_malloc(DELONE, cwd_update, 0, NULL);
		ft_handle_malloc(DELONE, check, 0, NULL);
		return ;
	}
	else if (ft_strncmp(check, "../", ft_strlen(check)) == 0)
		tmp_path = ft_get_path_parent(cwd_update, data);
	else
		tmp_path = ft_update_path_tmppath(cwd_update, check, data);
	ft_handle_malloc(DELONE, cwd_update, 0, NULL);
	ft_handle_malloc(DELONE, check, 0, NULL);
	ft_handle_malloc(DELONE, cmd->cmd_path, 0, NULL);
	cmd->cmd_path = tmp_path;
}

/*	<SUMMARY> Gets full path (absolute path) from a potential relative path by:
	- cleaning ./ & ../
	- using strjoin to gather root part to cmd part
	Next step will be to check it (rigths/access & directory)
*/

static int	ft_get_full_path2(t_int	*var, char *token, t_cmd *cmd, t_data *data)
{
	int	k;

	(var->j) = (var->i);
	while (token[var->j] && token[var->j] != '/')
		(var->j)++;
	if (token[var->j] && token[var->j] == '/')
	{
		k = (var->j);
		while (token[k] && token[k] == '/')
			k++;
		ft_update_path(cmd, data, var->i, var->j);
		(var->i) = k - 1;
	}
	else
	{
		ft_update_path(cmd, data, var->i, var->j - 1);
		return (1);
	}
	return (0);
}

char	*ft_get_full_path(t_cmd *cmd, t_data *data)
{
	char	*token;
	t_int	var;

	token = cmd->token->token;
	if (cmd->cmd_path)
		ft_handle_malloc(DELONE, cmd->cmd_path, 0, NULL);
	cmd->cmd_path = ft_strdup(data->cwd);
	ft_handle_malloc(ADD_C + TAB_STR1, cmd->cmd_path, 0, data);
	var.i = 0;
	var.j = 0;
	while (token[var.i])
	{
		if (token[var.i] && token[var.i] != '/')
		{
			if (ft_get_full_path2(&var, token, cmd, data) == 1)
				break ;
		}
		(var.i)++;
	}
	return (cmd->cmd_path);
}
