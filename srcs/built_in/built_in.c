/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:39:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/17 17:04:50 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_exec_built_in(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;

	token = cmd->token;
	if (ft_strncmp(token->token, "echo", 4) == 0)
		g_val_exit = ft_echo(cmd, data, flag);
	else if (ft_strncmp(token->token, "cd", 2) == 0)
		g_val_exit = ft_cd(cmd, data, flag);
	else if (ft_strncmp(token->token, "pwd", 3) == 0)
		g_val_exit = ft_pwd(data);
	else if (ft_strncmp(token->token, "export", 6) == 0)
		g_val_exit = ft_export(cmd, data, flag);
	else if (ft_strncmp(token->token, "unset", 5) == 0)
		g_val_exit = ft_unset(cmd, data);
	else if (ft_strncmp(token->token, "env", 3) == 0)
		g_val_exit = ft_env(cmd, data);
	else if (ft_strncmp(token->token, "exit", 4) == 0)
		g_val_exit = ft_exit(cmd, data, flag);
	return (g_val_exit);
}
