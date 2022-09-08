/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:41:20 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/08 16:21:07 by lmelard          ###   ########.fr       */
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

// int	ft_find_space(char *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == ' ')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_only_closed_quotes(char *token)
// {
// 	int		i;
// 	char	c;

// 	i = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == 34 || token[i] == 39)
// 		{
// 			c = token[i];
// 			i++;
// 			if (token[i] != c)
// 				return (0);
// 		}
// 		else
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

static int ft_new_len(char *token)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(token);
	if (len == 2 && token[i] == -34 && token[i + 1] == -34)
		return (len);
	while (token[i])
	{
		if (token[i] == -34)
		{
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

int	ft_clean_token(t_cmd *cmd, t_data *data)
{
	t_token	*token;
//	int		i;
	int		len;

	(void)data;
	token = cmd->token;
//	i = 0;
	len = ft_new_len(token->token);
	printf("len clean token = %d\n", len);
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