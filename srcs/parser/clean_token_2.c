/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:57:24 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/20 17:58:01 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_clean_token3(char *tmp_token, char *token, int *i, int *j)
{
	token[*j] = tmp_token[*i];
	(*j)++;
	(*i)++;
	token[*j] = tmp_token[*i];
	(*j)++;
}

static void	ft_fill_clean_token2(char *tmp_token, char *token, int *i, int *j)
{
	char	c;

	if ((tmp_token[*i] == 34 || tmp_token[*i] == 39) && \
			(tmp_token[*i + 1] == tmp_token[*i]))
		ft_fill_clean_token3(tmp_token, token, i, j);
	else if (tmp_token[*i] == 34 || tmp_token[*i] == 39)
	{
		c = tmp_token[*i];
		(*i)++;
		while (tmp_token[*i] && tmp_token[*i] != c)
		{
			token[*j] = tmp_token[*i];
			(*j)++;
			(*i)++;
		}
	}
	else
	{
		token[*j] = tmp_token[*i];
		(*j)++;
	}
}

char	*ft_fill_clean_token(char *tmp_token, int len)
{
	char	*token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (tmp_token[i])
	{
		ft_fill_clean_token2(tmp_token, token, &i, &j);
		i++;
	}
	token[j] = '\0';
	return (token);
}
