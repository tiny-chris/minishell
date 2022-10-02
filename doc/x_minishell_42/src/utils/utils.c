/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:52:22 by athirion          #+#    #+#             */
/*   Updated: 2022/06/29 15:52:22 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Add a duplicate of 'dup' to 'lst' list.
 */

void	ft_dlst_elem_dup(t_data *data, t_dlist **lst, t_dlist *dup)
{
	t_tok	*new_tok;

	new_tok = ft_w_malloc (data, sizeof(t_tok));
	new_tok->tokid = ((t_tok *)dup->content)->tokid;
	new_tok->tokpos = ((t_tok *)dup->content)->tokpos;
	new_tok->tok = ft_w_strdup(data, ((t_tok *)dup->content)->tok);
	ft_dlstadd_back(lst, ft_dlstnew(new_tok));
}

/*
 ** Security layer for 'ft_strjoin'.
 */

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	char	*temp;

	temp = s2;
	s2 = ft_strjoin(s1, s2);
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (s2);
}

/*
 ** Security layer for 'ft_strjoin'.
 */

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*temp;

	temp = s1;
	s2 = ft_strjoin(s1, s2);
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (s2);
}

/*
 ** Security layer for 'ft_strjoin'.
 */

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp1;
	char	*temp2;
	char	*s3;

	temp1 = s1;
	temp2 = s2;
	s3 = ft_strjoin(s1, s2);
	if (temp1)
	{
		free(temp1);
		temp1 = NULL;
	}
	if (temp2)
	{
		free(temp2);
		temp2 = NULL;
	}
	return (s3);
}
