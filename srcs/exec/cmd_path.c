/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:26:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/19 15:51:49 by lmelard          ###   ########.fr       */
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
			data->val_exit = ft_msg(126, "/", ": ", ERRDIR); // A AJUSTER POUR NE PAS AVOIR 2 MSG D'ERREUR
			return (NULL);
		}
		else if (cmd->token->token[0] == '/')
		{
			if (access((const char *)cmd->token->token, F_OK | X_OK) == 0)
				return (cmd->token->token);
			data->val_exit = ft_msg(127, cmd->token->token, ": ", ERRFOD);
			return (NULL);
		}
		cmd_path = ft_strjoin("./", cmd->token->token);
		if (!cmd_path)
		{
			val_exit = ft_msg(1, "", "", ERRMAL);
			return (NULL);
		}
		if (access((const char *)cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		data->val_exit = ft_msg(127, cmd->token->token, ": ", ERRFOD);
		return (NULL);
	}
	cmd_path = ft_find_cmd_path2(cmd, data);
	return (cmd_path);
}
