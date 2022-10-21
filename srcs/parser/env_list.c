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

int	ft_lstadd_env(t_env **env, char *envp, t_data *data, int flag)
{
	t_env	*new;
	t_env	*last;
	int		equal;

	new = ft_handle_malloc(flag + 1 + LST_ENV, NULL, 1, data);
	equal = ft_new_strchr(envp, '=');
	new->var = ft_substr(envp, 0, equal);
	ft_handle_malloc(flag + TAB_STR1, new->var, 0, data);
	new->var_equal = ft_substr(envp, 0, equal + 1);
	ft_handle_malloc(flag + TAB_STR1, new->var_equal, 0, data);
	new->content = ft_substr(envp, equal + 1, (ft_strlen(envp) - equal + 1));
	ft_handle_malloc(flag + TAB_STR1, new->content, 0, data);
	new->envp = ft_strdup(envp);
	ft_handle_malloc(flag + TAB_STR1, new->envp, 0, data);
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
