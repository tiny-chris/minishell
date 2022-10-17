/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:07:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/17 06:53:55 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//si c'est le contraire de "ce n'est pas un file ou un directory"
//alors on nettoie check et last dans ft_is_OK...
//et on renvoie 1
/// PEUT ETRE A COMPLETER
static int	ft_is_OK(char *token, char *last, char *check)
{
	if (access((const char *)token, F_OK || X_OK) == 0)
	{
		ft_handle_malloc(DELONE, check, 0, NULL);
		ft_handle_malloc(DELONE, last, 0, NULL);
		return (1);
	}
	return (0);
}

static int	ft_check_env_case(char *token, int len, char **s_path)
{
	int	i;
	char	*last;
	char	*check;

	i = -1;
	// dprintf(2, "passe dans check env case\n");//
	if (len < 4)
		return (0);
	last = ft_substr(token, len - 3, 3);
	ft_handle_malloc(ADD_M + TAB_STR1, last, 3, NULL);
	if (ft_strncmp(last, "env", 3) != 0)
		return (ft_handle_malloc(DELONE, last, 0, NULL), 0);
	// dprintf(2, "last = %s\n", last);//
	check = ft_substr(token, 0, len - 4);
	ft_handle_malloc(ADD_M + TAB_STR1, check, 0, NULL);
	// dprintf(2, "check = %s\n", check);//
	while (s_path[++i])
	{
		if ((ft_strncmp(s_path[i], check, len - 4) == 0) \
			&& ((int)ft_strlen(s_path[i]) == len - 4))
		{
			if (ft_is_OK(token, last, check))
				return (1);
		}
	}
	ft_handle_malloc(DELONE, check, 0, NULL);
	ft_handle_malloc(DELONE, last, 0, NULL);
	return (0);
}

/*	si token->next est nul
	*		alors on affiche env ==>
	*			- token->type = BUILTIN
	*			- token->token = env
	*
	*	si token->next n'est pas nul mais est vide (token[0] == '\0')
	*		alors:
	*			- si next->next == NULL --> mettre SP_QUOTES ???
	*			- si next->next != NULL --> ???
	*
	*	autrement, si token-> next n'est pas nul ni vide
	*		alors
	*			- récupérer token->fd (-1) pour token->next
	*			- récupérer token->env (0) pour token->next => QUEL CAS OU ENV != 0???????????????????
	*			- mettre token->next->type == COMMAND (vérif que ça mettra bien BUILTIN dans type token)
	*			- conserver token->next->token as is
	*			- supprimer le 1er token
	*/
static void	ft_deal_env_case(t_cmd *cmd, t_data *data)
{
	t_token	*tok;

	(void) data;
	// dprintf(2, "deal env case rentre dans ce cas\n");
	tok = cmd->token;
	if (tok->next == NULL)
	{
		ft_handle_malloc(DELONE, tok->token, 0, NULL);
		tok->token = ft_strdup("env");
		ft_handle_malloc(ADD_M + TAB_STR1, tok->token, 0, NULL);
		tok->type = BUILTIN;
	}
	else if (tok->next != NULL && tok->next->token[0] == '\0')
	{
		printf("cas à revoir\n");//A REVOIR
	}
	else//si tok->next != NULL && tok->next->token != '\0'
	{
		tok->next->fd = tok->fd;// VRAI ???
		tok->next->env = tok->env;// VRAI ??
		tok->next->type = COMMAND;//verif que ft_type_token va bien changer l'info si besoin
		cmd->token = tok->next;
		tok->next = NULL;
		ft_lstdelone_tok_bin(tok);
	}
}

int	ft_spec_env_case(t_cmd *cmd, t_data *data)
{
	// dprintf(2, "rentre dans spec env case\n");
	t_token	*token;
	int	len;
	char	**s_path;

	token = cmd->token;
	if (!token)
		return (0);// a revoir
	// dprintf(2, "token->token = %s et type = %d\n", token->token, token->type);
	//if (token->type != COMMAND)
	//	return (0);
	len = (int)ft_strlen(token->token);
	// dprintf(2, "len = %d\n", len);
	s_path = data->s_env_path;
	// if (s_path)
	// 	dprintf(2, "s_path ok et s_path[0] = %s\n", s_path[0]);
	if (ft_check_env_case(token->token, len, s_path))
		ft_deal_env_case(cmd, data);
	return (0);
}
