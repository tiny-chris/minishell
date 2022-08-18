/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/18 12:28:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env	*env;

	env = NULL;
	if (argc == 1 && !argv[1])
	{
		env = ft_get_env(envp);
		printf("env %s", env[0].var);/////
		prompt = ft_strdup("minishell> ");
		while (1)
		{
			line = readline(prompt);
			add_history(line);
			free(line);
		}
		rl_clear_history();
		free(prompt);
		ft_free_env(&env);
	}
	return (1);
}
