/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:35:41 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 14:30:57 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* adding a /tmp/tmp_heredoc[cmd id] for each command in case of a heredoc */

int	ft_heredoc_path(t_data *data)
{
	t_cmd	*cmd;
	int		i;
	char	*tmp;

	cmd = data->cmd;
	i = 0;
	while (cmd)
	{
		tmp = ft_itoa(i);
		ft_handle_malloc(ADD_M + TAB_STR1, tmp, 0, NULL);
		cmd->heredoc_path = ft_strjoin("/tmp/tmp_heredoc", tmp);
		ft_handle_malloc(ADD_M + TAB_STR1, cmd->heredoc_path, 0, NULL);
		ft_handle_malloc(DELONE, tmp, 0, NULL);
		cmd = cmd->next;
		i++;
	}
	return (0);
}
