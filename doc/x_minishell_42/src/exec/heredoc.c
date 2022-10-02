/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:38:35 by athirion          #+#    #+#             */
/*   Updated: 2022/07/10 07:51:47 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_end_heredoc(t_dlist *cmd)
{
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-line (wanted `", 2);
	ft_putstr_fd(((t_cmd *)cmd->content)->stop_word, 2);
	ft_putendl_fd("')", 2);
}

void	ft_close_heredoc(t_data *data, t_dlist *cmd, t_hd *hd, char *file)
{
	ft_free(hd->temp);
	ft_close(data, cmd, &hd->fd_file);
	((t_cmd *)cmd->content)->fd_in = open(file, O_RDONLY);
	unlink(file);
}

void	ft_write_heredoc(t_data *data, t_hd *hd)
{
	hd->expand = NULL;
	if (ft_has_a_var(hd->temp) && ft_strlen(hd->temp) > 2)
	{
		hd->expand = ft_expand_heredoc(data, hd->temp);
		write(hd->fd_file, hd->expand, ft_strlen(hd->expand));
		ft_free(hd->expand);
	}
	else
	{
		write(hd->fd_file, hd->temp, ft_strlen(hd->temp));
		ft_free(hd->temp);
	}
	ft_init_signals (data);
}

int	ft_heredoc_prompt(t_data *data, t_hd *hd)
{
	extern int	g_sig_status;

	ft_heredoc_signals (data);
	write(1, "> ", 2);
	hd->temp = get_next_line(0);
	return (g_sig_status);
}

void	ft_here_doc(t_data *data, t_dlist *cmd, t_dlist *redir, char *file)
{
	extern int	g_sig_status;
	t_hd		hd;

	hd.fd_file = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (hd.fd_file == -1)
		ft_perror(data, cmd, errno);
	g_sig_status = 0;
	while (1)
	{
		if (ft_heredoc_prompt (data, &hd))
			break ;
		if (hd.temp == NULL)
		{
			ft_end_heredoc(cmd);
			break ;
		}
		if (ft_strlen(((t_redir *)redir->content)->file)
			== (ft_strlen(hd.temp) - 1)
			&& !(ft_strncmp(hd.temp,
					((t_redir *)redir->content)->file, ft_strlen(hd.temp) - 1)))
			break ;
		ft_write_heredoc(data, &hd);
	}
	ft_close_heredoc(data, cmd, &hd, file);
}
