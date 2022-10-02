/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:21:21 by athirion          #+#    #+#             */
/*   Updated: 2022/07/07 15:37:52 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_update_here_doc(t_data *data, char *str, char *val, int index)
{
	char	*new_heredoc;
	int		i;

	i = 0;
	if (val)
		new_heredoc = ft_w_malloc(data, ft_strlen(val) + (size_t)index + 1);
	else
		new_heredoc = ft_w_malloc(data, (size_t) index + 1);
	while (i < index)
	{
		new_heredoc[i] = str[i];
		i ++;
	}
	i = 0;
	while (val && val[i])
	{
		new_heredoc[i + index] = val[i];
		i ++;
	}
	new_heredoc[i + index] = '\0';
	return (new_heredoc);
}

int	ft_has_dol(char *str, size_t index)
{
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] && !ft_isspace(str[index + 1]))
			return ((int)index);
		index ++;
	}
	return (-1);
}

size_t	ft_end_var(char *str, size_t i)
{
	size_t	len;

	len = 0;
	while (str[i] && str[i] != '$')
		i ++;
	if (str[i] == '$')
		i ++;
	while (str[i] && ft_isalnum(str[i]))
	{
		i ++;
		len ++;
	}
	return (len);
}

/*
 ** tmp[0] = new_heredoc;
 ** tmp[1] = temp;
 ** i[0] = i;
 ** i[1] = rest;
 ** var[0] = key;
 ** var[1] = val;
*/

char	*ft_expand_heredoc(t_data *data, char *str)
{
	size_t			i[2];
	char			*var[2];
	char			*tmp[2];

	i[0] = 0;
	while (str[i[0]])
	{
		if (ft_valid_var_format(i[0], str))
		{
			var[0] = ft_substr(str, (unsigned int) ft_has_dol(str, i[0]) + 1,
					ft_end_var(str, i[0]));
			var[1] = ft_getenv(data, data->envlist, var[0]);
			if (ft_has_dol(str, i[0]) != -1)
				tmp[0] = ft_update_here_doc(data, str, var[1],
						ft_has_dol(str, i[0]));
			i[1] = (size_t) ft_has_dol(str, i[0]) + ft_strlen(var[0]) + 1;
			tmp[1] = ft_substr(str, (unsigned int) i[1], ft_strlen(str) - i[1]);
			str = ft_update_str(tmp, str, var[0], var[1]);
			if (!var[1])
				continue ;
		}
		if (str[i[0]])
			i[0]++;
	}
	return (str);
}
