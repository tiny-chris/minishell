/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:53:43 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/16 14:13:30 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_echo(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	char	*tmp;

	(void)data;
	token = cmd->token;
	token = token->next;
	if (token)
	{
		if (token->type != WORD_N)
		{
			if (token->type == SP_QUOTES)
			{
				free(token->token);
				token->token = ft_strdup("\n");
			}
			else
			{
				tmp = ft_strdup(token->token);
				if (!tmp)
					return (NULL); // FREEE + EXIT
				free(token->token);
				token->token = ft_strjoin(tmp, "\n");
				free(tmp);
			}
			return (token->token);
		}
		if (token->next)
		{
			if (token->next->type == SP_QUOTES)
			{
				free(token->next->token);
				token->next->token = ft_strdup("");
			}
			return (token->next->token);
		}
	}
	return ("");
}
