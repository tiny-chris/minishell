/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:06 by cvidon            #+#    #+#             */
/*   Updated: 2022/07/10 11:24:26 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Check is there is a valid '-n' flag.
 */

static int	ft_is_n_flag(char *arg)
{
	size_t	i;

	if (strcmp(arg, "-n") == 0)
		return (TRUE);
	i = strlen(arg) - 1;
	if (i == 0)
		return (FALSE);
	while (i > 0 && arg[0] == '-' && arg[i] == 'n')
		i--;
	if (i == 0)
		return (TRUE);
	return (FALSE);
}

/*
 ** Tiny 'echo' builtin that handle the '-n' flag.
 */

int	ft_echo(t_data *data, char **cmd)
{
	int		i;
	int		argcount;
	int		n_flag;

	(void)data;
	n_flag = 0;
	i = 1;
	while (cmd[i] && ft_is_n_flag(cmd[i]))
		n_flag = (i++, 1);
	argcount = 0;
	while (cmd[argcount])
		argcount++;
	while (cmd[i])
	{
		write (1, cmd[i], strlen(cmd[i]));
		if (i != argcount - 1)
			write (1, " ", 1);
		i++;
	}
	if (n_flag && !cmd[2])
		;
	else if (!n_flag)
		write (1, "\n", 1);
	return (SUCCESS);
}
