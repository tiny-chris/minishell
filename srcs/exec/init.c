/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:30:46 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/19 14:13:12 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

char	**ft_init_cmd_opt(t_cmd *cmd, t_data *data)
{
	char	**cmd_opt;
	t_token	*token;
	int		i;

	(void) data;
	token = cmd->token;
	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	cmd_opt = ft_handle_malloc(MALLOC_C + TAB_STR2, NULL, (i + 1), data);
	i = 0;
	token = cmd->token;
	while (token)
	{
		cmd_opt[i] = ft_strdup(token->token);
		ft_handle_malloc(ADD_C + TAB_STR1, cmd_opt[i], 0, data);
		i++;
		token = token->next;
	}
	cmd_opt[i] = NULL;
	return (cmd_opt);
}

int	**ft_init_pipe(t_data *data)
{
	int	**tab_int;
	int	i;

	tab_int = ft_handle_malloc(MALLOC_M + TAB_INT2, NULL, data->nb_pipes, data);
	i = 0;
	while (i < data->nb_pipes)
	{
		tab_int[i] = ft_handle_malloc(MALLOC_M + TAB_INT1, NULL, 2, data);
		tab_int[i][0] = -1;
		tab_int[i][1] = -1;
		i++;
	}
	return (tab_int);
}

int	*ft_init_pid(t_data *data)
{
	int	*pid;
	int	i;

	i = 0;
	pid = ft_handle_malloc(MALLOC_M + TAB_INT1, NULL, \
			(data->nb_pipes + 1), data);
	while (i < (data->nb_pipes + 1))
	{
		pid[i] = -1;
		i++;
	}
	return (pid);
}
