/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:03 by cgaillag          #+#    #+#             */
/*   Updated: 2022/08/24 14:55:03 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	2 étapes
	1. check contenu i+1
		- espaces uniquement
		- quotes fermées directement (simples ou doubles)
		-
	2. check file
*/
int	ft_check_redir(char *line, int i)
{
	int		j;
	char	q;

	j = i;
	if (line[j] && line[j] == ' ')
	{
		while (line[j] && line[j] == ' ')
			j++;
		if ((line[j] == '\0') || (line[j] == '|') || (line[j] == 60) || (line[j] == 62))
			return (-1);
	}
	while (line[j] && (line[j] != '|') && (line[j] != 60) && (line[j] != 62) && (line[j] != ' '))
	{
		if (line[j] == 34 || line[j] == 39)
		{
			q = line[j];
			j++;
			while (line[j] != q)
				j++;
			return (j);
		}
		j++;
	}
	if (j == i)
		return (-1);
	return (j - 1);
}

/*	check 'chevrons'
**	val ASCII redir infile : 60
**	val ASCII redir outfile : 62
*/
int	ft_redir(char *line)
{
	int		i;
	char	q;
	char	c;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i];
			i++;
			while (line[i] != q)
				i++;
		}
		else if (line[i] == 60 || line[i] == 62)
		{
			c = line[i];
			i++;
			if (line[i] == c)
				i++;
			i = ft_check_redir(line, i);
			if (i == -1)
				return (1);
		}
		i++;
	}
	return (0);
}

/*	check if 'quotes englobantes' sont bien fermées
**	val ASCII simple quote : 39
**	val ASCII double quote : 34
*/
int	ft_quote(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
		{
			if (line[i] == 39)
			{
				j = i + 1;
				while (line[j] && line[j] != 39)
					j++;
			}
			else if (line[i] == 34)
			{
				j = i + 1;
				while (line[j] && line[j] != 34)
					j++;
			}
			if (!line[j])
				return (1);
			i = j;
		}
		i++;
	}
	return (0);
}

/* on compte le nombre de pipes hors quotes
*/

int	ft_count_pipe(char *line)
{
	int		count;
	int		i;
	char	c;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
		}
		else if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int	ft_first_pipe(char *line)
{
	int		i;
	char	c;

	i = 0;
	if (line[i] == '|')
		return (1);
	if (line[i] == ' ')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '|')
			return (1);
	}
	if (line[i] == 34 || line[i] == 39)
	{
		c = line[i];
		i++;
		while (line[i] != c)
			i++;
	}
	while (line[i] && line[i] != '|')
		i++;
	return (i);
}

int	ft_pipe(char *line)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = ft_count_pipe(line);
	while (line[i] && count)
	{
		if (i == 0)
			i = ft_first_pipe(line);
		i++;
		if (line[i] == '\0' || line[i] == '|')
			return (1);
		if (line[i] == ' ')
		{
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] == '\0' || line[i] == '|')
				return (1);
		}
		if (line[i] == 34 || line[i] == 39)
		{
			c = line[i];
			i++;
			while (line[i] != c)
				i++;
		}
		while (line[i] && line[i] != '|')
			i++;
		count--;
	}
	return(0);
}

int	ft_lexer(char *line)
{
	if (!line)
		return (0);
	else
	{
		if (ft_quote(line) == 1)
			return (1);
		if (ft_pipe(line) == 1)
			return (2);
		if (ft_redir(line) == 1)
			return (3);
	}
	return (0);
}
