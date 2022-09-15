/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_empty_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:55:53 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/15 02:03:17 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	ft_del_empty_token(t_cmd *cmd, t_data *data)
// {
// 	t_token	*tok;
// 	t_token	*tmp1;
// 	t_token	*tmp2;

// 	(void) data;
// 	tok = cmd->token;
// 	tmp1 = NULL;
// 	tmp2 = NULL;
// 	if (tok && tok->token[0] == '\0')
// 	{
// 		if (tok->next)
// 		{
// 			dprintf(2, "y'a kekchose ici\n");
// 			tmp1 = tok;
// 			tmp2 = tok->next;
// 			tok = tmp2;
// 			ft_lstdelone_tok(tmp1);
// 		}
// 		else
// 		{
// 			dprintf(2, "passe ici\n");
// 			ft_lstdelone_tok(tok);
// 			cmd->token = NULL;
// 			dprintf(2, "passe là\n");
// 			return (0);
// 		}
// 	}
// 	cmd->token = tok;
// 	while (tok->next)
// 	{
// 		dprintf(2, "y'a kekchose la suite\n");
// 		if (tok->next->token[0] == '\0')
// 		{
// 			if (tok->next->next)
// 			{
// 				tmp1 = tok->next;
// 				tmp2 = tok->next->next;
// 				tok->next = tmp2;
// 				ft_lstdelone_tok(tmp1);
// 			}
// 			else
// 			{
// 				tmp1 = tok->next;
// 				tok->next = NULL;
// 				ft_lstdelone_tok(tok->next);
// 				return (0);
// 			}
// 		}
// 		tok = tok->next;
// 	}
// 	return (0);
// }

/*
Notes : la boucle = reprendre depuis le début de la liste à chaque fois
	- cas 1:	tok->token[0] == '\0'		--> on déplace la tête de la liste vers token-next et on supprime l'ancien 1er maillon tok
				et	1. tok->next est NULL
					2. tok->next n'est pas NULL
	- cas 2:	tok->token[0] != '\0'
				et 	1. tok->next est NULL			--> on sort de la fonction
					1. tok->next-token[0] == '\0'	--> on rattache le maillon tok->next->next à tok et on supprime le maillon token->next
					2. tok->next->token[0] != '\0'	--> on avance
*/
// int	ft_del_empty_token(t_cmd **cmd, t_data *data)
// {
// 	dprintf(2, "check dans empty token\n");
// 	t_token	*tok;
// 	t_token	*todel;
// 	t_token	*tmp;

// 	(void) data;
// 	if ((*cmd)->token == NULL)
// 		return (1);
// 	tok = (*cmd)->token;
// 	todel = NULL;
// 	tmp = NULL;
// 	while (tok)
// 	{
// 		dprintf(2, "check dans empty token - v2\n");
// 		if (tok->token[0] == '\0')
// 		{
// 			dprintf(2, "check dans empty token - v3 (tok empty)\n");
// 			if (tok->next != NULL)
// 			{
// 				dprintf(2, "check dans empty token - v3b\n");
// 				todel = tok;
// 				tok = tok->next;
// 				todel->next = NULL;
// 				ft_lstdelone_tok(todel);
// 				(*cmd)->token = tok;
// 			}
// 			else//pas de tok->next
// 			{
// 				ft_lstdelone_tok(tok);
// 				(*cmd)->token = NULL;
// 				return (0);
// 			}
// 		}
// 		else//(tok->token[0] != '\0' )
// 		{
// 			dprintf(2, "check dans empty token - v4 (tok PAS empty)\n");
// 			if (tok->next == NULL)
// 			{
// 				dprintf(2, "check dans empty token - v4b (pas de tok->next)\n");
// 				return (0);
// 			}
// 			else if (tok->next != NULL && tok->next->token[0] == '\0')
// 			{
// 				dprintf(2, "tok->next == 0 - v4c (tok->next == 0)\n");
// 				if (tok->next->next != NULL)
// 				{
// 					todel = tok->next;
// 					tmp = tok->next->next;
// 					todel->next = NULL;
// 					tok->next = tmp;
// 					ft_lstdelone_tok(todel);
// 					tok = (*cmd)->token;
// 				}
// 				else//next next is NULL
// 				{
// 					todel = tok->next;
// 					tok->next = NULL;
// 					ft_lstdelone_tok(todel);
// 					return (0);
// 				}
// 			}
// 			else
// 			{
// 				dprintf(2, "tok->next == 0 - v4c (tok->next != 0)\n");
// 				tok = tok->next;
// 			}
// 		}
// 	}
// 	return (0);
// }

int	ft_del_empty_token(t_cmd *cmd, t_data *data)
{
	dprintf(2, "check dans empty token\n");
	t_token	*tok;
	t_token	*todel;
	t_token	*tmp;

	(void) data;
	if (cmd->token == NULL)
		return (1);
	tok = cmd->token;
	todel = NULL;
	tmp = NULL;
	while (tok)
	{
		dprintf(2, "check dans empty token - v2\n");
		if (tok->token[0] == '\0')
		{
			dprintf(2, "check dans empty token - v3 (tok empty)\n");
			if (tok->next != NULL)
			{
				dprintf(2, "check dans empty token - v3b\n");
				todel = tok;
				tok = tok->next;
				todel->next = NULL;
				ft_lstdelone_tok(todel);
				cmd->token = tok;
			}
			else//pas de tok->next
			{
				ft_lstdelone_tok(tok);
				cmd->token = NULL;
				return (0);
			}
		}
		else//(tok->token[0] != '\0' )
		{
			dprintf(2, "check dans empty token - v4 (tok PAS empty)\n");
			if (tok->next == NULL)
			{
				dprintf(2, "check dans empty token - v4b (pas de tok->next)\n");
				return (0);
			}
			else if (tok->next != NULL && tok->next->token[0] == '\0')
			{
				dprintf(2, "tok->next == 0 - v4c (tok->next == 0)\n");
				if (tok->next->next != NULL)
				{
					todel = tok->next;
					tmp = tok->next->next;
					todel->next = NULL;
					tok->next = tmp;
					ft_lstdelone_tok(todel);
					tok = cmd->token;
				}
				else//next next is NULL
				{
					todel = tok->next;
					tok->next = NULL;
					ft_lstdelone_tok(todel);
					return (0);
				}
			}
			else
			{
				dprintf(2, "tok->next == 0 - v4c (tok->next != 0)\n");
				tok = tok->next;
			}
		}
	}
	return (0);
}
