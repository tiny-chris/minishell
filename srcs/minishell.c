/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/25 18:18:52 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_val_exit;

void	ft_minishell(t_data *data)
{
	if (ft_lexer(data->line))
		g_val_exit = ft_msg(2, "", "", ERRSTX);
	else
	{
		ft_parser(data);
		if (data->nb_pipes < 500)
		{
			ft_exec(data);
			ft_free_cmd(&(data->cmd));	
		}
	}
	if (data != NULL)
	{
		if (data->line)
			ft_handle_malloc(DELONE, data->line, 0, NULL);
		if (data->str_exit)
			ft_handle_malloc(DELONE, data->str_exit, 0, NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 1 && !argv[1])
	{
		if (ft_init_data_1(&data, envp))
			return (1);
		while (1)
		{
			ft_init_signals(&data);
			data.line = readline(data.prompt);
			if (!data.line)
				ft_exit_ctrl_d(&data);
			if (data.line && ft_strlen(data.line) != 0)
			{
				add_history(data.line);
				ft_minishell(&data);
			}
		}
		rl_clear_history();
		ft_handle_malloc(0, NULL, 0, NULL);
		return (0);
	}
	ft_msg(1, "minishell", ": ", ERRARC);
	return (1);
}
