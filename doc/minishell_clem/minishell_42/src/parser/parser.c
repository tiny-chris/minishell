/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:33:44 by clem              #+#    #+#             */
/*   Updated: 2022/07/14 17:33:48 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_concat_consec_word_2(t_data *data, t_dlist *temp)
{
	char	*str;

	while (temp && temp->next && ft_is_tokid(temp, WD)
		&& ft_is_tokid(temp->next, WD))
	{
		temp = temp->next;
		str = ft_strjoin(((t_tok *)temp->prev->content)->tok,
				((t_tok *)temp->content)->tok);
		free(((t_tok *)temp->content)->tok);
		((t_tok *)temp->content)->tok = ft_w_strdup(data, str);
		free(str);
	}
	return (temp);
}

void	ft_concat_consecutive_word(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*ptrcpy[2];
	t_dlist	*new;

	new = ft_w_malloc(data, sizeof(t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	temp = data->toklist;
	ptrcpy[0] = temp;
	while (temp)
	{
		temp = ft_concat_consec_word_2 (data, temp);
		ft_dlst_elem_dup(data, &new, temp);
		if (temp)
			temp = temp->next;
	}
	data->toklist = new;
	ft_clearlist_tok(&ptrcpy[0], ft_free);
	ft_free(ptrcpy[1]);
}

void	ft_parser_2(t_data *data)
{
	ft_expand_vars(data);
	ft_expand_tilde(data);
	ft_expand_quote(data);
	ft_concat_consecutive_word(data);
	ft_parse_space(data);
	ft_parse_redir(data);
	ft_count_pipe(data);
}

void	ft_parser(t_data *data)
{
	extern int	g_sig_status;

	if (!ft_parse_special_tok(data))
	{
		g_sig_status = 2;
		return ;
	}
	if (!ft_parse_pipe(data) || !ft_parse_quote(data, data->toklist))
	{
		g_sig_status = 2;
		return ;
	}
	if (!ft_check_redir(data))
	{
		g_sig_status = 2;
		return ;
	}
	ft_parser_2(data);
	if (!ft_parse_empty_cmd(data))
		return ;
	ft_create_cmdlist(data);
	ft_create_redlist(data);
}
