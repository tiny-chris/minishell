/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:51:41 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/11 14:46:41 by cgaillag         ###   ########.fr       */
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
	ft_handle_malloc(ADD_M, new, LST_CMD, 1);
	// if (!new)
	// {
	// 	dprintf(2, "CA BUGGGG !!!!!!!!!!!!!!!!!!!!!!!\n");
	// 	//ft_free_cmd(cmd);// A FAIRE !!
	// 	return (1);
	// }
	new->raw_cmd = ft_strdup(cmdline);
	ft_handle_malloc(ADD_M, new->raw_cmd, TAB_STR1, 0);
	new->unspace_cmd = NULL;
	new->no_redir_cmd = NULL;
	new->undoll_cmd = NULL;
	new->clean_cmd = NULL;
	new->token = NULL;
	new->tok_redir = NULL;
	new->infile = 0;
	new->outfile = 1;
	new->file_err = 0;
	new->cmd_opt = NULL;
	new->cmd_path = NULL;
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
	free(node->unspace_cmd);
	node->unspace_cmd = NULL;
	free(node->no_redir_cmd);
	node->no_redir_cmd = NULL;
	free(node->undoll_cmd);
	node->undoll_cmd = NULL;
	free(node->clean_cmd);
	node->clean_cmd = NULL;
	ft_free_token(&(node->tok_redir));
	ft_free_token(&(node->token));
	if (node->cmd_opt != NULL)
		ft_free_tabstr(node->cmd_opt);
	if (node->cmd_path)
		free(node->cmd_path);
	node->cmd_path = NULL;
	node->next = NULL;
	free(node);
	node = NULL;
}

void	ft_lstdelone2_cmd(t_cmd *node)
{
	if (!node)
		return ;
	node->next = NULL;
	free(node);
	node = NULL;
}

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!*cmd)
		return ;
	while ((*cmd) != NULL)
	{
		tmp = (*cmd)->next;
		ft_lstdelone_cmd(*cmd);
		(*cmd) = tmp;
	}
	(*cmd) = NULL;
}
