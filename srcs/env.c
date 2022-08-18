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

#include "../includes/minishell.h"

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

int	ft_lstadd_env(t_env **env, char *envp)
{
	t_env	*new;
	t_env	*last;
	int		equal;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ft_free_env(env);
		return (1);
	}
	equal = ft_new_strchr(envp, '=');
	// si equal == NULL ?
	new->var = ft_substr(envp, 0, equal);
	new->content = ft_substr(envp, equal + 1, (ft_strlen(envp) - equal + 1));
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

t_env	*ft_get_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_lstadd_env(&env, envp[i]) == 1)
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
	free(node->content);
	node->content = NULL;
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
