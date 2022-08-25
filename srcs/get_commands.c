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

#include "../includes/minishell.h"

int	ft_get_pipe(char *line, int i)
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

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	t_cmd	*node;

	if (!lst)
		return (0);
	node = lst;
	while (node->next)
		node = node->next;
	return (node);
}

int	ft_lstadd_cmd(t_cmd **cmd, char *cmdline)
{
	t_cmd	*new;
	t_cmd	*last;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		//ft_free_cmd(cmd);// A FAIRE !!
		return (1);
	}
	new->raw_cmd = ft_strdup(cmdline);
	printf("raw cmd = %s\n", new->raw_cmd);
	new->clean_cmd = NULL;
	new->next = NULL;
	if (ft_lstlast_cmd(*cmd) == 0)
	{
		*cmd = new;
		return (0);
	}
	last = ft_lstlast_cmd(*cmd);
	last->next = new;
	return (0);
}

char	*ft_get_cmdline(t_data *data, int i)
{
	char	*cmdline;
	char	*tmp;

	cmdline = NULL;
	tmp = NULL;
	tmp = ft_substr(data->line, i, ft_get_pipe(data->line, i));
	if (!tmp)
		return (NULL);//free tous les malloc
	cmdline = ft_strtrim(tmp, " ");
	if (!cmdline)
		return (NULL);//free tous les malloc
	free(tmp);
	return (cmdline);
}

int	ft_next_pipe(char *line, int i)
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

/*	substr et strtrim
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
		tmp = ft_get_cmdline(data, i);
		if (ft_lstadd_cmd(&cmd, tmp) == 1)
			return (NULL);
		i = ft_next_pipe(data->line, i);
		free(tmp);
		nb_cmd--;
	}
	return (cmd);
}

void	ft_lstdelone_cmd(t_cmd *node)
{
	if (!node)
		return ;
	free(node->raw_cmd);
	node->raw_cmd = NULL;
	free(node->unquote_cmd);
	node->unquote_cmd = NULL;
	free(node->clean_cmd);
	node->clean_cmd = NULL;
	node->next = NULL;
	free(node);
}

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!*cmd)
		return ;
	while (*cmd != NULL)
	{
		tmp = (*cmd)->next;
		ft_lstdelone_cmd(*cmd);
		(*cmd) = tmp;
	}
	(*cmd) = NULL;
}
