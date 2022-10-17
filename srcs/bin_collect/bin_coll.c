/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:14:02 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/17 13:07:48 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/* <SUMMARY> Gets the 'sizeof' corresponding to the given type
*/
static size_t	ft_get_sizeof(int type)
{
	if (type == TAB_INT1)
		return (sizeof(int));
	else if (type == TAB_INT2 || type == TAB_INTS)
		return (sizeof(int *));
	else if (type == TAB_STR1)
		return (sizeof(char));
	else if (type == TAB_STR2 || type == TAB_STRS)
		return (sizeof(char *));
	else if (type == LST_ENV)
		return (sizeof(t_env));
	else if (type == LST_CMD)
		return (sizeof(t_cmd));
	else if (type == LST_TOK)
		return (sizeof(t_token));
	return (0);
}

void	ft_free_ptr_type(void *ptr, int type, int size)
{
	if (!ptr)
		return ;
	if (ptr && type == TAB_INT1)
		ft_free_ints((int *)ptr, NULL, NULL);
	else if (ptr && (type == TAB_INT2 || type == TAB_INTS))
		ft_free_tabint2((int **)ptr, size, type);
	else if (ptr && type == TAB_STR1)
		ft_free_strs((char *)ptr, NULL, NULL);
	else if (ptr && (type == TAB_STR2 || type == TAB_STRS))
		ft_free_tabstr2((char **)ptr, type);
	else if (ptr && type == LST_ENV)
		ft_lstdelone_env((t_env *)ptr);
	else if (ptr && type == LST_CMD)
		ft_lstdelone_cmd((t_cmd *)ptr);
	else if (ptr && type == LST_TOK)
		ft_lstdelone_tok((t_token *)ptr);
	return ;
}

static void	ft_failed_malloc(t_bin **bin_head, int flag, t_data *data)
{
	ft_putendl_fd(ERRMAL, 2);
	ft_close_std();
	if (data)
		ft_close_fd(data);
	rl_clear_history();
	if (flag == ADD_C || flag == MALLOC_C)
		g_val_exit = 42;
	else
		g_val_exit = 1;
	ft_free_bin(bin_head);
	exit (g_val_exit);
}

/*	<SUMMARY> Garbage/bin collector to manage any malloc in the prog (4 options)
**	1. MALLOC:	allocates uninitialized space and returns a pointer to the
**				allocated memory + ADD
**	2. ADD:		checks the memory allocation and stores 'ptr' in a t_bin node
**				+ adds this node to linked list 'bin_head'
**	3. DELONE:	cleans and deletes a selected node of 'bin_head'
**	4. else: 	delete the whole linked list 'bin_head'
**	<REMARKS>	- use of a static linked list t_bin 'bin_head'
**				- a malloc failure (MALLOC or ADD) leads to clean exit and
**					g_val_exit is set to 42 in a child process & 1 otherwise
**					(defined according to 'C' for child and 'M' for main/other)
**					+ for ADD opt: clean of the 'ptr' (not be added to bin_head)
*/
void	*ft_handle_malloc(int flag_type, void *ptr, int size, t_data *data)
{
	static t_bin	*bin_head;
	void			*ptr2;
	int				flag;

	ptr2 = NULL;
	flag = ((flag_type / 1000) * 1000) + (flag_type % 10);
	if (flag == MALLOC_C || flag == MALLOC_M)
		ptr2 = malloc(ft_get_sizeof(flag_type - flag) * size);
	else
		ptr2 = ptr;
	if (flag == MALLOC_C || flag == MALLOC_M || flag == ADD_C || flag == ADD_M)
	{
		if (ptr2 == NULL)
			ft_failed_malloc(&bin_head, flag, data);
		if (ft_lstadd_bin(&bin_head, ptr2, (flag_type - flag), size) == 1)
		{
			ft_free_ptr_type(ptr2, (flag_type - flag), size);
			ft_failed_malloc(&bin_head, flag, data);
		}
	}
	else if (flag == DELONE)
		ft_lstclearone_bin(&bin_head, ptr);
	else
		ft_free_bin(&bin_head);
	return (ptr2);
}
