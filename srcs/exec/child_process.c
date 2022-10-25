/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:25:45 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/25 19:11:10 by cgaillag         ###   ########.fr       */
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

static void	ft_check_file_err(t_cmd *cmd, t_data *data)
{
	if (cmd->file_err == 1)
	{
		ft_close_fd(data);
		ft_free_data_child(1, data);
		exit(1);
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
	ft_check_file_err(cmd, data);
	res = ft_redirect_inout(data, cmd, i);
	ft_close_fd(data);
	ft_start_child_process(cmd, data, res);
	cmd->cmd_opt = ft_init_cmd_opt(cmd, data);
	cmd->cmd_path = ft_find_cmd_path(cmd, data);
	if (execve(cmd->cmd_path, cmd->cmd_opt, data->s_env) == -1)
	{
		res = ft_msg(126, cmd->token->token, ": ", strerror(errno));
		ft_free_data_child(res, data);
		exit(res);
	}
	ft_close_std();
}
