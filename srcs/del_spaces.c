/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:32:00 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/14 09:55:11 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	***** PARSING | raw_cmd_no_space - LEN *****
**	<SUMMARY>
**	Defines the length of the new string (raw_cmd_no_space) by removing useless
**	spaces
**	<PARAM>		{char *} raw_cmd --> from get_commands.c
**	<RETURNS>	the size of the new string to be copied raw_cmd_no_space (int)
*/


// TO BE NORMED
int	ft_unspace_cmd_len(char	*raw_cmd)
{
	int		len;
	int		i;
	char	c;

	len = ft_strlen(raw_cmd);
	i = 0;
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
		{
			c = raw_cmd[i];
			i++;
			while (raw_cmd[i] && raw_cmd[i] != c)
				i++;
		}
		else if (raw_cmd[i] == ' ')
		{
			i++;
			while (raw_cmd[i] && raw_cmd[i] == ' ')
			{
				len--;
				i++;
			}
			i--;
		}
		else if (raw_cmd[i] == '>' || raw_cmd[i] == '<')
		{
			c = raw_cmd[i];
			i++;
			if (raw_cmd[i] == c)
				i++;
			if (raw_cmd[i] == ' ')
			{
				i++;
				len--;
				while (raw_cmd[i] && raw_cmd[i] == ' ')
				{
					len--;
					i++;
				}
				i--;
			}
			else
				i--;
		}
		i++;
	}
	return (len);
}

/*	***** PARSING | raw_cmd_no_space - CONTENT *****
**	<SUMMARY>
**	Creates the new string to be copied as 'raw_cmd_no_space' in the t_cmd
**	'cmd' linked list
**	<PARAM>		{char *} raw_cmd
				{int} len --> previously calculated len
**	<RETURNS>	the new string value (char *) without useless spaces
*/


// TO BE NORMED
char	*ft_fill_unspace_cmd(char *raw_cmd, int len)
{
	char	*raw_cmd_no_space;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	raw_cmd_no_space = malloc(sizeof(char) * (len + 1));
	if (!raw_cmd_no_space)
		return (NULL); // free tout ce qu'il y a à free
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
		{
			c = raw_cmd[i];
			raw_cmd_no_space[j] = raw_cmd[i];
			i++;
			j++;
			while (raw_cmd[i] != c)
			{
				raw_cmd_no_space[j] = raw_cmd[i];
				i++;
				j++;
			}
			raw_cmd_no_space[j] = raw_cmd[i];
			j++;
		}
		else if (raw_cmd[i] == ' ')
		{
			raw_cmd_no_space[j] = raw_cmd[i];
			i++;
			j++;
			while (raw_cmd[i] && raw_cmd[i] == ' ')
				i++;
			i--;
		}
		else if (raw_cmd[i] == '>' || raw_cmd[i] == '<')
		{
			c = raw_cmd[i];
			raw_cmd_no_space[j] = raw_cmd[i];
			i++;
			j++;
			if (raw_cmd[i] == c)
			{
				raw_cmd_no_space[j] = raw_cmd[i];
				i++;
				j++;
			}
			if (raw_cmd[i] == ' ')
			{
				i++;
				while (raw_cmd[i] && raw_cmd[i] == ' ')
					i++;
				i--;
			}
			else
				i--;
		}
		else
		{
			raw_cmd_no_space[j] = raw_cmd[i];
			j++;
		}
		i++;
	}
	raw_cmd_no_space[j] = '\0';
	return (raw_cmd_no_space);
}

/*	***** PARSING | raw_cmd_no_space *****
**	<SUMMARY>
**	Gets an updated cmd with unnecessary spaces (raw_cmd_no_space) in 2 steps:
**	1. Defines the length of the new string by removing useless spaces
**	2. Copies the matching string in 'raw_cmd_no_space' of the t_cmd 'cmd'
**	linked list
**	<PARAM>		{t_data *} data
**	<RETURNS>	t_cmd 'cmd' linked list --> with an additional string
**	<REMARKS>	useless spaces are those outside of closed quotes
**				- when there are consecutive spaces: keep only 1
**				- except if they are just after an unquoted redirection: delete
**					all spaces just after a redir
*/
int	ft_del_spaces(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	cmd = data->cmd;
	while (cmd)
	{
		len = ft_unspace_cmd_len(cmd->raw_cmd);
		cmd->raw_cmd_no_space = ft_fill_unspace_cmd(cmd->raw_cmd, len);
		if (!cmd->raw_cmd_no_space)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!
		dprintf(2, "raw cmd no space = %s\n", cmd->raw_cmd_no_space);
		dprintf(2, "  --> len = %d vs. strlen = %ld\n", len, ft_strlen(cmd->raw_cmd));
		cmd = cmd->next;
	}
	return (0);
}
