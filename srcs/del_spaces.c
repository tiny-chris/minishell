/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:32:00 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/06 18:00:22 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_del_spaces(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	cmd = data->cmd;
	while (cmd)
	{
		len = ft_unspace_cmd_len(cmd->raw_cmd);
		dprintf(2, "raw cmd len = %ld\n", ft_strlen(cmd->raw_cmd));
		dprintf(2, "len = %d\n", len);
		cmd->raw_cmd_no_space = ft_fill_unspace_cmd(cmd->raw_cmd, len);
		if (!cmd->raw_cmd_no_space)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!
		dprintf(2, "raw cmd no space = %s\n", cmd->raw_cmd_no_space);
		cmd = cmd->next;
	}
	return (0);
}
