/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:11:22 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 16:37:46 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

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
			new_cwd = ft_substr(cwd_update, 0, i);
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
	ft_handle_malloc(ADD_C + TAB_STR1, cmd->cmd_path, 0, data);
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

/*	<SUMMARY> Checks if absolute path as a directory & its access
**
**	Details (TO BE REMOVED) !!!!!!!!!!!!!!!!!!!!!!!!!!
**	Check #1: is it a directory?
**	- if yes: 'is a directory', 126
**	- if no:
**		Check #2: is the last character of token a '/' (slash)?
**		- if no:
**			Check #3: is access 'F_OK' = success?
**				- if yes:
**					Check #4: is access 'X_OK' = success?
**						- if yes: return token
**						- it no: 'permission denied', 126
**				- if no: 'no such file or directory', 127
**		- if yes (last char = '/')
**			Check #5: is access 'F_OK' = success?
**				- if yes: 'not a directory', 126
**				- if no: 'no such file or directory', 127
*/
char	*ft_check_abs_path(char *token, char *full_path, t_data *data, int len)
{
	DIR		*directory;
	char	*tmp;

	directory = NULL;
	tmp = NULL;
	if (!token)
		return (NULL);
	directory = opendir(full_path);
	dprintf(2, "val de directory = %p\n", directory);//
	if (directory != NULL)
	{
		closedir(directory);
		g_val_exit = ft_msg(126, token, ": ", ERRDIR);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (g_val_exit);
	}
	else
	{
		dprintf(2, "token (len-1) = %c\n", token[len - 1]);
		if (token[len - 1] != '/')
		{
			dprintf(2, "val access full path F OK = %d\n", access((const char *)full_path, F_OK));//
			if (access((const char *)full_path, F_OK) == 0)
			{
				dprintf(2, "val access full path X OK = %d\n", access((const char *)full_path, X_OK));//
				if (access((const char *)full_path, X_OK) == 0)
					return (ft_strdup(full_path));
				else
				{
					g_val_exit = ft_msg(126, token, ": ", ERRPRD);
					ft_handle_malloc(0, NULL, 0, NULL);
					exit (g_val_exit);
				}
			}
		}
		else
		{
			tmp = ft_substr(full_path, 0, ft_strlen(full_path) - 1);
			ft_handle_malloc(ADD_M + TAB_STR1, tmp, 0, data);
			if (access((const char *)tmp, F_OK) == 0)
			{
				ft_handle_malloc(DELONE, tmp, 0, NULL);
				g_val_exit = ft_msg(126, token, ": ", ERRNDR);
				ft_handle_malloc(0, NULL, 0, NULL);
				exit (g_val_exit);
			}
			if (tmp)
				ft_handle_malloc(DELONE, tmp, 0, NULL);
			if (full_path)
				ft_handle_malloc(DELONE, full_path, 0, NULL);
		}
		g_val_exit = ft_msg(127, token, ": ", ERRFOD);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (g_val_exit);
	}
	return (NULL);
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

char	*ft_find_cmd_path2(t_cmd *cmd, t_data *data)
{
	char	*new_path;
	char	*cmd_path;
	t_env	*env_path;
	int		j;
	int		res;

	cmd_path = NULL;
	new_path = NULL;
	env_path = data->env_path;
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
	while (env_path)
	{
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
