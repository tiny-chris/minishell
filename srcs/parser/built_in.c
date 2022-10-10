/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:50:57 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/10 15:05:30 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_built_in(void)
{
	char	**built_in;

	built_in = ft_handle_malloc(MALLOC_M, NULL, TAB_STRS, 8);
	// TEST3
	printf("test ici 1\n");
	ft_handle_malloc(DELONE, built_in, 0, 0);
	ft_handle_malloc(0, NULL, 0, 0);
	

	// built_in = malloc(sizeof(char*) * 8);
	// if (!built_in)
	// 	return (NULL); // free ce qu'on a deja malloc dans data;
	built_in[0] = ft_strdup("echo");
	ft_handle_malloc(ADD_M, built_in[0], TAB_STR1, ft_strlen("echo") + 1);
	built_in[1] = ft_strdup("cd");
	ft_handle_malloc(ADD_M, built_in[1], TAB_STR1, ft_strlen("cd") + 1);
	built_in[2] = ft_strdup("pwd");
	ft_handle_malloc(ADD_M, built_in[2], TAB_STR1, ft_strlen("pwd") + 1);
	built_in[3] = ft_strdup("export");
	ft_handle_malloc(ADD_M, built_in[3], TAB_STR1, ft_strlen("export") + 1);
	built_in[4] = ft_strdup("unset");
	ft_handle_malloc(ADD_M, built_in[4], TAB_STR1, ft_strlen("unset") + 1);
	built_in[5] = ft_strdup("env");
	ft_handle_malloc(ADD_M, built_in[5], TAB_STR1, ft_strlen("env") + 1);
	built_in[6] = ft_strdup("exit");
	ft_handle_malloc(ADD_M, built_in[6], TAB_STR1, ft_strlen("exit") + 1);
	built_in[7] = NULL;
	// if (!built_in[0] || !built_in[1] || !built_in[3] || !built_in[4] || !built_in[5]
	// 	|| !built_in[6])
	// 	return (NULL); // free ce qu'on a deja malloc dans data;
	return (built_in);
}
