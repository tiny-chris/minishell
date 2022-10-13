/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:53:43 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/13 16:14:16 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, t_data *data, int flag)
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
				ft_handle_malloc(DELONE, token->token, 0, NULL);
				// free(token->token);
				token->token = ft_strdup("\n");
				ft_handle_malloc(flag + TAB_STR1, token->token, 0, data);
				// if (!token->token)
				// 	return (ft_msg(1, "", "", ERRMAL));
			}
			else
			{
				tmp = ft_strdup(token->token);
				ft_handle_malloc(flag + TAB_STR1, tmp, 0, data);
				// if (!tmp)
				// 	return (ft_msg(1, "", "", ERRMAL)); // FREEE + EXIT
				ft_handle_malloc(DELONE, token->token, 0, NULL);
				// free(token->token);
				token->token = ft_strjoin(tmp, "\n");
				ft_handle_malloc(flag + TAB_STR1, token->token, 0, data);
				// if (!token->token)
				// {
				// 	free(tmp);
				// 	return (ft_msg(1, "", "", ERRMAL));
				// }
				ft_handle_malloc(DELONE, tmp, 0, NULL);
				// free(tmp);
			}
			printf("%s", token->token);
			//ft_putstr_fd(token->token, STDOUT_FILENO);
			return (0);
		}
		if (token->next == NULL)
		// {
			return (write(1, "", 0));
			// printf("");
			// return (0);
		// }
		else//if (token->next)
		{
			if (token->next->type == SP_QUOTES)
			{
				ft_handle_malloc(DELONE, token->next->token, 0, NULL);
				// free(token->next->token);
				token->next->token = ft_strdup("");
				ft_handle_malloc(flag + TAB_STR1, token->next->token, 0, data);
				// if (!token->next->token)
				// 	return (ft_msg(1, "", "", ERRMAL));
			}
			printf("%s", token->next->token);
			//ft_putstr_fd(token->next->token, STDOUT_FILENO);
			return (0);
		}
	}
	printf("\n");
	return (0);
}