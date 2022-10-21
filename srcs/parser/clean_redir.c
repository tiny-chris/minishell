// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   clean_redir.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/09 11:11:08 by cgaillag          #+#    #+#             */
// /*   Updated: 2022/10/20 17:07:25 by cgaillag         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// /*	***** PARSING | undoll_redir - CONTENT *****
// **	<SUMMARY> As for del_dolls for t_cmd cmd --> fills the redir token and
// **	removes $
// **	<RETURNS>	the token->token for redirections
// */

// int	ft_fill_undoll_redir(t_token *token, int len)
// {
// 	char	*undoll;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	undoll = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
// 	while (token->token[i])
// 	{
// 		if (token->token[i] == 34 || token->token[i] == 39)
// 			undoll = ft_fill_undoll_quotes(token->token, &i, undoll, &j);
// 		else if (token->token[i] == '$')
// 			undoll = ft_fill_undoll_doll(token->token, &i, undoll, &j);
// 		else
// 		{
// 			undoll[j] = token->token[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	undoll[j] = '\0';
// 	ft_handle_malloc(DELONE, token->token, 0, NULL);
// 	token->token = undoll;
// 	return (0);
// }

// static char	*ft_fill_clean_redir2(t_token *tok, int *i, char *t_unquote, int *j)
// {
// 	char	c;

// 	c = tok->token[*i];
// 	if (tok->token[(*i) + 1] == c)
// 	{
// 		t_unquote[*j] = tok->token[*i];
// 		(*j)++;
// 		(*i)++;
// 		t_unquote[*j] = tok->token[*i];
// 		(*j)++;
// 	}
// 	else
// 	{
// 		i++;
// 		while (tok->token[*i] && tok->token[*i] != c)
// 		{
// 			t_unquote[*j] = tok->token[*i];
// 			(*j)++;
// 			(*i)++;
// 		}
// 	}
// 	return (t_unquote);
// }

// int	ft_fill_clean_redir(t_token *token, int len)
// {
// 	char	*tok_unquote;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tok_unquote = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
// 	while (token->token[i])
// 	{
// 		if (token->token[i] == 34 || token->token[i] == 39)
// 			tok_unquote = ft_fill_clean_redir2(token, &i, tok_unquote, &j);
// 		else
// 		{
// 			tok_unquote[j] = token->token[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	tok_unquote[j] = '\0';
// 	ft_handle_malloc(DELONE, token->token, 0, NULL);
// 	token->token = tok_unquote;
// 	return (0);
// }

// int	ft_clean_redir(t_cmd *cmd, t_data *data)
// {
// 	t_token	*tok_redir;
// 	int		len;

// 	len = 0;
// 	tok_redir = cmd->tok_redir;
// 	while (tok_redir)
// 	{
// 		if (tok_redir->type != HERE_DOC)
// 		{
// 			len = ft_undoll_cmd_len(tok_redir->token);
// 			ft_fill_undoll_redir(tok_redir, len);
// 			ft_neg_dolls(tok_redir->token);
// 			ft_fill_expand_redir(tok_redir, len, data);
// 			len = ft_consec_quotes_len(tok_redir->token);
// 			ft_fill_consec_quotes_redir(tok_redir, len);
// 			len = ft_clean_len(tok_redir->token);
// 			ft_fill_clean_redir(tok_redir, len);
// 			ft_positive_token(tok_redir);
// 		}
// 		else
// 			ft_clean_heredoc(tok_redir);
// 		tok_redir = tok_redir->next;
// 	}
// 	return (0);
// }


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

/////////////////

void	ft_fill_expand(char *undoll_cmd, int *i, char *clean_cmd, int *j, t_data *data)
{
	t_env	*env;
	char	*var_to_expand;
	int		k;
	int		l;

	env = data->env;
	k = *i;
	l = 0;
	// while (undoll_cmd[k] > 0 && undoll_cmd[k] != '\0' && undoll_cmd[k] != '$' \
	// 	&& undoll_cmd[k] != '<' && undoll_cmd[k] != '>' && undoll_cmd[k] != 34 \
	// 	&& undoll_cmd[k] != 39 && undoll_cmd[k] != ' ' && undoll_cmd[k] != '?')
	while (undoll_cmd[k] && (undoll_cmd[k] > 0) && ft_isalnum(undoll_cmd[k]))
		k++;
	var_to_expand = ft_substr(undoll_cmd, *i, (k - *i));
	ft_handle_malloc(ADD_M + TAB_STR1, var_to_expand, 0, data);
	// if (!var_to_expand)
	// 	return ;// A CHECKER POUR FREE SI PB DE MALLOC - garbage collector
	while (env)
	{
		if ((ft_strlen(var_to_expand) == ft_strlen(env->var)) \
			&& (ft_strncmp(var_to_expand, env->var, (k - *i)) == 0))
		{
			while (env->content[l])
			{
				if (env->content[l] == 34 || env->content[l] == 39)
					clean_cmd[*j] = env->content[l] * (-1);
				else
					clean_cmd[*j] = env->content[l];
				(*j)++;
				l++;
			}
			break ;
		}
		env = env->next;
	}
	ft_handle_malloc(DELONE, var_to_expand, 0, NULL);
	// free(var_to_expand);
	*i = k;
	return ;
}


////////////////

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
