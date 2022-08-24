/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/24 16:47:45 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.env = NULL;
	data.val_exit = 0;
	if (argc == 1 && !argv[1])
	{
		data.env = ft_get_env(envp);
		printf("env %s", data.env[0].var);/////
		data.prompt = ft_strdup("minishell> ");
		while (1)
		{
			data.line = readline(data.prompt);
			add_history(data.line);
			if (ft_lexer(data.line) == 1)
			{// msg : syntax error et exit status = 2
				ft_putendl_fd(ERRSTX, 2);
				data.val_exit = 2;
				printf("exit status %d\n", data.val_exit);
			}
		//	ft_get_commands(data.line);
			free(data.line);
		}
		rl_clear_history();
		free(data.prompt);
		ft_free_env(&(data.env));
	}
	return (1);
}
