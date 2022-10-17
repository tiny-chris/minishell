/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:22:17 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/17 18:23:02 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_check_digit(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	if (token[i] == '+' || token[i] == '-')
		i++;
	if (token[i])
	{
		while (token[i])
		{
			if (ft_isdigit(token[i]) == 0)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

char	*ft_get_check2(char *token, int flag, t_data *data)
{
	char	*check2;
	char	*tmp;
	int		i;

	i = 0;
	if (token[i] == '+' || token[i] == '-')
		i++;
	while (token[i] && token[i] == '0')
		i++;
	if (token[i] == '\0')
		check2 = ft_strdup("0");
	else if (token[0] == '-')
	{
		tmp = ft_substr(token, i, ft_strlen(token) - i);
		ft_handle_malloc(flag + TAB_STR1, tmp, 0, data);
		check2 = ft_strjoin("-", tmp);
	}
	else
		check2 = ft_substr(token, i, ft_strlen(token) - i);
	ft_handle_malloc(flag + TAB_STR1, check2, 0, data);
	return (check2);
}
