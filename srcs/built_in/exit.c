/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:41:59 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/07 18:07:29 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static int	ft_check_digit(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	if (token[i] == '+' || token[i] == '-')
		i++;
	if (token[i])
	{
		while (token[i])
		{
			if (ft_isdigit(token[i]) == 0)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	ft_tmp_free(t_data *data) // fonction a supprimer remplacee par ft_handle_malloc
{
	ft_free_cmd(&(data->cmd)); // A AJUSTER
	ft_clean_cmdline(data);
	ft_clean_cmdline(data);
	rl_clear_history();
	ft_clean_loop(data);
	free(data->pid);
	if (data->pipe_fd)
		ft_free_tabint(data->pipe_fd, data->nb_pipes);
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	t_token			*token;
	char			*check;
	long long int	ret;

	token = cmd->token->next; // le token apres exit
	ret = 0;
	check = NULL;
	if (token == NULL) // exit sans argument
	{
		// ft_handle_malloc(0, NULL, 0, 0); // a uncomment
		// rl_clear_history(); // a uncomment
		ft_putstr_fd("exit\n", 1);
		if (data->nb_pipes == 0 && data->cmd->tok_redir)
			ft_redirect_std(data->cmd);
		ft_tmp_free(data); // free temporaire
		exit(EXIT_SUCCESS);
	}
	if (ft_check_digit(token->token) == 0)
	{
		g_val_exit = ft_msg(2, "exit\n", "exit: ", "numeric argument required");
		if (data->nb_pipes == 0 && data->cmd->tok_redir)
			ft_redirect_std(data->cmd);
		ft_tmp_free(data);
		exit(g_val_exit);
	}
	if (token->next)
		return (ft_msg(1, "exit\n", "exit: ", "too many arguments"));
	ret = ft_atoi(token->token);
	check = ft_itoa(ret);
	if (ft_strncmp(check, token->token, ft_strlen(check)))
	{
		g_val_exit = ft_msg(2, "exit\n", "exit: ", "numeric argument required");
		if (data->nb_pipes == 0 && data->cmd->tok_redir)
			ft_redirect_std(data->cmd);
		ft_tmp_free(data); // free temporaire
		free(check); // a ajuster avec ft_handle malloc
		exit(g_val_exit);
	}
	// ft_handle_malloc(0, NULL, 0, 0);
	// rl_clear_history(); // a uncomment
	printf("test avant \n");
	if (data->nb_pipes == 0 && data->cmd->tok_redir)
	{
		printf("test rentre dans le if\n");
		ft_redirect_std(data->cmd);
	}
	ft_tmp_free(data); // free temporaire
	free(check); // a ajuster avec ft_handle malloc
	exit(ret);
}
