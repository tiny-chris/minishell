/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/08 13:41:28 by lmelard          ###   ########.fr       */
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
	cmd->stin = dup(STDIN_FILENO);
	if (cmd->stin == -1)
		return (-1);
	cmd->stout = dup(STDOUT_FILENO);
	if (cmd->stout == -1)
		return (-1);
	if (cmd->infile != 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmd->outfile != 1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	ft_redirect_std(t_cmd *cmd)
{
	if (dup2(cmd->stin, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(cmd->stout, STDOUT_FILENO) == -1)
		return (-1);
	close(cmd->stin);
	close(cmd->stout);
	return (0);
}

static void	ft_close_builtin_fd(t_cmd *cmd)
{
	t_token *tok_redir;

	tok_redir = cmd->tok_redir;
	while (tok_redir)
	{
		if (tok_redir->fd != -1)
			close(tok_redir->fd);
		tok_redir = tok_redir->next;
	}
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
			if (data->cmd->tok_redir)
			{
				res = ft_redirect_builtin(data->cmd);
				ft_close_builtin_fd(data->cmd);
				if (res == -1 || data->cmd->token == NULL)
				{
					ft_redirect_std(data->cmd);
					ft_exit_exec(data); // il vaut mieux tout free
					//ft_handle_malloc(0, NULL, 0, 0);
					//g_val_exit = errno;
					ft_msg(errno, ERRMSG, "", strerror(errno));
					exit(errno); // exit a la place comme lors d'une erreur de malloc
				}
			}
			g_val_exit = ft_exec_built_in(data->cmd, data);
			if (data->cmd->tok_redir)
			{
				if (ft_redirect_std(data->cmd) == -1)
				{
					g_val_exit = errno;
					ft_msg(errno, ERRMSG, "", strerror(errno));
					//tout free
					//ft_handle_malloc(0, NULL, 0, 0);
					exit(errno);
				}
			}
			ft_exit_exec(data);
		}
		return (g_val_exit);
	}
	i = 0;
	while (i < data->nb_pipes)
	{
		if (pipe(data->pipe_fd[i]) == -1)
		{
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
			ft_exit_exec(data); // peut etre mieux de tout free et exit
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < (data->nb_pipes + 1))
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno)); // peut etre mieux de tout free et exit aussi
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
