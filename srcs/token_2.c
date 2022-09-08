/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:52:35 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/08 16:22:36 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_token(t_cmd *cmd)
{
	char	*clean_cmd;
	t_token	*token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = NULL;
	clean_cmd = cmd->clean_cmd;
	while (clean_cmd[i] && clean_cmd[i] != ' ')
		i++;
	if (ft_lstadd_token(&token, COMMAND, ft_substr(clean_cmd, j, i - j)))
		return (1);
	if (!clean_cmd[i])
	{
		cmd->token = token;
		return (1);
	}
	i++;// le 1 = ' '
	j = i;
	if (clean_cmd[j])
	{
		while (clean_cmd[j])
		{
			//dprintf(2, "i: %d\n, j: %d\n", i, j);
			while (clean_cmd[j] != '\0' && clean_cmd[j] != ' ')
				j++;
			//dprintf(2, "i: %d\n, j: %d\n", i, j);
			if (ft_lstadd_token(&token, WORD, ft_substr(clean_cmd, i, j - i)))
				return (1);
			if (clean_cmd[j] == '\0')
			{
				cmd->token = token;
				return (0);
			}
			j++;
			i = j;
		}
	}
	cmd->token = token;
	return (0);
}

int	ft_tokenizer(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		ft_get_token(cmd);
		ft_clean_token(cmd, data);
		cmd = cmd->next;
	}

	/* TO PRINT */
	t_cmd	*tmp;
	t_token	*token;

	tmp = data->cmd;
	while (tmp)
	{
		token = tmp->token;
		while (token)
		{
			printf("token = %s, type = %d, size = %ld\n", token->token, token->type, ft_strlen(token->token));
			token = token->next;
		}
		tmp = tmp->next;
	}
	return (0);

}
