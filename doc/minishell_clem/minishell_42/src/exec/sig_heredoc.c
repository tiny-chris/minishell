/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:41:55 by athirion          #+#    #+#             */
/*   Updated: 2022/06/29 20:44:53 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_sigint(int sig)
{
	extern int	g_sig_status;

	g_sig_status = (128 + sig);
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_heredoc_signals(t_data *data)
{
	ft_w_signal(data, SIGHUP, SIG_IGN);
	ft_w_signal(data, SIGTERM, SIG_IGN);
	ft_w_signal(data, SIGTTIN, SIG_IGN);
	ft_w_signal(data, SIGTTOU, SIG_IGN);
	ft_w_signal(data, SIGTSTP, SIG_IGN);
	ft_w_signal(data, SIGQUIT, SIG_IGN);
	ft_w_signal(data, SIGINT, ft_heredoc_sigint);
}
