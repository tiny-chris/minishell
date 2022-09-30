/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:12:08 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/30 21:17:11 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int  g_val_exit;

/*  rl_replace_line(const char *text, int clear_undo) Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
        -> en gros si on ne replace pas line par "" ca redisplay la commande qu'on avait (éventuellement) commencé à taper
    rl_on_new_line(void) Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
        -> permet de reafficher le prompt
    rl_redisplay() Change what’s displayed on the screen to reflect the current contents of rl_line_buffer (le texte qu'on a mis dans rl_replace_line). 
        -> permet de reafficher le prompt directement (sinon il ne s'affiche que lorsque l'on commence à tapper une nouvelle commande)*/

void	sig_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
    g_val_exit = 1;
}

void    sig_quit(int sig)
{
    
}

// static void	display_for_blocking_cmd(int num)
// {
// 	num++;
// 	write(1, "\n", 1);
// }

// static void	quit_process(int num)
// {
// 	num++;
// 	printf("Quit (core dumped)\n");
// }

// void	signal_for_blocking_cmd(void)
// {
// 	signal(SIGINT, display_for_blocking_cmd);
// 	signal(SIGQUIT, quit_process);
// }

// void	interrupt_here_document(int signal)
// {
// 	(void)signal;
// 	write(1, "\n", 1);
// 	exit(errno);
// }