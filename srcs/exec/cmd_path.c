/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:26:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/20 15:24:09 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_new_strchr(cmd->token->token, '/'))
	{
		if (ft_strlen(cmd->token->token) == 1)
		{
			ft_exit_exec(data);
			exit(ft_msg(126, "/", ": ", ERRDIR)); // A AJUSTER POUR NE PAS AVOIR 2 MSG D'ERREUR
		}
		else if (cmd->token->token[0] == '/')
		{
			if (access((const char *)cmd->token->token, F_OK | X_OK) == 0)
				return (cmd->token->token);
			ft_exit_exec(data);
			exit(ft_msg(127, cmd->token->token, ": ", ERRFOD));
		}
		cmd_path = ft_strjoin("./", cmd->token->token);
		if (!cmd_path)
		{
			ft_exit_exec(data);
			exit(ft_msg(1, "", "", ERRMAL));
		}
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		ft_exit_exec(data);
		exit(ft_msg(127, cmd->token->token, ": ", ERRFOD));
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

	//printf("debut env_path2\n");
	cmd_path = NULL;
	new_path = NULL;
	env_path = data->env_path;
	if (!data->env_path)
	{
		//printf("env path existe pas\n");
		ft_exit_exec(data);
		exit(ft_msg(127, cmd->token->token, ": ", ERRFOD));
	}
	while (env_path)
	{
		j = ft_strlen(env_path->content) - 1;
		//printf("env pathe content = %s\n", env_path->content);
		if (env_path->content[j] != '/')
		{
			new_path = ft_strjoin(env_path->content, "/");
			//printf("new_path = %s\n", new_path);
		}
		else
			new_path = ft_strdup(env_path->content);
		cmd_path = ft_strjoin(new_path, cmd->token->token);
		free(new_path);
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		env_path = env_path->next;
	}
	ft_exit_exec(data);
	exit(ft_msg(127, cmd->token->token, ": ", ERRCMD));
}
