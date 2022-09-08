/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:41:20 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/08 18:03:50 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* STEPS
	- clean 1st token
	- check built-in
		- if command --> cleaning (negative, delete quotes...)
			BEWARE: empty token
			BEWARE: $?
		- if built-in
			--> check specific situations incl. echo case (WORD_N...)
*/

static int ft_new_len(char *token)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(token);
	if (token[i] == -34 && token[i + 1] == -34)
	{
		while (token[i] && token[i] == -34 && token[i + 1] == -34)
			i += 2;
		if (token[i] == '\0')
			return (2);
		i = 0;
	}
	while (token[i])
	{
		if (token[i] == -34)
		{
			i++;
			while (token[i] && token[i] != -34)
				i++;
			if (token[i] == '\0')
				return (len);
			len -= 2;
		}
		i++;
	}
	return (len);
}

int	ft_check_dq_neg(char *old_token, int i)
{
	if (old_token[i] == -34)
	{
		i++;
		while (old_token[i] && old_token[i] != -34)
			i++;
		if (old_token[i] == '\0')
			return (0);
	}
	return (1);
}

int	ft_first_token(t_token *token, int len)
{
	char	*new_token;
	char	*old_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	old_token = token->token;
	new_token = malloc(sizeof(char) * (len + 1));
	if (!new_token)
		return (1);// FREE TOUT ET EXIT
	if (old_token[i] == -34 && old_token[i + 1] == -34)
	{
		while (old_token[i] && old_token[i] == -34 && old_token[i + 1] == -34)
			i += 2;
		if (old_token[i] == '\0')
		{
			new_token[j] = 34;
			new_token[j + 1] = 34;
			new_token[j + 2] = '\0';
			free(old_token);
			token->token = new_token;
			return (0);
		}
		i = 0;
	}
	while (old_token[i])
	{
		if (old_token[i] == -34 && ft_check_dq_neg(old_token, i))//on copie pas les quotes
		{
			i++;
			while (old_token[i] != -34)
			{
				new_token[j] = old_token[i];
				i++;
				j++;
			}
		}
		else
		{
			new_token[j] = old_token[i];
			j++;
		}
		i++;
	}
	new_token[j] = '\0';
	free(old_token);
	token->token = new_token;
	return (0);
}

void	ft_positive_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->token[i])
	{
		if(token->token[i] < 0)
			token->token[i] = (-1) * token->token[i];
		i++;
	}
}

int	ft_clean_token(t_cmd *cmd, t_data *data)
{
	t_token	*token;
//	int		i;
	int		len;

	(void)data;
	token = cmd->token;
//	i = 0;
	while (token)
	{
		len = ft_new_len(token->token);
		//printf("len clean token = %d\n", len);
		ft_first_token(token, len);
		ft_positive_token(token);
		//printf("clean new 1st token = %s, len = %ld\n", token->token, ft_strlen(token->token));
		token = token->next;
	}
	return (0);
	// while (token->token[i])
	// {
	// 	if (token->token[i] == -34 && token->token[i + 1] == -34 && y a rien apres )
	// 	if (token->token[i] < 0)
	// 		token->token[i] = (-1) * (token->token[i]);
	// 	i++;
	// }
	// i = 0;
}
