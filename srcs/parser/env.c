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
		if (ft_lstadd_env(&env, envp[i], ADD_M) == 1)
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
// ajout de head_addr pour nettoyer dans t_env via l'appel de t_bin (pas d eliste doublement chainee)

int	ft_lstadd_env(t_env **env, char *envp, int flag)
{
	t_env	*new;
	t_env	*last;
	int		equal;

	new = ft_handle_malloc(flag + 1, NULL, LST_ENV, 1);
	// printf("test ici 1\n");
	equal = ft_new_strchr(envp, '=');
	// QUID si equal == NULL ?
	// printf("test ici\n");
	new->var = ft_substr(envp, 0, equal);
	ft_handle_malloc(flag, new->var, TAB_STR1, equal + 1);
	new->var_equal = ft_substr(envp, 0, equal + 1);
	ft_handle_malloc(flag, new->var_equal, TAB_STR1, equal + 2);
	new->content = ft_substr(envp, equal + 1, (ft_strlen(envp) - equal + 1));
	ft_handle_malloc(flag, new->content, TAB_STR1, (ft_strlen(envp) - equal + 2));
	new->envp = ft_strdup(envp);
	ft_handle_malloc(flag, new->envp, TAB_STR1, ft_strlen(envp) + 1);
	new->next = NULL;
	if (ft_lstlast_env(*env) == 0)
	{
		*env = new;
		return (0);
	}
	last = ft_lstlast_env(*env);
	last->next = new;
	// new->head_addr = (*env);
	return (0);
}

// // OLD VERSION - WITH NO ft_handle_malloc
// int	ft_lstadd_env(t_env **env, char *envp)
// {
// 	t_env	*new;
// 	t_env	*last;
// 	int		equal;
// 	int		len;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 	{
// 		ft_free_env(env);
// 		return (1);
// 	}
// 	equal = ft_new_strchr(envp, '=');
// 	len = ft_strlen(envp);
// 	printf("equal = %d\n", equal);
// 	// si equal == NULL ?
// 	new->var = ft_substr(envp, 0, equal);
// 	new->var_equal = ft_substr(envp, 0, equal + 1);
// 	new->content = ft_substr(envp, equal + 1, (len - equal + 1));
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

void	ft_lstdelone_env(t_env *node, int flag)
{
	if (!node)
		return ;
	(void) flag;
	// if (flag == DELONE)
	// {
	// 	ft_free_strs(node->var, node->var_equal, node->content);
	// //	dprintf(2, "ca bug pas là\n");
	// 	ft_free_strs(node->envp, NULL, NULL);
	// // free(node->head_addr);
	// // node->head_addr = NULL;
	// }
	node->next = NULL;
	free(node);
	node = NULL;
}

static int	ft_lstclearfirst_env(t_env **env_head)
{
	t_env	*todel;
	t_env	*tmp;

	todel = (*env_head);
	tmp = (*env_head)->next;
	ft_handle_malloc(DELONE, todel, 0, 0);
	ft_lstdelone_env(todel, 1);
	(*env_head) = tmp;
	return (0);
}

void	ft_lstclearone_env(t_env **env_head, t_env *ptr)
{
//	t_env	**env_head;
	t_env	*env;
	t_env	*todel;
	t_env	*tmp;

	if (env_head == NULL)
		(*env_head) = ptr->head_addr;
	if (ptr->head_addr == NULL)
		return ;
	env = (*env_head);
	todel = NULL;
	tmp = NULL;
	if (!(*env_head) || !ptr)
		return ;
	if (env == ptr)
	{
		ft_lstclearfirst_env(env_head);
		return ;
	}
	while (env != NULL)
	{
		if (env->next && env->next == ptr)
		{
			todel = env->next;
			tmp = env->next->next;
			ft_handle_malloc(DELONE, todel, 0, 0);
			ft_lstdelone_env(todel, 1);// corriger/checker le flag ///
			env->next = tmp;
			break ;
		}
		env = env->next;
	}
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*todel;

	tmp = NULL;
	todel = NULL;
	if (!*env)
		return ;
	while ((*env) != NULL)
	{
		todel = (*env);
		tmp = (*env)->next;
		ft_handle_malloc(DELONE, todel, 0, 0);
//		ft_lstdelone_env(todel);
		(*env) = tmp;
	}
	(*env) = NULL;
}
