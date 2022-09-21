/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_empty_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:12:15 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/21 17:54:32 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_cmd_lst_size(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	cmd = data->cmd;
	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	ft_del_empty_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*todel;
	t_cmd	*tmp;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->token == NULL)
		{
			if (cmd->next != NULL)
			{
				todel = cmd;
				cmd = cmd->next;
				todel->next = NULL;
				ft_lstdelone_cmd(todel);
				data->cmd = cmd;
			}
			else//pas de cmd->next
			{
				ft_lstdelone_cmd(cmd);
				data->cmd = NULL;
				return (0);
			}
		}
		else if (cmd->token)
		{
			if (cmd->next == NULL)
				return (0);
			else if (cmd->next != NULL && cmd->next->token == NULL)
			{
				if (cmd->next->next != NULL)
				{
					todel = cmd->next;
					tmp = cmd->next->next;
					todel->next = NULL;
					cmd->next = tmp;
					ft_lstdelone_cmd(todel);
					cmd = data->cmd;
					//data->cmd = cmd;
				}
				else
				{
					todel = cmd->next;
					cmd->next = NULL;
					ft_lstdelone_cmd(todel);
					return (0);
				}
			}
			else
				cmd = cmd->next;
		}
	}
	return (0);
}
