/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:27:17 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/11 23:27:17 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* <SUMMARY> Functions for linked list 't_env'
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

int	ft_lstadd_env(t_env **env, char *envp, t_data *data, int flag)
{
	t_env	*new;
	t_env	*last;
	int		equal;

	new = ft_handle_malloc(flag + 1 + LST_ENV, NULL, 1, data);
	// printf("test ici 1\n");
	equal = ft_new_strchr(envp, '=');
	// QUID si equal == NULL ?
	// printf("test ici 2\n");
	new->var = ft_substr(envp, 0, equal);
	ft_handle_malloc(flag + TAB_STR1, new->var, 0, data);
	new->var_equal = ft_substr(envp, 0, equal + 1);
	ft_handle_malloc(flag + TAB_STR1, new->var_equal, 0, data);
	new->content = ft_substr(envp, equal + 1, (ft_strlen(envp) - equal + 1));
	ft_handle_malloc(flag + TAB_STR1, new->content, 0, data);
	new->envp = ft_strdup(envp);
	ft_handle_malloc(flag + TAB_STR1, new->envp, 0, data);
	new->next = NULL;
	// printf("test ici 3\n");
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
//	new->var_equal = ft_substr(envp, 0, equal + 1);
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

// void	ft_lstdelone_env(t_env *node, int flag)
// {
// 	if (!node)
// 		return ;
// 	(void) flag;
// 	// if (flag == DELONE)
// 	// {
// 	// 	ft_free_strs(node->var, node->var_equal, node->content);
// 	// //	dprintf(2, "ca bug pas là\n");
// 	// 	ft_free_strs(node->envp, NULL, NULL);
// 	// // free(node->head_addr);
// 	// // node->head_addr = NULL;
// 	// }
// 	node->next = NULL;
// 	free(node);
// 	node = NULL;
// }

void	ft_lstdelone_env(t_env *node)
{
	if (!node)
		return ;
	node->next = NULL;
	free(node);
	node = NULL;
}

void	ft_lstdelone_env_bin(t_env *node)
{
	if (!node)
		return ;
	if (node->var)
		ft_handle_malloc(DELONE, node->var, 0, NULL);
	if (node->var_equal)
		ft_handle_malloc(DELONE, node->var_equal, 0, NULL);
	if (node->content)
		ft_handle_malloc(DELONE, node->content, 0, NULL);
	if (node->envp)
		ft_handle_malloc(DELONE, node->envp, 0, NULL);
	// if (node->head_addr)// A REVOIR !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// 	ft_handle_malloc(DELONE, node->head_addr, 0, 0);
	ft_handle_malloc(DELONE, node, 0, NULL);
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
		ft_lstdelone_env_bin(todel);
		(*env) = tmp;
	}
	(*env) = NULL;
}

// A VOIR SI ON LES UTILISE...

// static int	ft_lstclearfirst_env(t_env **env_head)
// {
// 	t_env	*todel;
// 	t_env	*tmp;

// 	todel = (*env_head);
// 	tmp = (*env_head)->next;
// 	ft_handle_malloc(DELONE, todel, 0, NULL);
// 	ft_lstdelone_env(todel);
// 	(*env_head) = tmp;
// 	return (0);
// }

// void	ft_lstclearone_env(t_env **env_head, t_env *ptr)
// {
// //	t_env	**env_head;
// 	t_env	*env;
// 	t_env	*todel;
// 	t_env	*tmp;

// 	if (env_head == NULL)
// 		(*env_head) = ptr->head_addr;
// 	if (ptr->head_addr == NULL)
// 		return ;
// 	env = (*env_head);
// 	todel = NULL;
// 	tmp = NULL;
// 	if (!(*env_head) || !ptr)
// 		return ;
// 	if (env == ptr)
// 	{
// 		ft_lstclearfirst_env(env_head);
// 		return ;
// 	}
// 	while (env != NULL)
// 	{
// 		if (env->next && env->next == ptr)
// 		{
// 			todel = env->next;
// 			tmp = env->next->next;
// 			ft_handle_malloc(DELONE, todel, 0, NULL);
// 			ft_lstdelone_env(todel);// corriger/checker le flag ///
// 			env->next = tmp;
// 			break ;
// 		}
// 		env = env->next;
// 	}
// }
