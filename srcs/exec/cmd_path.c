/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:26:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/12 22:59:37 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

char	*ft_get_path_parent(char *cwd_update)
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
		ft_handle_malloc(ADD_C + TAB_STR1, new_cwd, 0, data);// revoir le flag
		// if (!new_cwd)
		// 	return (NULL);//tout nettoyer car pb de malloc
	}
	else
	{
		i = ft_strlen(cwd_update) - 1;
		if (cwd_update[i] == '/')
		{
			tmp_cwd = ft_substr(cwd_update, 0, i);
			ft_handle_malloc(ADD_C, tmp_cwd, TAB_STR1, 0);// revoir le flag
			// if (!tmp_cwd)
			// 	return (NULL);//tout nettoyer car pb de malloc
		}
		else
		{
			tmp_cwd = ft_strdup(cwd_update);
			ft_handle_malloc(ADD_C, tmp_cwd, TAB_STR1, 0);// revoir le flag
			// if (!tmp_cwd)
			// 	return (NULL);//tout nettoyer car pb de malloc
		}
		i = ft_new_strrchr(tmp_cwd, '/');
		ft_handle_malloc(DELONE, tmp_cwd, 0, 0);
		// free(tmp_cwd);//ft_free_str(tmp_cwd);// pour tout mettre a NULL
		// tmp_cwd = NULL;
		if (i == 0)
		{
			new_cwd = ft_strdup("/");
			ft_handle_malloc(ADD_C, new_cwd, TAB_STR1, 0);// revoir le flag
			// if (!new_cwd)
			// 	return (NULL);//tout nettoyer car pb de malloc
		}
		else
		{
			new_cwd = ft_substr(cwd_update, 0, i);//sans le slash
			ft_handle_malloc(ADD_C, new_cwd, TAB_STR1, 0);// revoir le flag
		}
	}
	return (new_cwd);
}

/*	<SUMMARY> Updates the cmd_path
	Next step will be to check it (rigths/access & directory)
*/
void	ft_update_path(char **cmd_path, char *token, int i, int j)
{
	char	*tmp_path;
	char	*tmp_path2;
	char	*cwd_update;
	char	*check;

	tmp_path = NULL;
	tmp_path2 = NULL;
	cwd_update = ft_strdup((*cmd_path));
	ft_handle_malloc(ADD_C, cwd_update, TAB_STR1, 0);// revoir le flag
	// if (!cwd_update)
	// 	return ;//malloc / exit
	check = ft_substr(token, i, (j - i + 1));
	ft_handle_malloc(ADD_C, check, TAB_STR1, 0);
	// if (!check)
	// 	return ;//malloc / exit (y compris cwd_update)
	if (ft_strncmp(check, "./", ft_strlen(check)) == 0)
	{
		ft_handle_malloc(DELONE, cwd_update, 0, 0);
		ft_handle_malloc(DELONE, check, 0, 0);
		return ;
	}
	else if (ft_strncmp(check, "../", ft_strlen(check)) == 0)
		tmp_path = ft_get_path_parent(cwd_update);
	else
	//j'ajoute la partie
	{
		i = ft_strlen(cwd_update) - 1;
		if (cwd_update[ft_strlen(cwd_update) - 1] != '/')
		{
			tmp_path2 = ft_strjoin(cwd_update, "/");
			ft_handle_malloc(ADD_C, tmp_path2, TAB_STR1, 0);// revoir le flag
			tmp_path = ft_strjoin(tmp_path2, check);
			ft_handle_malloc(ADD_C, tmp_path, TAB_STR1, 0);// revoir le flag
			ft_handle_malloc(DELONE, tmp_path2, 0, 0);
			// free(tmp_path2);
			// tmp_path2 = NULL;
		}
		else
		{
			tmp_path = ft_strjoin(cwd_update, check);
			ft_handle_malloc(ADD_C, tmp_path, TAB_STR1, 0);// revoir le flag
		}
	}
	// je free cmd_path
	ft_handle_malloc(DELONE, cwd_update, 0, 0);
	ft_handle_malloc(DELONE, check, 0, 0);
	// je recup tmp
	ft_handle_malloc(DELONE, (*cmd_path), 0, 0);
	// free((*cmd_path));
	// (*cmd_path) = NULL;
	(*cmd_path) = tmp_path;
}

