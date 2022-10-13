/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:14:29 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/12 02:07:03 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	<SUMMARY> adds a new node at the beginning of the t_bin list
**	<REMARK> keeps malloc function & protection for 'new' node as is to avoid
**			'circular ref'
*/
int	ft_lstadd_bin(t_bin **bin_head, void *ptr, int type, int size)
{
	t_bin	*new;
	t_bin	*first;

	first = (*bin_head);
	new = malloc(sizeof(t_bin));
	if (!new)
		return (1);
	// printf("test - lstadd_bin début\n");
	new->ptr = ptr;
	new->type = type;
	new->size = size;
	new->next = first;
	(*bin_head) = new;
	// /* affichage de bin_head */
	// printf("affichage APRES lstadd_bin :\n");
	// t_bin *tmp;
	// tmp = (*bin_head);
	// if (tmp != NULL)
	// {
	// 	printf("tmp[0] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
	// 	tmp = tmp->next;
	// 	if (tmp != NULL)
	// 	{
	// 		printf("tmp[1] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
	// 		tmp = tmp->next;
	// 		if (tmp != NULL)
	// 			printf("tmp[2] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
	// 	}
	// }
	// else
	// 	printf("vide --> plus de bin_head\n");
	// /* fin d'affichage */
	return (0);
}

/*	<SUMMARY> frees one node (specified in parameter)
**	<REMARK> defines which kind of free to apply depending on type & size
*/
void	ft_lstdelone_bin(t_bin *node)
{
	if (!node)
		return ;
	// printf("rentre dans delone bin et va aller dans free typ ptr\n");
	// printf("ptr = %p, type = %d, size = %d\n", node->ptr, node->type, node->size);
	ft_free_ptr_type(node->ptr, node->type, node->size);
	node->type = 0;
	node->size = 0;
	node->next = NULL;
	free(node);
	node = NULL;
}

static int	ft_lstclearfisrt_bin(t_bin **bin_head)
{
	t_bin	*todel;
	t_bin	*tmp;

	todel = (*bin_head);
	tmp = (*bin_head)->next;
	ft_lstdelone_bin(todel);
	(*bin_head) = tmp;
	return (0);
}

/*	<SUMMARY> frees the node associated to 'ptr' and removes it from the
**	linked list
*/
void	ft_lstclearone_bin(t_bin **bin_head, void *ptr)
{
	t_bin	*bin;
	t_bin	*todel;
	t_bin	*tmp;

	bin = (*bin_head);
	todel = NULL;
	tmp = NULL;
	if (!(*bin_head) || !ptr)
		return ;
	if (bin->ptr == ptr)
	{
		ft_lstclearfisrt_bin(bin_head);
		return ;
	}
	while (bin)
	{
		if (bin->next && bin->next->ptr == ptr)
		{
			todel = bin->next;
			tmp = bin->next->next;
			ft_lstdelone_bin(todel);
			bin->next = tmp;
			break ;
		}
		bin = bin->next;
	}
}

/*	<SUMMARY> deletes the full t_bin linked list by deleting one node after
**	the other: starting from 1st node (head)
*/
void	ft_free_bin(t_bin **bin_head)
{
	t_bin	*tmp;
	t_bin	*todel;
	// int		i = 0;//

	tmp = NULL;
	todel = NULL;
	if (!(*bin_head))
		return ;
	while ((*bin_head) != NULL)
	{
		todel = (*bin_head);
		tmp = (*bin_head)->next;
		// printf("i = %d avant delone bin\n", i);//
		ft_lstdelone_bin(todel);
		(*bin_head) = tmp;
		// i++;//
	}
	(*bin_head) = NULL;
}
