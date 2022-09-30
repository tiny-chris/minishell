/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:41:20 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/16 14:13:44 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* STEPS
	- clean 1st token
	- check built-in
		- if command --> cleaning (negative, delete quotes...)
			BEWARE: empty token
			BEWARE: $?
		- if built-in
			--> check specific situations incl. echo case (WORD_N...)
*/

static int	ft_only_neg_space(char *token, int i)
{
	if (token[i] == 34 && token[i + 1] == 34)
		return (0);
	if (token[i] == 34)
	{
		i++;
		while (token[i] && token[i] != 34)
		{
			if (token[i] != -32)
				return (0);
			i++;
		}
		if (token[i] != 34)
			return (0);
	}
	return (1);
}

//pour retirer les double quotes avec des espaces uniquement à l'interieur
static int	ft_new_len_2(char *token)
{
	int		len;
	int		i;
	char	c;

	len = 0;
	i = 0;
	while (token[i])
	{// cas des simples quotes négatives
		if (token[i] == -39)
		{
			i++;
			while (token[i] && token[i] != -39)
				i++;
			len +=2;
		}
	 	else if ((token[i] == 34) && ft_only_neg_space(token, i))
		{
			c = token[i];
			i++;
			len += 2;
			while (token[i] && token[i] != c)
				i++;
		}
		i++;
	}
	return (len);
}

static int ft_new_len(char *token)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(token);
	if (token[i] == -34 && token[i + 1] == -34)
	{
		while (token[i] && token[i] == -34 && token[i + 1] && token[i + 1] == -34)
			i += 2;
		if (token[i] == '\0')
			return (2);
		i = 0;
	}
	while (token[i])
	{
		if (token[i] == -34)
		{
			i++;
			while (token[i] && token[i] != -34)
				i++;
			if (token[i] == '\0')
			{
				printf("test rentre dasn le if \n");
				return (len);
			}
			len -= 2;
		}
		i++;
	}
	len -= ft_new_len_2(token);// retirer les simple quotes négatives mais garder le texte entre les quotes
	return (len);
}

int	ft_check_dq_neg(char *old_token, int i)
{
	if (old_token[i] == -34)
	{
		i++;
		while (old_token[i] && old_token[i] != -34)
			i++;
		if (old_token[i] == '\0')
			return (0);
	}
	return (1);
}

int	ft_first_token(t_token *token, int len)
{
	char	*new_token;
	char	*old_token;
	char 	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	old_token = token->token;
	new_token = malloc(sizeof(char) * (len + 1));
	if (!new_token)
		return (1);// FREE TOUT ET EXIT
	if ((old_token[i] == -34 && old_token[i + 1] == -34))
	{
		while (old_token[i] && old_token[i] == -34 && old_token[i + 1] == -34)
			i += 2;
		if (old_token[i] == '\0')
		{
			new_token[j] = 34;
			new_token[j + 1] = 34;
			new_token[j + 2] = '\0';
			free(old_token);
			token->token = new_token;
			return (0);
		}
		i = 0;
	}
	while (old_token[i])
	{
		if (old_token[i] == -34 && ft_check_dq_neg(old_token, i))//on copie pas les quotes
		{
			i++;
			while (old_token[i] != -34)
			{
				new_token[j] = old_token[i];
				i++;
				j++;
			}
		}
		else if (old_token[i] == -39)
		{
			i++;
			while (old_token[i] && old_token[i] != -39)
			{

				new_token[j] = old_token[i];
				i++;
				j++;
			}
		}
		else if ((old_token[i] == 34) && ft_only_neg_space(old_token, i))
		{
			c = old_token[i];
			i++;
			while (old_token[i] != c)
			{
				new_token[j] = old_token[i];
				i++;
				j++;
			}
		}
		else
		{
			new_token[j] = old_token[i];
			j++;
		}
		i++;
	}
	new_token[j] = '\0';
	free(old_token);
	token->token = new_token;
	return (0);
}

void	ft_positive_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->token[i])
	{
		if(token->token[i] < 0)
			token->token[i] = (-1) * token->token[i];
		i++;
	}
}

int	ft_check_built_in(char *token, t_data *data, int i)
{
	int	len;
	int	j;
	char **built_in;

	len = 0;
	j = 0;
	built_in = data->built_in;
	while (built_in[j])
	{
		len = ft_strlen(built_in[j]);
		if (len == i)
		{
			if (ft_strncmp(token, built_in[j], len) == 0)
				return (1);
		}
		j++;
	}
	return (0);
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
		//printf("last clean token = %s, type =%d \n", token->token, token->type);
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
			//printf("clean token = %s, type =%d \n", tmp_token->token, tmp_token->type);
		}
		else
			return (tmp_token);
		tmp_token = tmp_token->next;
		i = 0;
	}
	return (NULL);
}

int	ft_clean_token(t_cmd *cmd, t_data *data)
{
	t_token		*token;
	t_token		*n_token;
//	int			i;
	int			len;

	(void)data;
	token = cmd->token;
	n_token = NULL;
//	i = 0;
	while (token)
	{
		len = ft_new_len(token->token);
		printf("len clean token = %d\n", len);
		ft_first_token(token, len);
		ft_positive_token(token);
		//printf("new clean token = %s, len = %ld\n", token->token, ft_strlen(token->token));
		token = token->next;
	}
	token = cmd->token;
	if (ft_check_built_in(token->token, data, ft_strlen(token->token)))
		token->type = BUILTIN;
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
