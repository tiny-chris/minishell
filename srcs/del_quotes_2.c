/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:43:56 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/07 18:18:24 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_allspace(char *str, int i, char c)
{
	int	j;

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

int	ft_contains_doll(char *undoll_cmd, int i, char c)
{
	i++;
	while (undoll_cmd[i] != c)
	{
		if (undoll_cmd[i] == '$')
			return (1);
		i++;
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
			if (ft_contains_doll(undoll_cmd, i, c) && c == 34)
				len += 2;
			i++;
			while (undoll_cmd[i] && undoll_cmd[i] != c)
				i++;
		}
		i++;
	}
	return (len);
}

static void	ft_empty_quotes_case(char *undoll_cmd, int *i, char *unquote_cmd, int *j)
{
	char	c;

	c = undoll_cmd[*i];
	unquote_cmd[*j] = undoll_cmd[*i];
	(*i)++;
	(*j)++;
	while (undoll_cmd[*i] && undoll_cmd[*i] != c)
	{
		unquote_cmd[*j] = (-1) * undoll_cmd[*i];
		(*i)++;
		(*j)++;
	}
	unquote_cmd[*j] = undoll_cmd[*i];
	(*j)++;
}

static void	ft_quotes_case(char *undoll_cmd, int *i, char *unquote_cmd, int *j)
{
	char	c;

	c = undoll_cmd[*i];
	if (ft_is_allspace(undoll_cmd, *i, c) == 0)
		ft_empty_quotes_case(undoll_cmd, i, unquote_cmd, j);
	else if (ft_contains_doll(undoll_cmd, *i, c) && c == 34)
	{
		unquote_cmd[*j] = (-1) * undoll_cmd[*i];
		(*i)++;
		(*j)++;
		while (undoll_cmd[*i] && undoll_cmd[*i] != c)
		{
			if (undoll_cmd[*i] == '$' && (undoll_cmd[*i + 1] == c || undoll_cmd[*i + 1] == ' ' || undoll_cmd[*i + 1] == '<' || undoll_cmd[*i + 1] == '>'))
				unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			else if ((undoll_cmd[*i] == '<') || (undoll_cmd[*i] == '>') || (undoll_cmd[*i] == ' '))//on garde les chevrons ?
				unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			else
				unquote_cmd[*j] = undoll_cmd[*i];
			(*i)++;
			(*j)++;
		}
		unquote_cmd[*j] = (-1) * undoll_cmd[*i];
		(*j)++;
	}
	else
	{
		(*i)++;
		if (undoll_cmd[*i] && undoll_cmd[*i] != c)
		{
			unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			(*i)++;
			(*j)++;
		}
		while (undoll_cmd[*i] && undoll_cmd[*i] != c)
		{
			if ((undoll_cmd[*i] == '$' && c == 39) || (undoll_cmd[*i] == '<') || (undoll_cmd[*i] == '>') || (undoll_cmd[*i] == ' '))
				unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			else
				unquote_cmd[*j] = undoll_cmd[*i];
			(*i)++;
			(*j)++;
		}
	}
}

char	*ft_fill_unquote_cmd(char *undoll_cmd, int len)
{
	char	*unquote_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	unquote_cmd = malloc(sizeof(char) * (len + 1));
	if (!unquote_cmd)
		return (NULL);
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == 34 || undoll_cmd[i] == 39)
			ft_quotes_case(undoll_cmd, &i, unquote_cmd, &j);
		else
		{
			unquote_cmd[j] = undoll_cmd[i];
			j++;
		}
		i++;
	}
	unquote_cmd[j] = '\0';
	return (unquote_cmd);
}

int	ft_del_quotes(t_data *data)
{
	t_cmd	*cmd;
	int		unquote_cmd_len;

	cmd = data->cmd;
	while (cmd)
	{
		unquote_cmd_len = ft_unquote_cmd_len(cmd->undoll_cmd);
		printf("len cmd unquote = %d\n", unquote_cmd_len);
		cmd->unquote_cmd = ft_fill_unquote_cmd(cmd->undoll_cmd, unquote_cmd_len);
		if (!cmd->unquote_cmd)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!!
		printf("unquote_cmd = %s, size = %ld\n", cmd->unquote_cmd, ft_strlen(cmd->unquote_cmd));
		cmd = cmd->next;
	}
	return (0);
}
