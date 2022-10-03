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

/*	Fonction SANS ft_malloc*/
// int	ft_lstadd_env(t_data *data, t_env **env, char *envp)
// {
// 	t_env	*new;
// 	t_env	*last;
// 	int		equal;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 	{
// 		ft_free_env(env);
// 		return (1);
// 	}
// 	equal = ft_new_strchr(envp, '=');
// 	// si equal == NULL ?
// 	new->var = ft_substr(envp, 0, equal);
// 	new->var_equal = ft_substr(envp, 0, equal + 1);
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
/*	Fonction AVEC ft_malloc*/
int	ft_lstadd_env(t_data *data, t_env **env, char *envp)
{
	t_env	*new;
	t_env	*last;
	int		equal;

	new = NULL;
	new = ft_malloc(data, new, LST_ENV, 1);
	if (new == NULL)
		return (1);// plutôt exit direct ???
	equal = ft_new_strchr(envp, '=');
	// si equal == NULL ?
	new->var = ft_substr_malloc(data, envp, 0, equal);
	new->var_equal = ft_substr_malloc(data, envp, 0, equal + 1);
	new->content = ft_substr_malloc(data, envp, equal + 1, (ft_strlen(envp) - equal + 1));
	new->envp = ft_strdup_malloc(data, envp);
	//ajouter les conditions de sortie... si pb de malloc
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

/*	Fonction SANS ft_malloc*/
// t_env	*ft_get_env(char **envp)
// {
// 	t_env	*env;
// 	int		i;

// 	env = NULL;
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_lstadd_env(&env, envp[i]) == 1)
// 			return (NULL);
// 		i++;
// 	}
// 	return (env);
// }
/*	Fonction AVEC ft_malloc*/
t_env	*ft_get_env(t_data *data, char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_lstadd_env(data, &env, envp[i]) == 1)
			return (NULL);
		i++;
	}
	return (env);
}

void	ft_lstdelone_env(t_env *node)
{
	if (!node)
		return ;
	free(node->var);
	node->var = NULL;
	free(node->var_equal);
	node->var_equal = NULL;
	free(node->content);
	node->content = NULL;
	free(node->envp);
	node->envp = NULL;
	node->next = NULL;
	free(node);
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	if (!*env)
		return ;
	while (*env != NULL)
	{
		tmp = (*env)->next;
		ft_lstdelone_env(*env);
		(*env) = tmp;
	}
	(*env) = NULL;
}
