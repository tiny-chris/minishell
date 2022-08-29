/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:40:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/08/29 15:44:28 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstdelone_tok(t_token *node)
{
	if (!node)
		return ;
	free(node->token);
	node->token = NULL;
	node->next = NULL;
	free(node);
}

void	ft_free_tok(t_token **tok)
{
	t_token	*tmp;

	if (!*tok)
		return ;
	while (*tok != NULL)
	{
		tmp = (*tok)->next;
		ft_lstdelone_tok(*tok);
		(*tok) = tmp;
	}
	(*tok) = NULL;
}

t_token	*ft_lstlast_tok(t_token *lst)
{
	t_token	*node;

	if (!lst)
		return (0);
	node = lst;
	while (node->next)
		node = node->next;
	return (node);
}

int	ft_lstadd_token(t_token **tok, int type, char *token)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		ft_free_tok(tok);
		return (1);
	}
	new->token = token;
	new->type = type;
	new->next = NULL;
	if (ft_lstlast_tok(*tok) == 0)
	{
		*tok = new;
		return (0);
	}
	last = ft_lstlast_tok(*tok);
	last->next = new;
	return (0);
}

/*
// cf. val enum s_type
*/

int	ft_is_redir(char *clean_cmd, int *i)
{
	if (clean_cmd[*i] == '<')
	{
		(*i)++;
		if (clean_cmd[*i] && clean_cmd[*i] == '<')
		{
			(*i)++;
			return (7);
		}
		else
			return (6);
	}
	else if (clean_cmd[*i] == '>')
	{
		(*i)++;
		if (clean_cmd[*i] && clean_cmd[*i] == '>')
		{
			(*i)++;
			return (5);
		}
		else
			return (4);
	}
	return (0);
}

t_token	*ft_get_token(char *clean_cmd, t_data *data)
{
	t_token	**token;
	int		redir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(clean_cmd[j])
	{
		if (j == 0)
		{
			redir = ft_is_redir(clean_cmd, &i);
			if (redir > 0)
			{
				if (ft_lstadd_token(token, redir, ft_substr(clean_cmd, j, i - j)))
					return (NULL); //free tout ce qu'il y a à free
				j = i;
				if (clean_cmd[j] == ' ')
					j++;
				while (clean_cmd[j] &&)
			}
			if ()
		}
	}
	return (0);
}

int	ft_tokenizer(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		ft_get_token(cmd->clean_cmd, data);
		cmd = cmd->next;
	}
}

