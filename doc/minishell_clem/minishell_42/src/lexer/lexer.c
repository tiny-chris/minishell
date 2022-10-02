/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:30:37 by clem              #+#    #+#             */
/*   Updated: 2022/07/10 09:32:55 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Set the tokenid.
 */

static int	ft_set_token(char *tok)
{
	int	id;

	id = WS * (!ft_strncmp(" ", tok, 1) || (!ft_strncmp("\t", tok, 1)))
		+ PP * (!ft_strncmp("|", tok, 1))
		+ DO * (!ft_strncmp("$", tok, 1) && ft_strncmp("$?", tok, 2))
		+ QT * (!ft_strncmp("\'", tok, 1))
		+ DQ * (!ft_strncmp("\"", tok, 1))
		+ GT * (!ft_strncmp(">", tok, 1) && ft_strncmp(">>", tok, 2))
		+ DG * (!ft_strncmp(">>", tok, 2))
		+ LS * (!ft_strncmp("<", tok, 1) && ft_strncmp("<<", tok, 2))
		+ DL * (!ft_strncmp("<<", tok, 2))
		+ WD * (!ft_strchr("\t \n|\\$\'\"><", *tok))
		+ RV * (!ft_strncmp("$?", tok, 2));
	return (id);
}

/*
 ** Return the str-size of a token.
 */

static size_t	ft_token_size(char *cmdline)
{
	size_t	size;

	size = 0;
	if (ft_strchr("\t \n|$\'\"><", *cmdline))
	{
		if (!ft_strncmp("<<", cmdline, 2) || !ft_strncmp(">>", cmdline, 2)
			|| !ft_strncmp("$?", cmdline, 2))
			return (2);
		else
			return (1);
	}
	else
	{
		while (!ft_strchr("\t \n|$\'\"><", cmdline[size]))
			size ++;
	}
	return (size);
}

/*
 ** Create toklist.
 */

static void	ft_tokenize(t_data *data, char **cmdline, int *pos)
{
	char	*newtok;
	size_t	size;
	int		id;

	size = ft_token_size(*cmdline);
	newtok = ft_w_substr(data, *cmdline, 0, size);
	id = ft_set_token(newtok);
	ft_add_tok(data, id, *pos, newtok);
	*cmdline += size;
	*pos += 1;
}

/*
 **	Lex cmdline (lexical/vocabulary).
 */

void	ft_lexer(t_data *data)
{
	int		pos;
	char	*ptr;

	pos = 0;
	ptr = data->cmdline;
	while (*data->cmdline)
		ft_tokenize(data, &data->cmdline, &pos);
	ft_free(ptr);
}
