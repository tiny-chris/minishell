/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:26:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/03 02:05:25 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// fonction à déployer
// cas :
/*	./		--> ./: Is a directory
	..		--> ..: command not found
	..///	--> ..///: Is a directory
	///		--> ///: Is a directory
	.//.	--> ././: Is a directory
	././c	--> ././c: No such file or directory


	./a.out	--> Hello Hello !

	utiliser data->cwd (+ / + texte)
	revoir les . et ..


*/
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
		if (!new_cwd)
			return (NULL);//tout nettoyer car pb de malloc
	}
	else
	{
		i = ft_strlen(cwd_update) - 1;
		if (cwd_update[i] == '/')
		{
			tmp_cwd = ft_substr(cwd_update, 0, i);
			if (!tmp_cwd)
				return (NULL);//tout nettoyer car pb de malloc
		}
		else
		{
			tmp_cwd = ft_strdup(cwd_update);
			if (!tmp_cwd)
				return (NULL);//tout nettoyer car pb de malloc
		}
		i = ft_new_strrchr(tmp_cwd, '/');
		free(tmp_cwd);//ft_free_str(tmp_cwd);// pour tout mettre a NULL
		tmp_cwd = NULL;
		if (i == 0)
		{
			new_cwd = ft_strdup("/");
			if (!new_cwd)
				return (NULL);//tout nettoyer car pb de malloc
		}
		else
			new_cwd = ft_substr(cwd_update, 0, i);//sans le slash
	}
	return (new_cwd);
}

/*	<SUMMARY> Updates the cmd_
	Next step will be to check it (acces & opendir)
*/
void	ft_update_path(char **cmd_path, char *token, int i, int j)
{
	char	*tmp_path;
	char	*tmp_path2;
	char	*cwd_update;
	char	*check;
	//int		k;

	tmp_path = NULL;
	tmp_path2 = NULL;
	cwd_update = ft_strdup((*cmd_path));
	if (!cwd_update)
		return ;//malloc / exit
	check = ft_substr(token, i, (j - i + 1));
	if (!check)
		return ;//malloc / exit
	if (ft_strncmp(check, "./", ft_strlen(check)) == 0)
		return ;
	else if (ft_strncmp(check, "../", ft_strlen(check)) == 0)
		tmp_path = ft_get_path_parent(cwd_update);
	else
	//j'ajoute la partie
	{
		i = ft_strlen(cwd_update) - 1;
		if (cwd_update[ft_strlen(cwd_update) - 1] != '/')
		{
			tmp_path2 = ft_strjoin(cwd_update, "/");
			tmp_path = ft_strjoin(tmp_path2, check);
			free(tmp_path2);
		}
		else
			tmp_path = ft_strjoin(cwd_update, check);
	}
	free (cwd_update);
	cwd_update = NULL;
	free(check);
	check = NULL;
	// je free cmd_path
	// je recup tmp
	free((*cmd_path));
	(*cmd_path) = NULL;
	(*cmd_path) = tmp_path;
}

