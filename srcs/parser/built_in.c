/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:50:57 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/13 10:55:15 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_built_in(void)
{
	char	**built_in;

	built_in = ft_handle_malloc(MALLOC_M + TAB_STR2, NULL, (7 + 1), NULL);
	printf("built in char ** addr = %p\n", built_in);
	// // TEST3
	// printf("test 3 ici 1\n");
	// ft_handle_malloc(0, NULL, 0, 0);
	// exit (EXIT_FAILURE);

	// built_in = malloc(sizeof(char*) * 8);
	// if (!built_in)
	// 	return (NULL); // free ce qu'on a deja malloc dans data;


	// // TEST4
	// built_in[0] = NULL;///
	built_in[0] = ft_strdup("echo");
	printf("built in[0] char * addr = %p\n", built_in[0]);
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[0], 0, NULL);
	printf("built in[0] char * addr = %p\n", built_in[0]);
	built_in[1] = ft_strdup("cd");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[1], 0, NULL);
	built_in[2] = ft_strdup("pwd");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[2], 0, NULL);
	built_in[3] = ft_strdup("export");
	// // TEST5
	// free(built_in[3]);
	// built_in[3] = NULL;///
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[3], 0, NULL);
	built_in[4] = ft_strdup("unset");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[4], 0, NULL);
	built_in[5] = ft_strdup("env");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[5], 0, NULL);
	built_in[6] = ft_strdup("exit");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[6], 0, NULL);
	built_in[7] = NULL;
	// if (!built_in[0] || !built_in[1] || !built_in[3] || !built_in[4] || !built_in[5]
	// 	|| !built_in[6])
	// 	return (NULL); // free ce qu'on a deja malloc dans data;
	return (built_in);
}
