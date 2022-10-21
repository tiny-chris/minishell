/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:36:10 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 21:39:31 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

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

static void	ft_find_cmd_path_slash(t_cmd *cmd, char *full_path, t_data *data)
{
	if (cmd->token->token[0] == '/')
	{
		full_path = ft_strdup(cmd->token->token);
		dprintf(2, "val full path = %s\n", full_path);
		ft_handle_malloc(ADD_C + TAB_STR1, full_path, 0, data);
		cmd->cmd_path = ft_check_abs_path(cmd->token->token, full_path, data, \
			ft_strlen(cmd->token->token));
		dprintf(2, "val de full path apres check abs = %s\n", cmd->cmd_path);
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

static void	ft_find_cmd_path2_error(t_data *data, t_cmd *cmd)
{
	int	res;

	res = -2;
	if (!data->env_path)
	{
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit(res);
	}
	if (ft_strncmp(cmd->token->token, "..", ft_strlen(cmd->token->token)) == 0)
	{
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit(res);
	}
}

static char	*ft_malloc_cmd_path(t_env *env_path, t_data *data, t_cmd *cmd)
{
	char	*new_path;
	char	*cmd_path;
	int		j;

	new_path = NULL;
	cmd_path = NULL;
	j = ft_strlen(env_path->content) - 1;
	if (env_path->content[j] != '/')
	{
		new_path = ft_strjoin(env_path->content, "/");
		ft_handle_malloc(ADD_C + TAB_STR1, new_path, 0, data);
	}
	else
	{
		new_path = ft_strdup(env_path->content);
		ft_handle_malloc(ADD_C + TAB_STR1, new_path, 0, data);
	}
	cmd_path = ft_strjoin(new_path, cmd->token->token);
	ft_handle_malloc(ADD_C + TAB_STR1, cmd_path, 0, data);
	ft_handle_malloc(DELONE, new_path, 0, NULL);
	return (cmd_path);
}

char	*ft_find_cmd_path2(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	t_env	*env_path;
	int		res;

	cmd_path = NULL;
	env_path = data->env_path;
	res = -2;
	ft_find_cmd_path2_error(data, cmd);
	while (env_path)
	{
		cmd_path = ft_malloc_cmd_path(env_path, data, cmd);
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_handle_malloc(DELONE, cmd_path, 0, NULL);
		env_path = env_path->next;
	}
	if (cmd->token->env == 1)
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
	else
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
	ft_handle_malloc(0, NULL, 0, NULL);
	exit(res);
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
	{
		ft_find_cmd_path_slash(cmd, full_path, data);
	}
	else
		cmd->cmd_path = ft_find_cmd_path2(cmd, data);
	return (cmd->cmd_path);
}
