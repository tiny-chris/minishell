/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:26:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/02 14:20:39 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	int		res;

	cmd_path = NULL;
	res = -2;
	if ()
}


char	*ft_find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	DIR		*directory;
	int		res;

	directory = NULL;
	cmd_path = NULL;
	res = -2;
	printf("val cmd token token = %s\n", cmd->token->token);
	printf("val ft_is in set = %d\n", ft_is_in_set(cmd->token->token, '/'));
	//if (ft_new_strchr(cmd->token->token, '/'))
	if (ft_is_in_set(cmd->token->token, '/'))
	{
		if (cmd->token->token[0] == '/')
		{
			
		}
		
		if (ft_strlen(cmd->token->token) == 1)
		{
			//ft_exit_exec(data);
			ft_free_data_child(data);
			exit(ft_msg(126, "/", ": ", ERRDIR)); // A AJUSTER POUR NE PAS AVOIR 2 MSG D'ERREUR
		}
		else if (cmd->token->token[0] == '/')
		{
			if (access((const char *)cmd->token->token, F_OK | X_OK) == 0)
				return (cmd->token->token);
			//ft_exit_exec(data);
			res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
			ft_free_data_child(data);
			exit(res);
		}
		//ft_relative_path(cmd->token->token, data);
		//
		// A CORRIGER !!!!!*****!!!!!!******!!!!!!*****!!!!!!
		//
		// cmd_path = ft_strjoin(tmp_path, cmd->token->token + j);
		// printf("cmd_path = %s\n", tmp_path);
		if (!cmd_path)
		{
			//ft_exit_exec(data);
			ft_free_data_child(data);
			exit(ft_msg(1, "", "", ERRMAL));
		}
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		//ft_exit_exec(data);
		res = ft_msg(127, cmd->token->token, ": ", ERRFOD);
		ft_free_data_child(data);
		exit(res);
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

// fonction à déployer
// cas :
/*	.		--> filename argument required
	./		--> ./: Is a directory
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


char	*ft_relative_path(char *token, t_data *data)
{
	int		i;
	char	*cwd_update;

	i = 0;
	cwd_update = ft_strdup(data->cwd);
	if (!data->cwd)
		return (NULL);//tout nettoyer !!
	while (token[i])
	{
		if (token[i] && token[i] == '.')
		{
			if(token[i + 1] && token[i + 1] == '.')
			{
				if (token[i + 2] == '\0')
					return (ft_get_dir_parent(cwd_update));
				else if (token[ i + 2] && token[i + 2] == '/')
				{
					while (token[i + 2] & token[i + 2] == '/')
						i++;
					if (token[i + 2] == '\0')
						return (ft_get_dir_parent(cwd_update));
				}
				i++;
			}
		}
		i++;
	}

	/*
		Tant que
	*/


}
