/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:25:45 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 23:14:52 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static void	ft_start_child_process(t_cmd *cmd, t_data *data, int res)
{
	if (res == -1)
	{
		g_val_exit = ft_free_data_child(EXIT_FAILURE, data);
		exit(g_val_exit);
	}
	if (cmd->token == NULL)
	{
		g_val_exit = ft_free_data_child(EXIT_SUCCESS, data);
		exit(g_val_exit);
	}
	if (cmd->token->type == BUILTIN)
	{
		g_val_exit = ft_exec_built_in(cmd, data, ADD_C);
		ft_free_data_child(g_val_exit, data);
		exit(g_val_exit);
	}
	if (cmd->token->type == SP_QUOTES)
	{
		g_val_exit = ft_msg(127, "''", ": ", ERRCMD);
		ft_free_data_child(g_val_exit, data);
		exit(res);
	}
}

void	ft_child_process(t_data *data, int i)
{
	t_cmd	*cmd;
	int		j;
	int		res;

	cmd = data->cmd;
	j = i;
	while (j > 0)
	{
		cmd = cmd->next;
		j--;
	}
	res = ft_redirect_inout(data, cmd, i);
	ft_close_fd(data);
	ft_start_child_process(cmd, data, res);
	cmd->cmd_opt = ft_init_cmd_opt(cmd, data);
	cmd->cmd_path = ft_find_cmd_path(cmd, data);
	if (execve(cmd->cmd_path, cmd->cmd_opt, data->s_env_path) == -1)
	{
		res = ft_msg(126, cmd->token->token, ": ", strerror(errno));
		ft_free_data_child(res, data);
		exit(res);
	}
	ft_close_std();
}
