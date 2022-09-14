/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:11:08 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/14 12:02:26 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
- undoll (diff pour heredoc)
- expand (sauf heredoc)
- quotes
*/

int	ft_fill_undoll_redir(t_token *token, int len)
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
					free(token->token);
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
	free(token->token);
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
	tok_expand = malloc(sizeof(char) * (len + 1));
	if (!tok_expand)
		return (1);// FREE TOUT ET EXIT !!
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
	free(token->token);
	token->token = tok_expand;
	return (0);
}

int	ft_clean_redir(t_cmd *cmd, t_data *data)
{
	t_token	*tok_redir;
	int		len;

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
			dprintf(2, "undoll tok_redir = %s, len = %d vs. strlen = %ld\n", tok_redir->token, len, ft_strlen(tok_redir->token));
			len = ft_expand_cmd_len(tok_redir->token, data);
			ft_fill_expand_redir(tok_redir, len, data);
			dprintf(2, "expand tok_redir = %s, len = %d vs. strlen = %ld\n", tok_redir->token, len, ft_strlen(tok_redir->token));
		}
//		else
//			ft_here_doc(tok_redir);
		tok_redir = tok_redir->next;
	}
	return (0);
}
