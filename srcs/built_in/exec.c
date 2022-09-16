/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:04 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/16 14:13:30 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->token->type == BUILTIN && (ft_strncmp(cmd->token->token, "echo", 4) == 0))
			printf("%s", ft_echo(cmd, data));
		cmd = cmd->next;
	}
	return (0);
}
