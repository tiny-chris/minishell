/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:17:53 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/09 12:22:19 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len_no_redir(char *raw_cmd_no_space)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(raw_cmd_no_space);
	while (raw_cmd_no_space[i])
	{
		if (raw_cmd_no_space[i] == 34 || raw_cmd_no_space[i] == 39)
		{
			c = raw_cmd_no_space[i];
			i++;
			while (raw_cmd_no_space[i] != c)
				i++;
		}
		else if (raw_cmd_no_space[i] == '>' || raw_cmd_no_space[i] == '<')
		{
			len--;
			i++;
			if (raw_cmd_no_space[i] && (raw_cmd_no_space[i] == '>' || raw_cmd_no_space[i] == '<'))
			{
				len--;
				i++;
			}
			if (raw_cmd_no_space[i] && (raw_cmd_no_space[i] == 34 || raw_cmd_no_space[i] == 39))
			{
				c = raw_cmd_no_space[i];
				i++;
				len--;
				while (raw_cmd_no_space[i] != c)
				{
					i++;
					len--;
				}
				len--;
				while (raw_cmd_no_space[i] && raw_cmd_no_space[i] != ' ' && raw_cmd_no_space[i] != '>' && raw_cmd_no_space[i] != '<')
				{
					len--;
					i++;
				}
				if (raw_cmd_no_space[i] == ' ')
					len--;
				else if (raw_cmd_no_space[i] == '>' || raw_cmd_no_space[i] == '<')
					i--;
			}
			else
			{
				while (raw_cmd_no_space[i] && raw_cmd_no_space[i] != ' ' && raw_cmd_no_space[i] != '>' && raw_cmd_no_space[i] != '<')
				{
					len--;
					i++;
				}
				if (raw_cmd_no_space[i] == ' ')
					len--;
				else if (raw_cmd_no_space[i] == '>' || raw_cmd_no_space[i] == '<')
					i--;
			}
		}
		i++;
	}
	return (len);
}

char	*ft_fill_no_redir(char *raw_cmd_no_space, int len)
{
	char	*no_redir_cmd;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	no_redir_cmd = malloc(sizeof(char) * (len + 1));
	if (!no_redir_cmd)
		return (NULL); // free tout
	while (raw_cmd_no_space[i])
	{
		if (raw_cmd_no_space[i] == 34 || raw_cmd_no_space[i] == 39)
		{
			c = raw_cmd_no_space[i];
			no_redir_cmd[j] = c;
			i++;
			j++;
			while (raw_cmd_no_space[i] && raw_cmd_no_space[i] != c)
			{
				no_redir_cmd[j] = raw_cmd_no_space[i];
				i++;
				j++;
			}
			no_redir_cmd[j] = c;
			j++;
		}
		else if (raw_cmd_no_space[i] == '>' || raw_cmd_no_space[i] == '<')
		{
			i++;
			if (raw_cmd_no_space[i] == '>' || raw_cmd_no_space[i] == '<')
				i++;
			if (raw_cmd_no_space[i] && (raw_cmd_no_space[i] == 34 || raw_cmd_no_space[i] == 39))
			{
				c = raw_cmd_no_space[i];
				i++;
				while (raw_cmd_no_space[i] != c)
					i++;
				while (raw_cmd_no_space[i] && raw_cmd_no_space[i] != ' ' && raw_cmd_no_space[i] != '>' && raw_cmd_no_space[i] != '<')
					i++;
				if (raw_cmd_no_space[i] != ' ')
					i--;
			}
			else
			{
				while (raw_cmd_no_space[i] && raw_cmd_no_space[i] != ' ' && raw_cmd_no_space[i] != '>' && raw_cmd_no_space[i] != '<')
					i++;
				if (raw_cmd_no_space[i] != ' ')
					i--;
			}
		}
		else
		{
			no_redir_cmd[j] = raw_cmd_no_space[i];
			j++;
		}
		i++;
	}
	no_redir_cmd[j] = '\0';
	return (no_redir_cmd);
}

int	ft_is_redir(char *raw_cmd_no_space, int *j)
{
	if (raw_cmd_no_space[*j] == '<')
	{
		(*j)++;
		if (raw_cmd_no_space[*j] && raw_cmd_no_space[*j] == '<')
		{
			(*j)++;
			return (13);
		}
		else
			return (12);
	}
	else if (raw_cmd_no_space[*j] == '>')
	{
		(*j)++;
		if (raw_cmd_no_space[*j] && raw_cmd_no_space[*j] == '>')
		{
			(*j)++;
			return (11);
		}
		else
			return (10);
	}
	return (0);
}

int	ft_get_redir_list(char *raw_cmd_no_space, t_token **tok_redir)
{
	int		i;
	int		j;
	int		type;
	char	c;

	i = 0;
	j = 0;
	type = 0;
	while(raw_cmd_no_space[i])
	{
		if (raw_cmd_no_space[i] == 34 || raw_cmd_no_space[i] == 39)
		{
			c = raw_cmd_no_space[i];
			i++;
			while (raw_cmd_no_space[i] && raw_cmd_no_space[i] != c)
				i++;
		}
		else
		{
			type = ft_is_redir(raw_cmd_no_space, &j);
			if (type)
			{
				if (ft_lstadd_token(tok_redir, type, ft_substr(raw_cmd_no_space, i, (j - i))))
					return (1); //free tout ce qu'il y a à free
				i = j;
				if (raw_cmd_no_space[j] && (raw_cmd_no_space[j] == 34 || raw_cmd_no_space[j] == 39))
				{
					c = raw_cmd_no_space[j];
					j++;
					while (raw_cmd_no_space[j] != c)
						j++;
					j++;
				}
				else
				{
					while (raw_cmd_no_space[j] && raw_cmd_no_space[j] != ' ' && raw_cmd_no_space[j] != '>'  && raw_cmd_no_space[j] != '<')
						j++;
				}
				if (ft_lstadd_token(tok_redir, type + 10, ft_substr(raw_cmd_no_space, i, j - i)))
					return (1); //free tout ce qu'il y a à free
				i = j - 1;
			}
		}
		i++;
		j = i;
	}
	return (0);
}

int	ft_get_redir(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	cmd = data->cmd;
	len = 0;
	while (cmd)
	{
		dprintf(2, "passe dans get redir avant calcul len = %d\n", len);
		len = ft_len_no_redir(cmd->raw_cmd_no_space);
		dprintf(2, "passe dans get redir apres calcul len = %d\n", len);
		cmd->no_redir_cmd = ft_fill_no_redir(cmd->raw_cmd_no_space, len);
		if (!cmd->no_redir_cmd)
			return (1); // FREE tout ce qu'il y a à free
		dprintf(2, "cmd sans redir = %s\n", cmd->no_redir_cmd);
		dprintf(2, "cmd sans redir len = %d vs; strlen = %ld\n", len, ft_strlen(cmd->no_redir_cmd));
		if (ft_get_redir_list(cmd->raw_cmd_no_space, &cmd->tok_redir))
			return (1); // FREE tout ce qu'il y a à free
		cmd = cmd->next;
	}
//	if (ft_clean_redir(data))
//		return (1); // FREE tout ce qu'il y a à free + EXIT

	//PRINT
	t_cmd	*tmp;
	t_token	*token;

	tmp = data->cmd;
	while (tmp)
	{
		token = tmp->tok_redir;
		while (token)
		{
			dprintf(2, "token redir = %s, type = %d\n", token->token, token->type);
			token = token->next;
		}
		tmp = tmp->next;
	}

	return (0);
}
