/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:09:32 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/13 17:02:33 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_std(void)
{
	if (STDIN_FILENO != -1)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != -1)
		close(STDOUT_FILENO);
	if (STDERR_FILENO != -1)
		close(STDERR_FILENO);
}

void	ft_clean_exec(t_data *data)
{
	int	i;

	i = 0;
	if (data != NULL)
	{
		if (data->pid != NULL)
			ft_handle_malloc(DELONE, data->pid, 0, NULL);
		if (data->pipe_fd != NULL)
		{
			i = 0;
			while (i < data->nb_pipes)
			{
				ft_handle_malloc(DELONE, data->pipe_fd[i], 0, NULL);
				i++;
			}
			ft_handle_malloc(DELONE, data->pipe_fd, 0, NULL);
		}
	}
}

void	ft_exit_exec(t_data *data)//, int val_exit)
{
	int	i;

	i = 0;
	if (data != NULL)
	{
		if (data->pid != NULL)
		{
			free (data->pid);
			data->pid = NULL;
		}
		if (data->pipe_fd != NULL)
		{
			ft_free_tabint(data->pipe_fd, data->nb_pipes);// incorrect sinon creer une fonction comme ft_free_tabstr_bin
			data->pipe_fd = NULL;
		}
		if (data->s_env_path != NULL)
		{
			while (data->s_env_path[i])
			{
				ft_handle_malloc(DELONE, data->s_env_path[i], 0, NULL);
				i++;
			}
			ft_handle_malloc(DELONE, data->s_env_path, 0, NULL);
		}
		// if (val_exit != -1)
		// 	data->val_exit = val_exit;
	}
}

// void	ft_free_data_child(t_data *data)
// {
// 	if (data->line != NULL)
// 	{
// 		free(data->line);
// 		data->line = NULL;
// 	}
// 	if (data->prompt != NULL)
// 	{
// 		free(data->prompt);
// 		data->prompt = NULL;
// 	}
// 	if (data->env != NULL)
// 	{
// 		ft_free_env(&(data->env));
// 		data->env = NULL;
// 	}
// 	if (data->cwd != NULL)
// 	{
// 		free(data->cwd);
// 		data->cwd = NULL;
// 	}
// 	if (data->oldpwd != NULL)
// 	{
// 		free(data->oldpwd);
// 		data->oldpwd = NULL;
// 	}
// 	if (data->home != NULL)
// 	{
// 		free(data->home);
// 		data->home = NULL;
// 	}
// 	if (data->str_exit != NULL)
// 	{
// 		free(data->str_exit);
// 		data->str_exit = NULL;
// 	}
// 	if (data->cmd != NULL)
// 	{
// 		ft_free_cmd(&(data->cmd));
// 		data->cmd = NULL;
// 	}
// 	if (data->built_in != NULL)
// 		ft_free_tabstr_bin(data->built_in, TAB_STRS);
// 	if (data->pid != NULL)
// 	{
// 		free (data->pid);
// 		data->pid = NULL;
// 	}
// 	if (data->pipe_fd != NULL)
// 		ft_free_tabint_bin(data->pipe_fd, data->nb_pipes, TAB_INTS);
// 	if (data->env_path != NULL)
// 	{
// 		ft_free_env(&(data->env_path));
// 		data->env_path = NULL;
// 	}
// 	if (data->s_env_path != NULL)
// 		ft_free_tabstr_bin(data->s_env_path, TAB_STRS);
// }

int	ft_free_data_child(int res, t_data *data)
{
	(void) data;// A REVOIR
	rl_clear_history();
	ft_handle_malloc(0, NULL, 0, NULL);
	ft_close_std();
	// ft_close_fd(data);//close fd autres???
	return (res);
}


// voir si plutôt faire :
// si fd >2
// fermer !?
void	ft_close_fd(t_data *data)
{
	t_cmd	*cmd;
	t_token	*token;
	int		i;

	cmd = data->cmd;
	token = NULL;
	i = 0;
	if (!data)
		return ;
	if (data->cmd)
	{
		while (cmd)
		{
			token = cmd->tok_redir;
			while (token)
			{
				if (token->fd != -1)
					close(token->fd);
				token = token->next;
			}
			cmd = cmd->next;
		}
	}
	if (data->pipe_fd)
	{
		while (i < data->nb_pipes)
		{
			if (data->pipe_fd[i][0] != -1)
				close(data->pipe_fd[i][0]);
			if (data->pipe_fd[i][1] != -1)
				close(data->pipe_fd[i][1]);
			i++;
		}
	}
}

int	ft_msg(int val_exit, char *msg1, char *msg2, char *msg3)
{
	char	*tmp;
	char	*tmp2;
	char	*msg;

	tmp = ft_strjoin(msg1, msg2);
	if (!tmp)
		return (1); // FREE QUIT
	tmp2 = ft_strjoin(tmp, msg3);
	if (!tmp2)
		return (1); // FREE QUIT
	free(tmp);
	msg = ft_strjoin(tmp2, "\n");
	if (!msg)
		return (1); // FREE QUIT
	free(tmp2);
	ft_putstr_fd(msg, 2);
	free(msg);
	return (val_exit);
}

// int	ft_free_exit(int val_exit)
// {
// 	//faire un message d'erreur --> selon message d'erreur ??
// 	ft_handle_malloc(val_exit, NULL, NULL, NULL);
// 	exit(val_exit);
// }
