/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:40:34 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/30 12:44:10 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/*	<SUMMARY> Checks if absolute path as a directory & its access (cont'd)
*/

char	*ft_path_last_slash(char *full_path, char *tmp)
{
	int	len;

	len = ft_strlen(full_path);
	while (len > 0 && full_path[len - 1] && full_path[len - 1] != '/')
	{
		if (full_path[len - 1] && full_path[len - 1] != '/')
			len--;
	}
	if (len > 0)
	{
		tmp = ft_substr(full_path, 0, len);
		ft_handle_malloc(ADD_C + TAB_STR1, tmp, 0, NULL);
	}
	return (tmp);
}
