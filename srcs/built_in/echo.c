/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:53:43 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/27 16:16:23 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_no_word_n(t_token *token, t_data *data, int flag)
{
	char	*tmp;

	tmp = NULL;
	if (token->type == SP_QUOTES)
	{
		ft_handle_malloc(DELONE, token->token, 0, NULL);
		token->token = ft_strdup("\n");
		ft_handle_malloc(flag + TAB_STR1, token->token, 0, data);
	}
	else
	{
		tmp = ft_strdup(token->token);
		ft_handle_malloc(flag + TAB_STR1, tmp, 0, data);
		ft_handle_malloc(DELONE, token->token, 0, NULL);
		token->token = ft_strjoin(tmp, "\n");
		ft_handle_malloc(flag + TAB_STR1, token->token, 0, data);
		ft_handle_malloc(DELONE, tmp, 0, NULL);
	}
	ft_putstr_fd(token->token, STDOUT_FILENO);
	return (0);
}

int	ft_echo(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;

	token = cmd->token;
	token = token->next;
	if (token)
	{
		if (token->type != WORD_N)
			return (ft_print_no_word_n(token, data, flag));
		if (token->next == NULL)
			return (write(STDOUT_FILENO, "", 0));
		else
		{
			token = token->next;
			if (token->type == SP_QUOTES)
			{
				ft_handle_malloc(DELONE, token->token, 0, NULL);
				token->token = ft_strdup("");
				ft_handle_malloc(flag + TAB_STR1, token->next->token, 0, data);
			}
			ft_putstr_fd(token->token, STDOUT_FILENO);
			return (0);
		}
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
