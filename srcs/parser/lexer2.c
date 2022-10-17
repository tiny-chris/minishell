/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:03 by cgaillag          #+#    #+#             */
/*   Updated: 2022/08/24 14:55:03 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* <SUMMARY> checks the first pipe (if any)
*/
int	ft_first_pipe(char *line)
{
	int		i;

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
	i = ft_btw_quotes(line, i);
	while (line[i] && line[i] != '|')
		i++;
	return (i);
}

/* <SUMMARY> checks if no arguments before or after a pipe
*/
int	ft_pipe(char *line, int count)
{
	int		i;

	i = 0;
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
		i = ft_btw_quotes(line, i);
		while (line[i] && line[i] != '|')
			i++;
		count--;
	}
	return (0);
}
