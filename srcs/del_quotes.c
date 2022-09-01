/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:22:23 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/01 16:53:15 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_allspace(char *str, int i, char c)
{
	int	j;

	//j = i + 1;
	j = i;
	j++;
	if (str[j] == c)
		return (0);
	while (str[j] && str[j] != c)
	{
		if (str[j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	ft_unquote_cmd_len(char *raw_cmd)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(raw_cmd);
	//printf("strlen raw_cmd = %d\n", len);
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
		{
			c = raw_cmd[i];
			if (ft_is_allspace(raw_cmd, i, c) == 1)
				len -= 2;
			i++;
			while (raw_cmd[i] && raw_cmd[i] != c)
				i++;
		}
		else if (raw_cmd[i] == ' ')
		{
			i++;
			while (raw_cmd[i] && raw_cmd[i] == ' ')
			{
				len--;
				i++;
			}
			i--;
		}
		else if (raw_cmd[i] == '$')
		{
			i++;
			while(raw_cmd[i] == '$')
			{
				i++;
				len--;
			}
			if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
				len--;
			i--;
		}
		else if (raw_cmd[i] == '>' || raw_cmd[i] == '<')
		{
			c = raw_cmd[i];
			i++;
			if (raw_cmd[i] == c)
				i++;
			if (raw_cmd[i] == ' ')
			{
				i++;
				len--;
				while (raw_cmd[i] && raw_cmd[i] == ' ')
				{
					len--;
					i++;
				}
				i--;
			}
		}
		i++;
	}
	//printf("len à malloc %d\n", len);
	return (len);
}

static void	ft_empty_quotes_case(char *raw_cmd, int *i, char *unquote_cmd, int *j)
{
	char	c;

	c = raw_cmd[*i];
	unquote_cmd[*j] = raw_cmd[*i];
	(*i)++;
	(*j)++;
	while (raw_cmd[*i] && raw_cmd[*i] != c)
	{
		unquote_cmd[*j] = (-1) * raw_cmd[*i];
		(*i)++;
		(*j)++;
	}
	unquote_cmd[*j] = raw_cmd[*i];
	(*j)++;
}

static void	ft_quotes_case(char *raw_cmd, int *i, char *unquote_cmd, int *j)
{
	char	c;
//	int		k;

	c = raw_cmd[*i];
//	k = (*i) + 1;
	if (ft_is_allspace(raw_cmd, *i, c) == 0)
		ft_empty_quotes_case(raw_cmd, i, unquote_cmd, j);
	else
	{
		(*i)++;
		if (raw_cmd[*i] && raw_cmd[*i] != c && !(c == 34 && raw_cmd[*i] =='$'))
		{
			unquote_cmd[*j] = (-1) * raw_cmd[*i];
			printf("char unquote_cmd[*j = %d] = %c\n", (*j), unquote_cmd[*j]);
			(*i)++;
			(*j)++;
		}
		if (raw_cmd[*i])
		{
			while (raw_cmd[*i] && raw_cmd[*i] != c)
			{
				if ((raw_cmd[*i] == '$' && c == 39) || (raw_cmd[*i] == '<') || (raw_cmd[*i] == '>') || (raw_cmd[*i] == ' '))
				{
					unquote_cmd[*j] = (-1) * raw_cmd[*i];
					printf("char unquote_cmd[*j = %d] = %c\n", (*j), unquote_cmd[*j]);
				}
				else if (raw_cmd[*i] == '$' && c == 34 && raw_cmd[*i + 1] == '$')
				{
					(*i)++;
					while (raw_cmd[*i] && raw_cmd[*i] == '$')
						(*i)++;
					(*i)--;
					unquote_cmd[*j] = raw_cmd[*i];
				}
				else
					unquote_cmd[*j] = raw_cmd[*i];
				(*i)++;
				(*j)++;
			}
		}
	}
}

static void	ft_spaces_case(char *raw_cmd, int *i, char *unquote_cmd, int *j)
{
	unquote_cmd[*j] = raw_cmd[*i];
	(*i)++;
	(*j)++;
	while (raw_cmd[*i] && raw_cmd[*i] == ' ')
		(*i)++;
	(*i)--;
}

/*
	- simple quote:
		- si caractere d'apres = meme quote --> copier les quotes (les 2)
		- si que des espaces entre les quotes --> on copie tout (même les quotes)
		- sinon: tant qu'on n'a pas atteint la quote fermante, on avance
			et on regarde caractère par caractère et:
			- si $ : on copie et on passe en négatif
			- si < : on copie et on passe en négatif
			- si > : on copie et on passe en négatif
			- sinon on copie uniquement le caractère
			et on ne copie ma quote fermante

	- double quote:
		- si caractere d'apres = meme quote --> copier les quotes (les 2)
		- si que des espaces entre les quotes --> on copie tout (même les quotes)
		- sinon: tant qu'on n'a pas atteint la quote fermante, on avance
			et on regarde caractère par caractère et:
			- si < : on copie et on passe en négatif
			- si > : on copie et on passe en négatif
			- sinon on copie uniquement le caractère
			et on ne copie ma quote fermante

	+ ne pas copier qu'un espace si plusieurs espaces contigus
*/
char	*ft_fill_unquote_cmd(char *raw_cmd, int len)
{
	char	*unquote_cmd;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	unquote_cmd = NULL;
	unquote_cmd = malloc(sizeof(char) * (len + 1));
	if (!unquote_cmd)
		return (NULL);
	while (raw_cmd[i])
	{
		if (raw_cmd[i] == 34 || raw_cmd[i] == 39)
			ft_quotes_case(raw_cmd, &i, unquote_cmd, &j);
		else if ((raw_cmd[i] == '>') || (raw_cmd[i] == '<'))
		{
			c = raw_cmd[i];
			unquote_cmd[j] = raw_cmd[i];
			i++;
			j++;
			if (raw_cmd[i] == c)
			{
				unquote_cmd[j] = raw_cmd[i];
				i++;
				j++;
			}
			if (raw_cmd[i] == ' ')
			{
				i++;
				while (raw_cmd[i] && raw_cmd[i] == ' ')
					i++;
			}
			i--;
		}
		else if (raw_cmd[i] == ' ')
			ft_spaces_case(raw_cmd, &i, unquote_cmd, &j);
		else if (raw_cmd[i] == '$' && raw_cmd[i + 1] && raw_cmd[i + 1] == '$')
		{
			i++;
			while (raw_cmd[i] == '$')
				i++;
			i--;
			//cas de $'USER' ou $"coucou" --> bash ne conserve pas le $
			if (raw_cmd[i + 1] != 34 && raw_cmd[i + 1] != 39)
			{
				unquote_cmd[j] = raw_cmd[i];
				j++;
			}
		}
		else
		{
			if ((raw_cmd[i] != '$') ||
			((raw_cmd[i] == '$') && (raw_cmd[i + 1] != 34 && raw_cmd[i + 1] != 39)))
			{
				unquote_cmd[j] = raw_cmd[i];
				j++;
			}
		}
		i++;
	}
	unquote_cmd[j] = '\0';
	return (unquote_cmd);
}

/*	objectif = malloc "unquote_cmd" par cmd
	//x malloc unquote_cmd
	//x copier texte (sans quote)
	//  /!\ mettre les caractères spéciaux en négatif (chevrons et expand)
*/
int	ft_del_quotes(t_data *data)
{
	t_cmd	*cmd;
	int		unquote_cmd_len;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->raw_cmd == NULL)/////chris
			return (2);// check si la commande n'est pas nulle
		unquote_cmd_len = ft_unquote_cmd_len(cmd->raw_cmd);
		//printf("len cmd unquote = %d\n", unquote_cmd_len);
		cmd->unquote_cmd = ft_fill_unquote_cmd(cmd->raw_cmd, unquote_cmd_len);
		if (!cmd->unquote_cmd)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!!
		printf("unquote_cmd = %s, size = %ld\n", cmd->unquote_cmd, ft_strlen(cmd->unquote_cmd));
		cmd = cmd->next;
	}
	return (0);
}
