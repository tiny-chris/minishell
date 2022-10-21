/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:11:08 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 17:07:25 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | undoll_redir - CONTENT *****
**	<SUMMARY> As for del_dolls for t_cmd cmd --> fills the redir token and
**	removes $
**	<RETURNS>	the token->token for redirections
*/

static void	ft_copy_val(char *token, int *i, char *undoll, int *j)
{
	undoll[*j] = token[*i];
	(*j)++;
}

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
			ft_fill_undoll_quotes(token->token, &i, undoll, &j);
		else if (token->token[i] == '$')
		{
			if (ft_fill_undoll_doll(token->token, &i, undoll, &j))
				break ;
		}
		else
			ft_copy_val(token->token, &i, undoll, &j);
		i++;
	}
	undoll[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = undoll;
	return (0);
}

static void	ft_fill_clean_redir2(t_token *tok, int *i, char *t_unquote, int *j)
{
	char	c;

	c = tok->token[*i];
	if (tok->token[(*i) + 1] == c)
	{
		t_unquote[*j] = tok->token[*i];
		(*j)++;
		(*i)++;
		t_unquote[*j] = tok->token[*i];
		(*j)++;
	}
	else
	{
		(*i)++;
		while (tok->token[*i] && tok->token[*i] != c)
		{
			t_unquote[*j] = tok->token[*i];
			(*j)++;
			(*i)++;
		}
	}
}

int	ft_fill_clean_redir(t_token *token, int len)
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
			ft_fill_clean_redir2(token, &i, tok_unquote, &j);
		else
		{
			tok_unquote[j] = token->token[i];
			j++;
		}
		i++;
	}
	tok_unquote[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	token->token = tok_unquote;
	return (0);
}

int	ft_clean_redir(t_cmd *cmd, t_data *data)
{
	t_token	*tok_redir;
	int		len;

	len = 0;
	tok_redir = cmd->tok_redir;
	while (tok_redir)
	{
		if (tok_redir->type != HERE_DOC)
		{
			len = ft_undoll_cmd_len(tok_redir->token);
			ft_fill_undoll_redir(tok_redir, len);
			ft_neg_dolls(tok_redir->token);
			len = ft_expand_cmd_len(tok_redir->token, data);
			ft_fill_expand_redir(tok_redir, len, data);
			len = ft_consec_quotes_len(tok_redir->token);
			ft_fill_consec_quotes_redir(tok_redir, len);
			len = ft_clean_len(tok_redir->token);
			ft_fill_clean_redir(tok_redir, len);
			ft_positive_token(tok_redir);
		}
		else
			ft_clean_heredoc(tok_redir);
		tok_redir = tok_redir->next;
	}
	return (0);
}
