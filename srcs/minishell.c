/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/17 17:40:54 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_new_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i++);
		i++;
	}
	if ((char)c == '\0' && s[i] == '\0')
		return (0);
	return (0);
}

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
		//ft_free la liste chainee de l'env
		return (1);
	}
	equal = ft_new_strchr(envp, '=');
	// si equal == NULL ?
	new->var = ft_substr(envp, 0, equal);
	printf("new->var %s\n", new->var);
	new->content = ft_substr(envp, equal + 1, (ft_strlen(envp) - equal + 1));
	printf("new->content %s\n", new->content);
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
		ft_lstadd_env(&env, envp[i]);
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env	*env;

	if (argc == 1 && !argv[1])
	{
		env = ft_get_env(envp);
		prompt = ft_strdup("minishell> ");
		while (1)
		{
			line = readline(prompt);
			add_history(line);
			free(line);
		}
		rl_clear_history();
		free(prompt);
	//	ft_free_env(env);
	}
	return (1);
}
