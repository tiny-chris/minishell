/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:34:00 by clem              #+#    #+#             */
/*   Updated: 2022/07/13 10:35:28 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_status = 0;

/*
 ** Interactive mode signals handling
 */

static void	ft_sigint(int sig)
{
	g_sig_status = 128 + sig;
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_init_signals(t_data *data)
{
	ft_w_signal(data, SIGHUP, SIG_IGN);
	ft_w_signal(data, SIGTERM, SIG_IGN);
	ft_w_signal(data, SIGTTIN, SIG_IGN);
	ft_w_signal(data, SIGTTOU, SIG_IGN);
	ft_w_signal(data, SIGTSTP, SIG_IGN);
	ft_w_signal(data, SIGQUIT, SIG_IGN);
	ft_w_signal(data, SIGINT, ft_sigint);
}

/*
 ** Init data.
 */

static void	ft_init_data(t_data *data)
{
	extern char		**environ;
	extern int		g_sig_status;

	data->cmdid = 0;
	data->cmdcount = 0;
	data->cwd = NULL;
	data->oldcwd = NULL;
	data->cmd_path = NULL;
	data->envtab = NULL;
	data->cmdline = NULL;
	data->environ = environ;
	data->toklist = NULL;
	data->cmdlist = NULL;
	data->envlist = NULL;
	data->explist = NULL;
	data->redlist = NULL;
	data->cmd_path = NULL;
	g_sig_status = 0;
	data->toggle = 0;
	data->cwd = ft_w_getcwd(data);
	data->oldcwd = ft_w_getcwd(data);
}

/*
 ** Main.
 */

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1)
	{
		ft_init_data (&data);
		ft_init_signals (&data);
		ft_init_env (&data);
		ft_init_exp (&data);
		ft_shlvl_update (&data);
		ft_prompt (&data);
	}
	else
	{
		write (2, "minishell: ", 11);
		write (2, av[1], ft_strlen(av[1]));
		write (2, ": No such file or directory\n", 28);
		g_sig_status = 127;
	}
	return (g_sig_status);
}
