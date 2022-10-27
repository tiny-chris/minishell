/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/27 16:05:00 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_cd(t_token *token, t_cmd *cmd, t_data *data, int flag)
{
	DIR		*directory;
	int		res;

	directory = NULL;
	if (access(token->token, F_OK))
	{
		if (errno == 116)
			data->cwd_err = 1;
		return (ft_msg(1, token->token, ": ", strerror(errno)));
	}
	directory = opendir(token->token);
	if (directory == NULL)
		return (ft_msg(1, token->token, ": ", ERRNDR));
	closedir(directory);
	res = chdir(token->token);
	if (res != 0)
		return (ft_msg(1, token->token, ": ", strerror(errno)));
	if (ft_update_pwd(cmd, data, flag))
		return (1);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;
	int		res;

	token = cmd->token;
	token = token->next;
	if (token == NULL)
	{
		ft_get_home(data, flag);
		if (data->home == NULL)
			return (ft_msg(1, cmd->token->token, ": ", ERRHOM));
		else if (data->home[0] == '\0')
			return (0);
		res = chdir(data->home);
		if (res == -1)
			return (ft_msg(errno, data->home, ": ", strerror(errno)));
		ft_update_pwd(cmd, data, flag);
		return (0);
	}
	if (token->next)
		return (ft_msg(1, cmd->token->token, ": ", ERRARG));
	if (token->type == SP_QUOTES)
		return (0);
	return (ft_exec_cd(token, cmd, data, flag));
}