/*	<SUMMARY> Gets full path (absolute path) from a potential relative path by:
	- cleaning ./ & ../
	- using strjoin to gather root part to cmd part
	Next step will be to check it (rigths/access & directory)
*/
char	*ft_get_full_path(char *token, t_data *data)
{
	char	*cmd_path;
	int		i;
	int		j;
	int		k;

	cmd_path = ft_strdup(data->cwd);
	ft_handle_malloc(ADD_C, cmd_path, TAB_STR1, 0);// revoir le flag
	// if (!cmd_path)
	// 	return (NULL);//nettoyer tout les malloc & exit (new prompt)
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
				//je récupère un 'directory' ('./' ou '..////' ou 'usr/'...)
				//je mets à jour mon cwd_update
				ft_update_path(&cmd_path, token, i, j);
				i = k - 1;
			}
			else// (token[j] == '\0')
			{
				ft_update_path(&cmd_path, token, i, j - 1);
				break ;
			}
		}
		i++;
	}
	return (cmd_path);
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

	(void) data;
	directory = NULL;
	tmp = NULL;
	if (!token)
		return (NULL);
	directory = opendir(full_path);
	//printf("val de directory = %p\n", directory);
	if (directory != NULL)// c'est un directory
	{
		closedir(directory);
		g_val_exit = ft_msg(126, token, ": ", ERRDIR);
		// ft_free_data_child(data);
		ft_handle_malloc(0, NULL, 0, 0);
		// if (full_path)
		// 	ft_handle_malloc(DELONE, full_path, 0, 0);
		// {
		// 	free(full_path);
		// 	full_path = NULL;
		// }
		exit (g_val_exit);
	}
	else
	{
		if (token[len - 1] != '/')
		{
			if (access((const char *)full_path, F_OK) == 0)
			{
				if (access((const char *)full_path, X_OK) == 0)
					return (ft_strdup(full_path));
				else
				{
					g_val_exit = ft_msg(126, token, ": ", ERRPRD);//enlever 'test'
					// ft_free_data_child(data);
					ft_handle_malloc(0, NULL, 0, 0);
					// if (full_path)
					// 	ft_handle_malloc(DELONE, full_path, 0, 0);
					// {
					// 	free(full_path);
					// 	full_path = NULL;
					// }
					exit (g_val_exit);
				}
			}
			// printf("full path n'est PAS F_OK\n");
		}
		else
		{
			tmp = ft_substr(full_path, 0, ft_strlen(full_path) - 1);
			ft_handle_malloc(ADD_M, tmp, TAB_STR1, 0);
			if (access((const char *)tmp, F_OK) == 0)
			{
				free(tmp);
				tmp = NULL;
				g_val_exit = ft_msg(126, token, ": ", ERRNDR);
				// ft_free_data_child(data);
				ft_handle_malloc(0, NULL, 0, 0);
				// if (full_path)
				// 	ft_handle_malloc(DELONE, full_path, 0, 0);
				// {
				// 	free(full_path);
				// 	full_path = NULL;
				// }
				exit (g_val_exit);
			}
			if (tmp)
				ft_handle_malloc(DELONE, tmp, 0, 0);
			// {
			// 	free(tmp);
			// 	tmp = NULL;
			// }
			if (full_path)
				ft_handle_malloc(DELONE, full_path, 0, 0);
			// {
			// 	free(full_path);
			// 	full_path = NULL;
			// }
		}
		g_val_exit = ft_msg(127, token, ": ", ERRFOD);
		// ft_free_data_child(data);
		ft_handle_malloc(0, NULL, 0, 0);
		// if (full_path)
		// 	ft_handle_malloc(DELONE, full_path, 0, 0);
		// {
		// 	free(full_path);
		// 	full_path = NULL;
		// }
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
char	*ft_find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	char	*full_path;

	cmd_path = NULL;
	full_path = NULL;
	if (!cmd->token->token)
		return (NULL);
	if (ft_strlen(cmd->token->token) == 1 && cmd->token->token[0] == '.')
		exit(ft_msg(2, ERRFAR, "\n", ERRFAU));
	if (ft_is_in_set(cmd->token->token, '/'))
	{
		if (cmd->token->token[0] == '/')
		{
			full_path = ft_strdup(cmd->token->token);
			ft_handle_malloc(ADD_C + TAB_STR1, full_path, 0, data);
			cmd_path = ft_check_abs_path(cmd->token->token, full_path, data, \
				ft_strlen(cmd->token->token));
			ft_handle_malloc(ADD_C + TAB_STR1, cmd_path, 0, data);
		}
		else
		{
			full_path = ft_get_full_path(cmd->token->token, data);
			// a proteger dans la fonction OK
			// if (!full_path)
			// 	return (NULL);//tout nettoyer malloc et exit
			cmd_path = ft_check_abs_path(cmd->token->token, full_path, data, \
				ft_strlen(cmd->token->token));
			ft_handle_malloc(ADD_C + TAB_STR1, cmd_path, 0, data);
		}
	}
	else
		cmd_path = ft_find_cmd_path2(cmd, data);
	dprintf(2, "passe et ne fait pas cmd_path1\n");
	return (cmd_path);
}

