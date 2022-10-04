/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:14:02 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/04 02:50:20 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* <SUMMARY> Function that gets the consistent 'sizeof' for ft_handle_malloc
** function
*/


//Fonction qui permet de récupérer le bon sizeof à utiliser dans ft_malloc

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
	return (0);
}

/*	Handles malloc
**	protéger le size en indiquant un size_t ????

**	<SUMMARY> Allocates memory depending on variable type (to malloc) & its size
*/
void	*ft_handle_malloc(int val_exit, void *ptr, int type, int size)
{
	static t_bin	*bin_head = NULL;

	if (val_exit == 1000)//faire un malloc
		return (malloc(ft_get_sizeof(type) * size));
	else if (val_exit == 2000)//add malloc to 'bin' linked list
	{
		if (ptr == NULL)
		{
			exit (val_exit);
			/*faire une fonction (pour tout supprimer et quitter) :
				- free ptr.../// A REVOIR !!! (exp : ft_split)
				- message d'erreur de malloc
				- ft_free_bin(&bin);
				- exit;// fonction à écrire pour
			*/
		}
		ft_lstadd_bin(&bin_head, ptr, type, size);
		return (NULL);
	}
	else if (val_exit = 3000)//supprime un maillon quand on veut libérer un malloc
	{
		ft_lstclearone_bin(&bin_head, ptr);
		return (NULL);
	}
	else//tout free
	{
		ft_free_bin(&bin_head);
		return (NULL);//exit
	}
}
