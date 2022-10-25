/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:00:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/25 20:18:16 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

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
void	ft_count_btw_quotes(char *line, int *i)
{
	char	c;

	if (line[*i] && (line[*i] == 34 || line[*i] == 39))
	{
		c = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != c)
			(*i)++;
	}
}

/*	<SUMMARY> Helper function to check the number of consecutive redir
**	<RETURNS> 1 or 2, if there are redir, 0 otherwise
*/
void	ft_nb_csq_redir(char *line, int *i, int *len)
{
	char	c;

	if (line[*i] && (line[*i] == '>' || line[*i] == '<'))
	{
		c = line[*i];
		if (len)
			(*len)--;
		(*i)++;
		if (line[*i] && (line[*i] == c))
		{
			if (len)
				(*len)--;
			(*i)++;
		}
	}
}

static int	ft_get_nbredir(t_data *data)
{
	t_cmd	*cmd;
	t_token	*tok_redir;
	int		i;

	i = 0;
	cmd = data->cmd;
	tok_redir = NULL;
	while (cmd != NULL)
	{
		tok_redir = cmd->tok_redir;
		if (tok_redir)
		{
			while (tok_redir)
			{
				i++;
				tok_redir = tok_redir->next;
			}	
		}
		cmd = cmd->next;
	}
	if (i)
		i = i / 2;
	return (i);
}

/*	<SUMMARY> parses the command line - main function
*/
int	ft_parser(t_data *data)
{
	data->nb_pipes = ft_count_pipe(data->line);
	if (data->nb_pipes < 500)
	{
		data->cmd = ft_get_commands(data);
		ft_del_tabs(data);
		ft_del_spaces(data);
		ft_get_redir(data);
		ft_del_dolls(data);
		ft_expand(data);
		ft_tokenizer(data);
		ft_heredoc_path(data);
		data->nb_redir = ft_get_nbredir(data);
	}
	if (data->nb_pipes + data->nb_redir >= 500)
		g_val_exit = ft_msg(1, ERRFIL, "", "");
	return (0);
}
