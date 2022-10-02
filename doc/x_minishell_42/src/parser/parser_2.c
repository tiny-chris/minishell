/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:58:08 by cvidon            #+#    #+#             */
/*   Updated: 2022/07/13 11:05:35 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Parse cmdline (syntax/grammar)
 **
 ** DEBUG:
 **  dprintf (2, "==============[1]=============> ");
 **  dprintf (2, "%i : ", ((t_tok *)temp->content)->tokpos);
 **  dprintf (2, "'%s'\n", ((t_tok *)temp->content)->tok);
 **  ft_printlist_tok (data->toklist);
 */

int	ft_parse_special_tok(t_data *data)
{
	extern int	g_sig_status;
	t_dlist		*temp;

	temp = data->toklist;
	if (ft_dlstsize(temp) != 1)
		return (1);
	if (!ft_strcmp(((t_tok *)temp->content)->tok, "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		g_sig_status = 2;
		return (0);
	}
	if (!ft_strcmp(((t_tok *)temp->content)->tok, "&"))
	{
		ft_putstr_fd("minishell: syntax error near token `&'\n", 2);
		g_sig_status = 2;
		return (0);
	}
	if (!ft_strncmp(((t_tok *)temp->content)->tok, "&&", 2))
	{
		ft_putstr_fd("minishell: syntax error near token `&&'\n", 2);
		g_sig_status = 2;
		return (0);
	}
	return (1);
}

int	ft_parse_empty_cmd(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	if (ft_dlstsize(temp) != 1)
		return (1);
	if (!ft_strcmp(((t_tok *)temp->content)->tok, ""))
		return (0);
	if (ft_is_tokid(temp, WS))
		return (0);
	return (1);
}

int	ft_check_redir(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if ((ft_is_tokid(temp, DL) || ft_is_tokid(temp, LS)
				|| ft_is_tokid(temp, DG) || ft_is_tokid(temp, GT))
			&& temp->next && (ft_is_tokid(temp->next, DL)
				|| ft_is_tokid(temp->next, LS) || ft_is_tokid(temp->next, DG)
				|| ft_is_tokid(temp->next, GT)))
		{
			while (temp && (ft_is_tokid(temp, DL) || ft_is_tokid(temp, LS)
					|| ft_is_tokid(temp, DG) || ft_is_tokid(temp, GT)))
				temp = temp->next;
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(((t_tok *)temp->prev->content)->tok, 2);
			ft_putstr_fd("'\n", 2);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
