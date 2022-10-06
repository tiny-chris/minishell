/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/06 18:49:14 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

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

static int	ft_redirect_builtin(t_cmd *cmd)
{
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmd->outfile != 1)
	{
		printf("testoutfile \n");
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

static void	ft_redirect_std(void)
{
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}

static void	ft_close_builtin_fd(t_data *data)
{
	if (data->cmd->infile != 0)
		close (data->cmd->infile);
	if (data->cmd->outfile != 1)
		close (data->cmd->outfile);
}

int	ft_exec(t_data *data)
{
	int	i;
	int	res;

	if (data->nb_pipes > 0)
		data->pipe_fd = ft_init_pipe(data);
	data->pid = ft_init_pid(data);
	ft_get_files_io(data);
	if (data->nb_pipes == 0 && data->cmd->token == NULL)
	{
		g_val_exit = EXIT_SUCCESS;
		ft_exit_exec(data);
		return (EXIT_SUCCESS);
	}
	if (data->nb_pipes == 0 && data->cmd->token->type == BUILTIN)
	{
		if (data->cmd->file_err == 1)
			g_val_exit = 1;
		else
		{
			printf("passe dans builin unique\n"); //
			res = ft_redirect_builtin(data->cmd);
			dprintf(2, "test\n");
			ft_close_builtin_fd(data);
			if (res == -1 || data->cmd->token == NULL)
			{
				ft_exit_exec(data);
				ft_redirect_std();
				return (EXIT_FAILURE);
			}
			g_val_exit = ft_exec_built_in(data->cmd, data);
			ft_exit_exec(data);
			printf("stdin %d\n", STDERR_FILENO);
			ft_redirect_std();
		}
		return (g_val_exit);
	}
	//dprintf(2, "init ok\n");
	i = 0;
	while (i < data->nb_pipes)
	{
		if (pipe(data->pipe_fd[i]) == -1)
		{
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
			ft_exit_exec(data);
			return (1);
		}
		i++;
	}
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
