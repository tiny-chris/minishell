/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:30:55 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/15 16:21:45 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_space_quotes(char *tmp_token, t_token *token)
{
	if (ft_strlen(tmp_token) == 2 && (tmp_token[0] == 34 || tmp_token[0] == 39) && tmp_token[1] == tmp_token[0])
		token->type = SP_QUOTES;
	return (0);
}
