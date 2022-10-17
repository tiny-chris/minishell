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

#include "minishell.h"


static int	ft_btw_quotes(char *line, int i)
{
	int		j;
	char	c;

	j = i;
	if (line[j] == 34 || line[j] == 39)
	{
		c = line[j];
		j++;
		while (line[j] && line[j] != c)
			j++;
		return (j);
	}
	return (i);
}

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
	// char	q;
	char	c;

	i = 0;
	while (line[i])
	{
		i = ft_btw_quotes(line, i);
		// if (line[i] == 34 || line[i] == 39)
		// {
		// 	q = line[i];
		// 	i++;
		// 	while (line[i] && line[i] != q)
		// 		i++;
		// }
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

/*	<SUMMARY> checks if any open quote has its matching closing quote 
**	ASCII value for a simple quote : 39 and for a doubble quote : 34
*/
int	ft_quote(char *line)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
		{
			c = line[i];
			j = i + 1;
			while (line[j] && line[j] != c)
				j++;
			if (!line[j])
				return (1);
			i = j;
		}
		i++;
	}
	return (0);
}
// int	ft_quote(char *line)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == 39 || line[i] == 34)
// 		{
// 			if (line[i] == 39)
// 			{
// 				j = i + 1;
// 				while (line[j] && line[j] != 39)
// 					j++;
// 			}
// 			else if (line[i] == 34)
// 			{
// 				j = i + 1;
// 				while (line[j] && line[j] != 34)
// 					j++;
// 			}
// 			if (!line[j])
// 				return (1);
// 			i = j;
// 		}
// 		i++;
// 	}
// 	return (0);
// }


/* <SUMMARY> counts the number of pipes out of those between quotes
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
		return (-1);
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

int	ft_pipe(char *line, int count)
{
	int		i;

	i = 0;
	while (line[i] && count)
	{
		if (i == 0)
			if (ft_first_pipe(line) == -1)
				return (1);
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
		i = ft_btw_quotes(line, i);
		while (line[i] && line[i] != '|')
			i++;
		count--;
	}
	return (0);
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
		if (i == -1)
			return (1);
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
			while (line[i] && line[i] != c)
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
	int	count;

	count = 0;
	if (!line)
		return (0);
	else
	{
		if (ft_quote(line) == 1)
			return (1);
		count = ft_count_pipe(line);
		if (ft_pipe(line, count) == 1)
			return (2);
		if (ft_redir(line) == 1)
			return (3);
	}
	return (0);
}
