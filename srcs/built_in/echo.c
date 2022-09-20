/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:53:43 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/20 17:14:10 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, t_data *data)
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
				if (!token->token)
					return (ft_msg(1, "", "", ERRMAL));
			}
			else
			{
				tmp = ft_strdup(token->token);
				if (!tmp)
					return (ft_msg(1, "", "", ERRMAL)); // FREEE + EXIT
				free(token->token);
				token->token = ft_strjoin(tmp, "\n");
				if (!token->token)
				{
					free(tmp);
					return (ft_msg(1, "", "", ERRMAL));
				}
				free(tmp);
			}
			printf("%s", token->token);
			return (0);
		}
		if (token->next)
		{
			if (token->next->type == SP_QUOTES)
			{
				free(token->next->token);
				token->next->token = ft_strdup("");
				if (!token->next->token)
					return (ft_msg(1, "", "", ERRMAL));
			}
			printf("%s", token->next->token);
			return (0);
		}
	}
	printf("");
	return (0);
}
