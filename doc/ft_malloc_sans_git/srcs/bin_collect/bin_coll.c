/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:00:03 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/26 02:49:41 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui permet de récupérer le bon sizeof à utiliser dans ft_malloc
**	<SUMMARY> Function that get the consistent 'sizeof' for ft_malloc function
*/
int	ft_get_sizeof(int type)
{
	if (type == TAB_INT1)
	{
		printf("sizeof TAB_INT1 = %ld\n", sizeof(int));
		return (sizeof(int));
	}
	else if (type == TAB_INTS)
		return (sizeof(int *));
	else if (type == TAB_STR1)
	{
		printf("sizeof TAB_STR1 = %ld\n", sizeof(char));
		return (sizeof(char));
	}
	else if (type == TAB_STRS)
		return (sizeof(char *));
	else if (type == LST_ENV)
		return (sizeof(t_env));
	else if (type == LST_CMD)
		return (sizeof(t_cmd));
	else if (type == LST_TOK)
		return (sizeof(t_token));
	return (1);
}

/*	Fonction qui :
	1. malloc selon les données transmises
	2. ajoute 1 maillon à chaque malloc OK
**	<SUMMARY> allocate memory according to given parameters
**	and add a node to the data->'bin' linked list if malloc is OK
*/
void	*ft_malloc(t_data *data, void *ptr, int type, int size)
{
	int	sizeoftype;

	sizeoftype = ft_get_sizeof(type);
	dprintf(2, "full size = sizeof(type) %d * size %d = %d\n", sizeoftype, size, (sizeoftype * size));
	ptr = malloc(sizeoftype * size);
	if (!ptr)
	{
		ft_free_bin(ptr, type, size);//je nettoie le ptr si partiellement malloc
		//attention : revoir le size !!!
		ft_lstclear_bin(data->bin);//free bin !!
		dprintf(2, "malloc failure dans le check malloc\n");
		return (NULL);//exit(EXIT_FAILURE);// ou return - à revoir !!!!!!!!!!!
	}
	printf("ptr (post malloc) = %p\n", ptr);
	ft_lstadd_bin(&(data->bin), ptr, type, size);

	/*	pour affichage - test 	*/
	/*	*********************	*/
	t_bin	*tmp_bin;
	tmp_bin = data->bin;
	printf("(data->bin) tmp_bin->ptr = %p\n", tmp_bin->ptr);
	if (tmp_bin->next)
		printf("(data->bin) tmp_bin->next->ptr = %p\n", tmp_bin->next->ptr);
	printf("test - malloc ok\n");
	/*	*********************	*/
	return (ptr);
}

/*	autre idée
	faire une structure t_bin *bin_0 avant de rentrer dans la boucle

	ou faire en 2 fois:
	- un ft_void_malloc pour checker le malloc
		- si ok = 0
		- si pas ok = 1
	- un ft_handle_malloc(data, ...)
		- si ft_malloc2 = 0 --> add to bin linked list
		- si ft_malloc2 != 0 --> supprime la var + bin linked list + ...
*/
