/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:25:45 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/16 22:05:12 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_redirect_inout(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
	{
		if (cmd->infile != 0)
		{
			if (dup2(cmd->infile, STDIN_FILENO) == -1)
				return (-1);
		}
		if (data->nb_pipes > 0)
		{
			if (cmd->outfile != 1)
			{
				if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
					return (-1);
			}
			else
			{
				if (dup2(data->pipe_fd[i][1], STDOUT_FILENO) == -1)
					return (-1);
			}
		}
		else
		{
			if (cmd->outfile != 1)
			{
				if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
					return (-1);
			}
		}
	}
	else if (i > 0 && i == data->nb_pipes)
	{
		if (cmd->infile != 0)
		{
			if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (-1);
		}
		else
		{
			if (dup2(data->pipe_fd[i - 1][0], STDIN_FILENO) == -1)
				return (-1);
		}
		if (cmd->outfile != 1)
		{
			if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
				return (-1);
		}
	}
	else
	{
		if (cmd->infile != 0)
		{
			if (dup2(cmd->infile, STDIN_FILENO) == -1)
				return (-1);
		}
		else
		{
			if (dup2(data->pipe_fd[i - 1][0], STDIN_FILENO) == -1)
				return (-1);
		}
		if (cmd->outfile != 1)
		{
			if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
				return (-1);
		}
		else
		{
			if (dup2(data->pipe_fd[i][1], STDOUT_FILENO) == -1)
				return (-1);
		}
	}
	return (0);
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
	if (res == -1)
	{
		// ft_exit_exec(data);
		g_val_exit = ft_free_data_child(EXIT_FAILURE, data);
		// ft_handle_malloc(0, NULL, 0,0 );
		// ft_close_std();
		exit(g_val_exit);
	}
	if (cmd->token == NULL)//OK
	{
		g_val_exit = ft_free_data_child(EXIT_SUCCESS, data);
		// ft_handle_malloc(0, NULL, 0,0 );
		// ft_close_std();
		exit(g_val_exit);
	}
//	dprintf(2, "child %d: res(redirect inout) = %d\n", i, res);
	if (cmd->token->type == BUILTIN)
	{
		// dprintf(2, "passe dans les builtin\n");
		g_val_exit = ft_exec_built_in(cmd, data, ADD_C);
		ft_free_data_child(g_val_exit, data);
		exit(g_val_exit);// A CORRIGER
	}
	else
	{
		if (cmd->token->type == SP_QUOTES)
		{
			g_val_exit = ft_msg(127, "''", ": ", ERRCMD);
			//ft_exit_exec(data);
			ft_free_data_child(g_val_exit, data);
			// ft_close_std();
			exit(res);
		}
		cmd->cmd_opt = ft_init_cmd_opt(cmd, data);
	//	dprintf(2, "cmd option = %p\n", cmd->cmd_opt);
		// printf("cmd_opt = %s\n", cmd->cmd_opt[0]);
		// printf("cmd_opt = %s\n", cmd->cmd_opt[1]);

			// //TEST - cmd->cmd_opt --> NULL
			// //TEST - cmd->cmd_opt --> NULL ==> desactiver la ligne cmd->cmd_opt = ft_init_... 
			// cmd->cmd_opt = NULL;//TEST - cmd->cmd_opt --> NULL

		// if (cmd->cmd_opt == NULL)
		// {
		// 	//ft_exit_exec(data);
		// 	g_val_exit = ft_msg(1, "", "", ERRMAL);
		// 	ft_handle_malloc(0, NULL, 0, NULL);
		// 	// ft_free_data_child(data);
		// 	ft_close_std();
		// 	exit(res);
		// }
	//	printf("cmd->cmd_opt = %s\n", cmd->cmd_opt[0]);

		cmd->cmd_path = ft_find_cmd_path(cmd, data);
	//	dprintf(2, "cmd path = %s\n", cmd->cmd_path);//
	//	int x = 0;//
	//	char **s_env_path = data->s_env_path;
	//	while (s_env_path[x])//
	//	{//
	//		if (s_env_path[x])//
	//			dprintf(2, "s_env_path[%d] = %s\n", x, s_env_path[x]);//
	//		x++;//
	//	}//
		// if (!cmd->cmd_path)
		// {
		// 	//ft_exit_exec(data);
		// 	res = ft_msg(EXIT_FAILURE, "", "", ERRMAL);
		// 	// ft_free_data_child(data);
		// 	ft_handle_malloc(0, NULL, 0, NULL);
		// 	ft_close_std();
		// 	exit(res);
		// }
		// printf("val cmd path = %s\n", cmd->cmd_path);
		if (execve(cmd->cmd_path, cmd->cmd_opt, data->s_env_path) == -1)
		{
			//ft_exit_exec(data);
			res = ft_msg(126, cmd->token->token, ": ", strerror(errno));
			ft_free_data_child(res, data);
			// ft_handle_malloc(0, NULL, 0, NULL);
			// ft_close_std();
			exit(res);
		}
		ft_close_std();
	}
	ft_close_std();
}
