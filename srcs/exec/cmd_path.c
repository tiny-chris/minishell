/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:26:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 19:35:49 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

void	ft_check_error_cmd_path(t_data *data, t_cmd *cmd, int res)
{
	if (data->env_path == NULL || data->s_env_path == NULL)
	{
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
		ft_free_data_child(res, data);
		exit(res);
	}
	if (ft_strncmp(cmd->token->token, "..", ft_strlen(cmd->token->token)) == 0)
	{
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
		ft_free_data_child(res, data);
		exit(res);
	}
}

char	*ft_get_new_path(t_env *env_path, t_data *data)
{
	char	*new_path;
	int		j;

	new_path = NULL;
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
	return (new_path);
}

char	*ft_try_access_path(t_env *env_path, t_data *data, t_cmd *cmd)
{
	char	*new_path;
	char	*cmd_path;

	cmd_path = NULL;
	new_path = NULL;
	while (env_path)
	{
		new_path = ft_get_new_path(env_path, data);
		cmd_path = ft_strjoin(new_path, cmd->token->token);
		ft_handle_malloc(ADD_C + TAB_STR1, cmd_path, 0, data);
		ft_handle_malloc(DELONE, new_path, 0, NULL);
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_handle_malloc(DELONE, cmd_path, 0, NULL);
		env_path = env_path->next;
	}
	return (NULL);
}

char	*ft_find_cmd_path2(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	t_env	*env_path;
	int		res;

	cmd_path = NULL;
	env_path = data->env_path;
	res = -2;
	ft_check_error_cmd_path(data, cmd, res);
	cmd_path = ft_try_access_path(env_path, data, cmd);
	if (cmd_path != NULL)
		return (cmd_path);
	if (cmd->token->env == 1)
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
	else
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
	ft_free_data_child(res, data);
	exit(res);
}
