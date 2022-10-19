/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:12:08 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 21:20:21 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

void	sig_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_val_exit = 130;
}

void	sig_quit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	g_val_exit = 131;
}

void	ft_signal(t_data *data, int signum, t_sighandler handler)
{
	(void) data;
	if (signal(signum, handler) == SIG_ERR)
	{
		g_val_exit = errno;
		ft_msg(g_val_exit, "minishell: ", "error: ", strerror(errno));
		rl_clear_history();
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (42);
	}
}

void	ft_init_signals(t_data *data)
{
	ft_signal(data, SIGHUP, SIG_IGN);
	ft_signal(data, SIGTERM, SIG_IGN);
	ft_signal(data, SIGTTIN, SIG_IGN);
	ft_signal(data, SIGTTOU, SIG_IGN);
	ft_signal(data, SIGTSTP, SIG_IGN);
	ft_signal(data, SIGQUIT, SIG_IGN);
	ft_signal(data, SIGINT, sig_int);
}
