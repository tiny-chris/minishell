/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:55:17 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/21 15:16:51 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unquote_heredoc_len(char *token)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = ft_strlen(token);
	while (token[i])
	{
		if (token[i] == 34 || token[i] == 39)
		{
			c = token[i];
			i++;
			while (token[i] && token[i] != c)
				i++;
			len -= 2;
		}
		i++;
	}
	return (len);
}

void	ft_fill_unquote_hd2(t_token *token, char *unquote_token, int *i, int *j)
{
	char	c;

	c = token->token[*i];
	(*i)++;
	while (token->token[*i] && token->token[*i] != c)
	{
		unquote_token[*j] = token->token[*i];
		(*j)++;
		(*i)++;
	}
}

int	ft_fill_unquote_heredoc(t_token *token, int len)
{
	char	*unquote_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	unquote_token = ft_handle_malloc(MALLOC_M + TAB_STR1, \
		NULL, (len + 1), NULL);
	while (token->token[i])
	{
		if (token->token[i] == 34 || token->token[i] == 39)
			ft_fill_unquote_hd2(token, unquote_token, &i, &j);
		else
		{
				unquote_token[j] = token->token[i];
				j++;
		}
		i++;
	}
	unquote_token[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = unquote_token;
	return (0);
}

int	ft_clean_heredoc(t_token *token)
{
	int	len;

	len = ft_undoll_heredoc_len(token->token);
	ft_fill_undoll_heredoc(token, len);
	len = ft_unquote_heredoc_len(token->token);
	if ((size_t)len != ft_strlen(token->token))
		token->hd_quotes = 1;
	ft_fill_unquote_heredoc(token, len);
	return (0);
}
