/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dolls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/07 10:27:54 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_undoll_cmd_len(char *no_redir_cmd)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = ft_strlen(no_redir_cmd);
	while (no_redir_cmd[i])
	{
		if (no_redir_cmd[i] == 34 || no_redir_cmd[i] == 39)
		{
			c = no_redir_cmd[i];
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] != c)
			{
				if (no_redir_cmd[i] == '$' && c == 34)
				{
					i++;
					while (no_redir_cmd[i] && no_redir_cmd[i] == '$')
					{
						len--;
						i++;
					}
					if (ft_isdigit(no_redir_cmd[i]))
						len -= 2;
					else if (no_redir_cmd[i] == c)
						i--;
				}
				i++;
			}
		}
		else if (no_redir_cmd[i] == '$')
		{
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] == '$')
			{
				len--;
				i++;
			}
			if (no_redir_cmd[i] == 39 || no_redir_cmd[i] == 34)
				len--;//on enlève le dernier $
			else if (ft_isdigit(no_redir_cmd[i]))
			{
				len -= 2;
				i++;
			}
			else if (no_redir_cmd[i] && no_redir_cmd[i] == '?')
				i++;
			i--;
		}
		i++;
	}
	return (len);
}

char	*ft_fill_undoll_cmd(char *no_redir_cmd, int len)
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
	while (no_redir_cmd[i])
	{
		if (no_redir_cmd[i] == 34 || no_redir_cmd[i] == 39)
		{
			c = no_redir_cmd[i];
			undoll_cmd[j] = no_redir_cmd[i];
			i++;
			j++;
			while (no_redir_cmd[i] && no_redir_cmd[i] != c)
			{
				if (no_redir_cmd[i] == '$' && c == 34)
				{
					i++;
					while (no_redir_cmd[i] != c && no_redir_cmd[i] == '$')
						i++;
					if (no_redir_cmd[i] == '?')
					{
						undoll_cmd[j] = '$';
						j++;
						undoll_cmd[j] = no_redir_cmd[i];
						j++;
					}
					else if (ft_isdigit(no_redir_cmd[i]) == 0 && no_redir_cmd[i] != c)
					{
						undoll_cmd[j] = '$';
						j++;
						undoll_cmd[j] = no_redir_cmd[i];
						j++;
					}
					else if (no_redir_cmd[i] == c)
					{
						undoll_cmd[j] = '$';
						j++;
						i--;
					}
				}
				else
				{
					undoll_cmd[j] = no_redir_cmd[i];
					j++;
				}
				i++;
			}
			if (no_redir_cmd[i] == c)
			{
				undoll_cmd[j] = c;
				j++;
			}
		}
		else if (no_redir_cmd[i] == '$')
		{
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] == '$')
				i++;
			if (no_redir_cmd[i] == 39 || no_redir_cmd[i] == 34)
				i--;//on enlève le dernier $
			else if (!ft_isdigit(no_redir_cmd[i]))
			{
				undoll_cmd[j] = '$';
				j++;
				if (no_redir_cmd[i] != '\0')
				{
					undoll_cmd[j] = no_redir_cmd[i];
					j++;
				}
			}
		}
		else
		{
			undoll_cmd[j] = no_redir_cmd[i];
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
		undoll_len = ft_undoll_cmd_len(cmd->no_redir_cmd);
		printf("len de del_dolls = %d\n", undoll_len);
		cmd->undoll_cmd = ft_fill_undoll_cmd(cmd->no_redir_cmd, undoll_len);
		if (!cmd->undoll_cmd)
			return (1);
		printf("val undoll_cmd = %s\n", cmd->undoll_cmd);
		cmd = cmd->next;
	}
	return (0);
}
