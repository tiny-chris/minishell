/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/25 14:27:19 by cgaillag         ###   ########.fr       */
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

void	ft_make_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipes)
	{
		if (pipe(data->pipe_fd[i]) == -1)
		{
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
			ft_close_fd(data);
			g_val_exit = ft_free_data_child(1, data);
			exit (g_val_exit);
		}
		i++;
	}
}

void	ft_fork(t_data *data, int *res)
{
	int	i;

	i = 0;
	while (i < (data->nb_pipes + 1))
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
		{
			g_val_exit = errno;
			*res = i;
			i = data->nb_pipes + 1;
			break ;
		}
		else if (data->pid[i] == 0)
		{
			ft_signal(data, SIGQUIT, sig_quit);
			ft_child_process(data, i);
		}
		i++;
	}
}

int	ft_exec(t_data *data)
{
	int	res;
	int	j;

	j = 0;
	if (data->nb_pipes > 0)
		data->pipe_fd = ft_init_pipe(data);
	data->pid = ft_init_pid(data);
	ft_get_files_io(data);
	if (data->nb_pipes == 0 && data->cmd->token == NULL)
		return (ft_no_pipe_no_token(data));
	if (ft_check_heredoc(data) && g_val_exit == 130)
		return (ft_check_sigint_heredoc(data));
	if (data->nb_pipes == 0 && data->cmd->token->type == BUILTIN)
		return (ft_unique_builtin(data));
	ft_make_pipe(data);
	res = -1;
	ft_fork(data, &res);
	if (res >= 0)
		exit (ft_parent_exit(data, res));
	ft_signal(data, SIGQUIT, SIG_IGN);
	ft_signal(data, SIGINT, SIG_IGN);
	g_val_exit = ft_parent_process(data, j);
	return (0);
}
