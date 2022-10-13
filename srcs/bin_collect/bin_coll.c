/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:14:02 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/13 17:15:26 by cgaillag         ###   ########.fr       */
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
	// dprintf(2,"rentre dans le free ptr type\n");
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
	// else if (type == LST_BIN)// pas vraiment applicable - ne fait pas partie des pointeurs à l'intérieur de lui-même
	// 	ft_free_bin((t_bin **)ptr);
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
	printf("val exit main vs child = %d\n", g_val_exit);
	// /* affichage de bin_head - pour des STR1 */
	// dprintf(2, "affichage AVANT free bin :\n");
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
	ft_free_bin(bin_head);
	// /* affichage de bin_head - pour des STR1 */
	// dprintf(2, "affichage APRES free bin :\n");
	// tmp = (*bin_head);
	// if (tmp != NULL)
	// {
	// 	printf("tmp[0] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
	// 	tmp = tmp->next;
	// 	if (tmp != NULL)
	// 	{
	// 		printf("tmp[1] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
	// 		tmp = tmp->next;
	// 	if (tmp != NULL)
	// 		printf("tmp[2] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
	// 	}
	// }
	// else
	// 	printf("vide --> plus de bin_head\n");
	// /* fin d'affichage */
	exit (g_val_exit);
}

/*	<SUMMARY> Garbage/bin collector to manage any malloc in the prog (4 options)
**	1. MALLOC:	allocates uninitialized space and returns a pointer to the
**				allocated memory + ADD
**	2. ADD:		checks the memory allocation and stores 'ptr' in a t_bin node
**				+ adds this node to linked list'bin_head'
**	3. DELONE:	cleans and deletes a selected node of 'bin_head'
**	4. else: 	delete the whole linked list 'bin_head'
**	<REMARKS>	- use of a static linked list t_bin 'bin_head'
**				- a malloc failure (MALLOC or ADD) leads to clean exit and
**					g_val_exit is set to 42 in a child process & 1 otherwise
**					(defined according to 'C' for child and 'M' for main/other)
**					+ for ADD opt: clean of the 'ptr' (not be added to bin_head)
**	********
**	enum:
**				CHILD	OTHER (main, unique built-in...)
**	ADD			1000	2000	-->			 check + add to bin_head
**	MALLOC		1001	2001	-->	malloc + check + add to bin_head
**	DELONE		3000	same
*/
// void	*ft_malloc(int flag_type, void *ptr, int size, t_data *data)
// {
// 	void	*ptr2;
// 	int		flag;

// 	ptr2 = NULL;
// 	flag = ((flag_type / 1000) * 1000) + (flag_type % 10);
// 	printf("val de flag = %d\n", flag);
// 	if (flag == MALLOC_C || flag == MALLOC_M)
// 		ptr2 = malloc(ft_get_sizeof(flag_type - flag) * size);
// 	else
// 		ptr2 = ptr;
// 	if (ptr2 == NULL)
// 	{
// 		ft_close_std();
// 		ft_close_fd(data);
// 		rl_clear_history();
// 		ft_handle_malloc(0, NULL, 0, 0);
// 		if (flag == ADD_C || flag == MALLOC_C)
// 			g_val_exit = 42;
// 		else
// 			g_val_exit = 1;
// 		ft_putendl_fd(2, "Error: memory allocation failure");
// 		exit(g_val_exit);
// 	}
// 	return (ptr);
// }

