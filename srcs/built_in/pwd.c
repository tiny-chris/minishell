/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:12:40 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/27 15:35:50 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_pwd(t_data *data)
{
	if (data->cwd_err == 1)
		g_val_exit = ft_msg(1, ERRCWD, "", "");
	else
	{
		g_val_exit = 0;
		ft_putendl_fd(data->cwd, STDOUT_FILENO);
	}
	return (g_val_exit);
}
