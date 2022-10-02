/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:27:44 by clem              #+#    #+#             */
/*   Updated: 2022/07/13 09:53:59 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd_error(t_data *data, t_dlist *cmd, int error)
{
	extern int	g_sig_status;

	g_sig_status = error;
	if (((t_cmd *)cmd->content)->cmd)
	{
		ft_putstr_fd(((t_cmd *)cmd->content)->cmd[0], 2);
		if (error == 127)
			ft_putendl_fd(": command not found", 2);
		else if (error == 126)
		{
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
	}
	ft_exitmsg(data, "");
}

void	ft_file_error(t_data *data, char *file, int error)
{
	extern int	g_sig_status;

	(void)data;
	if (error == 2 || error == 13)
		g_sig_status = 1;
	ft_putstr_fd("minishell: ", 2);
	if (file)
		ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(error), 2);
}

void	ft_perror(t_data *data, t_dlist *cmd, int error)
{
	if (error == 127 || error == 126)
	{
		ft_cmd_error(data, cmd, error);
	}
	else if (error == 2)
		ft_putstr_fd("minishell: syntax error\n", 2);
	else if (errno)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		ft_putendl_fd("error: Something went wrong", 2);
	ft_exitmsg(data, "");
}
