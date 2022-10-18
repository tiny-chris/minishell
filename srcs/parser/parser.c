/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:00:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/19 01:21:11 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_del_tabs(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	cmd = data->cmd;
	i = 0;
	while (cmd)
	{
		if (cmd->raw_cmd)
		{
			while (cmd->raw_cmd[i])
			{
				if (cmd->raw_cmd[i] == 9)
					cmd->raw_cmd[i] = ' ';
				i++;
			}
		}
		cmd = cmd->next;
		i = 0;
	}
	return (0);
}

/*	<SUMMARY> Helper function to go through (closing) quotes
**	<RETURNS> i, the position on the line of the closing quote (or '\0') 
*/
int	ft_count_btw_quotes(char *line, int i)
{
	int		j;
	char	c;

	j = i;
	if (line[j] == 34 || line[j] == 39)
	{
		c = line[j];
		j++;
		while (line[j] && line[j] != c)
			j++;
		return (j - i);
	}
	return (0);
}

/*	<SUMMARY> Helper function to count extra spaces (on top of 1st one)
**	<RETURNS> the number of moves to get to the new position (last ' ')
**	<REMARK> new position is just before the 1st ' ' in case of redir
**			(space on 1st position has already been cleaned)
*/
int	ft_count_space(char *line, int i)
{
	int		j;

	j = i;
	if (line[j] && line[j] == ' ')
	{
		j++;
		while (line[j] && line[j] == ' ')
			j++;
		j--;
		return (j - i);
	}
	return (0);
}

/*	<SUMMARY> Helper function to check the number of consecutive redir
**	<RETURNS> 1 or 2, if there are redir, 0 otherwise
*/
int	ft_nb_csq_redir(char *line, int i)
{
	int		j;
	char	c;

	j = i;
	if (line[j] && (line[i] == '>' || line[i] == '<'))
	{
		c = line[j];
		j++;
		if (line[j] && line[j] == ' ')
			j++;
		return (j - i);
	}
	return (0);
}


/*	<SUMMARY> parses the command line - main function
*/
int	ft_parser(t_data *data)
{
	data->nb_pipes = ft_count_pipe(data->line);
	data->cmd = ft_get_commands(data);
	ft_del_tabs(data);
	ft_del_spaces(data);
	ft_get_redir(data);
	ft_del_dolls(data);
	ft_expand(data);
	ft_tokenizer(data);
	ft_heredoc_path(data);
	return (0);
}
