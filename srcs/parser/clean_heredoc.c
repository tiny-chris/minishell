/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:55:17 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/12 17:46:41 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- pas d'expand
- si quote juste après $ --> on supprime 1$
	$$$'toto'	-->	$$toto
- supprimer les quotes fermantes (toutes ! et on sort du temp file avec "entrer")
*/

int	ft_undoll_heredoc_len(char *token)
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
		}
		else if (token[i] == '$')
		{
			i++;
			while (token[i] && token[i] == '$')
				i++;
			if (token[i] == 34 || token[i] == 39)
				len--;
			i--;
		}
		i++;
	}
	return (len);
}

int	ft_fill_undoll_heredoc(t_token *token, int len)
{
	char	*undoll_token;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	undoll_token = malloc(sizeof(char) * (len + 1));
	if (!undoll_token)
		return (1);// FREE TOUT CE QU IL Y A A FREE
	while (token->token[i])
	{
		if (token->token[i] == 34 || token->token[i] == 39)
		{
			c = token->token[i];
			undoll_token[j] = token->token[i];
			i++;
			j++;
			while (token->token[i] && token->token[i] != c)
			{
				undoll_token[j] = token->token[i];
				i++;
				j++;
			}
			undoll_token[j] = token->token[i];
			j++;
		}
		else if (token->token[i] == '$')
		{
			i++;
			while (token->token[i] && token->token[i] == '$')
			{
				undoll_token[j] = token->token[i];
				i++;
				j++;
			}
			if (token->token[i] != 34 && token->token[i] != 39)
			{
				undoll_token[j] = '$';
				j++;
			}
			i--;
		}
		else
		{
			undoll_token[j] = token->token[i];
			j++;
		}
		i++;
	}
	undoll_token[j] = '\0';
	free(token->token);
	token->token = undoll_token;
	return (0);
}

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

int	ft_fill_unquote_heredoc(t_token *token, int len)
{
	char	*unquote_token;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	unquote_token = malloc(sizeof(char) * (len + 1));
	if (!unquote_token)
		return (1);// FREE TOUT CE QU IL Y A A FREE
	while (token->token[i])
	{
		if (token->token[i] == 34 || token->token[i] == 39)
		{
			c = token->token[i];
			i++;
			while (token->token[i] && token->token[i] != c)
			{
				unquote_token[j] = token->token[i];
				j++;
				i++;
			}
		}
		else
		{
				unquote_token[j] = token->token[i];
				j++;
		}
		i++;
	}
	unquote_token[j] = '\0';
	free(token->token);
	token->token = unquote_token;
	return (0);
}

int	ft_clean_heredoc(t_token *token)
{
	int	len;

	len = ft_undoll_heredoc_len(token->token);
	ft_fill_undoll_heredoc(token, len);
	dprintf(2, "undoll heredoc = %s, len = %d vs. strlen = %ld\n", token->token, len, ft_strlen(token->token));
	len = ft_unquote_heredoc_len(token->token);
	if ((size_t)len != ft_strlen(token->token))
		token->hd_quotes = 1;
	ft_fill_unquote_heredoc(token, len);
	dprintf(2, "unquote heredoc = %s, len = %d vs. strlen = %ld\n", token->token, len, ft_strlen(token->token));
	return (0);
}
