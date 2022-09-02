/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:07:15 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/02 18:23:10 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstclear_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token != NULL)
	{
		tmp = token->next;
		ft_lstdelone_tok(token);
		token = tmp;
	}
}

void	ft_echo_join_words_fill(t_token *token)
{
	t_token	*tmp;
	char	*char_tmp1;
	char	*char_tmp2;

	tmp = token;
	char_tmp1 = NULL;
	char_tmp2 = NULL;
	while (tmp && tmp->next)
	{
		char_tmp1 = ft_strjoin(token->token," ");
		free(token->token);
		char_tmp2 = ft_strjoin(char_tmp1, tmp->next->token);
		free(char_tmp1);
		token->token = ft_strdup(char_tmp2);
		tmp = tmp->next;
		free(char_tmp2);
	}
	if (token)
		printf("last clean token = %s, type =%d \n", token->token, token->type);
	ft_lstclear_token(token->next);
	token->next = NULL;
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
			free(tmp_token->token);
			tmp_token->token = ft_strdup("-n");
			printf("clean token = %s, type =%d \n", tmp_token->token, tmp_token->type);
		}
		else
			return (tmp_token);
		tmp_token = tmp_token->next;
		i = 0;
	}
	return (NULL);
}

//token sans val negatives
void	ft_clean_token(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	t_token	*n_token;
	int		i;
	int		type_init;
	int		type_real;

	i = 0;
	token = cmd->token;
	n_token = NULL;
	while (token->token[i] != '\0')
	{
		if (token->token[i] < 0)
			token->token[i] = (-1) * (token->token[i]);
		i++;
	}
	type_init = token->type;
	if (ft_check_built_in(token->token, data, ft_strlen(token->token)))
		token->type = BUILTIN;
	type_real = token->type;
	printf("token = %s, size = %ld, type = %d\n", token->token, ft_strlen(token->token), token->type);
	token = token->next;
	i = 0;
	while (token)
	{
		while (token->token[i] != '\0')
		{
			if (token->token[i] < 0)
				token->token[i] = (-1) * (token->token[i]);
			i++;
		}
		printf("token = %s, size = %ld, type = %d\n", token->token, ft_strlen(token->token), token->type);
		token = token->next;
		i = 0;
	}
	token = cmd->token;
	//printf("type_real = %d, type_init = %d\n", type_real, type_init);
	//printf("res ft_strncmp token / echo = %d\n", ft_strncmp(token->token, "echo", 4));
	if (token && type_real != type_init && (ft_strncmp(token->token, "echo", 4) == 0) && ft_strlen(token->token) == 4)
	{
		//printf("rentre dans condition -n pour echo avec quotes\n");
		n_token = ft_get_token_echo(&(cmd->token));
		if (n_token != NULL && n_token->next != NULL)
		{
			token = n_token;
			ft_echo_join_words_fill(token);
		}
	}
}
