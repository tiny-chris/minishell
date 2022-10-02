/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:40:00 by athirion          #+#    #+#             */
/*   Updated: 2022/07/12 14:43:58 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_command_redir_1(t_data *data, t_dlist **cmd, t_dlist **temp)
{
	if (((t_cmd *)(*cmd)->content)->file_in)
		free(((t_cmd *)(*cmd)->content)->file_in);
	((t_cmd *)(*cmd)->content)->file_in
		= ft_w_strdup(data, ((t_tok *)(*temp)->next->content)->tok);
	((t_cmd *)(*cmd)->content)->type_in
		= ((t_tok *)(*temp)->content)->tokid;
	*temp = (*temp)->next->next;
}

void	ft_parse_command_redir_2(t_data *data, t_dlist **cmd, t_dlist **temp)
{
	if (((t_cmd *)(*cmd)->content)->file_in)
		free(((t_cmd *)(*cmd)->content)->file_in);
	((t_cmd *)(*cmd)->content)->file_in
		= ft_w_strdup(data, "/tmp/temp_heredoc");
	((t_cmd *)(*cmd)->content)->stop_word
		= ft_w_strdup(data, ((t_tok *)(*temp)->next->content)->tok);
	((t_cmd *)(*cmd)->content)->type_in
		= ((t_tok *)(*temp)->content)->tokid;
	((t_cmd *)(*cmd)->content)->is_here_doc = 1;
	*temp = (*temp)->next->next;
}

void	ft_parse_command_2(t_data *data, t_dlist **cmd, t_dlist **temp, int *c)
{
	if ((*temp)->next && ft_is_tokid(*temp, LS))
		ft_parse_command_redir_1(data, cmd, temp);
	else if ((*temp)->next && ft_is_tokid(*temp, DL))
		ft_parse_command_redir_2(data, cmd, temp);
	else if ((*temp)->next && (ft_is_tokid(*temp, GT)
			|| ft_is_tokid(*temp, DG)))
	{
		if (((t_cmd *)(*cmd)->content)->file_out)
			free(((t_cmd *)(*cmd)->content)->file_out);
		((t_cmd *)(*cmd)->content)->file_out
			= ft_w_strdup(data, ((t_tok *)(*temp)->next->content)->tok);
		((t_cmd *)(*cmd)->content)->type_out
			= ((t_tok *)(*temp)->content)->tokid;
		*temp = (*temp)->next->next;
	}
	else if (*c == 1)
		*temp = (*temp)->next;
	else if (ft_is_tokid(*temp, WD) && ((t_tok *)(*temp)->content)->tok)
	{
			((t_cmd *)(*cmd)->content)->cmd = ft_arg_cmd(data, cmd, temp);
			((t_cmd *)(*cmd)->content)->prg
			= ft_command(data, ((t_cmd *)(*cmd)->content)->cmd[0]);
			*c = 1;
	}
}

void	ft_parse_command(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*cmd;
	int		c;

	c = 0;
	temp = data->toklist;
	cmd = data->cmdlist;
	while (temp && ft_is_tokid (temp, WS))
		temp = temp->next;
	while (temp)
	{
		while (temp && !ft_is_tokid(temp, PP))
		{
			ft_parse_command_2(data, &cmd, &temp, &c);
			if (temp && ft_is_tokid(temp, PP))
			{
				cmd = cmd->next;
				c = 0;
			}
		}
		if (temp)
			temp = temp->next;
	}
}
