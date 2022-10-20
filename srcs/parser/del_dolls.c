/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dolls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 17:21:23 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_neg_dolls_2(char *cmd, int *i)
{
	if (cmd[*i] == 39)
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != 39)
		{
			if (cmd[*i] == '$')
				cmd[*i] = (-1) * cmd[*i];
			(*i)++;
		}
	}
	else if (cmd[*i] == 34)
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != 34)
		{
			if (cmd[*i] == '$' && (cmd[(*i) + 1] == 34 || cmd[(*i) + 1] == 39 \
				|| cmd[(*i) + 1] == ' ' || cmd[(*i) + 1] == '<' \
				|| cmd[(*i) + 1] == '>'))
				cmd[(*i)] = (-1) * cmd[(*i)];
			(*i)++;
		}
	}
	return (cmd);
}

void	ft_neg_dolls(char *undoll_cmd)
{
	int		i;

	i = 0;
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == 39 || undoll_cmd[i] == 34)
			undoll_cmd = ft_neg_dolls_2(undoll_cmd, &i);
		else if (undoll_cmd[i] == '$')
		{
			if (undoll_cmd[i + 1] == '\0' || undoll_cmd[i + 1] < 0 \
				|| undoll_cmd[i + 1] == 39 || undoll_cmd[i + 1] == ' ' \
				|| undoll_cmd[i + 1] == '<' || undoll_cmd[i + 1] == '>')
				undoll_cmd[i] = (-1) * undoll_cmd[i];
		}
		i++;
	}
}

/*	***** PARSING | undoll_cmd *****
**	<SUMMARY>
**	Gets an updated cmd without useless $ and spaces (undoll_cmd) in 2 steps:
**	1. Defines the length of the new string by removing useless $
**	2. Copies the matching string in 'undoll_cmd' of the t_cmd 'cmd' linked list
**	<REMARKS>	1. useless dollars are those:
**					- when there are consecutive dollars: keep only 1
**					- when the next character is a digit and they are not into
**					simple quotes
**				2. useless spaces consecutive ones outside closed quotes that could
**					appear again because of removed redirections
*/
int	ft_del_dolls(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	len = 0;
	cmd = data->cmd;
	while (cmd)
	{
		len = ft_undoll_cmd_len(cmd->no_redir_cmd);
		cmd->undoll_cmd = ft_fill_undoll_cmd(cmd->no_redir_cmd, len);
		if (!cmd->undoll_cmd)
			return (1);
		ft_neg_dolls(cmd->undoll_cmd);
		cmd = cmd->next;
	}
	return (0);
}
