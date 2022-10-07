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
		if (ft_lstadd_env(&env, envp[i]) == 1)
		//if (ft_lstadd_env(&env, envp[i], ADD_M) == 1)
			return (NULL);
		i++;
	}
	return (env);
}

/* <SUMMARY> Functions for linked list 'env'
*/
t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*node;

	if (!lst)
		return (0);
	node = lst;
	while (node->next)
		node = node->next;
	return (node);
}

//flag = ADD_M ou ADD_C

// int	ft_lstadd_env(t_env **env, char *envp, int flag)
// {
// 	t_env	*new;
// 	t_env	*last;
// 	int		equal;

// 	new = malloc(sizeof(t_env));
// 	ft_handle_malloc(flag, new, LST_ENV, 1);
// 	// if (!new)
// 	// {
// 	// 	ft_free_env(env);
// 	// 	return (1);
// 	// }
// 	equal = ft_new_strchr(envp, '=');
// 	// QUID si equal == NULL ?
// 	new->var = ft_substr(envp, 0, equal);
// 	ft_handle_malloc(flag, new->var, TAB_STR1, equal + 1);
// 	new->var_equal = ft_substr(envp, 0, equal + 1);
// 	ft_handle_malloc(flag, new->var_equal, TAB_STR1, equal + 2);
// 	new->content = ft_substr(envp, equal + 1, (ft_strlen(envp) - equal + 1));
// 	new->envp = ft_strdup(envp);
// 	new->next = NULL;
// 	if (ft_lstlast_env(*env) == 0)
// 	{
// 		*env = new;
// 		return (0);
// 	}
// 	last = ft_lstlast_env(*env);
// 	last->next = new;
// 	return (0);
// }

int	ft_lstadd_env(t_env **env, char *envp)
{
	t_env	*new;
	t_env	*last;
	int		equal;
	int		len;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ft_free_env(env);
		return (1);
	}
	equal = ft_new_strchr(envp, '=');
	len = ft_strlen(envp);
	printf("equal = %d\n", equal);
	// si equal == NULL ?
	new->var = ft_substr(envp, 0, equal);
	new->var_equal = ft_substr(envp, 0, equal + 1);
	new->content = ft_substr(envp, equal + 1, (len - equal + 1));
	new->envp = ft_strdup(envp);
	new->next = NULL;
	if (ft_lstlast_env(*env) == 0)
	{
		*env = new;
		return (0);
	}
	last = ft_lstlast_env(*env);
	last->next = new;
	return (0);
}

void	ft_lstdelone_env(t_env *node)
{
	if (!node)
		return ;
	ft_free_strs(node->var, node->var_equal, node->content);
	ft_free_strs(node->envp, NULL, NULL);
	node->next = NULL;
	free(node);
	node = NULL;
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	if (!*env)
		return ;
	while ((*env) != NULL)
	{
		tmp = (*env)->next;
		ft_lstdelone_env(*env);
		(*env) = tmp;
	}
	(*env) = NULL;
}
