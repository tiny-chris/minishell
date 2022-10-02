/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:14:29 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/02 04:33:46 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	<SUMMARY> adds a new node at the beginning of the t_bin list
*/
int	ft_lstadd_bin(t_data *data, void *ptr, int type, int size)
{
	t_bin	**bin;
	t_bin	*new;
	//t_bin	*first;

	bin = &(data->bin);
	//(*bin) = data->bin;
	//first = data->bin;
	printf("test - lstadd_bin début\n");
	new = ft_malloc(data, LST_BIN, 1);
	new->ptr = NULL;
	new->ptr = ptr;
	new->type = type;
	new->size = size;
	new->next = NULL;
	if ((*bin) != NULL)
		new->next = (*bin);
	(*bin) = new;
	return (0);
}
/*	<SUMMARY> defines which kind of free to apply
	depending on type & size


	QUESTION = SHALL WE CAST ptr or not ?
*/
void	ft_free_bin(void *ptr, int type, int size)
{
	if (type == TAB_STR1 && (char *)ptr)
		free((char *)ptr);
	else if (type == TAB_INT1 && (int *)ptr)
		free((int *)ptr);
	else if (type == TAB_STRS && (char **)ptr)
		ft_free_tabstr((char **)ptr);
	else if (type == TAB_INTS && (int **)ptr)
		ft_free_tabint((int **)ptr, size);
	else if (type == LST_ENV && (t_env *)ptr)
		ft_free_env((t_env **)ptr);
	else if (type == LST_CMD && (t_cmd *)ptr)
		ft_free_cmd((t_cmd **)ptr);
	else if (type == LST_TOK && (t_token *)ptr)
		ft_free_token((t_token **)ptr);
}

/*	<SUMMARY> frees one node (in parameter) in the linked list
*/
void	ft_lstdelone_bin(t_bin *node)
{
	if (!node)
		return ;
	ft_free_bin(node->ptr, node->type, node->size);
	free(node);
	node = NULL;//useful ?
}

/*	<SUMMARY> deletes the full t_bin linked list by deleting one node after
**	the other: starting from 1st node (head)
*/
void	ft_lstclear_bin(t_bin *bin)
{
	t_bin	*tmp;

	if (!bin)
		return ;
	while (bin != NULL)
	{
		tmp = bin->next;
		ft_lstdelone_bin(bin);
		bin = tmp;
	}
}