char	*ft_find_cmd_path2(t_cmd *cmd, t_data *data)
{
	char	*new_path;
	char	*cmd_path;
	t_env	*env_path;
	int		j;
	int		res;

	printf("debut env_path2\n");
	cmd_path = NULL;
	new_path = NULL;
	env_path = data->env_path;
	res = -2;
	if (!data->env_path)
	{
		//printf("env path existe pas\n");
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
		// ft_free_data_child(data);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit(res);
	}
	if (ft_strncmp(cmd->token->token, "..", ft_strlen(cmd->token->token)) == 0)
	{
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
		// ft_free_data_child(data);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit(res);
	}
	dprintf(2, "passe dans env_path2 et va tester le PATH\n");
	while (env_path)
	{
		j = ft_strlen(env_path->content) - 1;
		//printf("env path content = %s\n", env_path->content);
		if (env_path->content[j] != '/')
		{
			new_path = ft_strjoin(env_path->content, "/");
			ft_handle_malloc(ADD_C + TAB_STR1, new_path, 0, data);
			// if (!new_path)
			// 	return (NULL);
			//printf("new_path = %s\n", new_path);
		}
		else
		{
			new_path = ft_strdup(env_path->content);
			ft_handle_malloc(ADD_C + TAB_STR1, new_path, 0, data);
			// if (!new_path)
			// 	return (NULL);
		}
		// printf("new_path avec join slash = %s\n", new_path);
		cmd_path = ft_strjoin(new_path, cmd->token->token);
		ft_handle_malloc(ADD_C + TAB_STR1, cmd_path, 0, data);
		// if (!cmd_path)
		// 	return (free(new_path), NULL);
		// printf("new_path avec join slash = %s\n", cmd_path);
		ft_handle_malloc(DELONE, new_path, 0, NULL);
		// free(new_path);
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_handle_malloc(DELONE, cmd_path, 0, NULL);
		// free(cmd_path);
		env_path = env_path->next;
	}
//	printf("check je suis là\n");
	if (cmd->token->env == 1)
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
	else
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
	// ft_free_data_child(data);
	ft_handle_malloc(0, NULL, 0, NULL);
	exit(res);
}
