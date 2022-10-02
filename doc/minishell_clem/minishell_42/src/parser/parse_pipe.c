/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:36:39 by clem              #+#    #+#             */
/*   Updated: 2022/07/11 22:39:40 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_multiple_pipe(t_dlist **token)
{
	t_dlist	*temp;

	temp = *token;
	while (temp)
	{
		if (temp && temp->next && ft_is_tokid(temp, PP)
			&& ft_is_tokid(temp->next, PP))
			return (1);
		else if (temp && temp->next && ft_is_tokid(temp, PP)
			&& ft_is_tokid(temp->next, WS))
		{
			temp = temp->next;
			while (temp && ft_is_tokid(temp, WS))
				temp = temp->next;
			if (temp)
			{
				if (ft_is_tokid(temp, PP))
					return (1);
			}
		}
		if (temp)
			temp = temp->next;
	}
	return (0);
}

static int	ft_last_tok_is_pipe(t_dlist *token)
{
	t_dlist	*temp;
	t_dlist	*last;

	temp = token;
	while (temp->next)
		temp = temp->next;
	last = temp;
	if (ft_is_tokid(last, WS))
	{
		while (last->prev && ft_is_tokid(last, WS))
			last = last->prev;
	}
	temp = token;
	while (temp && temp != last)
		temp = temp->next;
	if (ft_is_tokid(temp, PP))
		return (1);
	return (0);
}

/*
 ** Check pipes validity.
 */

static int	ft_just_pipe(t_dlist *token)
{
	t_dlist	*temp;
	int		i;

	temp = token;
	i = 0;
	while (temp && ft_is_tokid(temp, WS))
		temp = temp->next;
	while (temp && ft_is_tokid(temp, PP))
	{
		i ++;
		temp = temp->next;
	}
	return (i);
}

int	ft_parse_pipe(t_data *data)
{
	int		error;

	error = ft_just_pipe(data->toklist);
	if (error)
	{
		if (error >= 2)
			ft_putstr_fd
				("minishell: syntax error near unexpected token `||'\n", 2);
		else
			ft_putstr_fd
				("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	if (ft_last_tok_is_pipe(data->toklist))
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		return (0);
	}
	if (ft_multiple_pipe(&data->toklist))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (1);
}
