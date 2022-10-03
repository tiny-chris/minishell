// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   bin_coll.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/29 22:14:02 by cgaillag          #+#    #+#             */
// /*   Updated: 2022/10/02 04:23:35 by cgaillag         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"


// /*	FOCUS on "sizeof"
// 	The result of sizeof is of unsigned integral type which is usually denoted
// 	by size_t. sizeof can be applied to any datatype, including primitive types
// 	such as integer and floating-point types, pointer types, or compound data-
// 	types such as Structure, union etc.

// 	size_t is an unsigned integer type, which is defined in the stddef.h header
// 	It can hold any value returned by the sizeof operator, and has a min value
// 	of 0 , and a max value of the largest value, that can be returned by the
// 	sizeof operator.

// 	*****
// 	https://koor.fr/C/cstdlib/malloc.wp

// 	No. NULL is a value, not a type. NULL valued pointers point to nothing
// regardless the type of the pointer.

// <pointer var> = (pointer type cast)malloc( num bytes needed );

// */

// void	*ft_malloc(t_data *data, int type, int size)
// {
// 	char	*ptr_str1;
// 	int		*ptr_int1;
// 	char	**ptr_strs;
// 	int		**ptr_ints;

// 	ptr_str1 = NULL;
// 	ptr_int1 = NULL;
// 	ptr_strs = NULL;
// 	ptr_ints = NULL;
// 	if (size <= 0)
// 		return (NULL);
// 	if (type == TAB_STR1)
// 	{
// 		ptr_str1 = malloc(size);
// 		if (!ptr_str1)
// 		{
// 			ft_free_bin(ptr_str1, type, size);
// 			ft_lstclear_bin(data->bin);
// 			dprintf(2, "malloc failure dans lstadd_bin\n");// texte à prévoir
// 			return (NULL);//exit(EXIT_FAILURE);
// 			/*	suite : on quite la ligne de commande
// 				1. free data
// 				2. exit et pas return (NULL);
// 				*****
// 				Mais comment faire ?
// 				- si dans un child :
// 					- free tout data dans le child et exit
// 					- mais comment quitter dans le parent et les autres childs?
// 				- si dans parent :
// 					- free data (tout ou juste retour au prompt ?)
// 					- comment exit dans les childs et partout (forcer l'exit?)
// 			*/
// 		}
// 		ft_lstadd_bin(data, ptr_str1, type, size);
// 		return (ptr_str1);
// 	}
// 	else if (type == TAB_INT1)
// 	{
// 		ptr_int1 = malloc(sizeof(int) * size);
// 		if (!ptr_int1)
// 		{
// 			ft_free_bin(ptr_int1, type, size);
// 			ft_lstclear_bin(data->bin);
// 			// A VOIR : free data + exit
// 			return (NULL);// juste pour les tests
// 		}
// 		ft_lstadd_bin(data, ptr_int1, type, size);
// 		return (ptr_int1);
// 	}
// 	else if (type == TAB_STRS)
// 	{
// 		ptr_strs = malloc(sizeof(char *) * size);
// 		if (!ptr_strs)
// 		{
// 			ft_free_bin(ptr_strs, type, size);
// 			ft_lstclear_bin(data->bin);
// 			// A VOIR : free data + exit
// 			return (NULL);// juste pour les tests
// 		}
// 		ft_lstadd_bin(data, ptr_strs, type, size);
// 		return (ptr_strs);
// 	}
// 	else if (type == TAB_INTS)
// 	{
// 		ptr_ints = malloc(sizeof(int *) * size);
// 		if (!ptr_ints)
// 		{
// 			ft_free_bin(ptr_ints, type, size);
// 			ft_lstclear_bin(data->bin);
// 			// A VOIR : free data + exit
// 			return (NULL);// juste pour les tests
// 		}
// 		ft_lstadd_bin(data, ptr_ints, type, size);
// 		return (ptr_ints);
// 	}
// 	else
// 		return (ft_malloc2(data, type, size));
// }

// void	*ft_malloc2(t_data *data, int type, int size)
// {
// 	t_env	*ptr_env;
// 	t_cmd	*ptr_cmd;
// 	t_token	*ptr_token;
// 	t_bin	*ptr_bin;

