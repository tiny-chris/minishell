/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:14:02 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/04 15:36:00 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/* <SUMMARY> Function that gets the consistent 'sizeof' for ft_handle_malloc
** function
*/
static size_t	ft_get_sizeof(int type)
{
	if (type == TAB_STR1)
	{
		printf("sizeof TAB_STR1 = %ld\n", sizeof(char));//
		return (sizeof(char));
	}
	else if (type == TAB_INT1)
	{
		printf("sizeof TAB_INT1 = %ld\n", sizeof(int));//
		return (sizeof(int));
	}
	else if (type == TAB_INTS)
		return (sizeof(int *));
	else if (type == TAB_STRS)
		return (sizeof(char *));
	else if (type == LST_ENV)
		return (sizeof(t_env));
	else if (type == LST_CMD)
		return (sizeof(t_cmd));
	else if (type == LST_TOK)
		return (sizeof(t_token));
	else if (type == LST_BIN)
		return (sizeof(t_bin));
	return (0);
}

static void	ft_failed_malloc(t_bin **bin_head)
{
	g_val_exit = ft_msg(42, "", "", ERRMAL);
	ft_free_bin(bin_head);
	exit (g_val_exit);
}

/*	<SUMMARY> Allocates memory depending on variable type (to malloc) & its size
**		- val_exit = 1000	--> malloc + protect + add to 't_bin' linked list
**		- val_exit = 2000	--> protect + add to 't_bin'
**		- val_exit = 3000	--> free and delete a specific node of 't_bin'
**		- other val_exit	--> free and delete all nodes of 't_bin'
*/
void	*ft_handle_malloc(int flag, void *ptr, int type, int size)
{
	static t_bin	*bin_head;
	void			*tmp;

	tmp = NULL;
//	printf("ptr = %p\n", ptr);
	if (flag == MALLOC)
	{
		tmp = malloc(ft_get_sizeof(type) * size);
		if (tmp == NULL)
			ft_failed_malloc(&bin_head);
		if (ft_lstadd_bin(&bin_head, tmp, type, size) == 1)
			ft_failed_malloc(&bin_head);
		return (tmp);
	}
	if (flag == ADD)
	{
		printf("rentre dans ADD\n");
		if (ptr == NULL)
		{
			printf("rentre dans ADD - NULL\n");
			ft_failed_malloc(&bin_head);
		}
		ft_lstadd_bin(&bin_head, ptr, type, size);
	}
	else if (flag == DELONE)
	{
		printf("rentre dans DELONE\n");
		ft_lstclearone_bin(&bin_head, ptr);
	}
	else
	{
		printf("rentre dans else\n");
		ft_free_bin(&bin_head);
	}
	return (NULL);
}
