/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/13 15:41:40 by cgaillag         ###   ########.fr       */
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

char	**ft_init_cmd_opt(t_cmd *cmd, t_data *data)
{
	char	**cmd_opt;
	t_token	*token;
	int		i;

	(void) data;
	token = cmd->token;
	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	cmd_opt = ft_handle_malloc(MALLOC_C + TAB_STR2, NULL, (i + 1), data);
	// cmd_opt = malloc(sizeof(char *) * (i + 1));
	// if (!cmd_opt)
	// 	return (NULL);
	i = 0;
	token = cmd->token;
	while (token)
	{
		cmd_opt[i] = ft_strdup(token->token);
		// cmd_opt[i] = NULL;/// TEST
		// printf("TEST cmd opt [i] = NULL\n");// TEST
		ft_handle_malloc(ADD_C + TAB_STR1, cmd_opt[i], 0, data);
		// if (!cmd_opt[i])
		// {
		// 	ft_free_tabstr(cmd_opt);
		// 	return (NULL);
		// }
		i++;
		token = token->next;
	}
	cmd_opt[i] = NULL;
	return (cmd_opt);
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
		dprintf(2, "passe dans les builtin\n");
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
		//printf("cmd_path = %s\n", cmd->cmd_path);
		if (!cmd->cmd_path)
		{
			//ft_exit_exec(data);
			res = ft_msg(EXIT_FAILURE, "", "", ERRMAL);
			// ft_free_data_child(data);
			ft_handle_malloc(0, NULL, 0, NULL);
			ft_close_std();
			exit(res);
		}
		printf("val cmd path = %s\n", cmd->cmd_path);
		if (execve(cmd->cmd_path, cmd->cmd_opt, data->s_env_path) == -1)
		{
			//ft_exit_exec(data);
			res = ft_msg(126, cmd->token->token, ": ", strerror(errno));
			// ft_free_data_child(data);
			ft_handle_malloc(0, NULL, 0, NULL);
			ft_close_std();
			exit(res);
		}
		ft_close_std();
	}
	ft_close_std();
}

/*	<SUMMARY>
**	Manages the parent process:
**	- waits for the children processes to terminate
**	- gets the error status code from child processes (exit with last child)
**	<PARAM>		{char *} no_redir_cmd --> from get_redir.c
**	<RETURNS>	the size of the new string to be copied unspace_cmd (int)
*/
/*	Function that manages the parent process
**	--> waits for the children processes to terminate
**	and gets the error status code from child processes (exit with last child)
**	Parameters:
**	- ref structure that contains couall key data for pipex prog,
**	- the exit status code (initially set at 1 in main function) and to be
**		updated here
**	Return value: the exit status (when error) of the last child process
*/
int	ft_parent_process(t_data *data)
{
	int		i;
	int		status;

	ft_close_fd(data);
	i = 0;
	while (i < data->nb_pipes + 1)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	// printf("status = %d\n", status);//
	if (WIFEXITED(status))
	{
		if (status == 42)// A TESTER
			ft_free_data_child(1, data);
		status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			status = 128 + WTERMSIG(status);
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
		if (WTERMSIG(status) == SIGINT)
		{
			status = 128 + WTERMSIG(status);
			write(1, "\n", 1);
		}
		status = EINTR;
	}
	// printf("status 2 = %d\n", status);//
	ft_clean_exec(data);
	//ft_exit_exec(data);
	// i = 3;
	// while (i < 1000)
	// {
	// 	close(i);
	// 	i++;
	// }
	return (status);
}

int	ft_nopipe_checkcmd(t_data *data)
{
	if (data->nb_pipes == 0 && data->cmd->token == NULL)
	{
		printf("passe dans la commande vide\n");//
		if (data->cmd->file_err == 1)
			g_val_exit = EXIT_FAILURE;
		else
			g_val_exit = EXIT_SUCCESS;
		ft_clean_exec(data);
		return (g_val_exit);
	}
	if (data->nb_pipes == 0 && data->cmd->token->type == BUILTIN)
	{
		printf("passe dans builin unique\n");//
		if (data->cmd->file_err == 1)
			g_val_exit = EXIT_FAILURE;
		else
			g_val_exit = ft_exec_built_in(data->cmd, data, ADD_M);
		ft_clean_exec(data);
		return (g_val_exit);
	}
	return (-1);
}

int	ft_exec(t_data *data)
{
	int	i;

	if (data->nb_pipes > 0)
		data->pipe_fd = ft_init_pipe(data);
	data->pid = ft_init_pid(data);
	ft_get_files_io(data);
	// {
	// 	g_val_exit = EXIT_FAILURE;
	// 	ft_clean_exec(data);
	// 	return (g_val_exit);
	// }
	if (ft_nopipe_checkcmd(data) >= 0)
		return (g_val_exit);
	// if (data->nb_pipes == 0 && data->cmd->token == NULL)
	// {
	// 	printf("passe dans la commande vide\n");//
	// 	if (data->cmd->file_err == 1)
	// 		g_val_exit = 1;
	// 	else
	// 		g_val_exit = EXIT_SUCCESS;
	// //	ft_exit_exec(data);//a changer
	// 	ft_clean_exec(data);
	// 	return (g_val_exit);
	// }
// 	if (data->nb_pipes == 0 && data->cmd->token->type == BUILTIN)
// 	{
// 		if (data->cmd->file_err == 1)// POURQUOI ON CLEAN PAS ICI ?
// 			g_val_exit = 1;
// 		else
// 		{
// 			printf("passe dans builin unique\n");//
// 			g_val_exit = ft_exec_built_in(data->cmd, data, ADD_M);
// 			ft_clean_exec(data);
// //			ft_exit_exec(data);
// 		}
// 		return (g_val_exit);
// 	}
	//dprintf(2, "init ok\n");
	i = 0;
	while (i < data->nb_pipes)
	{
		if (pipe(data->pipe_fd[i]) == -1)
		{
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
			ft_clean_exec(data);
			return (1);
		}
		i++;
	}
	// // TEST EXEC 2
	//return (22);//
	i = 0;
	while (i < (data->nb_pipes + 1))
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
		else if (data->pid[i] == 0)
		{
			ft_signal(data, SIGQUIT, sig_quit); // default action ca va pas car quitte le minishell avec des leaks en plus
			ft_child_process(data, i);
		}
		i++;
	}
	ft_signal(data, SIGINT, SIG_IGN); // pour eviter d'avoir 2 prompts.
	ft_signal(data, SIGQUIT, SIG_IGN);
	g_val_exit = ft_parent_process(data);
	return (0);
}
