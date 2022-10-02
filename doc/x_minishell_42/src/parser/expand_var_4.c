/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:23:18 by cvidon            #+#    #+#             */
/*   Updated: 2022/07/14 10:54:21 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 ** if $0something -> return to join('minishell' + 'something')
 **
 **            echo $0tray
 **                 bashtray
 **
 ** if $+1 == digit -> substr(key, 1, strlend(key - 1));
 **
 **            echo $100
 **                 00
 **
 ** if $+1 = !alpha_ -> return join('$', key);
 **
 **            echo $=42
 **                 $=42
 **
 ** while alphanum_ until !alphanum_ -> join (getenv_var + after !alphanum_)
 **
 **            echo 1. "$t=TEST" 2. $USER=USER
 **                 1. =TEST     2. cvidon=USER
 **
 ** if all alphanum_ -> return getenv_var
 **
 **            echo $USERR
 */

char	*ft_expand_var_2(t_data *data, char *key, int i)
{
	char		*ptr;
	char		*var;

	if (ft_isdigit (key[0]))
		var = ft_w_substr(data, key, 0, 1);
	else
		var = ft_w_substr(data, key, 0, (size_t)i);
	ptr = var;
	var = ft_getenv(data, data->envlist, var);
	ft_free (ptr);
	return (var);
}

char	*ft_expand_var(t_data *data, char *key)
{
	char		*var;
	size_t		i;

	if (key[0] == '0')
		return (ft_strjoin_free_s2
			("minishell", ft_w_substr(data, key, 1, ft_strlen(key))));
	if (ft_isdigit (key[0]))
		return (ft_w_substr(data, key, 1, ft_strlen(key)));
	if (!(ft_isalpha (key[0]) || key[0] == '_'))
		return (ft_strjoin ("$", key));
	i = 0;
	while (1)
	{
		if (!(ft_isalnum (key[i]) || key[i] == '_'))
		{
			var = ft_expand_var_2 (data, key, (int)i);
			return (ft_strjoin_free_s1 (var, key + i));
		}
		i++;
	}
}
