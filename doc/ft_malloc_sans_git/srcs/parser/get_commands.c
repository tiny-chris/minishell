/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:32:07 by cgaillag          #+#    #+#             */
/*   Updated: 2022/08/24 16:32:07 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_pipe(char *line, int i)
{
	int		len;
	int		j;
	char	c;

	len = 0;
	j = i;
	while (line[j])
	{
		if (line[j] == 34 || line[j] == 39)
		{
			c = line[j];
			j++;
			len++;
			while (line[j] != c)
			{
				j++;
				len++;
			}
		}
		else if (line[j] == '|')// || line[j] == '\0')
			return (len);
		j++;
		len++;
	}
	return (len);
}

/*	***** PARSING | raw_cmd *****
**	<SUMMARY>
**	Two steps:
**	1. Gets the command from the command line starting from index i until next
**	unquoted pipe (or end of command line) via static function: ft_get_pipe()
**	2. Removes any space at both ends of the command via ft_strtrim() function
**	<PARAM>		{t_data *} data
**				{int} i --> index position to start the copy
**	<RETURNS>	the string "raw_cmd" (to be included in the linked list cmd)
*/

//update with more relevant name: 'raw_cmd / cmd' rather than 'cmdmline'
//char	*ft_get_cmdline(t_data *data, int i)



char	*ft_get_raw_cmd(t_data *data, int i)
{
	char	*cmd;
	char	*tmp;

	cmd = NULL;
	tmp = NULL;
	tmp = ft_substr(data->line, i, ft_get_pipe(data->line, i));
	if (!tmp)
		return (NULL);//free tous les malloc
	cmd = ft_strtrim(tmp, " ");
	if (!cmd)
		return (NULL);//free tous les malloc
	free(tmp);
	return (cmd);
}

static int	ft_next_pipe(char *line, int i)
{
	int		j;
	char	c;

	j = i;
	while (line[j])
	{
		if (line[j] == 34 || line[j] == 39)
		{
			c = line[j];
			j++;
			while (line[j] != c)
				j++;
		}
		else if (line[j] == '|')
			return (j + 1);
		j++;
	}
	return (j);
}

/*	***** PARSING | raw_cmd *****
**	<SUMMARY>
**	Gets the number of commands = number of unquoted pipes + 1
**	Selects commands one by one via ft_get_raw_cmd() function and copies/add
**	each command in a node of the t_cmd 'cmd' linked list
**	<PARAM>		{t_data *} data
**	<RETURNS>	t_cmd 'cmd' linked list
**	<REMARKS>	after each created node, the index is updated to be on the
**				next pipe
*/
t_cmd	*ft_get_commands(t_data *data)
{
	int		i;
	int		nb_cmd;
	char	*tmp;
	t_cmd	*cmd;

	i = 0;
	cmd = NULL;
	nb_cmd = data->nb_pipes + 1;
	while (nb_cmd > 0)
	{
		tmp = ft_get_raw_cmd(data, i);
		dprintf(2, "raw cmd        = %s --> strlen = %ld\n", tmp, ft_strlen(tmp));
		if (ft_lstadd_cmd(&cmd, tmp) == 1)
			return (NULL);
		i = ft_next_pipe(data->line, i);
		free(tmp);
		nb_cmd--;
	}
	return (cmd);
}
