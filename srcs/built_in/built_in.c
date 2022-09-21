/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:39:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/21 04:27:19 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_uniq_builtin(t_data *data)
{
	t_token	*token;

	token = data->cmd->token;
	if (ft_strncmp(token->token, "echo", 4) == 0)
	{
		data->val_exit = ft_echo(data->cmd, data);
		return (data->val_exit);
	}
	// if (ft_strncmp(token->token, "cd", 2) == 0)
	// 	return (ft_cd(data->cmd, data));
	// if (ft_strncmp(token->token, "pwd", 3) == 0)
	// 	return (ft_pwd(data->cmd, data));
	// if (ft_strncmp(token->token, "export", 6) == 0)
	// 	return (ft_export(data->cmd, data));
	// if (ft_strncmp(token->token, "unset", 5) == 0)
	// 	return (ft_unset(data->cmd, data));
	// if (ft_strncmp(token->token, "env", 3) == 0)
	// 	return (ft_env(data->cmd, data));
	// if (ft_strncmp(token->token, "exit", 4) == 0)
	// 	return (ft_exit(data->cmd, data));
	return (1);
}
