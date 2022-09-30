/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:50:57 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/26 03:00:37 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Fonction avant ft_malloc*/
// char	**ft_built_in(void)
// {
// 	char	**built_in;

// 	built_in = malloc(sizeof(char*) * 8);
// 	if (!built_in)
// 		return (NULL); // free ce qu'on a deja malloc dans data;
// 	built_in[0] = ft_strdup("echo");
// 	built_in[1] = ft_strdup("cd");
// 	built_in[2] = ft_strdup("pwd");
// 	built_in[3] = ft_strdup("export");
// 	built_in[4] = ft_strdup("unset");
// 	built_in[5] = ft_strdup("env");
// 	built_in[6] = ft_strdup("exit");
// 	built_in[7] = NULL;
// 	if (!built_in[0] || !built_in[1] || !built_in[3] || !built_in[4] || !built_in[5]
// 		|| !built_in[6])
// 		return (NULL); // free ce qu'on a deja malloc dans data;
// 	return (built_in);
// }
/*	Fonction AVEC ft_malloc*/
char	**ft_built_in(t_data *data)
{
	char	**built_in;

	built_in = NULL;
	built_in = ft_malloc(data, built_in, TAB_STRS, 8);
	if (built_in == NULL)
		//return (NULL);//je peux direct exit... au lieu de mettre la condition dans minishell.c
		exit(ft_msg(1, "built-in memory alloc failure: ", "", "could not initialise minishell" ));
	built_in[0] = ft_strdup_malloc(data, "echo");
	built_in[1] = ft_strdup_malloc(data, "cd");
	built_in[2] = ft_strdup_malloc(data, "pwd");
	built_in[3] = ft_strdup_malloc(data, "export");
	built_in[4] = ft_strdup_malloc(data, "unset");
	built_in[5] = ft_strdup_malloc(data, "env");
	built_in[6] = ft_strdup_malloc(data, "exit");
	built_in[7] = NULL;
	if (!built_in[0] || !built_in[1] || !built_in[3] || !built_in[4] || !built_in[5]
		|| !built_in[6])
		return (NULL); // free ce qu'on a deja malloc dans data;
	return (built_in);
}
