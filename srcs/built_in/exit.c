/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:41:59 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/24 15:32:08 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static void	ft_exit_no_args(t_data *data)
{
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

static void	ft_exit_no_numeric_arg(t_data *data)
{
	g_val_exit = ft_msg(2, "", "exit: ", "numeric argument required");
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

static void	ft_exit_no_error(t_data *data, long long int ret)
{
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

int	ft_exit(t_cmd *cmd, t_data *data, int flag)
{
	t_token			*token;
	char			*check;
	char			*check2;
	long long int	ret;

	token = cmd->token->next;
	ret = 0;
	check = NULL;
	if (data->nb_pipes == 0)
		ft_putstr_fd("exit\n", 1);
	if (token == NULL)
		ft_exit_no_args(data);
	if (ft_check_digit(token->token) == 0)
		ft_exit_no_numeric_arg(data);
	if (token->next)
		return (ft_msg(1, "", "exit: ", "too many arguments"));
	ret = ft_atoi(token->token);
	check = ft_itoa(ret);
	ft_handle_malloc(flag + TAB_STR1, check, 0, data);
	check2 = ft_get_check2(token->token, flag, data);
	if (ft_strncmp(check, check2, ft_strlen(check)))
		ft_exit_no_numeric_arg(data);
	ft_exit_no_error(data, ret);
	return (0);
}
