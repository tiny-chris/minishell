/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:50:57 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/21 00:35:06 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_built_in(void)
{
	char	**built_in;

	built_in = malloc(sizeof(char*) * 8);
	if (!built_in)
		return (NULL); // free ce qu'on a deja malloc dans data;
	built_in[0] = ft_strdup("echo");
	built_in[1] = ft_strdup("cd");
	built_in[2] = ft_strdup("pwd");
	built_in[3] = ft_strdup("export");
	built_in[4] = ft_strdup("unset");
	built_in[5] = ft_strdup("env");
	built_in[6] = ft_strdup("exit");
	built_in[7] = NULL;
	if (!built_in[0] || !built_in[1] || !built_in[3] || !built_in[4] || !built_in[5]
		|| !built_in[6])
		return (NULL); // free ce qu'on a deja malloc dans data;
	return (built_in);
}
