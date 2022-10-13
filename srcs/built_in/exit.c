/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:41:59 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/13 16:00:25 by cgaillag         ###   ########.fr       */
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

// static void	ft_tmp_free(t_data *data) // fonction a supprimer remplacee par ft_handle_malloc
// {
// 	ft_free_cmd(&(data->cmd)); // A AJUSTER
// 	ft_clean_cmdline(data);
// 	ft_clean_cmdline(data);
// 	rl_clear_history();
// 	ft_clean_loop(data);
// 	free(data->pid);
// }

int	ft_exit(t_cmd *cmd, t_data *data, int flag)
{
	t_token			*token;
	char			*check;
	long long int	ret;

	(void) data;// supprimer des paramètres de la fonction
	token = cmd->token->next; // le token apres exit
	ret = 0;
	check = NULL;
	if (token == NULL) // exit sans argument
	{
		ft_putstr_fd("exit\n", 1);
		if (data->nb_pipes == 0 && data->cmd->tok_redir)
		{
			if (ft_redirect_std(data->cmd) == -1)
			{
				g_val_exit = errno;
				ft_msg(errno, ERRMSG, "", strerror(errno));
				ft_handle_malloc(0, NULL, 0, NULL);
				rl_clear_history();
				exit(errno);
			}
			
		}
		ft_handle_malloc(0, NULL, 0, NULL); // a uncomment
		rl_clear_history(); // a uncomment
		exit(EXIT_SUCCESS);
	}
	if (ft_check_digit(token->token) == 0)
	{
		g_val_exit = ft_msg(2, "exit\n", "exit: ", "numeric argument required");
		if (data->nb_pipes == 0 && data->cmd->tok_redir)
		{
			if (ft_redirect_std(data->cmd) == -1)
			{
				g_val_exit = errno;
				ft_msg(errno, ERRMSG, "", strerror(errno));
				ft_handle_malloc(0, NULL, 0, NULL);
				rl_clear_history();
				exit(errno);
			}
			
		}
		ft_handle_malloc(0, NULL, 0, NULL);
		rl_clear_history();
		exit(g_val_exit);
	}
	if (token->next)
		return (ft_msg(1, "exit\n", "exit: ", "too many arguments"));
	ret = ft_atoi(token->token);
	check = ft_itoa(ret);
	ft_handle_malloc(flag + TAB_STR1, check, 0, data);
	if (ft_strncmp(check, token->token, ft_strlen(check)))
	{
		g_val_exit = ft_msg(2, "exit\n", "exit: ", "numeric argument required");
		if (data->nb_pipes == 0 && data->cmd->tok_redir)
		{
			if (ft_redirect_std(data->cmd) == -1)
			{
				g_val_exit = errno;
				ft_msg(errno, ERRMSG, "", strerror(errno));
				ft_handle_malloc(0, NULL, 0, NULL);
				rl_clear_history();
				exit(errno);
			}
		}
		ft_handle_malloc(0, NULL, 0, NULL);
		rl_clear_history();
		exit(g_val_exit);
	}
	if (data->nb_pipes == 0 && data->cmd->tok_redir)
	{
		if (ft_redirect_std(data->cmd) == -1)
		{
			g_val_exit = errno;
			ft_msg(errno, ERRMSG, "", strerror(errno));
			ft_handle_malloc(0, NULL, 0, NULL);
			rl_clear_history();
			exit(errno);
		}
	}
	ft_handle_malloc(0, NULL, 0, NULL);
	rl_clear_history();
	exit(ret);
}
