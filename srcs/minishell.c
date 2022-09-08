/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/08 15:02:48 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && ft_isdigit(line[i + 1]))
			i++;
		else if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

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
		data.str_exit = NULL;
		while (1)
		{
			data.line = readline(data.prompt);
			data.str_exit = NULL;
			if (data.line && ft_strlen(data.line) != 0 && ft_only_space(data.line) == 1)
			{
				add_history(data.line);
				//printf("nb pipes = %d\n", data.nb_pipes);
				if (ft_lexer(data.line))
				{// msg : syntax error et exit status = 2
					//printf("ft_lexer = %d\n", ft_lexer(data.line));
					ft_putendl_fd(ERRSTX, 2);
					data.val_exit = 2;
					//printf("exit status %d\n", data.val_exit);
				}
				else
				{
					data.nb_pipes = ft_count_pipe(data.line);
					data.cmd = ft_get_commands(&data);//separation des commandes en fonction du nb de pipes
					ft_del_spaces(&data);
					ft_get_redir(&data);
					ft_del_dolls(&data);
					ft_del_quotes(&data);
					ft_expand(&data);
					ft_tokenizer(&data);
					ft_free_cmd(&(data.cmd));
				}
				free(data.line);
				if (data.str_exit)
					free(data.str_exit);
			}
		}
		ft_free_tabstr(data.built_in);
		rl_clear_history();
		free(data.prompt);
		ft_free_env(&(data.env));
	}
	// penser à faire un message d'erreur si nb d'arg incorrect
	return (1);
}
