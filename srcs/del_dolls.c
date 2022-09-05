/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dolls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/05 17:07:36 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_undoll_cmd_len(char *raw_cmd)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = ft_strlen(raw_cmd);
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
		{
			c = raw_cmd[i];
			i++;
			while (raw_cmd[i] && raw_cmd[i] != c)
			{
				if (raw_cmd[i] == '$' && c == 34)
				{
					i++;
					while (raw_cmd[i] && raw_cmd[i] == '$')
					{
						len--;
						i++;
					}
					if (ft_isdigit(raw_cmd[i]))
						len -= 2;
				}
				i++;
			}
		}
		else if (raw_cmd[i] == '$')
		{
			i++;
			while (raw_cmd[i] && raw_cmd[i] == '$')
			{
				len--;
				i++;
			}
			if (raw_cmd[i] == 39 || raw_cmd[i] == 34)
				len--;//on enlève le dernier $
			else if (ft_isdigit(raw_cmd[i]))
			{
				len -= 2;
				i++;
			}
			else if (raw_cmd[i] && raw_cmd[i] == '?')
				i++;
			i--;
		}
		i++;
	}
	return (len);
}

char	*ft_fill_undoll_cmd(char *raw_cmd, int len)
{
	char	*undoll_cmd;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	undoll_cmd = malloc(sizeof(char) * (len + 1));
	if (!undoll_cmd)
		return (NULL);// FREE TOUT CE QU IL Y A A FREE
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
		{
			c = raw_cmd[i];
			undoll_cmd[j] = raw_cmd[i];
			i++;
			j++;
			while (raw_cmd[i] && raw_cmd[i] != c)
			{
				if (raw_cmd[i] == '$' && c == 34)
				{
					i++;
					while (raw_cmd[i] != c && raw_cmd[i] == '$')
						i++;
					if (raw_cmd[i] == '?')
					{
						undoll_cmd[j] = '$';
						j++;
						undoll_cmd[j] = raw_cmd[i];
						j++;
					}
					else if (ft_isdigit(raw_cmd[i]) == 0 && raw_cmd[i] != c)
					{
						undoll_cmd[j] = '$';
						j++;
						undoll_cmd[j] = raw_cmd[i];
						j++;
					}
					else if (raw_cmd[i] == c)
					{
						undoll_cmd[j] = '$';
						j++;
						undoll_cmd[j] = raw_cmd[i];
						j++;
					}
				}
				else
				{
					undoll_cmd[j] = raw_cmd[i];
					j++;
				}
				i++;
			}
			if (raw_cmd[i] == c)
			{
				undoll_cmd[j] = c;
				j++;
			}
		}
		else if (raw_cmd[i] == '$')
		{
			i++;
			while (raw_cmd[i] && raw_cmd[i] == '$')
				i++;
			if (raw_cmd[i] == 39 || raw_cmd[i] == 34)
				i--;//on enlève le dernier $
			else if (!ft_isdigit(raw_cmd[i]) && raw_cmd[i] != '\0')
			{
				undoll_cmd[j] = '$';
				j++;
				undoll_cmd[j] = raw_cmd[i];
				j++;
			}
		}
		else
		{
			undoll_cmd[j] = raw_cmd[i];
			j++;
		}
		i++;
	}
	undoll_cmd[j] = '\0';
	return (undoll_cmd);
}

int	ft_del_dolls(t_data *data)
{
	t_cmd	*cmd;
	int		undoll_len;

	undoll_len = 0;
	cmd = data->cmd;
	while (cmd)
	{
		undoll_len = ft_undoll_cmd_len(cmd->raw_cmd);
		printf("len de del_dolls = %d\n", undoll_len);
		cmd->undoll_cmd = ft_fill_undoll_cmd(cmd->raw_cmd, undoll_len);
		if (!cmd->undoll_cmd)
			return (1);
		printf("val undoll_cmd = %s\n", cmd->undoll_cmd);
		cmd = cmd->next;
	}
	return (0);
}
