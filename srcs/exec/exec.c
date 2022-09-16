/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/16 17:53:08 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_child_process(t_data *data, int i)
// {

// }

int	ft_exec(t_data *data)
{
	int	i;

	data->pipe_fd = ft_init_pipe(data);
	data->pid = ft_init_pid(data);
	i = 0;
	while (i < (data->nb_pipes + 1))
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			printf("pid error\n"); // modif var_exit free + exit
		//else if (data->pid[i] == 0)
			//ft_child_process(data, i);
	}
	//data->val_exit = ft_parent_process(data);
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
