/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:50:57 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 17:26:52 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_built_in(void)
{
	char	**built_in;

	built_in = ft_handle_malloc(MALLOC_M + TAB_STR2, NULL, (7 + 1), NULL);
	built_in[0] = ft_strdup("echo");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[0], 0, NULL);
	built_in[1] = ft_strdup("cd");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[1], 0, NULL);
	built_in[2] = ft_strdup("pwd");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[2], 0, NULL);
	built_in[3] = ft_strdup("export");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[3], 0, NULL);
	built_in[4] = ft_strdup("unset");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[4], 0, NULL);
	built_in[5] = ft_strdup("env");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[5], 0, NULL);
	built_in[6] = ft_strdup("exit");
	ft_handle_malloc(ADD_M + TAB_STR1, built_in[6], 0, NULL);
	built_in[7] = NULL;
	return (built_in);
}