// 	ptr_env = NULL;
// 	ptr_cmd = NULL;
// 	ptr_token = NULL;
// 	ptr_bin = NULL;
// 	if (type == LST_ENV)
// 	{
// 		ptr_env = malloc(sizeof(t_env) * size);
// 		if (!ptr_env)
// 		{
// 			ft_free_bin(ptr_env, type, size);
// 			ft_lstclear_bin(data->bin);
// 			// A VOIR : free data + exit
// 			return (NULL);// juste pour les tests
// 		}
// 		ft_lstadd_bin(data, ptr_env, type, size);
// 		return (ptr_env);
// 	}
// 	else if (type == LST_CMD)
// 	{
// 		ptr_cmd = malloc(sizeof(t_cmd) * size);
// 		if (!ptr_cmd)
// 		{
// 			ft_free_bin(ptr_cmd, type, size);
// 			ft_lstclear_bin(data->bin);
// 			// A VOIR : free data + exit
// 			return (NULL);// juste pour les tests
// 		}
// 		ft_lstadd_bin(data, ptr_cmd, type, size);
// 		return (ptr_cmd);
// 	}
// 	else if (type == LST_TOK)
// 	{
// 		ptr_token = malloc(sizeof(t_token) * size);
// 		if (!ptr_token)
// 		{
// 			ft_free_bin(ptr_token, type, size);
// 			ft_lstclear_bin(data->bin);
// 			// A VOIR : free data + exit
// 			return (NULL);// juste pour les tests
// 		}
// 		ft_lstadd_bin(data, ptr_token, type, size);
// 		return (ptr_token);
// 	}
// 	else// if (type == LST_BIN)
// 	{
// 		ptr_bin = malloc(sizeof(t_bin) * size);
// 		if (!ptr_bin)
// 		{
// 			ft_free_bin(ptr_bin, type, size);
// 			ft_lstclear_bin(data->bin);
// 			// A VOIR : free data + exit
// 			return (NULL);// juste pour les tests
// 		}
// 		ft_lstadd_bin(data, ptr_bin, type, size);
// 		return (ptr_bin);
// 	}
// }

// // //***********************
// // // 2e version plus compacte
// // //***********************

// // /* Fonction qui permet de récupérer le bon sizeof à utiliser dans ft_malloc
// // **	<SUMMARY> Function that gets the consistent 'sizeof' for ft_malloc function
// // */
// // size_t	ft_get_sizeof(int type)
// // {
// // 	if (type == TAB_STR1)
// // 	{
// // 		printf("sizeof TAB_STR1 = %ld\n", sizeof(char));//
// // 		return (sizeof(char));
// // 	}
// // 	else if (type == TAB_INT1)
// // 	{
// // 		printf("sizeof TAB_INT1 = %ld\n", sizeof(int));//
// // 		return (sizeof(int));
// // 	}
// // 	else if (type == TAB_INTS)
// // 		return (sizeof(int *));
// // 	else if (type == TAB_STRS)
// // 		return (sizeof(char *));
// // 	else if (type == LST_ENV)
// // 		return (sizeof(t_env));
// // 	else if (type == LST_CMD)
// // 		return (sizeof(t_cmd));
// // 	else if (type == LST_TOK)
// // 		return (sizeof(t_token));
// // 	return (0);
// // }

// // /*	<SUMMARY> Checks ptr's value:
// // **	  - if ptr = NULL --> clean t_bin linked list & all and exit (potential flag)
// // **	  - else --> add the address of the ptr (1st elem) to the t_bin linked list


// // on pourrait utiliser une variable statique: static t_bin *bin_head = NULL;
// // (et ne rien mettre dans data - mais comment nettoyer ?)
// // */
// // ft_check_malloc(t_data *data, void *ptr, int type, int size)
// // {
// // 	if (!ptr)
// // 	{
// // 		ft_free_bin(ptr, type, size);
// // 		ft_lstclear_bin(data->bin);
// // 		dprintf(2, "malloc failure dans lstadd_bin\n");// texte à prévoir
// // 		return (NULL);//exit(EXIT_FAILURE);
// // 			/*	suite : on quite la ligne de commande
// // 				1. free data
// // 				2. exit et pas return (NULL);
// // 				*****
// // 				Mais comment faire ?
// // 				- si dans un child :
// // 					- free tout data dans le child et exit
// // 					- mais comment quitter dans le parent et les autres childs?
// // 				- si dans parent :
// // 					- free data (tout ou juste retour au prompt ?)
// // 					- comment exit dans les childs et partout (forcer l'exit?)
// // 			*/
// // 	}
// // 	ft_lstadd_bin(data, ptr, type, size);
// // }

// // /*	<SUMMARY> Allocates memory depending on variable type (to malloc) & its size
// // */
// // void	*ft_malloc(t_data *data, int type, int size, int flag)
// // {
// // 	void	*ptr;

// // 	ptr = NULL;
// // 	(void) flag;//peut-être utile pour la gestion des child/parents...
// // 	//return NULL ou exit si pb malloc...
// // 	if (size <= 0)
// // 		return (NULL);
// // 	if (type == TAB_STR1)
// // 		ptr = (char *)ptr;
// // 	else if (type == TAB_INT1)
// // 		ptr = (int *)ptr;
// // 	else if (type == TAB_STRS)
// // 		ptr = (char **)ptr;
// // 	else if (type == TAB_INTS)
// // 		ptr = (int **)ptr;
// // 	else if (type == LST_ENV)
// // 		ptr = (t_env *)ptr;
// // 	else if (type == LST_CMD)
// // 		ptr = (t_cmd *)ptr;
// // 	else if (type == LST_TOK)
// // 		ptr = (t_token *)ptr;
// // 	else if (type == LST_BIN)
// // 		ptr = (t_bin *)ptr;
// // 	ptr = malloc(ft_get_sizeof(type) * size);
// // 	ft_check_malloc(data, ptr, type, size);
// // 	return (ptr);
// // }
