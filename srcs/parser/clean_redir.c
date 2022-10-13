/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:11:08 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/13 17:46:45 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- undoll + neg doll (diff pour heredoc)
- expand (sauf heredoc)
- quotes + positive doll
*/

int	ft_fill_undoll_redir(t_token *token, int len)
{
	char	*undoll_token;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	undoll_token = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	// undoll_token = malloc(sizeof(char) * (len + 1));
	// if (!undoll_token)
	// 	return (1);// FREE TOUT CE QU IL Y A A FREE
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
				if (token->token[i] == '$' && c == 34)
				{
					i++;
					while (token->token[i] != c && token->token[i] == '$')
						i++;
					if (token->token[i] == '?')
					{
						undoll_token[j] = '$';
						j++;
						undoll_token[j] = token->token[i];
						j++;
					}
					else if (ft_isdigit(token->token[i]) == 0 && token->token[i] != c)
					{
						undoll_token[j] = '$';
						j++;
						undoll_token[j] = token->token[i];
						j++;
					}
					else if (token->token[i] == c)
					{
						undoll_token[j] = '$';
						j++;
						i--;
					}
				}
				else
				{
					undoll_token[j] = token->token[i];
					j++;
				}
				i++;
			}
			if (token->token[i] == c)
			{
				undoll_token[j] = c;
				j++;
			}
		}
		else if (token->token[i] == '$')
		{
			i++;
			while (token->token[i] && token->token[i] == '$')
				i++;
			if (token->token[i] == 39 || token->token[i] == 34)
				i--;//on enlève le dernier $
			else if (!ft_isdigit(token->token[i]))
			{
				undoll_token[j] = '$';
				j++;
				if (token->token[i] == '\0')
				{
					undoll_token[j] = '\0';
					ft_handle_malloc(DELONE, token->token, 0, NULL);
					// free(token->token);
					token->token = undoll_token;
					return (0);
				}
				else if (token->token[i] != '\0')
				{
					undoll_token[j] = token->token[i];
					j++;
				}
			}
		}
		else
		{
			undoll_token[j] = token->token[i];
			j++;
		}
		i++;
	}
	undoll_token[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	// free(token->token);
	token->token = undoll_token;
	return (0);
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
	// tok_expand = malloc(sizeof(char) * (len + 1));
	// if (!tok_expand)
	// 	return (1);// FREE TOUT ET EXIT !!
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
	// free(token->token);
	token->token = tok_expand;
	return (0);
}

int	ft_fill_consec_quotes_redir(t_token *token, int len)
{
	char	*tok_unquote;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	tok_unquote = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	// tok_unquote = malloc(sizeof(char) * (len + 1));
	// if (!tok_unquote)
	// 	return (1); // FREE TOUTTTT + EXIT OF COURSE
	while (token->token[i])
	{
		if (token->token[i] == 34 || token->token[i] == 39)
		{
			c = token->token[i];
			if (token->token[i + 1] == c)
			{
				if (i == 0)
				{
					i += 2;
					while (token->token[i] && (token->token[i] == 34 || token->token[i] == 39)
					&& (token->token[i + 1] && token->token[i + 1] == token->token[i]))
						i += 2;
					if (token->token[i] == '\0')
					{
						tok_unquote[j] = c;
						j++;
						tok_unquote[j] = c;
						j++;
						tok_unquote[j] = '\0';
						ft_handle_malloc(DELONE, token->token, 0, NULL);
						// free (token->token);
						token->token = tok_unquote;
						return (0);
					}
					i--;
				}
				else if (i > 0)
				{
					i += 2;
					while (token->token[i] && (token->token[i] == 34 || token->token[i] == 39)
						&& (token->token[i + 1] && token->token[i + 1] == token->token[i]))
						i += 2;
					i--;
				}
			}
			else
			{
				tok_unquote[j] = c;
				j++;
				i++;
				while (token->token[i] && token->token[i] != c)
				{
					tok_unquote[j] = token->token[i];
					i++;
					j++;
				}
				tok_unquote[j] = c;
				j++;
			}
		}
		else
		{
			tok_unquote[j] = token->token[i];
			j++;
		}
		i++;
	}
	tok_unquote[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	// free (token->token);
	token->token = tok_unquote;
	return (0);
}

int	ft_fill_clean_redir(t_token *token, int len)
{
	char	*tok_unquote;
	char 	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tok_unquote = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	// tok_unquote = malloc(sizeof(char) * (len + 1));
	// if (!tok_unquote)
	// 	return (1);// FREE TOUT ET EXIT
	while (token->token[i])
	{
		if ((token->token[i] == 34 || token->token[i] == 39) && (token->token[i + 1] == token->token[i]))
		{
			tok_unquote[j] = token->token[i];
			j++;
			i++;
			tok_unquote[j] = token->token[i];
			j++;
		}
		else if (token->token[i] == 34 || token->token[i] == 39)
		{
			c = token->token[i];
			i++;
			while (token->token[i] && token->token[i] != c)
			{
				tok_unquote[j] = token->token[i];
				j++;
				i++;
			}
		}
		else
		{
			tok_unquote[j] = token->token[i];
			j++;
		}
		i++;
	}
	tok_unquote[j] = '\0';
	ft_handle_malloc(DELONE, token->token, 0, NULL);
	// free(token->token);
	token->token = tok_unquote;
	return (0);
}

int	ft_clean_redir(t_cmd *cmd, t_data *data)
{
	t_token	*tok_redir;
	int		len;
	int		nb = 0;//A SUPPRIMER - juste pour impression

	(void) data;//TO DELETE
	len = 0;
	tok_redir = cmd->tok_redir;
	while (tok_redir)
	{
		if (tok_redir->type != HERE_DOC)
		{
			len = ft_undoll_cmd_len(tok_redir->token);
			ft_fill_undoll_redir(tok_redir, len);
			ft_neg_dolls(tok_redir->token);
			//dprintf(2, "undoll tok_redir[%d]   = %s, len = %d vs. strlen = %ld\n", nb, tok_redir->token, len, ft_strlen(tok_redir->token));
			len = ft_expand_cmd_len(tok_redir->token, data);
			ft_fill_expand_redir(tok_redir, len, data);
			//dprintf(2, "expand tok_redir[%d]   = %s, len = %d vs. strlen = %ld\n", nb, tok_redir->token, len, ft_strlen(tok_redir->token));
			len = ft_consec_quotes_len(tok_redir->token);
			ft_fill_consec_quotes_redir(tok_redir, len);
			//dprintf(2, "unquote1 tok_redir[%d] = %s, len = %d vs. strlen = %ld\n", nb, tok_redir->token, len, ft_strlen(tok_redir->token));
			len = ft_clean_len(tok_redir->token);
			ft_fill_clean_redir(tok_redir, len);
			//dprintf(2, "unquote2 tok_redir[%d] = %s, len = %d vs. strlen = %ld\n", nb, tok_redir->token, len, ft_strlen(tok_redir->token));
			ft_positive_token(tok_redir);
			// dprintf(2, "clean tok_redir[%d]    = %s, len = %d vs. strlen = %ld\n", nb, tok_redir->token, len, ft_strlen(tok_redir->token));
		}
		else
			ft_clean_heredoc(tok_redir);
		tok_redir = tok_redir->next;
		nb++;//A SUPPRIMER - juste pour impression

	}
	return (0);
}
