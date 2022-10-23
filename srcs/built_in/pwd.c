/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:12:40 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/23 17:36:23 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_pwd(t_data *data)
{
	g_val_exit = 0;
	ft_putendl_fd(data->cwd, STDOUT_FILENO);
	return (0);
}
