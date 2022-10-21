/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:35:41 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 12:12:34 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_wordn(t_token *tmp_token)
{
	tmp_token->type = WORD_N;
	ft_handle_malloc(DELONE, tmp_token->token, 0, NULL);
	tmp_token->token = ft_strdup("-n");
	ft_handle_malloc(ADD_M + TAB_STR1, tmp_token->token, 0, NULL);
}

t_token	*ft_get_token_echo(t_token **token)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_token = *token;
	tmp_token = tmp_token->next;
	while (tmp_token)
	{
		if (tmp_token->token[i] == '-')
			i++;
		else
			return (tmp_token);
		if (tmp_token->token[i] != 'n')
			return (tmp_token);
		while (tmp_token->token[i] && tmp_token->token[i] == 'n')
			i++;
		if (tmp_token->token[i] == '\0')
			ft_add_wordn(tmp_token);
		else
			return (tmp_token);
		tmp_token = tmp_token->next;
		i = 0;
	}
	return (NULL);
}

static void	ft_join_words(t_token *tmp, t_token *token)
{
	char	*char_tmp1;
	char	*char_tmp2;

	char_tmp1 = NULL;
	char_tmp2 = NULL;
	while (tmp && tmp->next)
	{
		char_tmp1 = ft_strjoin(token->token, " ");
		ft_handle_malloc(ADD_M + TAB_STR1, char_tmp1, 0, NULL);
		ft_handle_malloc(DELONE, token->token, 0, NULL);
		char_tmp2 = ft_strjoin(char_tmp1, tmp->next->token);
		ft_handle_malloc(ADD_M + TAB_STR1, char_tmp2, 0, NULL);
		ft_handle_malloc(DELONE, char_tmp1, 0, NULL);
		token->token = ft_strdup(char_tmp2);
		ft_handle_malloc(ADD_M + TAB_STR1, token->token, 0, NULL);
		tmp = tmp->next;
		ft_handle_malloc(DELONE, char_tmp2, 0, NULL);
	}
}

void	ft_echo_join_words_fill(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SP_QUOTES)
		{
			ft_handle_malloc(DELONE, tmp->token, 0, NULL);
			tmp->token = ft_strdup("");
			ft_handle_malloc(ADD_M + TAB_STR1, tmp->token, 0, NULL);
		}
		tmp = tmp->next;
	}
	tmp = token;
	if (tmp->next)
		tmp->type = WORD;
	ft_join_words(tmp, token);
	if (token)
	{
		ft_free_token(&(token->next));
		token->next = NULL;
	}
}
