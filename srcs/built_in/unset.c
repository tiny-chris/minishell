/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:27:14 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/26 15:47:27 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_token_token(t_token *token, t_data *data)
{
	int	res;
	int	i;

	i = 0;
	if ((ft_isalpha(token->token[0]) == 0) && (token->token[0] != '_'))
			res = ft_msg(1, token->token, ": ", ERRNAM);
	else
	{
		while (token->token[i])
		{
			if (ft_isalnum(token->token[i]) == 0)
			{
				res = ft_msg(1, token->token, ": ", ERRNAM);
				break ;
			}
			else
			{
				i++;
				res = 0;
			}
		}
		if (token->token[i] == '\0')
			res = ft_check_unset(token, data);
	}
	return (res);
}

/* <SUMMARY> Unsets tokens that are in the env
** <REMARKS>	- Previous check of name validity
**				- Additional cleaning for PATH & HOME
*/
int	ft_unset(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	int		res;
	int		res2;

	token = cmd->token;
	res = 0;
	res2 = 0;
	if (token->next == NULL)
		return (0);
	token = token->next;
	while (token)
	{
		res = ft_check_token_token(token, data);
		if (res == 0 && res2 == 0)
			res2 = 0;
		else
			res2 = 1;
		token = token->next;
	}
	return (res2);
}
