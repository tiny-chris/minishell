/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:30:46 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/06 16:30:47 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**ft_init_pipe(t_data *data)
{
	int	**tab_int;
	int	i;

	//dprintf(2, "entre dans init pipe\n");
	tab_int = (int **) malloc(sizeof(int *) * data->nb_pipes);
	if (tab_int == NULL)
		return (free(tab_int), NULL);
	i = 0;
	while (i < data->nb_pipes)
	{
		tab_int[i] = (int *) malloc(sizeof(int) * 2);
		if (!tab_int[i])
		{
			ft_free_tabint(tab_int, i - 1);
			break ;
		}
		tab_int[i][0] = -1;
		tab_int[i][1] = -1;
		i++;
	}
	return (tab_int);
}

int	*ft_init_pid(t_data *data)
{
	int	*pid;
	int	i;

	i = 0;
	//dprintf(2, "entre dans init pid\n");
	pid = malloc(sizeof(int) * (data->nb_pipes + 1));
	if (!pid)
		return (NULL);//FREE TOUT ET EXIT
	while (i < (data->nb_pipes + 1))
	{
		pid[i] = -1;
		i++;
	}
	return (pid);
}

int	ft_get_files_io(t_data *data)
{
	t_cmd	*cmd;
	t_token	*tok_redir;

	cmd = data->cmd;
	tok_redir = NULL;
	//dprintf(2, "entre dans get files io\n");
	while (cmd)
	{
		tok_redir = cmd->tok_redir;
		while (tok_redir)
		{
			if (tok_redir->type == GREAT)
			{
				tok_redir = tok_redir->next;
				tok_redir->fd = open(tok_redir->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
				if (tok_redir->fd < 0)
				{
					cmd->file_err = 1;
					//printf("outfile error\n"); // afficher error avec erno + strerror
					ft_msg(errno, ERRMSG, "", strerror(errno));
				}
				cmd->outfile = tok_redir->fd;
			}
			else if (tok_redir->type == D_GREAT)
			{
				tok_redir = tok_redir->next;
				tok_redir->fd = open(tok_redir->token, O_CREAT | O_RDWR | O_APPEND);
				if (tok_redir->fd < 0)
				{
					cmd->file_err = 1;
					//printf("outfile error\n"); // afficher error avec erno + strerror
					ft_msg(errno, ERRMSG, "", strerror(errno));
				}
				cmd->outfile = tok_redir->fd;
			}
			else if (tok_redir->type == LESS)
			{
				tok_redir = tok_redir->next;
				tok_redir->fd = open(tok_redir->token, O_RDONLY);
				if (tok_redir->fd < 0)
				{
					cmd->file_err = 1;
					//printf("infile error\n"); // afficher error avec erno + strerror
					ft_msg(errno, ERRMSG, "", strerror(errno));
				}
				cmd->infile = tok_redir->fd;
			}
			else if (tok_redir->type == D_LESS)
			{
				tok_redir = tok_redir->next;
				tok_redir->fd = open(tok_redir->token, O_RDONLY);
				if (tok_redir->fd < 0)
				{
					cmd->file_err = 1;
					//printf("infile error\n"); // afficher error avec erno + strerror
					ft_msg(errno, ERRMSG, "", strerror(errno));
				}
				cmd->infile = tok_redir->fd;
			}
			tok_redir = tok_redir->next;
		}
	//	dprintf(2, "pour cmd->token = %s\n", cmd->token->token);
	//	dprintf(2, "cmd->infile = %d et cmd->outfile = %d\n", cmd->infile, cmd->outfile);
		cmd = cmd->next;
	}
	return (0);
}
