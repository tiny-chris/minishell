// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   token.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/08/29 12:40:11 by cgaillag          #+#    #+#             */
// /*   Updated: 2022/09/07 17:53:54 by cgaillag         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// t_token	*ft_lstlast_tok(t_token *lst)
// {
// 	t_token	*node;

// 	if (!lst)
// 		return (0);
// 	node = lst;
// 	while (node->next)
// 		node = node->next;
// 	return (node);
// }

// int	ft_lstadd_token(t_token **tok, int type, char *token)
// {
// 	t_token	*new;
// 	t_token	*last;

// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 	{
// 		ft_free_token(tok);
// 		return (1);
// 	}
// 	new->token = token;
// 	//dprintf(2, "new token %s, size = %ld\n", new->token, ft_strlen(new->token));
// 	new->type = type;
// 	//dprintf(2, "type %d\n", new->type);
// 	new->next = NULL;
// 	if (ft_lstlast_tok(*tok) == 0)
// 	{
// 		*tok = new;
// 		return (0);
// 	}
// 	last = ft_lstlast_tok(*tok);
// 	last->next = new;
// 	return (0);
// }

// /*
// // cf. val enum s_type
// */

// int	ft_is_redir(char *clean_cmd, int *i)
// {
// 	if (clean_cmd[*i] == '<')
// 	{
// 		(*i)++;
// 		if (clean_cmd[*i] && clean_cmd[*i] == '<')
// 		{
// 			(*i)++;
// 			return (13);
// 		}
// 		else
// 			return (12);
// 	}
// 	else if (clean_cmd[*i] == '>')
// 	{
// 		(*i)++;
// 		if (clean_cmd[*i] && clean_cmd[*i] == '>')
// 		{
// 			(*i)++;
// 			return (11);
// 		}
// 		else
// 			return (10);
// 	}
// 	return (0);
// }

// int	ft_check_built_in(char *clean_cmd, t_data *data, int i)
// {
// 	int	len;
// 	int	j;
// 	char **built_in;

// 	len = 0;
// 	j = 0;
// 	built_in = data->built_in;
// 	while (built_in[j])
// 	{
// 		len = ft_strlen(built_in[j]);
// 		if (len == i)
// 		{
// 			if (ft_strncmp(clean_cmd, built_in[j], len) == 0)
// 				return (1);
// 		}
// 		j++;
// 	}
// 	return (0);
// }

// int	ft_check_word_n(char *clean_cmd_no_redir, int *i, t_token **token)
// {
// 	int	j;

// 	j = (*i);
// 	while (clean_cmd_no_redir[j])
// 	{
// 		//printf("passe dans ft_checj word n\n");
// 		if (clean_cmd_no_redir[j] == '-')
// 		{
// 			//printf("1er char = -\n");
// 			j++;
// 		}
// 		else
// 			return (0);
// 		if (clean_cmd_no_redir[j] && clean_cmd_no_redir[j] != 'n')
// 		{
// 			//printf("1er char = n\n");
// 			return (0);
// 		}
// 		while (clean_cmd_no_redir[j] && clean_cmd_no_redir[j] == 'n')
// 			j++;
// 		if (clean_cmd_no_redir[j] == ' ' || clean_cmd_no_redir[j] == '\0')
// 		{
// 			if (ft_lstadd_token(token, WORD_N, ft_strdup("-n")))
// 				return (-1); // free all
// 		}
// 		else
// 			return (0);
// 		j++;
// 		(*i) = j;
// 	}
// 	return (1);
// }

// t_token	*ft_get_token(t_cmd *cmd, t_data *data)
// {
// 	char	*clean_cmd_no_redir;
// 	t_token	*token;
// 	int		type;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	token = NULL;
// 	clean_cmd_no_redir = cmd->clean_cmd_no_redir;
// 	while (clean_cmd_no_redir[i] && clean_cmd_no_redir[i] != ' ')
// 		i++;
// 	if (ft_check_built_in(clean_cmd_no_redir, data, i))
// 		type = BUILTIN;
// 	else
// 		type = COMMAND;
// 	if (ft_lstadd_token(&token, type, ft_substr(clean_cmd_no_redir, j, i - j)))
// 		return (NULL);
// 	if (!clean_cmd_no_redir[i])
// 	{
// 		cmd->token = token;
// 		return (0);
// 	}
// 	i++;// le 1 = ' '
// 	j = i;
// 	//printf("val de i après lecture du 1er arg + espace = %d\n", i);
// 	if (clean_cmd_no_redir[j])
// 	{
// 		if (type == BUILTIN && ft_strncmp(token->token, "echo", 4) == 0)
// 		{
// 			//printf("builtin (1) = %d et val token->token = %s\n", type, token->token);
// 			//printf("resul ft_strncmp = %d\n", ft_strncmp(token->token, "echo", 4));
// 			ft_check_word_n(clean_cmd_no_redir, &i, &token);
// 			j = i;
// 			if (clean_cmd_no_redir[j] != '\0')
// 			{
// 				while (clean_cmd_no_redir[j])
// 					j++;
// 				if (ft_lstadd_token(&token, WORD, ft_substr(clean_cmd_no_redir, i, j - i)))
// 					return (NULL);
// 			}
// 			cmd->token = token;
// 			return (0);
// 		}
// 		else
// 		{
// 			while (clean_cmd_no_redir[j])
// 			{
// 				//dprintf(2, "i: %d\n, j: %d\n", i, j);
// 				while (clean_cmd_no_redir[j] != '\0' && clean_cmd_no_redir[j] != ' ')
// 					j++;
// 				//dprintf(2, "i: %d\n, j: %d\n", i, j);
// 				if (ft_lstadd_token(&token, WORD, ft_substr(clean_cmd_no_redir, i, j - i)))
// 					return (NULL);
// 				if (clean_cmd_no_redir[j] == '\0')
// 				{
// 					cmd->token = token;
// 					return (0);
// 				}
// 				j++;
// 				i = j;
// 			}
// 		}
// 	}
// 	cmd->token = token;
// 	return (0);
// }

