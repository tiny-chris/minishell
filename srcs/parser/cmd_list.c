/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:51:41 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/12 04:05:28 by cgaillag         ###   ########.fr       */
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

	new = ft_handle_malloc(MALLOC_M, NULL, LST_CMD, 1);
	// new = malloc(sizeof(t_cmd));
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

// void	ft_lstdelone_cmd(t_cmd *node, int type)
// {
// 	if (!node)
// 		return ;
// 	if (type != LST_CMD)
// 	{
// 		ft_free_strs(node->raw_cmd, node->unspace_cmd, node->no_redir_cmd);
// 		ft_free_strs(node->undoll_cmd, node->clean_cmd, node->cmd_path);
// 		ft_free_token(&(node->token));
// 		ft_free_token(&(node->tok_redir));
// 		if (node->cmd_opt != NULL)
// 			ft_free_tabstr(node->cmd_opt);
// 		node->infile = 0;
// 		node->outfile = 1;
// 		node->file_err = 0;
// 	}
// 	node->next = NULL;
// 	free(node);
// 	node = NULL;
// }

/*	<SUMMARY> Deletes the t_cmd node ONLY (not its content) and removes it
**	from the garbage collector at the same time
**	<REMARK>	a malloc of t_cmd node is always done without content
**				(on the contrary of char **, e.g. ft_split function)
*/
void	ft_lstdelone_cmd(t_cmd *node)
{
	if (!node)
		return ;
	node->next = NULL;
	free(node);
	node = NULL;
}

void	ft_lstdelone_cmd_bin(t_cmd *node)
{
	if (!node)
		return ;
	if (node->raw_cmd)
		ft_handle_malloc(DELONE, node->raw_cmd, 0, 0);
	if (node->unspace_cmd)
		ft_handle_malloc(DELONE, node->unspace_cmd, 0, 0);
	if (node->no_redir_cmd)
		ft_handle_malloc(DELONE, node->no_redir_cmd, 0, 0);
	if (node->undoll_cmd)
		ft_handle_malloc(DELONE, node->undoll_cmd, 0, 0);
	if (node->clean_cmd)
		ft_handle_malloc(DELONE, node->clean_cmd, 0, 0);
	if (node->tok_redir)
		ft_free_token(&(node->tok_redir));
	if (node->token)
		ft_free_token(&(node->token));
	if (node->cmd_opt != NULL)
		ft_free_tabstr_bin(node->cmd_opt, TAB_STRS);
	if (node->cmd_path)
		ft_handle_malloc(DELONE, node->cmd_path, 0, 0);
	ft_handle_malloc(DELONE, node, 0, 0);
}

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*todel;

	tmp = NULL;
	todel = NULL;
	if (!*cmd)
		return ;
	while ((*cmd) != NULL)
	{
		todel = (*cmd);
		tmp = (*cmd)->next;
		ft_lstdelone_cmd_bin(todel);
		(*cmd) = tmp;
	}
	(*cmd) = NULL;
}
