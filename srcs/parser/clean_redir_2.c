/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 16:45:42 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_fill_exp_red_val_exit(char *t_expand, int *j, t_data *data)
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

static char	*ft_fill_ex_red(t_token *tok, char *t_expand, t_int *var, t_data *d)
{
	while (tok->token[var->i])
	{
		if (tok->token[var->i] == '$')
		{
			(var->i)++;
			if (tok->token[var->i] == '?')
			{
				t_expand = ft_fill_exp_red_val_exit(t_expand, var->j, d);
				(var->i)++;
			}
			else
				ft_fill_ex2(tok->token, var, t_expand, d);
		}
		else
		{
			t_expand[j] = tok->token[*i];
			(*i)++;
			j++;
		}
	}
	return (t_expand);
}

int	ft_fill_expand_redir(t_token *token, int len, t_data *data)
{
	char	*tok_expand;
	t_int	var;

	var.i = 0;
	var.j = 0;
	tok_expand = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	tok_expand = ft_fill_exp_redir2(token, &var, tok_expand, data);
	tok_expand[len] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = tok_expand;
	return (0);
}