// int	ft_len_no_redir(char *clean_cmd)
// {
// 	int	len;
// 	int	i;

// 	i = 0;
// 	len = ft_strlen(clean_cmd);
// 	while(clean_cmd[i])
// 	{
// 		if (clean_cmd[i] == '>' || clean_cmd[i] == '<')
// 		{
// 			len--;
// 			i++;
// 			if (clean_cmd[i] && (clean_cmd[i] == '>' || clean_cmd[i] == '<'))
// 			{
// 				len--;
// 				i++;
// 			}
// 			while (clean_cmd[i] && clean_cmd[i] != ' ' && clean_cmd[i] != '>' && clean_cmd[i] != '<')
// 			{
// 				len--;
// 				i++;
// 			}
// 			if (clean_cmd[i] == ' ')
// 				len--;
// 			i--;
// 		}
// 		i++;
// 	}
// 	return (len);
// }

// int	ft_get_redir_list(char *clean_cmd, t_token **tok_redir)
// {
// 	int	i;
// 	int	j;
// 	int	type;

// 	i = 0;
// 	j = 0;
// 	type = 0;
// 	while(clean_cmd[j])
// 	{
// 		type = ft_is_redir(clean_cmd, &i);
// 		if (type)
// 		{
// 			if (ft_lstadd_token(tok_redir, type, ft_substr(clean_cmd, j, (i - j))))
// 				return (1); //free tout ce qu'il y a à free
// 			j = i;
// 			while (clean_cmd[i] && clean_cmd[i] != ' ' && clean_cmd[i] != '>'  && clean_cmd[i] != '<')
// 				i++;
// 			if (ft_lstadd_token(tok_redir, type + 10, ft_substr(clean_cmd, j, i - j)))
// 				return (1); //free tout ce qu'il y a à free
// 			j = i - 1;
// 		}
// 		j++;
// 		i = j;
// 	}
// 	return (0);
// }

// void	ft_fill_no_redir(char *clean_cmd, char *clean_cmd_no_redir)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while(clean_cmd[j])
// 	{
// 		if (clean_cmd[j] == '>' || clean_cmd[j] == '<')
// 		{
// 			j++;
// 			if ((clean_cmd[j] == '>' || clean_cmd[j] == '<'))
// 				j++;
// 			while (clean_cmd[j] && clean_cmd[j] != ' ' && clean_cmd[j] != '>' && clean_cmd[j] != '<')
// 				j++;
// 			if (clean_cmd[j] != ' ')
// 				j--;
// 		}
// 		else
// 		{
// 			clean_cmd_no_redir[i] = clean_cmd[j];
// 			i++;
// 		}
// 		j++;
// 	}
// 	clean_cmd_no_redir[i] = '\0';
// }

// int	ft_get_redir(t_cmd	*cmd)
// {
// 	char	*clean_cmd;
// 	char	*clean_cmd_no_redir;
// 	t_token *tok_redir;

// 	tok_redir = NULL;
// 	clean_cmd = cmd->clean_cmd;
// 	if (!clean_cmd)
// 		return (1);
// 	clean_cmd_no_redir = malloc(sizeof(char) * (ft_len_no_redir(clean_cmd) + 1));
// 	if (!clean_cmd_no_redir)
// 		return (1); // bien free tout ce qu'il y a à free
// 	if (ft_get_redir_list(clean_cmd, &tok_redir))
// 		return (1);// FREE
// 	cmd->tok_redir = tok_redir;
// 	cmd->clean_cmd_no_redir = clean_cmd_no_redir;
// 	ft_fill_no_redir(clean_cmd, clean_cmd_no_redir);
// 	return (0);
// }

// int	ft_tokenizer(t_data *data)
// {
// 	t_cmd	*cmd;

// 	cmd = data->cmd;
// 	while (cmd)
// 	{
// 		if (ft_get_redir(cmd))
// 			return (1);
// 		//printf("clean cmd no redir = %s\n", cmd->clean_cmd_no_redir);
// 		ft_get_token(cmd, data);
// 		//ft_clean_token(cmd, data);
// 		cmd = cmd->next;
// 	}
// 	t_cmd	*tmp;
// 	t_token	*token;


// 	tmp = data->cmd;
// 	while (tmp)
// 	{
// 		token = tmp->token;
// 		while (token)
// 		{
// 			printf("token = %s, type = %d\n", token->token, token->type);
// 			token = token->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
