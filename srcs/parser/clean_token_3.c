/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:22:43 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/12 17:38:14 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_consec_quotes_len(char *token)
{
	int		i;
	int		j;
	int		len;
	char	c;

	i = 0;
	j = 0;
	len = ft_strlen(token);
	while (token[i])
	{
		if (token[i] == 34 || token[i] == 39)
		{
			c = token[i];
			if (token[i + 1] == c)
			{
				if (i == 0)// && token[i + 2] != '\0')
				{
					if (token[i + 2] != ' ')
					{
						i += 2;
						while ((token[i] && (token[i] == 34 || token[i] == 39))
						&& (token[i + 1] && token[i + 1] == token[i]))
							i += 2;
						if (token[i] == '\0')
						{
							len = 2;
							return (2);
						}
						else
							len -= i;
					}
				}
				else if (i > 0)
				{
					j = i;
					j += 2;
					while ((token[j] && (token[j] == 34 || token[j] == 39))
						&& (token[j + 1] && token[j + 1] == token[j]))
						j += 2;
					len -= (j - i);
					i = j - 1;
				}
			}
			else
			{
				i++;
				while (token[i] && token[i] != c)
					i++;
			}
		}
		i++;
	}
	return (len);
}

char	*ft_fill_consec_quotes(char *token, int len)
{
	char	*tmp_cmd;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	tmp_cmd = malloc(sizeof(char) * (len + 1));
	if (!tmp_cmd)
		return (NULL); // FREE TOUTTTT + EXIT OF COURSE
	while (token[i])
	{
		if (token[i] == 34 || token[i] == 39)
		{
			c = token[i];
			if (token[i + 1] == c)
			{
				if (i == 0)
				{
					i += 2;
					while (token[i] && (token[i] == 34 || token[i] == 39)
					&& (token[i + 1] && token[i + 1] == token[i]))
						i += 2;
					if (token[i] == '\0')
					{
						tmp_cmd[j] = c;
						j++;
						tmp_cmd[j] = c;
						j++;
						tmp_cmd[j] = '\0';
						return (tmp_cmd);
					}
					i--;
				}
				else if (i > 0)
				{
					i += 2;
					while (token[i] && (token[i] == 34 || token[i] == 39)
						&& (token[i + 1] && token[i + 1] == token[i]))
						i += 2;
					i--;
				}
			}
			else
			{
				tmp_cmd[j] = c;
				j++;
				i++;
				while (token[i] && token[i] != c)
				{
					tmp_cmd[j] = token[i];
					i++;
					j++;
				}
				tmp_cmd[j] = c;
				j++;
			}
		}
		else
		{
			tmp_cmd[j] = token[i];
			j++;
		}
		i++;
	}
	tmp_cmd[j] = '\0';
	return (tmp_cmd);
}

int	ft_clean_len(char *token)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(token);
	while (token[i])
	{
		if ((token[i] == 34 || token[i] == 39) && (token[i + 1] == token[i]))
			i++;
		else if (token[i] == 34 || token[i] == 39)
		{
			c = token[i];
			i++;
			while (token[i] && token[i] != c)
				i++;
			len -= 2;
		}
		i++;
	}
	return (len);
}

char	*ft_fill_clean_token(char *tmp_token, int len)
{
	char	*token;
	char 	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);// FREE TOUT ET EXIT
	while (tmp_token[i])
	{
		if ((tmp_token[i] == 34 || tmp_token[i] == 39) && (tmp_token[i + 1] == tmp_token[i]))
		{
			token[j] = tmp_token[i];
			j++;
			i++;
			token[j] = tmp_token[i];
			j++;
		}
		else if (tmp_token[i] == 34 || tmp_token[i] == 39)
		{
			c = tmp_token[i];
			i++;
			while (tmp_token[i] && tmp_token[i] != c)
			{
				token[j] = tmp_token[i];
				j++;
				i++;
			}
		}
		else
		{
			token[j] = tmp_token[i];
			j++;
		}
		i++;
	}
	token[j] = '\0';
	return (token);
}

void	ft_positive_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->token[i] != '\0')
	{
		if(token->token[i] < 0)
			token->token[i] = (-1) * token->token[i];
		i++;
	}
}

int	ft_clean_token(t_cmd *cmd, t_data *data)
{
	t_token		*token;
	// t_token		*n_token;
	char		*tmp_token;
	int			len;

	(void)data;// A SUPPRIMER
	token = cmd->token;
//	n_token = NULL;
	while (token)
	{
		tmp_token = NULL;
		dprintf(2, "token->token   = %s, strlen = %ld\n", token->token, ft_strlen(token->token));
		len = ft_consec_quotes_len(token->token);
		tmp_token = ft_fill_consec_quotes(token->token, len);
		dprintf(2, "csquotes token = %s --> len = %d vs. strlen = %ld\n", tmp_token, len, ft_strlen(tmp_token));
		free(token->token);
		//2e étape
		ft_space_quotes(tmp_token, token);
		len = ft_clean_len(tmp_token);
		token->token = ft_fill_clean_token(tmp_token, len);
		free(tmp_token);
		ft_positive_token(token);
	//	dprintf(2, "clean_token = %s\n", token->token);
	//	dprintf(2, "  --> len = %d vs. strlen = %ld\n", len, ft_strlen(token->token));
		token = token->next;
	}
	return (0);
}
