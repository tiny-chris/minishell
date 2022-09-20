/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:26:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/20 15:24:47 by cgaillag         ###   ########.fr       */
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
	env_path = NULL;
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
		//	printf("ptrpath = %s\n", ptr_path);
			break ;
		}
		i++;
	}
	if (!ptr_path)
		return ;
	tab_path = ft_split(ptr_path, ':');
	// printf("tabpath 1 = %s\n", tab_path[0]);
	// printf("tabpath 2 = %s\n", tab_path[1]);
	// printf("tabpath 3 = %s\n", tab_path[2]);
	if (!tab_path)
		return ;
	free(ptr_path);
	data->env_path = ft_lst_env_path(tab_path);
}

char	**ft_get_str_env_path(t_data *data)
{
	t_env	*env_path;
	char	**s_env_path;
	int		i;

	env_path = data->env_path;
	i = 0;
	while (env_path)
	{
		i++;
		env_path = env_path->next;
	}
	s_env_path = malloc (sizeof(char *) * (i + 1));
	if (!s_env_path)
		return (NULL);
	i = 0;
	env_path = data->env_path;
	while (env_path)
	{
		s_env_path[i] = ft_strdup(env_path->content);
		if (!s_env_path)
		{
			ft_free_tabstr(s_env_path);
			return (NULL);
		}
		i++;
		env_path = env_path->next;
	}
	s_env_path[i] = ft_strdup("\0");
	return (s_env_path);
}
