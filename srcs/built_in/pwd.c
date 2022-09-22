/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:12:40 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/22 15:13:34 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	<SUMMARY> pwd built-in
**	Returns the current work directory absolute path
**	<PARAM>		{t_data *}	data --> to get the char *cwd (initialised at
**				the launch of minishell & updated when using 'cd' built-in)
**	<RETURNS>	0 as success
**	<REMARK>	this function should not fail (always return 0)
*/
int	ft_pwd(t_data *data)
{
	data->val_exit = 0;
	printf("%s\n", data->cwd);
	return (0);
}
