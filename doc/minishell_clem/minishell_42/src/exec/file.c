/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:38:32 by athirion          #+#    #+#             */
/*   Updated: 2022/07/12 14:48:11 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_2(t_data *data, t_dlist *cmd, t_dlist *temp, int redir_in_ok)
{
	if (((t_redir *)temp->content)->type == DL)
		ft_here_doc(data, cmd, temp, "/tmp/temp_heredoc");
	else if (((t_redir *)temp->content)->type == LS && redir_in_ok)
	{
		((t_cmd *)cmd->content)->fd_in
			= open(((t_redir *)temp->content)->file, O_RDONLY);
		if (((t_cmd *)cmd->content)->fd_in == -1)
		{
			redir_in_ok = 0;
			ft_file_error(data, ((t_redir *)temp->content)->file, errno);
			return (0);
		}
	}
	return (1);
}

int	ft_open_3(t_data *data, t_dlist *cmd, t_dlist *temp, int redir_in_ok)
{
	if ((((t_redir *)temp->content)->type == GT
			|| ((t_redir *)temp->content)->type == DG) && redir_in_ok)
	{
		if (((t_redir *)temp->content)->type == DG)
			((t_cmd *)cmd->content)->fd_out
				= open(((t_redir *)temp->content)->file,
					O_CREAT | O_APPEND | O_RDWR, 0644);
		else if (((t_redir *)temp->content)->type == GT)
			((t_cmd *)cmd->content)->fd_out
				= open(((t_redir *)temp->content)->file,
					O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	if (((t_cmd *)cmd->content)->fd_out == -1)
	{
		ft_file_error(data, ((t_redir *)temp->content)->file, errno);
		return (0);
	}
	return (1);
}

int	ft_open(t_data *data, t_dlist *cmd)
{
	t_dlist	*temp;
	int		redir_in_ok;

	temp = data->redlist;
	redir_in_ok = 1;
	while (temp && (((t_cmd *)cmd->content)->cmdid
			!= ((t_redir *)temp->content)->cmdid))
		temp = temp->next;
	while (temp && (((t_cmd *)cmd->content)->cmdid
			== ((t_redir *)temp->content)->cmdid))
	{
		if (!ft_open_2 (data, cmd, temp, redir_in_ok))
			return (0);
		if (!ft_open_3 (data, cmd, temp, redir_in_ok))
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	ft_close(t_data *data, t_dlist *cmd, int *fd)
{
	if (*fd != -1)
		if (close(*fd) == -1)
			ft_perror(data, cmd, errno);
	*fd = -1;
}
