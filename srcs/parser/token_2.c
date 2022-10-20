/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:52:35 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 15:39:21 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_token(t_cmd *cmd, t_data *data)
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
			ft_lstadd_token(&token, WORD, ft_substr(clean_cmd, i, j - i), data);
			// if (ft_lstadd_token(&token, WORD, ft_substr(clean_cmd, i, j - i)))
			// 	return (1);//FREE & EXIT
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
	ft_lstadd_token(&token, WORD, ft_substr(clean_cmd, i, j - i), data);
	// if (ft_lstadd_token(&token, WORD, ft_substr(clean_cmd, i, j - i)))
	// 	return (1);
	if (clean_cmd[j] == '\0')
	{
		cmd->token = token;
		return (0);
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
		// dprintf(2, "check check check\n");
		ft_get_token(cmd, data);
		ft_clean_token(cmd, data);
//		ft_del_empty_token(&cmd, data);
		ft_del_empty_token(cmd, data);
		// ft_spec_env_case(cmd, data);// vérifier que c'est bien placé par rapport à type_token
		if (cmd->token)
		{
			// dprintf(2, "passe avant type token\n");
			ft_type_token(cmd, data);
		}
		ft_del_nword(cmd);
		// ft_print_token(cmd);//A SUPPRIMER
		cmd = cmd->next;
	}

	// /* 	TEMPORARY --> TO PRINT */
	// /*	start */
	// t_cmd	*tmp;
	// t_token	*token;
	// int		nb;

	// nb = 0;
	// tmp = data->cmd;
	// while (tmp)
	// {
	// 	token = tmp->token;
	// 	while (token)
	// 	{
	// 		dprintf(2, "clean token[%d] = %s, type = %d, size = %ld\n", nb, token->token, token->type, ft_strlen(token->token));
	// 		token = token->next;
	// 		nb++;
	// 	}
	// 	tmp = tmp->next;
	// 	nb = 0;
	// }
	// /*	end */
	return (0);
}
