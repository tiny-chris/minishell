/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/21 09:57:15 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_csq_quotes_redir2(t_token *t, int *i, char *unquote, int *j)
{
	char	c;
	int		x;

	c = t->token[*i];
	x = *i;
	if (t->token[(*i) + 1] == c)
	{
		(*i) += 2;
		while (t->token[*i] && (t->token[*i] == 34 || t->token[*i] == 39) \
			&& (t->token[(*i) + 1] && t->token[(*i) + 1] == t->token[*i]))
			(*i) += 2;
		if (x == 0 && t->token[(*i)] == '\0')
		{
			unquote[*j] = c;
			(*j)++;
			unquote[*j] = c;
			(*j)++;
			unquote[*j] = '\0';
			return (1);
		}
		(*i)--;
	}
	else
		ft_fill_btw_quotes(t->token, i, unquote, j);
	return (0);
}

int	ft_fill_consec_quotes_redir(t_token *token, int len)
{
	char	*tok_unquote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tok_unquote = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (token->token[i])
	{
		if (token->token[i] == 34 || token->token[i] == 39)
		{
			if (ft_csq_quotes_redir2(token, &i, tok_unquote, &j))
				break ;
		}
		else
		{
			tok_unquote[j] = token->token[i];
			(j)++;
		}
		(i)++;
	}
	tok_unquote[len] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = tok_unquote;
	return (0);
}
