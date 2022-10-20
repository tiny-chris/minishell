/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:52:35 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 15:22:11 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_token_quotes(char *clean_cmd, int *j)
{
	char	c;

	c = clean_cmd[*j];
	(*j)++;
	while (clean_cmd[*j] && clean_cmd[*j] != c)
		(*j)++;
	(*j)++;
}

int	ft_get_token_end(t_cmd *cmd, char *clean_cmd, t_token *token, int *j)
{
	if (clean_cmd[*j] == '\0')
	{
		cmd->token = token;
		return (0);
	}
	cmd->token = token;
	return (0);
}

int	ft_check_end(t_cmd *cmd, char *clean_cmd, t_token *token, t_int *var)
{
	if (clean_cmd[var->j] == '\0')
	{
		cmd->token = token;
		return (0);
	}
	var->i = var->j + 1;
	(var->j)++;
	return (1);
}

int	ft_get_token(t_cmd *cmd, t_data *data)
{
	char	*clean_cmd;
	t_token	*token;
	t_int	var;

	var.i = 0;
	var.j = 0;
	token = NULL;
	clean_cmd = cmd->clean_cmd;
	while (clean_cmd[var.j])
	{
		if (clean_cmd[var.j] == 34 || clean_cmd[var.j] == 39)
			ft_get_token_quotes(clean_cmd, &(var.j));
		if (clean_cmd[var.j] == ' ' || clean_cmd[var.j] == '\0')
		{
			ft_lstadd_tok(&token, WORD, \
				ft_substr(clean_cmd, var.i, (var.j) - (var.i)), data);
			if (ft_check_end(cmd, clean_cmd, token, &var) == 0)
				return (0);
		}
		else if (clean_cmd[var.j] != 34 && clean_cmd[var.j] != 39)
			(var.j)++;
	}
	ft_lstadd_tok(&token, WORD, \
		ft_substr(clean_cmd, var.i, (var.j) - (var.i)), data);
	return (ft_get_token_end(cmd, clean_cmd, token, &(var.j)));
}

int	ft_tokenizer(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		ft_get_token(cmd, data);
		ft_clean_token(cmd, data);
		ft_del_empty_token(cmd, data);
		if (cmd->token)
			ft_type_token(cmd, data);
		ft_del_nword(cmd);
		cmd = cmd->next;
	}
	return (0);
}
