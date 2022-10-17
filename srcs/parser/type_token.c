/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:40:01 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/17 07:11:13 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_built_in(char *token, t_data *data, int tok_len)
{
	int		len;
	int		j;
	char	**built_in;

	len = 0;
	j = 0;
	built_in = data->built_in;
	while (built_in[j])
	{
		len = ft_strlen(built_in[j]);
		if (len == tok_len)
		{
			if (ft_strncmp(token, built_in[j], len) == 0)
				return (1);
		}
		j++;
	}
	return (0);
}

t_token	*ft_get_token_echo(t_token **token)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_token = *token;
	tmp_token = tmp_token->next;
	while (tmp_token)
	{
		//printf("rentre dans boucle ft_get_token_echo\n");
		if (tmp_token->token[i] == '-')
		{
			i++;
		//	printf("on a un - mais un %c et i = %d\n", tmp_token->token[i], i);
		}
		else
		{
		//	printf("on n'a PAS un - \n");
			return (tmp_token);
		}
		if (tmp_token->token[i] != 'n')
		{
		//	printf("token[i = %d] = %c et diff de n\n", i, tmp_token->token[i]);
			return (tmp_token);
		}
		while (tmp_token->token[i] && tmp_token->token[i] == 'n')
			i++;
		if (tmp_token->token[i] == '\0')
		{
			tmp_token->type = WORD_N;
			ft_handle_malloc(DELONE, tmp_token->token, 0, NULL);
			// free(tmp_token->token);
			tmp_token->token = ft_strdup("-n");
			ft_handle_malloc(ADD_M + TAB_STR1, tmp_token->token, 0, NULL);
			//printf("clean token = %s, type =%d \n", tmp_token->token, tmp_token->type);
		}
		else
			return (tmp_token);
		tmp_token = tmp_token->next;
		i = 0;
	}
	return (NULL);
}

void	ft_echo_join_words_fill(t_token *token)
{
	t_token	*tmp;
	char	*char_tmp1;
	char	*char_tmp2;

	tmp = token;
	char_tmp1 = NULL;
	char_tmp2 = NULL;
	while (tmp)
	{
		if (tmp->type == SP_QUOTES)
		{
			ft_handle_malloc(DELONE, tmp->token, 0, NULL);
			// free(tmp->token);
			tmp->token = ft_strdup("");
			ft_handle_malloc(ADD_M + TAB_STR1, tmp->token, 0, NULL);
		}
		tmp = tmp->next;
	}
	tmp = token;
	if (tmp->next)
		tmp->type = WORD;
	while (tmp && tmp->next)
	{
		char_tmp1 = ft_strjoin(token->token, " ");

		// // TEST type_token
		// // TEST type_token --> desactiver la ligne char_tmp! = ft_strjoin...
		// char_tmp1 = NULL;// TEST type_token
		// dprintf(2, "check si char_tmp1 de type_token = NULL\n");// TEST type_token

		ft_handle_malloc(ADD_M + TAB_STR1, char_tmp1, 0, NULL);
		ft_handle_malloc(DELONE, token->token, 0, NULL);
		// free(token->token);
		char_tmp2 = ft_strjoin(char_tmp1, tmp->next->token);
		ft_handle_malloc(ADD_M + TAB_STR1, char_tmp2, 0, NULL);
		ft_handle_malloc(DELONE, char_tmp1, 0, NULL);
		// free(char_tmp1);
		token->token = ft_strdup(char_tmp2);
		ft_handle_malloc(ADD_M + TAB_STR1, token->token, 0, NULL);
		tmp = tmp->next;
		ft_handle_malloc(DELONE, char_tmp2, 0, NULL);
		// free(char_tmp2);
	}
	if (token)
	{
		//printf("last clean token = %s, type =%d \n", token->token, token->type);
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//ft_free_token(token->next);// remplacer lstclear par ça... à voir avec les **
		ft_lstclear_token(token->next);// nettoyage ici avec ft_handle_malloc !!!
		token->next = NULL;
	}
}

int	ft_type_token(t_cmd *cmd, t_data *data)
{
	t_token		*token;
	t_token		*n_token;
	t_token		*todel;
	t_token		*tmp;

	token = cmd->token;
	n_token = NULL;
	todel = NULL;
	if (ft_check_built_in(token->token, data, ft_strlen(token->token)))
		token->type = BUILTIN;
	else
		token->type = COMMAND;
	//check pour unset
	if (token && token->type == BUILTIN && (ft_strncmp(token->token, "unset", 5) == 0))
	{
		token = token->next;
		while (token)
		{
			if (token && ft_strncmp(token->token, "unset", ft_strlen(token->token)) == 0)
			{
				// printf("test\n");
				todel = token;
				tmp = token->next;
				ft_lstdelone_tok_bin(todel);
				cmd->token->next = tmp;
				token = cmd->token->next;
			}
			else
				break ;
		}
	}
	//check pour env
	//on retire les doublons de token-token 'env'
	//si le token suivant 'env' (2) contient un '=', c'est une variable qu'il faudra afficher/modifier
	//	avec les éléments après le '='
	//	et pareil pour les consécutifs qui contiennent '='
	//	si un token ne contient pas '=', alors il sera typé "token->env=1 pour erreur dans exec"
	//sinon, si le token suivant 'env' (2) ne contient pas de '='
	//	--> alors on supprime le token 'env' (1) et on modifie le token (2) en commande ou builtin
	//		et "token->env=1 pour erreur dans exec"
	else if (token && token->type == BUILTIN && (ft_strncmp(token->token, "env", 3) == 0)) // && data->env != NULL)
	{
		token = token->next;
		while (token)
		{
			if (token && ft_strncmp(token->token, "env", ft_strlen(token->token)) == 0)
			{
				todel = token;
				tmp = token->next;
				ft_lstdelone_tok_bin(todel);
				cmd->token->next = tmp;
				token = cmd->token->next;
			}
			else
				break ;
		}
		if (token && ft_new_strchr(token->token, '='))
		{
			while (token)
			{
				if (ft_new_strchr(token->token, '='))
					token = token->next;
				else
					break ;
			}
			if (token)
				token->env = 1;
		}
		else if (token)
		{
			if (ft_check_built_in(token->token, data, ft_strlen(token->token)))
				token->type = BUILTIN;
			else
				token->type = COMMAND;
			token->env = 1;
			todel = cmd->token;
			tmp = token;
			ft_lstdelone_tok_bin(todel);
			cmd->token = tmp;
		}
	}
	//check pour echo
	token = cmd->token;
	if (token && token->type == BUILTIN && (ft_strncmp(token->token, "echo", 4) == 0))
	{
		//printf("rentre dans condition -n pour echo avec quotes\n");
		n_token = ft_get_token_echo(&(cmd->token));
		if (n_token != NULL && n_token->next != NULL)
		{
			token = n_token;
			ft_echo_join_words_fill(token);
		}
	}
	return (0);
}
