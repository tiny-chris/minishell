/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:21:21 by athirion          #+#    #+#             */
/*   Updated: 2022/07/07 15:52:42 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_valid_var_format(size_t i, char *str)
{
	if (str[i] == '$' && str[i + 1]
		&& str[i + 1] != '$' && !ft_isspace(str[i + 1]))
		return (1);
	return (0);
}

char	*ft_update_str(char **temp, char *str, char *key, char *val)
{
	ft_free(str);
	str = ft_strjoin_free_s2(temp[0], temp[1]);
	ft_free(key);
	ft_free(val);
	ft_free(temp[0]);
	return (str);
}

int	ft_has_a_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i ++;
	}
	return (0);
}
