/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:35:31 by clem              #+#    #+#             */
/*   Updated: 2022/07/10 09:35:20 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Return True if the last token is valid.
 */

static int	ft_check_last_tok(t_dlist *toklist)
{
	t_dlist	*temp;

	temp = toklist;
	while (temp->next)
		temp = temp->next;
	if (((t_tok *) temp->content)->tokid != WD
		&& ((t_tok *) temp->content)->tokid != QT
		&& ((t_tok *) temp->content)->tokid != DQ
		&& ((t_tok *) temp->content)->tokid != WS
		&& ((t_tok *) temp->content)->tokid != RV
		&& ((t_tok *) temp->content)->tokid != DO)
		return (0);
	return (1);
}

/*
 ** Turn a QUOTE token into a WORD token.
 */

static void	ft_set_word_token(t_dlist **token)
{
	if (!ft_is_tokid (*token, DO))
		((t_tok *)(*token)->content)->tokid = WD;
	*token = (*token)->next;
}

/*
 ** Changes to WORDS all what is surrounded by QUOTES.
 */

static void	ft_quoted_becomes_words(t_dlist *toklist)
{
	t_dlist	*temp;

	temp = toklist;
	while (temp)
	{
		if (ft_is_tokid (temp, QT))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid (temp, QT))
				ft_set_word_token (&temp);
		}
		if (ft_is_tokid (temp, DQ))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid (temp, DQ))
				ft_set_word_token (&temp);
		}
		temp = temp->next;
	}
}

/*
 ** Return True if all the quotes are pair.
 */

static int	ft_check_quote_pairs(t_dlist *toklist)
{
	t_dlist	*temp;

	temp = toklist;
	while (temp)
	{
		if (ft_is_tokid (temp, QT))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid (temp, QT))
				temp = temp->next;
			if (!temp)
				return (0);
		}
		if (ft_is_tokid (temp, DQ))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid (temp, DQ))
				temp = temp->next;
			if (!temp)
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}

/*
 ** Check that all quotes have a pair, give the WORD token to what is found
 ** between a pair of quotes and check that the last token is valid.
 */

int	ft_parse_quote(t_data *data, t_dlist *toklist)
{
	(void)data;
	if (!ft_check_quote_pairs (toklist))
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		return (0);
	}
	ft_quoted_becomes_words (toklist);
	if (!ft_check_last_tok (toklist))
	{
		ft_putstr_fd
			("minishell: syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	return (1);
}
