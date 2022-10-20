/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:32:00 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 11:46:56 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_btw_quotes(char *src, int *i, char *dst, int *j)
{
	char	c;

	if (src[*i] == 34 || src[*i] == 39)
	{
		c = src[*i];
		dst[*j] = c;
		(*i)++;
		(*j)++;
		while (src[*i] && src[*i] != c)
		{
			dst[*j] = src[*i];
			(*i)++;
			(*j)++;
		}
		dst[*j] = c;
		(*j)++;
	}
	return (dst);
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
	if (raw[*i] == ' ')
	{
		unspace[*j] = raw[*i];
		(*j)++;
		(*i)++;
		while (raw[*i] && raw[*i] == ' ')
			(*i)++;
		(*i)--;
	}
	else
	{
		unspace[*j] = raw[*i];
		(*j)++;
	}
	return (unspace);
}

/*	***** PARSING | unspace_cmd - CONTENT *****
**	<SUMMARY> Creates the new string to be copied in the t_cmd linked list
**	<RETURNS>	the new string value (char *) without useless spaces
*/
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
			unspace_cmd = ft_fill_btw_quotes(raw_cmd, &i, unspace_cmd, &j);
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
		len = ft_unspace_cmd_len(cmd->raw_cmd);
		// dprintf(2, "len raw cmd = %d\n", len);//
		cmd->unspace_cmd = ft_fill_unspace_cmd(cmd->raw_cmd, len);
		// dprintf(2, "unspace cmd    = %s --> len = %d vs. strlen = %ld\n", cmd->unspace_cmd, len, ft_strlen(cmd->unspace_cmd));//
		cmd = cmd->next;
	}
	return (0);
}
