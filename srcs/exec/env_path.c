/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:26:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/16 18:01:49 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstadd_env2(t_env **env, char *tab_path)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ft_free_env(env);
		return (1);
	}
	//equal = ft_new_strchr(tab_path, '=');
	// si equal == NULL ?
	new->var = NULL;
	new->content = ft_strdup(tab_path);
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

t_env	*ft_lst_env_path(char **tab_path)
{
	t_env	*env_path;
	int		i;

	i = 0;
	env_path = malloc(sizeof(t_env));
	if (!env_path)
		return (NULL);// FREE TOUT ET EXIT
	while (tab_path[i])
	{
		if (ft_lstadd_env2(&env_path, tab_path[i]))
			return (NULL);// FREE TOUT ET EXIT
		i++;
	}
	ft_free_tabstr(tab_path);
	return (env_path);
}

void	ft_get_env_path(t_data *data, char **envp)
{
	char	*ptr_path;
	char	**tab_path;
	int		i;

	i = 0;
	ptr_path = NULL;
	tab_path = NULL;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			ptr_path = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	if (!ptr_path)
		return ;
	tab_path = ft_split(ptr_path, ':');
	if (!tab_path)
		return ;
	free(ptr_path);
	data->env_path = ft_lst_env_path(tab_path);
}
