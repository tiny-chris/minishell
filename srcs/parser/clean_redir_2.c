/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 06:53:09 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | undoll_redir - CONTENT *****
**	<SUMMARY> As for del_dolls for t_cmd cmd --> fills the redir token and
**	removes $
**	<RETURNS>	the token->token for redirections
*/
int	ft_fill_undoll_redir(t_token *token, int len)
{
	char	*undoll;
	int		i;
	int		j;

	i = 0;
	j = 0;
	undoll = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (token->token[i])
	{
		if (token->token[i] == 34 || token->token[i] == 39)
			undoll = ft_fill_undoll_quotes(token->token, &i, undoll, &j);
		else if (token->token[i] == '$')
			undoll = ft_fill_undoll_doll(token->token, &i, undoll, &j);
		else
		{
			undoll[j] = token->token[i];
			j++;
		}
		i++;
	}
	undoll[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = undoll;
	return (0);
}

static char	*ft_fill_exp_redir3(char*tok_exp, int *i, int *j, t_data * data)
{
	int	k;

	k = 0;
	while (data->str_exit[k])
	{
		tok_exp[*j] = data->str_exit[k];
		(*j)++;
		k++;
	}
}

static char	*ft_fill_exp_redir2(t_token *tok, int *i, char*tok_exp, t_data *d)
{
	int *j;

	*j = 0;
	while (tok->token[*i])
	{
		if (tok->token[*i] == '$')
		{
			(*i)++;
			if (tok->token[*i] == '?')
			{
				tok->token = ft_fill_exp_redir3(tok_exp, &i, &j, d);
				(*i)++;
			}
			else
				ft_fill_expand(tok->token, &i, tok_exp, &j, d);
		}
		else
		{
			tok_exp[*j] = tok->token[*i];
			(*i)++;
			(*j)++;
		}
	}
}

int	ft_fill_expand_redir(t_token *token, int len, t_data *data)
{
	char	*tok_expand;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tok_expand = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (token->token[i])
	{
		if (token->token[i] == '$')
		{
			i++;
			if (token->token[i] == '?')
			{
				while (data->str_exit[k])
				{
					tok_expand[j] = data->str_exit[k];
					j++;
					k++;
				}
				i++;
				k = 0;
			}
			else
				ft_fill_expand(token->token, &i, tok_expand, &j, data);
		}
		else
		{
			tok_expand[j] = token->token[i];
			i++;
			j++;
		}
	}
	tok_expand[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = tok_expand;
	return (0);
}

