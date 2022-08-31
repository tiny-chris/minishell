/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/31 15:56:56 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 1 && !argv[1])
	{
		data.env = NULL;
		data.val_exit = 0;
		data.env = ft_get_env(envp);
		data.prompt = ft_strdup("minishell> ");
		data.built_in = ft_built_in();
		//while (1)
		{
			data.line = readline(data.prompt);
			add_history(data.line);
			data.nb_pipes = ft_count_pipe(data.line);
			//printf("nb pipes = %d\n", data.nb_pipes);
			if (ft_lexer(data.line))
			{// msg : syntax error et exit status = 2
				//printf("ft_lexer = %d\n", ft_lexer(data.line));
				ft_putendl_fd(ERRSTX, 2);
				data.val_exit = 2;
				printf("exit status %d\n", data.val_exit);
			}
			else
			{
				data.cmd = ft_get_commands(&data);
				ft_del_quotes(&data);
				ft_expand(&data);
				ft_tokenizer(&data);
				ft_free_cmd(&(data.cmd));
			}
			free(data.line);
		}
		ft_free_tabstr(data.built_in);
		rl_clear_history();
		free(data.prompt);
		ft_free_env(&(data.env));
	}
	return (1);
}
