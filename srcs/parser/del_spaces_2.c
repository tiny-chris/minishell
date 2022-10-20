/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spaces_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:32:00 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/20 11:46:47 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count_space_len(char *raw_cmd, int *i, int *len)
{
	if (raw_cmd[*i] == ' ')
	{
		(*i)++;
		while (raw_cmd[*i] && raw_cmd[*i] == ' ')
		{
			(*len)--;
			(*i)++;
		}
		(*i)--;
	}
}

static void	ft_count_space_redir_len(char *raw_cmd, int *i, int *len)
{
	if (raw_cmd[*i] == ' ')
	{
		(*i)++;
		(*len)--;
		while (raw_cmd[*i] && raw_cmd[*i] == ' ')
		{
			(*len)--;
			(*i)++;
		}
		(*i)--;
	}
	else
		(*i)--;
}

/*	***** PARSING | unspace_cmd - LEN *****
**	<SUMMARY> Defines the length of the new string by removing useless spaces
**	<RETURNS>	the size of the new string to be copied
*/
int	ft_unspace_cmd_len(char	*raw_cmd)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(raw_cmd);
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
			ft_count_btw_quotes(raw_cmd, &i);
		else if (raw_cmd[i] == ' ')
			ft_count_space_len(raw_cmd, &i, &len);
		else if (raw_cmd[i] == '>' || raw_cmd[i] == '<')
		{
			ft_nb_csq_redir(raw_cmd, &i, NULL);
			ft_count_space_redir_len(raw_cmd, &i, &len);
		}
		i++;
	}
	return (len);
}
