/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dolls_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/28 17:17:54 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | undoll_cmd - CONTENT *****
**	<SUMMARY> Creates the new string to be copied as 'undoll_cmd' in the t_cmd
**	'cmd' linked list
**	<RETURNS>	the new string value (char *) without useless $ & spaces
*/
int	ft_fill_undoll_doll(char *no_redir, int *i, char *undoll, int *j)
{
	if (no_redir[*i] == '$')
	{
		(*i)++;
		while (no_redir[*i] && no_redir[*i] == '$')
			(*i)++;
		if (no_redir[*i] == 39 || no_redir[*i] == 34)
			(*i)--;
		else// if (!ft_isdigit(no_redir[*i]))
		{
			undoll[*j] = '$';
			(*j)++;
			if (no_redir[*i] == '\0')
			{
				undoll[*j] = '\0';
				return (1);
			}
			else if (no_redir[*i] != '\0')
			{
				undoll[*j] = no_redir[*i];
				(*j)++;
			}
		}
	}
	return (0);
}

static void	ft_fill_undoll_space(char *no_redir, int *i, char *undoll, int *j)
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
}

static void	ft_fill_doll_dquotes(char *no_redir, int *i, char *undoll, int *j)
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
	// else if (ft_isdigit(no_redir[*i]) == 0 && no_redir[*i] != 34)
	else if (no_redir[*i] != 34)
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
}

void	ft_fill_undoll_quotes(char *no_redir, int *i, char *undoll, int *j)
{
	char	c;

	c = no_redir[*i];
	undoll[*j] = no_redir[*i];
	(*i)++;
	(*j)++;
	while (no_redir[*i] && no_redir[*i] != c)
	{
		if (no_redir[*i] == '$' && c == 34)
			ft_fill_doll_dquotes(no_redir, i, undoll, j);
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
}

char	*ft_fill_undoll_cmd(char *no_redir, int len, int i, int j)
{
	char	*undoll;

	undoll = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (no_redir[i])
	{
		if (no_redir[i] == 34 || no_redir[i] == 39)
			ft_fill_undoll_quotes(no_redir, &i, undoll, &j);
		else if (no_redir[i] == ' ')
			ft_fill_undoll_space(no_redir, &i, undoll, &j);
		else if (no_redir[i] == '$')
		{
			if (ft_fill_undoll_doll(no_redir, &i, undoll, &j))
				break ;
		}
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
