/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/30 20:55:29 by lmelard          ###   ########.fr       */
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
	cmd_opt = malloc(sizeof(char *) * (i + 1));
	if (!cmd_opt)
		return (NULL);
	i = 0;
	token = cmd->token;
	while (token)
	{
		cmd_opt[i] = ft_strdup(token->token);
		if (!cmd_opt[i])
		{
			ft_free_tabstr(cmd_opt);
			return (NULL);
		}
		i++;
		token = token->next;
	}
	//cmd_opt[i] = ft_strdup("");
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
		ft_exit_exec(data);
		ft_free_data_child(data);
		ft_close_std();
		exit(EXIT_FAILURE);
	}
	if (cmd->token == NULL)
	{
		ft_free_data_child(data);
		ft_close_std();
		exit(EXIT_SUCCESS);
	}
//	dprintf(2, "child %d: res(redirect inout) = %d\n", i, res);
	if (cmd->token->type == BUILTIN)
	{
		dprintf(2, "passe dans les builtin\n");
	 	//data->val_exit = ft_exec_built_in(cmd, data);
		g_val_exit = ft_exec_built_in(cmd, data);
		ft_free_data_child(data);
		exit(g_val_exit);// A CORRIGER
	}
	else
	{
		if (cmd->token->type == SP_QUOTES)
		{
			//ft_exit_exec(data);
			res = ft_msg(127, "''", ": ", ERRCMD);
			ft_free_data_child(data);
			ft_close_std();
			exit(res);
		}
		cmd->cmd_opt = ft_init_cmd_opt(cmd, data);
		// printf("cmd_opt = %s\n", cmd->cmd_opt[0]);
		// printf("cmd_opt = %s\n", cmd->cmd_opt[1]);
		if (cmd->cmd_opt == NULL)
		{
			//ft_exit_exec(data);
			res = ft_msg(1, "", "", ERRMAL);
			ft_free_data_child(data);
			ft_close_std();
			exit(res);
		}
	//	printf("cmd->cmd_opt = %s\n", cmd->cmd_opt[0]);
		cmd->cmd_path = ft_find_cmd_path(cmd, data);
		//printf("cmd_path = %s\n", cmd->cmd_path);
		if (!cmd->cmd_path)
		{
			//ft_exit_exec(data);
			res = ft_msg(EXIT_FAILURE, "", "", ERRMAL);
			ft_free_data_child(data);
			ft_close_std();
			exit(res);
		}
		/*	*****
			partie à commenter pour tester export y.c. pour PATH */
		// data->s_env_path = ft_get_str_env_path(data);
		// if (!data->s_env_path)
		// {
		// 	//ft_exit_exec(data);
		// 	res = ft_msg(EXIT_FAILURE, "", "", ERRMAL);
		// 	ft_free_data_child(data);
		// 	ft_close_std();
		// 	exit(res);
		// }
		/*	*****
			fin de la partie à commenter*/
		if (execve(cmd->cmd_path, cmd->cmd_opt, data->s_env_path) == -1)
		{
			//ft_exit_exec(data);
			res = ft_msg(126, cmd->token->token, ": ", strerror(errno));
			ft_free_data_child(data);
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
	// pid_t	wpid;
	int		i;
	int		status;

	ft_close_fd(data);
	i = 0;
	while (i < data->nb_pipes + 1)
	{
		// wpid = waitpid(data->pid[i], &status, 0);
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	ft_exit_exec(data);
	// i = 3;
	// while (i < 1000)
	// {
	// 	close(i);
	// 	i++;
	// }
	return (status);
}

int	ft_exec(t_data *data)
{
	int	i;

	// if (data->cmd == NULL)
	// 	return (0);
	if (data->nb_pipes > 0)
		data->pipe_fd = ft_init_pipe(data);
	data->pid = ft_init_pid(data);
	ft_get_files_io(data);
	if (data->nb_pipes == 0 && data->cmd->token == NULL)
	{
		//data->val_exit = EXIT_SUCCESS;
		g_val_exit = EXIT_SUCCESS;
		ft_exit_exec(data);
		return (EXIT_SUCCESS);
	}
	if (data->nb_pipes == 0 && data->cmd->token->type == BUILTIN)
	{
		// if (data->cmd->file_err == 1)
		// {
		// 	data->val_exit = 1;
		// 	return (1);
		// }
		// printf("passe dans builin unique\n");
		// return (ft_exec_uniq_builtin(data));
		//
		// //***** nouvelle version - fusion ft_exec_builtin:
		if (data->cmd->file_err == 1)
		{
			//data->val_exit = 1;
			g_val_exit = 1;
		}
		else
		{
			printf("passe dans builin unique\n");//
			//data->val_exit = ft_exec_built_in(data->cmd, data);
			g_val_exit = ft_exec_built_in(data->cmd, data);
			ft_exit_exec(data);
		}
		return (g_val_exit);
		// //***** fin nouvelle version
	}
	//dprintf(2, "init ok\n");
	i = 0;
	while (i < data->nb_pipes)
	{
		if (pipe(data->pipe_fd[i]) == -1)
		{
			//data->val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));;
			ft_exit_exec(data);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < (data->nb_pipes + 1))
	{
		data->pid[i] = fork();
		//dprintf(2, "data->pid[i] = %d\n", data->pid[i]);
		if (data->pid[i] == -1)
		{
			//data->val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
			g_val_exit = ft_msg(errno, ERRMSG, "", strerror(errno));
		}
		else if (data->pid[i] == 0)
			ft_child_process(data, i);
		i++;
	}
	//data->val_exit = ft_parent_process(data);
	g_val_exit = ft_parent_process(data);
	return (0);
}

//Test echo
// int	ft_exec(t_data *data)
// {
// 	t_cmd	*cmd;

// 	cmd = data->cmd;
// 	while (cmd)
// 	{
// 		if (cmd->token->type == BUILTIN && (ft_strncmp(cmd->token->token, "echo", 4) == 0))
// 			printf("%s", ft_echo(cmd, data));
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }
