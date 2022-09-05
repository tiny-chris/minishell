/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:43:56 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/05 18:10:01 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_allspace(char *str, int i, char c)
{
	int	j;

	//j = i + 1;
	j = i;
	j++;
	if (str[j] == c)
		return (0);
	while (str[j] && str[j] != c)
	{
		if (str[j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	ft_unquote_cmd_len(char *undoll_cmd)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(undoll_cmd);
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == 34 || undoll_cmd[i] == 39)
		{
			c = undoll_cmd[i];
			if (ft_is_allspace(undoll_cmd, i, c))
				len -= 2;
			if (ft_is_allspace(undoll_cmd, i, c) && c == 34 && undoll_cmd[i + 1] == '$')
				len += 2;
			i++;
			while (undoll_cmd[i] && undoll_cmd[i] != c)
				i++;
		}
		else if (undoll_cmd[i] == ' ')
		{
			i++;
			while (undoll_cmd[i] && undoll_cmd[i] == ' ')
			{
				len--;
				i++;
			}
			i--;
		}
		else if (undoll_cmd[i] == '>' || undoll_cmd[i] == '<')
		{
			c = undoll_cmd[i];
			i++;
			if (undoll_cmd[i] == c)
				i++;
			if (undoll_cmd[i] == ' ')
			{
				i++;
				len--;
				while (undoll_cmd[i] && undoll_cmd[i] == ' ')
				{
					len--;
					i++;
				}
				i--;
			}
		}
		i++;
	}
	return (len);
}

int	ft_del_quotes(t_data *data)
{
	t_cmd	*cmd;
	int		unquote_cmd_len;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->undoll_cmd == NULL)/////chris
			return (2);// check si la commande n'est pas nulle
		unquote_cmd_len = ft_unquote_cmd_len(cmd->undoll_cmd);
		printf("len cmd unquote = %d\n", unquote_cmd_len);
		// cmd->unquote_cmd = ft_fill_unquote_cmd(cmd->undoll_cmd, unquote_cmd_len);
		// if (!cmd->unquote_cmd)
		// 	return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!!
		//printf("unquote_cmd = %s, size = %ld\n", cmd->unquote_cmd, ft_strlen(cmd->unquote_cmd));
		cmd = cmd->next;
	}
	return (0);
}
