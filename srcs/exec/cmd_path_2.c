/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:07:43 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 20:02:34 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_val_exit;

char	*ft_get_path_parent(char *cwd_update, t_data *data)
{
	char	*new_cwd;
	char	*tmp_cwd;
	int		i;

	new_cwd = NULL;
	tmp_cwd = NULL;
	i = 0;
	if (ft_strlen(cwd_update) == 1 && cwd_update[0] == '/')
	{
		new_cwd = ft_strdup(cwd_update);
		ft_handle_malloc(ADD_C + TAB_STR1, new_cwd, 0, data);
	}
	else
	{
		i = ft_strlen(cwd_update) - 1;
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
		i = ft_new_strrchr(tmp_cwd, '/');
		ft_handle_malloc(DELONE, tmp_cwd, 0, NULL);
		if (i == 0)
		{
			new_cwd = ft_strdup("/");
			ft_handle_malloc(ADD_C + TAB_STR1, new_cwd, 0, data);
		}
		else
		{
			new_cwd = ft_substr(cwd_update, 0, i);//sans le slash
			ft_handle_malloc(ADD_C + TAB_STR1, new_cwd, 0, data);
		}
	}
	return (new_cwd);
}

/*	<SUMMARY> Updates the cmd_path
	Next step will be to check it (rigths/access & directory)
*/
void	ft_update_path(t_cmd *cmd, t_data *data, int i, int j)
{
	char	*tmp_path;
	char	*tmp_path2;
	char	*cwd_update;
	char	*check;

	tmp_path = NULL;
	tmp_path2 = NULL;
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
	{
		i = ft_strlen(cwd_update) - 1;
		if (cwd_update[ft_strlen(cwd_update) - 1] != '/')
		{
			tmp_path2 = ft_strjoin(cwd_update, "/");
			ft_handle_malloc(ADD_C + TAB_STR1, tmp_path2, 0, data);// revoir le flag
			tmp_path = ft_strjoin(tmp_path2, check);
			ft_handle_malloc(ADD_C + TAB_STR1, tmp_path, 0, data);// revoir le flag
			ft_handle_malloc(DELONE, tmp_path2, 0, NULL);
		}
		else
		{
			tmp_path = ft_strjoin(cwd_update, check);
			ft_handle_malloc(ADD_C + TAB_STR1, tmp_path, 0, data);// revoir le flag
		}
	}
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
char	*ft_get_full_path(t_cmd *cmd, t_data *data)
{
	char	*token;
	int		i;
	int		j;
	int		k;

	token = cmd->token->token;
	if (cmd->cmd_path)
		ft_handle_malloc(DELONE, cmd->cmd_path, 0, NULL);
	cmd->cmd_path = ft_strdup(data->cwd);
	ft_handle_malloc(ADD_C + TAB_STR1, cmd->cmd_path, 0, data);// revoir le flag
	i = 0;
	j = 0;
	k = 0;
	while (token[i])
	{
		if (token[i] && token[i] != '/')
		{
			j = i;
			while (token[j] && token[j] != '/')
				j++;
			if (token[j] && token[j] == '/')
			{
				k = j;
				while (token[k] && token[k] == '/')
					k++;
				ft_update_path(cmd, data, i, j);
				i = k - 1;
			}
			else
			{
				ft_update_path(cmd, data, i, j - 1);
				break ;
			}
		}
		i++;
	}
	return (cmd->cmd_path);
}

/*	<SUMMARY> Gets the correct command path
**	- check #1:	if token = .
**	- check #2:	if token contains a '/'
**		1. token starts with a '/' --> absolute path
**			--> check absolute path (function)
**		2. token does not start with a '/' but has a slash --> relative path
**			a. reconstitute absolute path (function)
**			b. check absolute path (function)
**	- check #3:	if token has no /
**		- on check direct si cette commande existe (access / execve)
**			notre 'ft_find_cmd_path2'
*/

void	ft_path_given(t_data *data, t_cmd *cmd, char *full_path)
{
	if (cmd->token->token[0] == '/')
	{
		full_path = ft_strdup(cmd->token->token);
		ft_handle_malloc(ADD_C + TAB_STR1, full_path, 0, data);
		cmd->cmd_path = ft_check_abs_path(cmd->token->token, full_path, data, \
			ft_strlen(cmd->token->token));
		ft_handle_malloc(ADD_C + TAB_STR1, cmd->cmd_path, 0, data);
	}
	else
	{
		full_path = ft_get_full_path(cmd, data);
		cmd->cmd_path = ft_check_abs_path(cmd->token->token, full_path, data, \
			ft_strlen(cmd->token->token));
		ft_handle_malloc(ADD_C + TAB_STR1, cmd->cmd_path, 0, data);
	}
}

char	*ft_find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*full_path;

	full_path = NULL;
	if (!cmd->token->token)
		return (NULL);
	if (ft_strlen(cmd->token->token) == 1 && cmd->token->token[0] == '.')
	{
		g_val_exit = ft_msg(2, ERRFAR, "\n", ERRFAU);
		ft_free_data_child(g_val_exit, data);
		exit(g_val_exit);
	}
	if (ft_is_in_set(cmd->token->token, '/'))
		ft_path_given(data, cmd, full_path);
	else
		cmd->cmd_path = ft_find_cmd_path2(cmd, data);
	return (cmd->cmd_path);
}
