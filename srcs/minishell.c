/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/18 17:30:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env	*env;
	int		ex;

	env = NULL;
	ex = 0;
	if (argc == 1 && !argv[1])
	{
		env = ft_get_env(envp);
		printf("env %s", env[0].var);/////
		prompt = ft_strdup("minishell> ");
		while (1)
		{
			line = readline(prompt);
			add_history(line);
			if (ft_lexer(line) == 1)
			{// msg : syntax error et exit status = 2
				ft_putendl_fd(ERRSTX, 2);
				ex = 2;
				printf("ex %d\n", ex);
			}
			free(line);
		}
		rl_clear_history();
		free(prompt);
		ft_free_env(&env);
	}
	return (1);
}
