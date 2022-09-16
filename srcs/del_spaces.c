/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:32:00 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/16 09:13:35 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	***** PARSING | unspace_cmd - LEN *****
**	<SUMMARY>
**	Defines the length of the new string (unspace_cmd) by removing useless
**	spaces
**	<PARAM>		{char *} raw_cmd --> from get_commands.c
**	<RETURNS>	the size of the new string to be copied unspace_cmd (int)
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

/*	***** PARSING | unspace_cmd - CONTENT *****
**	<SUMMARY>
**	Creates the new string to be copied as 'unspace_cmd' in the t_cmd
**	'cmd' linked list
**	<PARAM>		{char *} raw_cmd
				{int} len --> previously calculated len
**	<RETURNS>	the new string value (char *) without useless spaces
*/


// TO BE NORMED
char	*ft_fill_unspace_cmd(char *raw_cmd, int len)
{
	char	*unspace_cmd;//raw_cmd_no_space;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	unspace_cmd = malloc(sizeof(char) * (len + 1));
	if (!unspace_cmd)
		return (NULL); // free tout ce qu'il y a à free
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
		{
			c = raw_cmd[i];
			unspace_cmd[j] = raw_cmd[i];
			i++;
			j++;
			while (raw_cmd[i] != c)
			{
				unspace_cmd[j] = raw_cmd[i];
				i++;
				j++;
			}
			unspace_cmd[j] = raw_cmd[i];
			j++;
		}
		else if (raw_cmd[i] == ' ')
		{
			unspace_cmd[j] = raw_cmd[i];
			i++;
			j++;
			while (raw_cmd[i] && raw_cmd[i] == ' ')
				i++;
			i--;
		}
		else if (raw_cmd[i] == '>' || raw_cmd[i] == '<')
		{
			c = raw_cmd[i];
			unspace_cmd[j] = raw_cmd[i];
			i++;
			j++;
			if (raw_cmd[i] == c)
			{
				unspace_cmd[j] = raw_cmd[i];
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
			unspace_cmd[j] = raw_cmd[i];
			j++;
		}
		i++;
	}
	unspace_cmd[j] = '\0';
	return (unspace_cmd);
}

/*	***** PARSING | unspace_cmd *****
**	<SUMMARY>
**	Gets an updated cmd with unnecessary spaces (unspace_cmd) in 2 steps:
**	1. Defines the length of the new string by removing useless spaces
**	2. Copies the matching string in 'unspace_cmd' of the t_cmd 'cmd'
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
		cmd->unspace_cmd = ft_fill_unspace_cmd(cmd->raw_cmd, len);
		if (!cmd->unspace_cmd)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!
		dprintf(2, "unspace cmd    = %s --> len = %d vs. strlen = %ld\n", cmd->unspace_cmd, len, ft_strlen(cmd->raw_cmd));//
		cmd = cmd->next;
	}
	return (0);
}
