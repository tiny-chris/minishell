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

// static void	ft_csq_quotes_uncopy(t_token *t, int *i)
// {
// 	if (*i >= 0)
// 	{
// 		(*i) += 2;
// 		while (t->token[*i] && (t->token[*i] == 34 || t->token[*i] == 39) \
// 			&& (t->token[(*i) + 1] && t->token[(*i) + 1] == t->token[*i]))
// 			(*i) += 2;
// 	}
// }

// static char	*ft_csq_quotes_start(t_token *t, int *i, char *t_unquote, int *j)
// {
// 	char	c;

// 	c = t->token[*i];
// 	*i += 2;
// 	while (t->token[*i] && (t->token[*i] == 34 || t->token[*i] == 39) \
// 		&& (t->token[(*i) + 1] && t->token[(*i) + 1] == t->token[*i]))
// 		(*i) += 2;
// 	if (t->token[*i] == '\0')
// 	{
// 		t_unquote[*j] = c;
// 		j++;
// 		t_unquote[*j] = c;
// 		j++;
// 		t_unquote[*j] = '\0';
// 		ft_handle_malloc(DELONE, t->token, 0, NULL);
// 		t->token = NULL;
// 	}
// 	return (t_unquote);
// }

// static char	*ft_csq_quotes_redir2(t_token *t, char *unquote, t_int *v)
// {
// 	char	c;

// 	if (t->token[v->i] == 34 || t->token[v->i] == 39)
// 	{
// 		c = t->token[v->i];
// 		if (t->token[(v->i) + 1] == c)
// 		{
// 			if (v->i == 0)
// 			{
// 				unquote = ft_csq_quotes_start(t, &(v->i), unquote, &(v->j));
// 				if (t->token == NULL)
// 					return (unquote);
// 				(v->i)--;
// 			}
// 			else if (v->i > 0)
// 			{
// 				ft_csq_quotes_uncopy(t, &(v->i));
// 				(v->i)--;
// 			}		
// 		}
// 		else
// 			unquote = ft_fill_btw_quotes(t->token, &(v->i), unquote, &(v->i));
// 	}
// 	return (unquote);
// }

// int	ft_fill_consec_quotes_redir(t_token *token, int len)
// {
// 	char	*tok_unquote;
// 	t_int	var;

// 	var.i = 0;
// 	var.j = 0;
// 	tok_unquote = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
// 	while (token->token[var.i])
// 	{
// 		if (token->token[var.i] == 34 || token->token[var.i] == 39)
// 		{
// 			tok_unquote = ft_csq_quotes_redir2(token, tok_unquote, &var);
// 			if (token->token == NULL)
// 				break ;
// 		}
// 		else
// 		{
// 			tok_unquote[var.j] = token->token[var.i];
// 			(var.j)++;
// 		}
// 		(var.i)++;
// 	}
// 	tok_unquote[len] = '\0';
// 	ft_handle_malloc(DELONE, token->token, 0, NULL);
// 	token->token = tok_unquote;
// 	return (0);
// }
