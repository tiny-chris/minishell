/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:59:58 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/26 01:11:14 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstadd_bin(t_bin **bin, void *ptr, int type, int size)
{
	t_bin *new;
	t_bin *last;

	printf("test - lstadd_bin début\n");
	new = malloc(sizeof(t_bin));
	if (!new)
	{
		ft_lstclear_bin(*bin);//free bin !!
		dprintf(2, "malloc failure dans lstadd_bin\n");
		exit(EXIT_FAILURE);// ou return - à revoir !!!!!!!!!!!
	}
	new->ptr = ptr;
	new->type = type;
	new->size = size;
	new->next = NULL;
	if (ft_lstlast_bin(*bin) == 0)
	{
		(*bin) = new;
		printf("test - lstadd fin si 0 maillon avant\n");
		return (0);
	}
	last = ft_lstlast_bin(*bin);
	last->next = new;
	return (0);
}

t_bin	*ft_lstlast_bin(t_bin *bin)
{
	t_bin	*node;

	if (!bin)
		return (0);
	node = bin;
	while (node->next)
		node = node->next;
	return (node);
}

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

void	ft_lstdelone_bin(t_bin *node)
{
	if (!node)
		return ;
	ft_free_bin(node->ptr, node->type, node->size);
	free(node);
}

void	ft_free_bin(void *ptr, int type, int size)
{
	if (type == TAB_INT1 && ptr)
		free(ptr);
	else if (type == TAB_INTS && ptr)
		ft_free_tabint(ptr, size);
	else if (type == TAB_STR1 && ptr)
		free(ptr);
	else if (type == TAB_STRS && ptr)
		ft_free_tabstr(ptr);
	else if (type == LST_ENV && ptr)
		ft_free_env(ptr);
	else if (type == LST_CMD && ptr)
		ft_free_cmd(ptr);
	else if (type == LST_TOK && ptr)
		ft_free_token(ptr);
}
