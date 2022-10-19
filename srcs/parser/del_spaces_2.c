/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spaces_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:32:00 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/19 16:01:35 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | unspace_cmd - LEN *****
**	<SUMMARY> Defines the length of the new string by removing useless spaces
**	<RETURNS>	the size of the new string to be copied
*/
int	ft_unspace_cmd_len(char	*raw_cmd, int len)
{
	int		i;

	i = 0;
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
			i += ft_count_btw_quotes(raw_cmd, i);
		else if (raw_cmd[i] == ' ')
		{
			len -= ft_count_space(raw_cmd, i);
			i += ft_count_space(raw_cmd, i);
		}
		else if (raw_cmd[i] == '>' || raw_cmd[i] == '<')
		{
			i += ft_nb_csq_redir(raw_cmd, i);
			len = len - (ft_count_space(raw_cmd, i) + 1);
			i += ft_count_space(raw_cmd, i);
		}
		i++;
	}
	return (len);
}
