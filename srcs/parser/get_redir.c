/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:17:53 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 16:59:47 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_redir(char *unspace_cmd, int *j)
{
	if (unspace_cmd[*j] == '<')
	{
		(*j)++;
		if (unspace_cmd[*j] && unspace_cmd[*j] == '<')
		{
			(*j)++;
			return (13);
		}
		else
			return (12);
	}
	else if (unspace_cmd[*j] == '>')
	{
		(*j)++;
		if (unspace_cmd[*j] && unspace_cmd[*j] == '>')
		{
			(*j)++;
			return (11);
		}
		else
			return (10);
	}
	return (0);
}

static void	ft_redir_list_type(char *cmd, int *i, int *j)
{
	char	c;

	(*i) = (*j);
	while (cmd[*j] && cmd[*j] != ' ' && cmd[*j] != '>' && cmd[*j] != '<')
	{
		if (cmd[*j] && (cmd[*j] == 34 || cmd[*j] == 39))
		{
			c = cmd[*j];
			(*j)++;
			while (cmd[*j] && cmd[*j] != c)
				(*j)++;
		}
		(*j)++;
	}
}

int	ft_get_redir_lst(char *cmd, t_token **tok_redir, t_data *d, int type)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] && (cmd[i] == 34 || cmd[i] == 39))
			ft_count_btw_quotes(cmd, &i);
		else
		{
			type = ft_is_redir(cmd, &j);
			if (type)
			{
				ft_lstadd_tok(tok_redir, type, ft_substr(cmd, i, (j - i)), d);
				ft_redir_list_type(cmd, &i, &j);
				ft_lstadd_tok(tok_redir, type + 10, \
					ft_substr(cmd, i, (j - i)), d);
				i = j - 1;
			}
		}
		i++;
		j = i;
	}
	return (0);
}

/*	***** PARSING | no_redir_cmd *****
**	<SUMMARY>
**	1. Gets an updated cmd without unquoted redirections
**	2. Creates a redir linked list with corresponding file (or here doc)
**	<RETURNS>	t_cmd 'cmd' linked list --> with an additional string
*/
int	ft_get_redir(t_data *data)
{
	t_cmd	*cmd;
	char	*trim_cmd;
	int		len;
	int		type;

	cmd = data->cmd;
	trim_cmd = NULL;
	len = 0;
	type = 0;
	while (cmd)
	{
		len = ft_len_no_redir(cmd->unspace_cmd);
		trim_cmd = ft_fill_no_redir(cmd->unspace_cmd, len);
		cmd->no_redir_cmd = ft_strtrim(trim_cmd, " ");
		ft_handle_malloc(ADD_M + TAB_STR1, cmd->no_redir_cmd, 0, NULL);
		ft_handle_malloc(DELONE, trim_cmd, 0, NULL);
		trim_cmd = NULL;
		ft_get_redir_lst(cmd->unspace_cmd, &cmd->tok_redir, data, type);
		ft_clean_redir(cmd, data);
		cmd = cmd->next;
	}
	return (0);
}
