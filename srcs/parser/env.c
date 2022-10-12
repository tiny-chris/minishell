/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:27:05 by marvin            #+#    #+#             */
/*   Updated: 2022/08/18 11:27:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* <SUMMARY> Gets char **envp (from main) and saves it in a linked list 'env'
** <REMARK>	flag is equal to ADD_M (add main) as this function is only called
**			once at the start of the program
*/
t_env	*ft_get_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		//if (ft_lstadd_env(&env, envp[i]) == 1)// OLD VERSION
		ft_lstadd_env(&env, envp[i], ADD_M);
		// if (ft_lstadd_env(&env, envp[i], ADD_M) == 1)
		// 	return (NULL);
		i++;
	}
	return (env);
}
