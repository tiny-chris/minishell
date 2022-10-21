/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:11:11 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 14:26:53 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_consec_quotes_len4(int *len, char *token, t_int *var)
{
	var->j = var->i;
	(var->j) += 2;
	while ((token[var->j] && (token[var->j] == 34 || token[var->j] == 39))
		&& (token[var->j + 1] && token[var->j + 1] == token[var->j]))
		(var->j) += 2;
	(*len) -= (var->j - var->i);
	(var->i) = (var->j) - 1;
}

static int	ft_consec_quotes_len3(int *len, char *token, t_int *var)
{
	if ((var->i) == 0)
	{
		if (token[var->i + 2] != '\0' && token[var->i + 2] != ' ')
		{
			(var->i) += 2;
			while ((token[var->i] && token[var->i + 1]) \
				&& (token[var->i] == 34 || token[var->i] == 39) \
				&& (token[var->i + 1] == token[var->i]))
				(var->i) += 2;
			if (token[var->i] == '\0')
			{
				*len = 2;
				return (2);
			}
			else
				*len -= (var->i);
		}
		else if (token [var->i + 2] == '\0')
			return (2);
	}
	else if ((var->i) > 0)
		ft_consec_quotes_len4(len, token, var);
	return (0);
}

static int	ft_consec_quotes_len2(int *len, int c, char *token, t_int *var)
{
	if (token[var->i + 1] == c)
	{
		if (ft_consec_quotes_len3(len, token, var) == 2)
			return (2);
	}
	else
	{
		(var->i)++;
		while (token[var->i] && token[var->i] != c)
			(var->i)++;
	}
	return (0);
}

int	ft_consec_quotes_len(char *token)
{
	t_int	var;
	int		len;
	char	c;

	var.i = 0;
	var.j = 0;
	len = ft_strlen(token);
	while (token[var.i] != '\0')
	{
		if (token[var.i] == 34 || token[var.i] == 39)
		{
			c = token[var.i];
			if (token[var.i + 1] != '\0')
			{
				if (ft_consec_quotes_len2(&len, c, token, &var) == 2)
					return (2);
			}	
		}
		(var.i)++;
	}
	return (len);
}
