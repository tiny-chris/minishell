/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:11:11 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/20 18:11:50 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_consec_quotes_len4(int *len, char *token, int *i, int *j)
{
	*j = *i;
	(*j) += 2;
	while ((token[*j] && (token[*j] == 34 || token[*j] == 39))
		&& (token[*j + 1] && token[*j + 1] == token[*j]))
		(*j) += 2;
	(*len) -= (*j - *i);
	(*i) = (*j) - 1;
}

static void	ft_consec_quotes_len3(int c, char *token, int *i, int *j)
{
	(*i)++;
	while (token[*i] && token[*i] != c)
		(*i)++;
}

static void	ft_consec_quotes_len2(int *len, char *token, int *i, int *j)
{
	if (*i == 0)
	{
		if (token[*i + 2] != '\0' && token[*i + 2] != ' ')
		{
			(*i) += 2;
			while ((token[*i] && token[*i + 1]) \
				&& (token[*i] == 34 || token[*i] == 39) \
				&& (token[*i + 1] == token[*i]))
				(*i) += 2;
			if (token[*i] == '\0')
			{
				*len = 2;
				return (2);
			}
			else
				*len -= (*i);
		}
		else if (token [*i + 2] == '\0')
			return (2);
	}
	else if ((*i) > 0)
		ft_consec_quotes_len4(&len, token, &i, &j);
}

int	ft_consec_quotes_len(char *token)
{
	int		i;
	int		j;
	int		len;
	char	c;

	i = 0;
	j = 0;
	len = ft_strlen(token);
	while (token[i] != '\0')
	{
		if (token[i] == 34 || token[i] == 39)
		{
			c = token[i];
			if (token[i + 1] != '\0')
			{
				if (token[i + 1] == c)
					ft_consec_quotes_len2(&len, token, &i, &j);
				else
					ft_consec_quotes_len3(c, token, &i, &j);
			}
		}
		i++;
	}
	return (len);
}
