/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 15:17:38 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_fill_exp_redir3(char *t_expand, int *j, t_data * data)
{
	int	k;

	k = 0;
	while (data->str_exit[k])
	{
		t_expand[*j] = data->str_exit[k];
		(*j)++;
		k++;
	}
	return (t_expand);
}

static char	*ft_fill_exp_redir2(t_token *tok, int *i, char *t_expand, t_data *d)
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
				t_expand = ft_fill_exp_redir3(t_expand, &j, d);
				(*i)++;
			}
			else
				ft_fill_expand(tok->token, &i, t_expand, &j);
		}
		else
		{
			t_expand[*j] = tok->token[*i];
			(*i)++;
			(*j)++;
		}
	}
	return (tok_exp);
}

int	ft_fill_expand_redir(t_token *token, int len, t_data *data)
{
	char	*tok_expand;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tok_expand = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	tok_expand = ft_fill_exp_redir2(token, &i, tok_expand, data);
	tok_expand[len] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = tok_expand;
	return (0);
}

// int	ft_fill_expand_redir(t_token *token, int len, t_data *data)
// {
// 	char	*tok_expand;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	tok_expand = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
// 	// tok_expand = malloc(sizeof(char) * (len + 1));
// 	// if (!tok_expand)
// 	// 	return (1);// FREE TOUT ET EXIT !!
// 	while (token->token[i])
// 	{
// 		if (token->token[i] == '$')
// 		{
// 			i++;
// 			if (token->token[i] == '?')
// 			{
// 				while (data->str_exit[k])
// 				{
// 					tok_expand[j] = data->str_exit[k];
// 					j++;
// 					k++;
// 				}
// 				i++;
// 				k = 0;
// 			}
// 			else
// 				ft_fill_expand(token->token, &i, tok_expand, &j, data);
// 		}
// 		else
// 		{
// 			tok_expand[j] = token->token[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	tok_expand[j] = '\0';
// 	ft_handle_malloc(DELONE, token->token, 0, NULL);
// 	// free(token->token);
// 	token->token = tok_expand;
// 	return (0);
// }
