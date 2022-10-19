/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:33:38 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 21:15:21 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/*	<SUMMARY> Gets full path (absolute path) from a potential relative path by:
	- cleaning ./ & ../
	- using strjoin to gather root part to cmd part
	Next step will be to check it (rigths/access & directory)
*/

static void	ft_get_j(char *token, int *j, int *i)
{
	*j = *i;
	while (token[*j] && token[*j] != '/')
		(*j)++;
}

static void	ft_init_get_fullpath(t_cmd *cmd, t_data *data, int *i, int *j)
{
	if (cmd->cmd_path)
		ft_handle_malloc(DELONE, cmd->cmd_path, 0, NULL);
	cmd->cmd_path = ft_strdup(data->cwd);
	ft_handle_malloc(ADD_C + TAB_STR1, cmd->cmd_path, 0, data);
	*i = 0;
	*j = 0;
}

static void	ft_full2(t_cmd *cmd, t_data *data, int *i, int *j)
{
	int		k;
	char	*token;

	k = *j;
	token = cmd->token->token;
	while (token[k] && token[k] == '/')
		k++;
	ft_update_path(cmd, data, *i, *j);
	*i = k - 1;
}

char	*ft_get_full_path(t_cmd *cmd, t_data *data)
{
	char	*token;
	int		i;
	int		j;

	token = cmd->token->token;
	ft_init_get_fullpath(cmd, data, &i, &j);
	while (token[i])
	{
		if (token[i] && token[i] != '/')
		{
			ft_get_j(token, &j, &i);
			if (token[j] && token[j] == '/')
				ft_full2(cmd, data, &i, &j);
			else
			{
				ft_update_path(cmd, data, i, j - 1);
				break ;
			}
		}
		i++;
	}
	return (cmd->cmd_path);
}