void	*ft_handle_malloc(int flag_type, void *ptr, int size, t_data *data)
{
	static t_bin	*bin_head;
	void			*ptr2;
	int				flag;

	ptr2 = NULL;
	flag = ((flag_type / 1000) * 1000) + (flag_type % 10);
	// printf("val de flag = %d\n", flag);
	if (flag == MALLOC_C || flag == MALLOC_M)
	{
	//	dprintf(2, "rentre dans MALLOC et ptr2 est NULL = %p\n", ptr2);//
		ptr2 = malloc(ft_get_sizeof(flag_type - flag) * size);

	// 	// TEST - BIN COLL - malloc failure - REMETTRE LE MALLOC
	// 	printf("size of type = %zu\n", ft_get_sizeof(flag_type - flag));// TEST - BIN COLL - malloc failure - REMETTRE LE MALLOC
	// 	if (ft_get_sizeof(flag_type - flag))// TEST - BIN COLL - malloc failure - REMETTRE LE MALLOC
	// 		ptr2 = NULL;// TEST - BIN COLL - malloc failure - REMETTRE LE MALLOC
	}
	else
		ptr2 = ptr;
	//dprintf(2, "valeur ptr2 apres MALLOC (fin) = %p\n", ptr2);
	if (flag == MALLOC_C || flag == MALLOC_M || flag == ADD_C || flag == ADD_M)
	{
		// dprintf(2, "valeur ptr2 apres MALLOC (ADD) = %p, type = %d, size = %d\n", ptr2, type, size);
		if (ptr2 == NULL)
			ft_failed_malloc(&bin_head, flag, data);
		if (ft_lstadd_bin(&bin_head, ptr2, (flag_type - flag), size) == 1)
		{
			ft_free_ptr_type(ptr2, (flag_type - flag), size);
			ft_failed_malloc(&bin_head, flag, data);
		}
	}
	else if (flag == DELONE)
	{
	//	dprintf(2, "rentre dans DELONE\n");
		// /* affichage de bin_head - pour des STR1 */
		// dprintf(2, "affichage DELONE AVANT :\n");
		// t_bin *tmp;
		// tmp = bin_head;
		// if (tmp != NULL)
		// {
		// 	printf("tmp[0] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	tmp = tmp->next;
		// 	if (tmp != NULL)
		// 	{
		// 		printf("tmp[1] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 		tmp = tmp->next;
		// 	if (tmp != NULL)
		// 		printf("tmp[2] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	}
		// }
		// else
		// 	printf("vide --> plus de bin_head\n");
		/* fin d'affichage */
		ft_lstclearone_bin(&bin_head, ptr);
		// /* affichage de bin_head - pour des STR1 */
		// dprintf(2, "affichage DELONE APRES :\n");
		// tmp = bin_head;
		// if (tmp != NULL)
		// {
		// 	printf("tmp[0] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	tmp = tmp->next;
		// 	if (tmp != NULL)
		// 	{
		// 		printf("tmp[1] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 		tmp = tmp->next;
		// 	if (tmp != NULL)
		// 		printf("tmp[2] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	}
		// }
		// else
		// 	printf("vide --> plus de bin_head\n");
		// /* fin d'affichage */
	}
	else
	{
		// dprintf(2, "passssssssssse dans le free bin\n");
		// dprintf(2, "rentre dans else\n");
		// /* affichage de bin_head - pour des STR1 */
		// dprintf(2, "affichage free bin AVANT :\n");
		// t_bin *tmp;
		// tmp = bin_head;
		// if (tmp != NULL)
		// {
		// 	printf("tmp[0] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	tmp = tmp->next;
		// 	if (tmp != NULL)
		// 	{
		// 		printf("tmp[1] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 		tmp = tmp->next;
		// 	if (tmp != NULL)
		// 		printf("tmp[2] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	}
		// }
		// else
		// 	printf("vide --> plus de bin_head\n");
		// /* fin d'affichage */
		ft_free_bin(&bin_head);
		// /* affichage de bin_head - pour des STR1 */
		// dprintf(2, "affichage free bin APRES :\n");
		// tmp = bin_head;
		// if (tmp != NULL)
		// {
		// 	printf("tmp[0] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	tmp = tmp->next;
		// 	if (tmp != NULL)
		// 	{
		// 		printf("tmp[1] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 		tmp = tmp->next;
		// 	if (tmp != NULL)
		// 		printf("tmp[2] = %p, type = %d, size = %d\n", tmp->ptr, tmp->type, tmp->size);
		// 	}
		// }
		// else
		// 	printf("vide --> plus de bin_head\n");
		// /* fin d'affichage */
	}
	return (ptr2);
}




// static void	ft_failed_malloc(t_bin **bin_head)
// {
// 	g_val_exit = ft_msg(42, "", "", ERRMAL);
// 	ft_free_bin(bin_head);
// 	exit (g_val_exit);
// }

/*	<SUMMARY> Allocates memory depending on variable type (to malloc) & its size
**		- val_exit = 1000	--> malloc + protect + add to 't_bin' linked list
**		- val_exit = 2000	--> protect + add to 't_bin'
**		- val_exit = 3000	--> free and delete a specific node of 't_bin'
**		- other val_exit	--> free and delete all nodes of 't_bin'
*/
// void	*ft_handle_malloc(int flag, void *ptr, int type, int size)
// {
// 	static t_bin	*bin_head;
// 	void			*tmp;

// 	tmp = NULL;
// //	printf("ptr = %p\n", ptr);
// 	if (flag == MALLOC)
// 	{
// 		tmp = malloc(ft_get_sizeof(type) * size);
// 		if (tmp == NULL)
// 			ft_failed_malloc(&bin_head);
// 		if (ft_lstadd_bin(&bin_head, tmp, type, size) == 1)
// 			ft_failed_malloc(&bin_head);
// 		return (tmp);
// 	}
// 	if (flag == ADD)
// 	{
// 		printf("rentre dans ADD\n");
// 		if (ptr == NULL)
// 		{
// 			printf("rentre dans ADD - NULL\n");
// 			ft_failed_malloc(&bin_head);
// 		}
// 		ft_lstadd_bin(&bin_head, ptr, type, size);
// 	}
// 	else if (flag == DELONE)
// 	{
// 		printf("rentre dans DELONE\n");
// 		ft_lstclearone_bin(&bin_head, ptr);
// 	}
// 	else
// 	{
// 		printf("rentre dans else\n");
// 		ft_free_bin(&bin_head);
// 	}
// 	return (NULL);
// }


// *********** //
