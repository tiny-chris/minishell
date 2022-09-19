/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:30:46 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/19 11:36:07 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**ft_init_pipe(t_data *data)
{
	int	**tab_int;
	int	i;

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
	while (cmd)
	{
		tok_redir = cmd->tok_redir;
		while (tok_redir)
		{
			if (tok_redir->type == GREAT)
			{
				tok_redir = tok_redir->next;
				cmd->outfile = open(tok_redir->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
				if (cmd->outfile < 0)
					printf("outfile error\n"); // afficher error avec erno + strerror	
			}
			else if (tok_redir->type == D_GREAT)
			{
				tok_redir = tok_redir->next;
				cmd->outfile = open(tok_redir->token, O_CREAT | O_RDWR | O_APPEND);
				if (cmd->outfile < 0)
					printf("outfile error\n"); // afficher error avec erno + strerror
			}
			else if (tok_redir->type == LESS)
			{
				tok_redir = tok_redir->next;
				cmd->infile = open(tok_redir->token, O_RDONLY);
				if (cmd->infile < 0)
					printf("infile error\n"); // afficher error avec erno + strerror
			}
			else if (tok_redir->type == D_LESS)
			{
				tok_redir = tok_redir->next;
				cmd->infile = open(tok_redir->token, O_RDONLY);
				if (cmd->infile < 0)
					printf("infile error\n"); // afficher error avec erno + strerror
			}
			tok_redir = tok_redir->next;
		}
	}
	return (0);
}
