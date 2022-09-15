/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:52:35 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/15 17:06:51 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_token(t_cmd *cmd)
{
	char	*clean_cmd;
	t_token	*token;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	token = NULL;
	clean_cmd = cmd->clean_cmd;
	while (clean_cmd[j])
	{
		if (clean_cmd[j] == 34 || clean_cmd[j] == 39)
		{
			c = clean_cmd[j];
			j++;
			while (clean_cmd[j] && clean_cmd[j] != c)
				j++;
			j++;
		}
		if (clean_cmd[j] == ' ' || clean_cmd[j] == '\0')
		{
			if (ft_lstadd_token(&token, WORD, ft_substr(clean_cmd, i, j - i)))
				return (1);//FREE & EXIT
			if (clean_cmd[j] == '\0')
			{
				cmd->token = token;
				return (0);
			}
			i = j + 1;
			j++;
		}
		else if (clean_cmd[j] != 34 && clean_cmd[j] != 39)
			j++;
	}
	if (ft_lstadd_token(&token, WORD, ft_substr(clean_cmd, i, j - i)))
		return (1);
	if (clean_cmd[j] == '\0')
	{
		cmd->token = token;
		return (0);
	}
	cmd->token = token;
	return (0);
}

static void	ft_print_token(t_cmd *cmd)//  A SUPPRIMER
{
	t_token	*token;
	int		nb;

	nb = 0;
	token = cmd->token;
	while (token)
	{
		dprintf(2, "print del empty token[%d] = %s, type = %d, size = %ld\n", nb, token->token, token->type, ft_strlen(token->token));
		token = token->next;
		nb++;
	}
}

int	ft_tokenizer(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		ft_get_token(cmd);
		ft_clean_token(cmd, data);
//		ft_del_empty_token(&cmd, data);
		ft_del_empty_token(cmd, data);
		ft_print_token(cmd);
		if (cmd->token)
		{
			dprintf(2, "passe avant type token\n");
			ft_type_token(cmd, data);
		}
		ft_del_nword(cmd);
		cmd = cmd->next;
	}

	/* 	TEMPORARY --> TO PRINT */
	/*	start */
	t_cmd	*tmp;
	t_token	*token;
	int		nb;

	nb = 0;
	tmp = data->cmd;
	while (tmp)
	{
		token = tmp->token;
		while (token)
		{
			dprintf(2, "clean token[%d] = %s, type = %d, size = %ld\n", nb, token->token, token->type, ft_strlen(token->token));
			token = token->next;
			nb++;
		}
		tmp = tmp->next;
		nb = 0;
	}
	/*	end */
	return (0);
}
