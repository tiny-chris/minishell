/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:53:43 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/07 15:05:13 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_echo(t_cmd *cmd, t_data *data)
// {
// 	t_token	*token;
// 	char	*tmp;

// 	(void)data;
// 	token = cmd->token;
// 	token = token->next;
// 	if (token)
// 	{
// 		if (token->type != WORD_N)
// 		{
// 			if (token->type == SP_QUOTES)
// 			{
// 				free(token->token);
// 				token->token = ft_strdup("\n");
// 				if (!token->token)
// 					return (ft_msg(1, "", "", ERRMAL));
// 			}
// 			else
// 			{
// 				tmp = ft_strdup(token->token);
// 				if (!tmp)
// 					return (ft_msg(1, "", "", ERRMAL)); // FREEE + EXIT
// 				free(token->token);
// 				token->token = ft_strjoin(tmp, "\n");
// 				if (!token->token)
// 				{
// 					free(tmp);
// 					return (ft_msg(1, "", "", ERRMAL));
// 				}
// 				free(tmp);
// 			}
// 			printf("%s", token->token);
// 			return (0);
// 		}
// 		if (token->next == NULL)
// 		{
// 			printf("");
// 			return (0);
// 		}
// 		if (token->next)
// 		{
// 			if (token->next->type == SP_QUOTES)
// 			{
// 				free(token->next->token);
// 				token->next->token = ft_strdup("");
// 				if (!token->next->token)
// 					return (ft_msg(1, "", "", ERRMAL));
// 			}
// 			printf("%s", token->next->token);
// 			return (0);
// 		}
// 	}
// 	printf("\n");
// 	return (0);
// }

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
			//ft_putstr_fd(token->token, STDOUT_FILENO);
			return (0);
		}
		if (token->next == NULL)
		{
			printf("");
			//ft_putstr_fd("", STDOUT_FILENO);
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
			//ft_putstr_fd(token->next->token, STDOUT_FILENO);
			return (0);
		}
	}
	printf("\n");
	return (0);
}