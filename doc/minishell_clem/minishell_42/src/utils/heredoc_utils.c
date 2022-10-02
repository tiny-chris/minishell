/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:38:12 by athirion          #+#    #+#             */
/*   Updated: 2022/06/29 20:43:02 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_get_var(t_data *data, char *str)
{
	size_t		i;
	char		*var;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != ' ' && str[i] != '\n')
		i ++;
	var = ft_w_substr(data, str, 0, i);
	var = ft_getenv(data, data->envlist, var);
	return (var);
}

int	ft_len_var(t_data *data, char *str)
{
	size_t		len;
	char		*var;
	char		*temp_var;

	len = 0;
	while (str[len] && str[len] != '$' && str[len] != '\'' && str[len] != '\"'
		&& str[len] != ' ' && str[len] != '\n')
		len ++;
	temp_var = ft_w_substr(data, str, 0, len);
	var = ft_getenv(data, data->envlist, temp_var);
	len = 0;
	if (var)
	{
		len = ft_strlen(var);
		free(var);
	}
	free(temp_var);
	return ((int)len);
}
