/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dolls_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/28 18:09:03 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | undoll_cmd - LEN *****
**	<SUMMARY>
**	Defines the length of the new string (undoll_cmd) by removing useless $ or
**	spaces
**	<PARAM>		{char *} no_redir_cmd --> from get_redir.c
**	<RETURNS>	the size of the new string to be copied unspace_cmd (int)
*/
static void	ft_undoll_len_btw_quotes(char *no_redir_cmd, int *i, int *len)
{
	char	c;

	if (no_redir_cmd[*i] == 34 || no_redir_cmd[*i] == 39)
	{
		c = no_redir_cmd[*i];
		(*i)++;
		while (no_redir_cmd[*i] && no_redir_cmd[*i] != c)
		{
			if (no_redir_cmd[*i] == '$' && c == 34)
			{
				(*i)++;
				while (no_redir_cmd[*i] && no_redir_cmd[*i] == '$')
				{
					(*len)--;
					(*i)++;
				}
				if (no_redir_cmd[*i] == c)
					(*i)--;
			}
			(*i)++;
		}
	}
}

static void	ft_undoll_len_space(char *no_redir_cmd, int *i, int *len)
{
	if (no_redir_cmd[*i] == ' ')
	{
		(*i)++;
		while (no_redir_cmd[*i] && no_redir_cmd[*i] == ' ')
		{
			(*len)--;
			(*i)++;
		}
		if (no_redir_cmd[*i] == '\0')
			(*len)--;
		(*i)--;
	}
}

static void	ft_undoll_len_doll(char *no_redir_cmd, int *i, int *len)
{
	if (no_redir_cmd[*i] == '$')
	{
		(*i)++;
		while (no_redir_cmd[*i] && no_redir_cmd[*i] == '$')
		{
			(*len)--;
			(*i)++;
		}
		if (no_redir_cmd[*i] == 39 || no_redir_cmd[*i] == 34)
			(*len)--;
		else if (no_redir_cmd[*i] && no_redir_cmd[*i] == '?')
			(*i)++;
		(*i)--;
	}
}

int	ft_undoll_cmd_len(char *no_redir_cmd)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(no_redir_cmd);
	while (no_redir_cmd[i])
	{
		if (no_redir_cmd[i] == 34 || no_redir_cmd[i] == 39)
			ft_undoll_len_btw_quotes(no_redir_cmd, &i, &len);
		else if (no_redir_cmd[i] == ' ')
			ft_undoll_len_space(no_redir_cmd, &i, &len);
		else if (no_redir_cmd[i] == '$')
			ft_undoll_len_doll(no_redir_cmd, &i, &len);
		i++;
	}
	return (len);
}
