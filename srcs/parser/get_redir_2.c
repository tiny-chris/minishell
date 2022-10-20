/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:17:53 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 11:47:39 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_len_no_redir2(char *cmd, int *i, int *len)
{
	char	c;

	while (cmd[*i] && cmd[*i] != ' ' && cmd[*i] != '>' && cmd[*i] != '<')
	{
		if (cmd[*i] && (cmd[*i] == 34 || cmd[*i] == 39))
		{
			c = cmd[*i];
			(*len)--;
			(*i)++;
			while (cmd[*i] && cmd[*i] != c)
			{
				(*len)--;
				(*i)++;
			}
			(*len)--;
		}
		else
			(*len)--;
		(*i)++;
	}
}

/*	***** PARSING | cmd_no_redir - LEN *****
**	<SUMMARY> Defines the length of the new string by removing redirections
**	& corresponding files (or here doc)
**	<RETURNS>	the size of the new string to be copied as 'cmd_no_redir" (int)
*/
int	ft_len_no_redir(char *unspace_cmd)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(unspace_cmd);
	while (unspace_cmd[i])
	{
		if (unspace_cmd[i] == 34 || unspace_cmd[i] == 39)
			ft_count_btw_quotes(unspace_cmd, &i);
		else if (unspace_cmd[i] == '>' || unspace_cmd[i] == '<')
		{
			ft_nb_csq_redir(unspace_cmd, &i, &len);
			ft_len_no_redir2(unspace_cmd, &i, &len);
			if (!unspace_cmd[i] || unspace_cmd[i] == ' ' || \
				unspace_cmd[i] == '>' || unspace_cmd[i] == '<')
				i--;
		}
		i++;
	}
	return (len);
}

static void	ft_fill_del_redir(char *unspace, int *i)
{
	char	c;

	if (unspace[*i] && (unspace[*i] == '>' || unspace[*i] == '<'))
	{
		ft_nb_csq_redir(unspace, i, NULL);
		while (unspace[*i] && unspace[*i] != ' ' && unspace[*i] != '>' \
			&& unspace[*i] != '<')
		{
			if (unspace[*i] && (unspace[*i] == 34 || unspace[*i] == 39))
			{
				c = unspace[*i];
				(*i)++;
				while (unspace[*i] && unspace[*i] != c)
					(*i)++;
			}
			(*i)++;
		}
		if (unspace[*i] || unspace[*i] != ' ' || unspace[*i] != '>' \
			|| unspace[*i] != '<')
			(*i)--;
	}
}

/*	***** PARSING | cmd_no_redir - CONTENT *****
**	<SUMMARY> Creates a new string to be copied in the t_cmd linked list
**	<RETURNS>	the new string value (char *) with no redirection
*/
char	*ft_fill_no_redir(char *unspace, int len)
{
	char	*no_redir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	no_redir = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (unspace[i])
	{
		if (unspace[i] == 34 || unspace[i] == 39)
			no_redir = ft_fill_btw_quotes(unspace, &i, no_redir, &j);
		else if (unspace[i] == '>' || unspace[i] == '<')
			ft_fill_del_redir(unspace, &i);
		else
		{
			no_redir[j] = unspace[i];
			j++;
		}
		i++;
	}
	no_redir[len] = '\0';
	return (no_redir);
}
