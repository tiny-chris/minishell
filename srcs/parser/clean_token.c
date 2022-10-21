/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:22:43 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/21 14:32:11 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_clean_len(char *token)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(token);
	while (token[i])
	{
		if ((token[i] == 34 || token[i] == 39) && (token[i + 1] == token[i]))
			i++;
		else if (token[i] == 34 || token[i] == 39)
		{
			c = token[i];
			i++;
			while (token[i] && token[i] != c)
				i++;
			len -= 2;
		}
		i++;
	}
	return (len);
}

void	ft_positive_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->token[i] != '\0')
	{
		if (token->token[i] < 0)
			token->token[i] = (-1) * token->token[i];
		i++;
	}
}

int	ft_space_quotes(char *tmp_token, t_token *token)
{
	if (ft_strlen(tmp_token) == 2 && (tmp_token[0] == 34 || tmp_token[0] == 39) \
		&& tmp_token[1] == tmp_token[0])
		token->type = SP_QUOTES;
	return (0);
}

int	ft_clean_token(t_cmd *cmd, t_data *data)
{
	t_token		*token;
	char		*tmp_token;
	int			len;

	(void)data;
	token = cmd->token;
	while (token)
	{
		tmp_token = NULL;
		len = ft_consec_quotes_len(token->token);
		tmp_token = ft_fill_consec_quotes(token->token, len);
		ft_handle_malloc(DELONE, token->token, 0, NULL);
		ft_space_quotes(tmp_token, token);
		len = ft_clean_len(tmp_token);
		token->token = ft_fill_clean_token(tmp_token, len);
		ft_handle_malloc(DELONE, tmp_token, 0, NULL);
		ft_positive_token(token);
		token = token->next;
	}
	return (0);
}