/*	<SUMMARY> Gets full path (absolute path) from a potential relative path by:
	- cleaning ./ & ../
	- using strjoin to gather root part to cmd part
	Next step will be to check it (acces & opendir)
*/
char	*ft_get_full_path(char *token, t_data *data)
{
	char	*cmd_path;
	int		i;
	int		j;
	int		k;

	cmd_path = ft_strdup(data->cwd);
	if (!cmd_path)
		return (NULL);//nettoyer tout les malloc & exit (new prompt)
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

/*	<SUMMARY> Gets the correct command path
**	- check #1:	if token = .
**	- check #2:	if token contains a /
**		- token starts with a / --> absolute path : check if access F_OK
**			- if yes : check if access F_OK et X_OK
**				- if OK : return token
**				- if not OK : check if is a directory
**					- if is a directory : is a directory, 126
**					- if not : not such file or directory, 127
**			- if no : check if is a directory
**				- if is a directory : is a directory, 126
**				- if not : not such file or directory, 127
**		- token does not start with a / --> relative path
**			a. boucle ./ et ../
**			b. get the tmp_path (pwd updated + token sans ./ ou ../)
**			c. on teste acces et si directory
**				- same as above
**	- check #3:	if token has no /
**		- on check direct si cette commande existe (access / execve)
**			notre 'ft_find_cmd_path2'
*/
char	*ft_find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	DIR		*directory;
	int		len;
	//int		res;

	cmd_path = NULL;
	directory = NULL;
	//res = -2;
	len = ft_strlen(cmd->token->token);
	//peut-on avoir cmd->token-token == empty ??
	if (len == 1 && cmd->token->token[0] == '.')
		exit(ft_msg(2, cmd->token->token, ": ", ERRFAR));
	printf("slash is in set = %d\n", ft_is_in_set(cmd->token->token, '/'));
	if (ft_is_in_set(cmd->token->token, '/'))
	{
		if (cmd->token->token[0] == '/')
		{
			printf("passe ici : 1er caractere est un slash\n");
			directory = opendir(cmd->token->token);
			if (directory != NULL)
			{
				closedir(directory);
				data->val_exit = ft_msg(126, cmd->token->token, ": testisdir ", ERRDIR);//enlever 'test'
				ft_free_data_child(data);
				exit (data->val_exit);
			}
			else
			{
				if (cmd->token->token[len - 1] == '/')
				{
					data->val_exit = ft_msg(126, cmd->token->token, ": testnotdir/ ", ERRNDR);//enlever 'test
					ft_free_data_child(data);
					exit (data->val_exit);
				}
				else
				{
					if (access((const char *)cmd->token->token, F_OK | X_OK) == 0)
						return (cmd->token->token);
					data->val_exit = ft_msg(127, cmd->token->token, ": testnotdir- ", ERRFOD);//enlever 'test
					ft_free_data_child(data);
					exit (data->val_exit);
				}
			}
		}
		else// ne commence pas par '/' mais en contient
		{
			printf("passe là : 1er caractere n'est pas un slash mais il y a un slash\n");
			/*
				1. je reconstitue le path absolu
				2. je vérifie dir/access
			*/
			//step 1: je reconstitue le path absolu
			cmd_path = ft_get_full_path(cmd->token->token, data);
			if (!cmd_path)
				return (NULL);//tout nettoyer malloc et exit
			//step 2: je vérifie dir/access
			directory = opendir(cmd_path);
			if (directory != NULL)
			{
				closedir(directory);
				data->val_exit = ft_msg(126, cmd->token->token, ": testisdir2 ", ERRDIR);//enlever 'test'
				ft_free_data_child(data);
				exit (data->val_exit);
			}
			else
			{
				if (cmd->token->token[len - 1] == '/')
				{
					data->val_exit = ft_msg(126, cmd->token->token, ": testnotdir2/ ", ERRNDR);//enlever 'test
					ft_free_data_child(data);
					exit (data->val_exit);
				}
				else
				{
					if (access((const char *)cmd_path, F_OK | X_OK) == 0)
						return (cmd_path);
				//	data->val_exit = ft_msg(127, cmd->token->token, ": testnotdir- ", ERRFOD);//enlever 'test
					data->val_exit = ft_msg(126, cmd->token->token, ": testnotdir- ", strerror(errno));
					/// BUG FORCE A LA MAIN : 126 au lieu de errno (13???) mais faute si 127...
					/// essayer d'inverser directory et access
					ft_free_data_child(data);
					exit (data->val_exit);
				}
			}
			// //else// ne commence pas par '/' mais en contient
			// cmd_path = ft_relative_path(cmd->token->token, data);
			// if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			// 	return (cmd_path);
			// free(cmd_path);
			// //ft_exit_exec(data);
			// res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
			// ft_free_data_child(data);
			// exit(res);

			// printf("passe là : 1er caractere n'est pas un slash mais il y a un slash\n");
			// return (NULL);
		}
	}
	else
		cmd_path = ft_find_cmd_path2(cmd, data);
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
		//ft_exit_exec(data);
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
		ft_free_data_child(data);
		exit(res);
	}
	if (ft_strncmp(cmd->token->token, "..", ft_strlen(cmd->token->token)) == 0)
	{
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
		ft_free_data_child(data);
		exit(res);
	}
	while (env_path)
	{
		j = ft_strlen(env_path->content) - 1;
		//printf("env path content = %s\n", env_path->content);
		if (env_path->content[j] != '/')
		{
			new_path = ft_strjoin(env_path->content, "/");
			if (!new_path)
				return (NULL);
			//printf("new_path = %s\n", new_path);
		}
		else
		{
			new_path = ft_strdup(env_path->content);
			if (!new_path)
				return (NULL);
		}
		cmd_path = ft_strjoin(new_path, cmd->token->token);
		if (!cmd_path)
			return (free(new_path), NULL);
		free(new_path);
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		env_path = env_path->next;
	}
	//ft_exit_exec(data);
	printf("check je suis là\n");
	if (cmd->token->env == 1)
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
	else
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
	ft_free_data_child(data);
	exit(res);
}
