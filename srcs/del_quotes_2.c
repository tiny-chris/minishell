/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:43:56 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/12 11:56:15 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_allspace(char *str, int i, char c)
{
	int	j;

	j = i;
	j++;
	if (str[j] == c)
		return (1);
	while (str[j] && str[j] != c)
	{
		if (str[j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int	ft_contains_doll(char *undoll_cmd, int i, char c)
{
	int	j;

	j = i;
	j++;
	while (undoll_cmd[j] && undoll_cmd[j] != c)
	{
		if (undoll_cmd[j] == '$')
			return (1);
		j++;
	}
	return (0);
}

static int	ft_contains_quote(char *undoll_cmd, int i, char c, char q)
{
	int	j;

	j = i;
	j++;
	while (undoll_cmd[j] != c)
	{
		if (undoll_cmd[j] == q)
			return (1);
		j++;
	}
	return (0);
}

/*	***** PARSING | unquote_cmd - LEN *****
**	<SUMMARY>
**	Defines the length of the new string by removing useless quotes
**	<PARAM>		{char *} undoll_cmd --> from del_dolls.c
**	<RETURNS>	the size of the new string to be copied unquote_cmd (int)
*/



// TO BE NORMED
/*	Notes pour nous:
	tant que le char * de ref existe (undoll_cmd) :
	1. 	si on rencontre des quotes simples ou doubles,
		alors :	- si il n'y a PAS que des espaces --> quotes en négatif et on enlève les quotes, sauf s'il y a un $ et qu'on est sur des doubles (rajoute les quotes)
				- tant qu'on n'est pas arrivé sur la quote fermante, on avance
	2. 	autrement, on avance
on retourne la len au final
*/
int	ft_unquote_cmd_len(char *undoll_cmd)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(undoll_cmd);
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == 39)
		{
			c = 39;
			if (ft_contains_quote(undoll_cmd, i, c, 34) == 0)
			// si ne contient pas de db quote, on 'peut' enlever les quotes de len
			//(ie, s'il y a des double quotes, on n'enlève pas de la len)
			// ou compter les pairs et impairs?
			{
				if (ft_is_allspace(undoll_cmd, i, c) == 0)
					len -= 2;
				if (ft_contains_doll(undoll_cmd, i, c))
					len += 2;
			}
			i++;
	 		while (undoll_cmd[i] && undoll_cmd[i] != c)
	 			i++;
		}
		else if (undoll_cmd[i] == 34)
		{
			c = 34;
			if (ft_is_allspace(undoll_cmd, i, c) == 0)
				len -= 2;
			if (ft_contains_doll(undoll_cmd, i, c))
				len += 2;
			i++;
	 		while (undoll_cmd[i] && undoll_cmd[i] != c)
	 			i++;
		}
		i++;
	}
	return (len);
}

static void	ft_empty_quotes_case(char *undoll_cmd, int *i, char *unquote_cmd, int *j)
{
	char	c;

	c = undoll_cmd[*i];
	unquote_cmd[*j] = undoll_cmd[*i];
	(*i)++;
	(*j)++;
	while (undoll_cmd[*i] && undoll_cmd[*i] != c)
	{
		unquote_cmd[*j] = (-1) * undoll_cmd[*i];
		(*i)++;
		(*j)++;
	}
	unquote_cmd[*j] = undoll_cmd[*i];
	(*j)++;
}

static void	ft_quotes_case(char *undoll_cmd, int *i, char *unquote_cmd, int *j)
{
	char	c;

	c = undoll_cmd[*i];
	if (c == 39)
	{
		if (ft_contains_quote(undoll_cmd, *i, c, 34) == 0)
		{
			if (ft_is_allspace(undoll_cmd, *i, c))
				ft_empty_quotes_case(undoll_cmd, i, unquote_cmd, j);
			else
			{
				(*i)++;
				if (undoll_cmd[*i] && undoll_cmd[*i] != c)
				{
					unquote_cmd[*j] = (-1) * undoll_cmd[*i];
					(*i)++;
					(*j)++;
				}
				while (undoll_cmd[*i] && undoll_cmd[*i] != c)
				{
					if ((undoll_cmd[*i] == '$' && c == 39) || (undoll_cmd[*i] == '<') || (undoll_cmd[*i] == '>') || (undoll_cmd[*i] == ' '))
						unquote_cmd[*j] = (-1) * undoll_cmd[*i];
					else
						unquote_cmd[*j] = undoll_cmd[*i];
					(*i)++;
					(*j)++;
				}
			}
		}
		else
		{
			unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			(*i)++;
			(*j)++;
			while (undoll_cmd[*i] && undoll_cmd[*i] != c)
			{
				if ((undoll_cmd[*i] == '$' && c == 39) || (undoll_cmd[*i] == '<') || (undoll_cmd[*i] == '>') || (undoll_cmd[*i] == ' '))
					unquote_cmd[*j] = (-1) * undoll_cmd[*i];
				else
					unquote_cmd[*j] = undoll_cmd[*i];
				(*i)++;
				(*j)++;
			}
			unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			(*j)++;
		}
	}
	else //if (c = 34)
	{
		if (ft_is_allspace(undoll_cmd, *i, c))
			ft_empty_quotes_case(undoll_cmd, i, unquote_cmd, j);
		else if (ft_contains_doll(undoll_cmd, *i, c))
		{
			unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			(*i)++;
			(*j)++;
			while (undoll_cmd[*i] && undoll_cmd[*i] != c)
			{
				if (undoll_cmd[*i] == '$' && (undoll_cmd[*i + 1] == c || undoll_cmd[*i + 1] == ' ' || undoll_cmd[*i + 1] == '<' || undoll_cmd[*i + 1] == '>'))
					unquote_cmd[*j] = (-1) * undoll_cmd[*i];
				else if ((undoll_cmd[*i] == '<') || (undoll_cmd[*i] == '>') || (undoll_cmd[*i] == ' '))//on garde les chevrons ?
					unquote_cmd[*j] = (-1) * undoll_cmd[*i];
				else
					unquote_cmd[*j] = undoll_cmd[*i];
				(*i)++;
				(*j)++;
			}
			unquote_cmd[*j] = (-1) * undoll_cmd[*i];
			(*j)++;
		}
		else
		{
			(*i)++;
			if (undoll_cmd[*i] && undoll_cmd[*i] != c)
			{
				unquote_cmd[*j] = (-1) * undoll_cmd[*i];
				(*i)++;
				(*j)++;
			}
			while (undoll_cmd[*i] && undoll_cmd[*i] != c)
			{
				if ((undoll_cmd[*i] == '$' && c == 39) || (undoll_cmd[*i] == '<') || (undoll_cmd[*i] == '>') || (undoll_cmd[*i] == ' '))
					unquote_cmd[*j] = (-1) * undoll_cmd[*i];
				else
					unquote_cmd[*j] = undoll_cmd[*i];
				(*i)++;
				(*j)++;
			}
		}
	}
}

char	*ft_fill_unquote_cmd(char *undoll_cmd, int len)
{
	char	*unquote_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	unquote_cmd = malloc(sizeof(char) * (len + 1));
	if (!unquote_cmd)
		return (NULL);
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == 34 || undoll_cmd[i] == 39)
			ft_quotes_case(undoll_cmd, &i, unquote_cmd, &j);
		else
		{
			unquote_cmd[j] = undoll_cmd[i];
			j++;
		}
		i++;
	}
	unquote_cmd[j] = '\0';
	return (unquote_cmd);
}

/*	***** PARSING | unquote_cmd *****
**	<SUMMARY>
**	Gets an updated cmd without useless quotes (unquote_cmd) in 2 steps:
**	1. Defines the length of the new string by removing useless quotes
**	2. Copies the matching string in 'unquote_cmd' of the t_cmd 'cmd' linked list
**	<PARAM>		{t_data *} data
**	<RETURNS>	t_cmd 'cmd' linked list --> with an additional string
**	<REMARKS>	!!!!!!!!!!!!!!
				TBcompleted (define what quotes to delete)
				!!!!!!!!!!!!!!
				!!!!!!!!!!!!!!
*/
int	ft_del_quotes(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	cmd = data->cmd;
	while (cmd)
	{
		len = ft_unquote_cmd_len(cmd->undoll_cmd);
		cmd->unquote_cmd = ft_fill_unquote_cmd(cmd->undoll_cmd, len);
		if (!cmd->unquote_cmd)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!!
		printf("unquote_cmd = %s\n", cmd->unquote_cmd);
		printf("  --> len = %d vs. strlen = %ld\n", len, ft_strlen(cmd->unquote_cmd));
		cmd = cmd->next;
	}
	return (0);
}
