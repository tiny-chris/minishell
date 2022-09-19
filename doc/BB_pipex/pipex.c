
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:42:54 by cgaillag          #+#    #+#             */
/*   Updated: 2022/07/21 18:26:56 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/*	Function that handles the child processes
**	Actions:
**	1. apply redirections depending on 'i' (command index = child number)
**		for stdin and stdout & close all fds + protect if error on dup2
**	2. for the command number 'i', get the command options and the command 
**		path + protect if not found
**	3. execute the command (with options) + protect if not possible
*/
void	ft_child_process(t_data *data, int i)
{
	int		res;

	res = ft_redirect_inout(data, i);
	ft_close_fd_pp(data);
	if (res == -1)
		ft_exit_pp(1, data);
	if (data->cmd[i][0] == '\0')
		ft_exit_pp(ft_msg(127, "", ": ", ERMSG_CM), data);
	data->cmd_opt = ft_init_cmd_opt_pp(data->cmd, i);
	if (data->cmd_opt == NULL)
		ft_exit_pp(ft_msg(errno, "", "", ERMSG_UE), data);
	data->cmd_path = ft_find_cmd_path(data, data->cmd_opt[0]);
	if (data->cmd_path == NULL)
		ft_exit_pp(errno, data); 
	if (execve(data->cmd_path, data->cmd_opt, data->envp) == -1)
	{
		ft_exit_pp(ft_msg(126, data->cmd_opt[0], ": ", strerror(errno)), \
		data);
	}
}

/*	Function that manages the parent process
**	--> waits for the children processes to terminate 
**	and gets the error status code from child processes (exit with last child)
**	Parameters: 
**	- ref structure that contains all key data for pipex prog, 
**	- the exit status code (initially set at 1 in main function) and to be 
**		updated here
**	Return value: the exit status (when error) of the last child process
*/
int	ft_parent_process(t_data *data, int exit_status)
{
	pid_t	wpid;
	int		i;
	int		status;

	ft_close_fd_pp(data);
	i = 0;
	while (i < data->nb_cmd)
	{
		wpid = waitpid(data->pid[i], &status, 0);
		if (wpid == data->pid[data->nb_cmd - 1])
		{
			if (i == (data->nb_cmd - 1) && WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (exit_status);
}

/*	Function that:
**	- creates the correct number of pipes considering commands that will be 
**		executed in child processes
**		i.e. for 2 commands, cmd1 in child 1 and cmd2 in child 2
**	- forks to get the correct number of child processes + call ft_child
**	- generates the final exit status via the parent process (call ft_parent)
**	Parameters: 
**	- ref structure that contains all key data for pipex prog, 
**	- the exit status code (initially set at 1 in main function) and to be 
**		updated here
**	Return value: exit status fetched in the parent proc (from child proc)
*/
int	pipex(t_data *data, int exit_status)
{
	int	i;

	i = -1;
	while (++i < data->nb_fd)
	{
		if (pipe(data->fd[i]) == -1)
			ft_exit_pp(ft_msg(errno, ERMSG_ER, "", strerror(errno)), data);
	}
	i = -1;
	while (++i < data->nb_cmd)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			ft_exit_pp(ft_msg(errno, ERMSG_ER, "", strerror(errno)), data);
		else if (data->pid[i] == 0)
			ft_child_process(data, i);
	}
	exit_status = ft_parent_process(data, exit_status);
	return (exit_status);
}

/*  Main function
**	1. check nb of argc (== 5 for basis, >= 5 for bonus)
**	2. check envp (env -i, env -u...)
**	3. initialise a reference structure that will contain all necessary data
**	4. call a pipex function (to generate pipes, fork, exec cmds)
**	5. clean & exit
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		exit_status;

	exit_status = 1;
	if (argc == 5)
	{
		data = ft_init_t_data_pp(argc, argv, envp);
		if (data == NULL)
			ft_exit_pp(ft_msg(1, ERMSG_ER, strerror(errno), ""), NULL);
		exit_status = pipex(data, exit_status);
		ft_exit_pp(exit_status, data);
	}
	ft_putendl_fd(ERMSG_AC, STDERR_FILENO);
	return (exit_status);
}
