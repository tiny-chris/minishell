/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:51:41 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/19 11:33:30 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	FUNCTIONS FOR LINKED LIST 'cmd'
**	- int	ft_lstadd_cmd(t_cmd **cmd, char *cmdline)
**	- t_cmd	*ft_lstlast_cmd(t_cmd *lst)
**	- void	ft_free_cmd(t_cmd **cmd)
**	- void	ft_lstdelone_cmd(t_cmd *node)
*/

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
	new->unspace_cmd = NULL;
	new->no_redir_cmd = NULL;
	new->undoll_cmd = NULL;
	new->clean_cmd = NULL;
	new->token = NULL;
	new->tok_redir = NULL;
	new->infile = 0;
	new->outfile = 1;
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

void	ft_lstdelone_cmd(t_cmd *node)
{
	if (!node)
		return ;
	free(node->raw_cmd);
	node->raw_cmd = NULL;
	free(node->unspace_cmd);//raw_cmd_no_space);
	node->unspace_cmd = NULL;
	free(node->no_redir_cmd);
	node->no_redir_cmd = NULL;
	free(node->undoll_cmd);
	node->undoll_cmd = NULL;
	// free(node->unquote_cmd);
	// node->unquote_cmd = NULL;
	free(node->clean_cmd);
	node->clean_cmd = NULL;
	// free(node->clean_cmd_no_redir);
	// node->clean_cmd_no_redir = NULL;
	ft_free_token(&(node->tok_redir));
	ft_free_token(&(node->token));
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
