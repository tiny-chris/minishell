/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_heredoc_dolls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:50:51 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 15:15:10 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_undoll_hd_len_doll(char *token, int *i, int *j, int *len)
{
	*j = 1;
	(*i)++;
	while (token[*i] && token[*i] == '$')
	{
		(*i)++;
		(*j)++;
	}	
	if (token[*i] == 34 || token[*i] == 39)
		if ((*j) % 2 != 0)
			(*len)--;
	(*i)--;
}

int	ft_undoll_heredoc_len(char *token)
{
	int		len;
	int		i;
	int		j;
	char	c;

	i = 0;
	len = (int) ft_strlen(token);
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
			ft_undoll_hd_len_doll(token, &i, &j, &len);
		i++;
	}
	return (len);
}

void	ft_fill_hd_quotes(t_token *token, char *undoll_token, int *i, int *j)
{
	char	c;

	c = token->token[*i];
	undoll_token[*j] = token->token[*i];
	(*i)++;
	(*j)++;
	while (token->token[*i] && token->token[*i] != c)
	{
		undoll_token[*j] = token->token[*i];
		(*i)++;
		(*j)++;
	}
	undoll_token[*j] = token->token[*i];
	(*j)++;
}

void	ft_fill_hd_doll(t_token *token, char *undoll_token, int *i, int *j)
{
	int	k;

	k = 1;
	(*i)++;
	while (token->token[*i] && token->token[*i] == '$')
	{
		(*i)++;
		k++;
	}	
	if (token->token[*i] == 34 || token->token[*i] == 39)
	{
		if (k % 2 != 0)
			k--;
	}
	while (k > 0)
	{
		undoll_token[*j] = '$';
		(*j)++;
		k--;
	}
	(*i)--;
}

int	ft_fill_undoll_heredoc(t_token *token, int len)
{
	char	*undoll_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	undoll_token = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (token->token[i])
	{
		if (token->token[i] == 34 || token->token[i] == 39)
			ft_fill_hd_quotes(token, undoll_token, &i, &j);
		else if (token->token[i] == '$')
			ft_fill_hd_doll(token, undoll_token, &i, &j);
		else
		{
			undoll_token[j] = token->token[i];
			j++;
		}
		i++;
	}
	undoll_token[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = undoll_token;
	return (0);
}
