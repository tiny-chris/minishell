/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dolls_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 06:18:45 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | undoll_cmd - CONTENT *****
**	<SUMMARY> Creates the new string to be copied as 'undoll_cmd' in the t_cmd
**	'cmd' linked list
**	<RETURNS>	the new string value (char *) without useless $ & spaces
*/
char	*ft_fill_undoll_doll(char *no_redir, int *i, char *undoll, int *j)
{
	if (no_redir[*i] == '$')
	{
		(*i)++;
		while (no_redir[*i] && no_redir[*i] == '$')
			(*i)++;
		if (no_redir[*i] == 39 || no_redir[*i] == 34)
			(*i)--;
		else if (!ft_isdigit(no_redir[*i]))
		{
			undoll[*j] = '$';
			(*j)++;
			if (no_redir[*i] == '\0')
			{
				undoll[*j] = '\0';
				return (undoll);
			}
			else if (no_redir[*i] != '\0')
			{
				undoll[*j] = no_redir[*i];
				(*j)++;
			}
		}
	}
	return (undoll);
}

static char	*ft_fill_undoll_space(char *no_redir, int *i, char *undoll, int *j)
{
	if (no_redir[*i] == ' ')
	{
		(*i)++;
		while (no_redir[*i] && no_redir[*i] == ' ')
			(*i)++;
		if (no_redir[*i] != '\0')
		{
			undoll[*j] = ' ';
			(*j)++;
		}
		(*i)--;
	}
	return (undoll);
}

static char	*ft_fill_doll_dquotes(char *no_redir, int *i, char *undoll, int *j)
{
	(*i)++;
	while (no_redir[*i] && no_redir[*i] != 34 && no_redir[*i] == '$')
		(*i)++;
	if (no_redir[*i] == '?')
	{
		undoll[*j] = '$';
		(*j)++;
		undoll[*j] = no_redir[*i];
		(*j)++;
	}
	else if (ft_isdigit(no_redir[*i]) == 0 && no_redir[*i] != 34)
	{
		undoll[*j] = '$';
		(*j)++;
		undoll[*j] = no_redir[*i];
		(*j)++;
	}
	else if (no_redir[*i] == 34)
	{
		undoll[*j] = '$';
		(*j)++;
		(*i)--;
	}
	return (undoll);
}

char	*ft_fill_undoll_quotes(char *no_redir, int *i, char *undoll, int *j)
{
	char	c;

	c = no_redir[*i];
	undoll[*j] = no_redir[*i];
	(*i)++;
	(*j)++;
	while (no_redir[*i] && no_redir[*i] != c)
	{
		if (no_redir[*i] == '$' && c == 34)
			undoll = ft_fill_doll_dquotes(no_redir, i, undoll, j);
		else
		{
			undoll[*j] = no_redir[*i];
			(*j)++;
		}
		(*i)++;
	}
	if (no_redir[*i] == c)
	{
		undoll[*j] = c;
		(*j)++;
	}
	return (undoll);
}

char	*ft_fill_undoll_cmd(char *no_redir, int len)
{
	char	*undoll;
	int		i;
	int		j;

	i = 0;
	j = 0;
	undoll = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (no_redir[i])
	{
		if (no_redir[i] == 34 || no_redir[i] == 39)
			undoll = ft_fill_undoll_quotes(no_redir, &i, undoll, &j);
		else if (no_redir[i] == ' ')
			undoll = ft_fill_undoll_space(no_redir, &i, undoll, &j);
		else if (no_redir[i] == '$')
			undoll = ft_fill_undoll_doll(no_redir, &i, undoll, &j);
		else
		{
			undoll[j] = no_redir[i];
			j++;
		}
		i++;
	}
	undoll[j] = '\0';
	return (undoll);
}
