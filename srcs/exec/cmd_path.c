/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:26:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/02 17:44:53 by cgaillag         ###   ########.fr       */
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

// char *tmp_path = NULL;//
// 		int	j = 0;//
// 		int i = 0;//
// 		//ajuster la fonction cf. ci-desssous
// 		if (cmd->token->token[0] == '.' && cmd->token->token[1] && cmd->token->token[1] == '/')
// 		{
// 			j = 1;
// 			while (cmd->token->token[j] && cmd->token->token[j] == '/')
// 				j++;
// 			i = ft_strlen(data->cwd) - 1;
// 			if (data->cwd[i] != '/')
// 			{
// 				tmp_path = ft_strjoin(data->cwd, "/");
// 				if (!tmp_path)
// 					return (NULL);
// 				printf("tmp_path = %s\n", tmp_path);
// 			}
// 			else
// 			{
// 				tmp_path = ft_strdup(data->cwd);
// 				if (!tmp_path)
// 					return (NULL);
// 			}
// 		}


// char	*ft_get_path_parent(char *cwd_update)
// {
// 	char	*new_cwd;
// 	char	*tmp_cwd;
// 	int		i;

// 	new_cwd = NULL;
// 	tmp_cwd = NULL;
// 	i = 0;
// 	if (ft_strlen(cwd_update) == 1 && cwd_update[0] == '/')
// 	{
// 		new_cwd = ft_strdup(cwd_update);
// 		if (!new_cwd)
// 			return (NULL);//tout nettoyer car pb de malloc
// 	}
// 	else
// 	{
// 		i = ft_strlen(cwd_update) - 1;
// 		if (cwd_update[i] == '/')
// 		{
// 			tmp_cwd = ft_substr(cwd_update, 0, i);
// 			if (!tmp_cwd)
// 			return (NULL);//tout nettoyer car pb de malloc
// 		}
// 		else
// 		{
// 			tmp_cwd = ft_strdup(cwd_update);
// 			if (!tmp_cwd)
// 			return (NULL);//tout nettoyer car pb de malloc
// 		}
// 		i = ft_new_strrchr(tmp_cwd, '/');
// 		free(tmp_cwd);//ft_free_str(tmp_cwd);// pour tout mettre a NULL
// 		if (i == 0)
// 		{
// 			new_cwd = ft_strdup("/");
// 			if (!new_cwd)
// 				return (NULL);//tout nettoyer car pb de malloc
// 		}
// 		else
// 			new_cwd = ft_substr(cwd_update, 0, i);//sans le slash
// 	}
// 	return (new_cwd);
// }

// char	*ft_relative_path(char *token, t_data *data)
// {
// 	int		i;
// 	char	*cwd_update;

// 	i = 0;
// 	cwd_update = ft_strdup(data->cwd);
// 	if (!data->cwd)
// 		return (NULL);//tout nettoyer !!
// 	while (token[i])
// 	{
// 		if (token[i] && token[i] == '.')
// 		{
// 			if(token[i + 1] && token[i + 1] == '.')
// 			{
// 				// if (token[i + 2] == '\0')// il y a toujours au moins 1 slash
// 				// 	return (ft_get_path_parent(cwd_update));
// 				if (token[ i + 2] && token[i + 2] == '/')
// 				{
// 					while (token[i + 2] & token[i + 2] == '/')
// 						i++;
// 					if (token[i + 2] == '\0')
// 						return (ft_get_dir_parent(cwd_update));
// 				}
// 				i++;
// 			}
// 		}
// 		i++;
// 	}


// }


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
	if (len == 1 && cmd->token->token[0] == '.')
		exit(ft_msg(2, cmd->token->token, ": ", ERRFAR));
	printf("slash is in set = %d\n", ft_is_in_set(cmd->token->token, '/'));
	if (ft_is_in_set(cmd->token->token, '/'))
	{
		if (cmd->token->token[0] == '/')
		{
			printf("passe ici\n");
			if (access((const char *)cmd->token->token, F_OK | X_OK) == 0)
			{
				printf("passe aussi ici\n");
				directory = opendir(cmd->token->token);
				if (directory == NULL)
				{
					if (cmd->token->token[len - 1] == '/')
						data->val_exit = ft_msg(126, cmd->token->token, ": test11", ERRNDR);//enlever 'test'
					else
						return (cmd->token->token);
				}
				else
				{
					closedir(directory);
					data->val_exit = ft_msg(126, cmd->token->token, ": test13", ERRDIR);//enlever 'test'
				}
			}
			// else if (access((const char *)cmd->token->token, F_OK) == 0)
			// {
			// 	directory = opendir(cmd->token->token);
			// 	if (directory == NULL)
			// 	{
			// 		if (cmd->token->token[len - 1] == '/')
			// 			res = ft_msg(126, cmd->token->token, ": test21", ERRNDR);//enlever 'test'
			// 		else
			// 			return (cmd->token->token);
			// 		// 	res = ft_msg(126, cmd->token->token, ": test22", ERRFOD);//enlever 'test'
			// 	}
			// 	else
			// 	{
			// 		closedir(directory);
			// 		res = ft_msg(126, cmd->token->token, ": test23", ERRDIR);//enlever 'test'
			// 	}
			// }
			else
				data->val_exit = ft_msg(errno, cmd->token->token, ": test auto access", strerror(errno));
			ft_free_data_child(data);
			exit (data->val_exit);
			// if (access((const char *)cmd->token->token, F_OK) == 0)
			// {
			// 	if (access((const char *)cmd->token->token, F_OK | X_OK) == 0)
			// 		return (cmd->token->token);
			// 	directory = opendir(cmd->token->token);
			// 	if (directory == NULL)
			// 		res = ft_msg(126, cmd->token->token, ": test1", ERRNDR);
			// 	else
			// 	{
			// 		closedir(directory);
			// 		res = ft_msg(127, cmd->token->token, ": test1", ERRFOD);
			// 	}
			// 	ft_free_data_child(data);
			// 	exit (res);
			// }
			// directory = opendir(cmd->token->token);
			// if (directory == NULL)
			// 	res = ft_msg(126, cmd->token->token, ": test2 - pas F_OK", ERRNDR);
			// else
			// {
			// 	closedir(directory);
			// 	res = ft_msg(127, cmd->token->token, ": test2 - pas F_OK", ERRFOD);
			// }
			// ft_free_data_child(data);
			// exit (res);
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
	}
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

	//printf("debut env_path2\n");
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
	while (env_path)
	{
		j = ft_strlen(env_path->content) - 1;
		//printf("env pathe content = %s\n", env_path->content);
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
	if (cmd->token->env == 1)
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
	else
		res = ft_msg(127, cmd->token->token, ": ", ERRCMD);
	ft_free_data_child(data);
	exit(res);
}
