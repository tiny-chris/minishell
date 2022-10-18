/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:32:00 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/19 01:36:38 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | unspace_cmd - CONTENT *****
**	<SUMMARY> Creates the new string to be copied in the t_cmd linked list
**	<RETURNS>	the new string value (char *) without useless spaces
*/
static char	*ft_fill_unspace_btw_q(char *raw, int *i, char *unspace, int *j)
{
	char	c;

	if (raw[*i] == 34 || raw[*i] == 39)
	{
		c = raw[*i];
		unspace[*j] = raw[*i];
		(*i)++;
		(*j)++;
		while (raw[*i] != c)
		{
			unspace[*j] = raw[*i];
			(*i)++;
			(*j)++;
		}
		unspace[*j] = raw[*i];
		(*j)++;
	}
	return (unspace);
}

static char	*ft_fill_unspace_redir(char *raw, int *i, char *unspace, int *j)
{
	char	c;

	if (raw[*i] == '>' || raw[*i] == '<')
	{
		c = raw[*i];
		unspace[*j] = raw[*i];
		(*i)++;
		(*j)++;
		if (raw[*i] == c)
		{
			unspace[*j] = raw[*i];
			(*i)++;
			(*j)++;
		}
		if (raw[*i] == ' ')
		{
			(*i)++;
			while (raw[*i] && raw[*i] == ' ')
				(*i)++;
			(*i)--;
		}
		else
			(*i)--;
	}
	return (unspace);
}

static char	*ft_fill_unspace_else(char *raw, int *i, char *unspace, int *j)
{
	unspace[*j] = raw[*i];
	(*j)++;
	if (raw[*i] == ' ')
	{
		(*i)++;
		while (raw[*i] && raw[*i] == ' ')
			(*i)++;
		(*i)--;
	}
	return (unspace);
}

char	*ft_fill_unspace_cmd(char *raw_cmd, int len)
{
	char	*unspace_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	unspace_cmd = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
			unspace_cmd = ft_fill_unspace_btw_q(raw_cmd, &i, unspace_cmd, &j);
		else if (raw_cmd[i] == '>' || raw_cmd[i] == '<')
			unspace_cmd = ft_fill_unspace_redir(raw_cmd, &i, unspace_cmd, &j);
		else
			unspace_cmd = ft_fill_unspace_else(raw_cmd, &i, unspace_cmd, &j);
		i++;
	}
	unspace_cmd[len] = '\0';
	return (unspace_cmd);
}

/*	***** PARSING | unspace_cmd *****
**	<SUMMARY> Gets an updated cmd with unnecessary spaces (unspace_cmd)
**	<REMARKS>	useless spaces are those outside of closed quotes
**				- when there are consecutive spaces: keep only 1
**				- except if they are just after an unquoted redirection: delete
**					all spaces just after a redir
*/
int	ft_del_spaces(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	cmd = data->cmd;
	while (cmd)
	{
		len = ft_unspace_cmd_len(cmd->raw_cmd, ft_strlen(cmd->raw_cmd));
		cmd->unspace_cmd = ft_fill_unspace_cmd(cmd->raw_cmd, len);
		cmd = cmd->next;
	}
	return (0);
}
