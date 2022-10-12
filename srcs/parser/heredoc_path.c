/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:35:41 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/12 16:01:54 by lmelard          ###   ########.fr       */
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
		if (!tmp)
			exit(EXIT_FAILURE); //free (error malloc)
		cmd->heredoc_path = ft_strjoin("/tmp/tmp_heredoc", tmp);
		printf("cmd->heredoc_path = %s\n", cmd->heredoc_path);
		if (!cmd->heredoc_path)
			exit(EXIT_FAILURE); //free (error malloc)
		free(tmp);
		tmp = NULL;
		cmd = cmd->next;
		i++;
	}
	return (0);
}
