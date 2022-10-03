/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:12:08 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/03 01:47:42 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int  g_val_exit;

/* 
** typedef void (*sighandler_t)(int);
** sighandler_t signal(int signum, sighandler_t handler);

** signal() installe le gestionnaire handler pour le signal signum. 
** handler peut être SIG_IGN, SIG_DFL 
** ou l'adresse d'une fonction définie par le programmeur 
** (un « gestionnaire de signal »).
*/

/*  rl_replace_line(const char *text, int clear_undo) Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
        -> en gros si on ne replace pas line par "" ca redisplay la commande qu'on avait (éventuellement) commencé à taper
    rl_on_new_line(void) Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
        -> permet de reafficher le prompt
    rl_redisplay() Change what’s displayed on the screen to reflect the current contents of rl_line_buffer (le texte qu'on a mis dans rl_replace_line). 
        -> permet de reafficher le prompt directement (sinon il ne s'affiche que lorsque l'on commence à tapper une nouvelle commande)*/

/* interractive mode signal handling */

// void	sig_int_child(int sig)
// {
// 	(void)sig;
// 	ft_free_data_child(data);
// 	ft_close_std();
// 	exit(130);
// }

void	sig_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_val_exit = 1;
}

void	sig_quit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	g_val_exit = 131;
}

void	ft_signal(t_data *data, int signum, t_sighandler handler)
{
	if (signal(signum, handler) == SIG_ERR)
	{
		g_val_exit = errno;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		//ft_exitmsg(data, "");
        ft_msg(g_val_exit, "minishell: ", "", "error\n");
        ft_free_cmd(&(data->cmd));// A AJUSTER
        ft_clean_cmdline(data);
        ft_clean_cmdline(data);
        rl_clear_history();
        ft_clean_loop(data);
	}
}

void	ft_init_signals(t_data *data)
{
    // ft_w_signal(data, SIGHUP, SIG_IGN);
	// ft_w_signal(data, SIGTERM, SIG_IGN);
	// ft_w_signal(data, SIGTTIN, SIG_IGN);
	// ft_w_signal(data, SIGTTOU, SIG_IGN);
	// ft_w_signal(data, SIGTSTP, SIG_IGN);
	ft_signal(data, SIGQUIT, SIG_IGN); // SIG_IGN = signal ignore (macro de la lib signal.h)
	ft_signal(data, SIGINT, sig_int);
}