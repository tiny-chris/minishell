/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dolls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:17:21 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/13 17:47:37 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | undoll_cmd - LEN *****
**	<SUMMARY>
**	Defines the length of the new string (undoll_cmd) by removing useless $ or
**	spaces
**	<PARAM>		{char *} no_redir_cmd --> from get_redir.c
**	<RETURNS>	the size of the new string to be copied unspace_cmd (int)
*/


// TO BE NORMED
/*	Notes pour nous:
	tant que le char * de ref existe (no_redir_cmd) :
	1. 	si on rencontre des quotes simples ou doubles, alors on avance et
		tant qu'on n'a pas atteint la quote fermante correspondante
			alors si le caractere est un dollar et les quotes sont des doubles, on avance
				tant que le caractère suivant est un dollar, on avance (et on retire de la len)
				si le caracètre d'après est un digit, alors on enlève le premier $ et ce digit de la len (expand vide)
				sinon, si le caractère d'après est la quote fermante, alors reculer de 1 (car i++ après)
	2.	AJOUT !!!
		s'il y a des espaces hors quotes juxtaposés, n'en garder qu'un et si en fin de commande, supprimer
	3.	si le caractere est un $ (hors quotes)
		tant que le caractère suivant est un dollar, on avance (et on retire de la len)
			si le caractère suivant est une quote (elle va avir sa correspondante après), alors on retire le $ de len
			sinon, si le caracètre d'après est un digit, alors on enlève le premier $ et ce digit de la len (expand vide) et on avance
			sinon, si le caractère d'après est un ?, alors on avance
	à la fin, on retourne la len
*/
int	ft_undoll_cmd_len(char *no_redir_cmd)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	len = ft_strlen(no_redir_cmd);
	// dprintf(2, "check ici si ça passe\n");
	while (no_redir_cmd[i])
	{
		if (no_redir_cmd[i] == 34 || no_redir_cmd[i] == 39)
		{
			c = no_redir_cmd[i];
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] != c)
			{
				if (no_redir_cmd[i] == '$' && c == 34)
				{
					i++;
					while (no_redir_cmd[i] && no_redir_cmd[i] == '$')
					{
						len--;
						i++;
					}
					if (ft_isdigit(no_redir_cmd[i]))
						len -= 2;
					else if (no_redir_cmd[i] == c)
						i--;
				}
				i++;
			}
		}
		else if (no_redir_cmd[i] == ' ')//ajout de cette condition pour nettoyer nos espaces suite aux redir
		{
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] == ' ')
			{
				len--;
				i++;
			}
			if (no_redir_cmd[i] == '\0')
				len--;
			i--;
		}
		else if (no_redir_cmd[i] == '$')
		{
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] == '$')
			{
				len--;
				i++;
			}
			if (no_redir_cmd[i] == 39 || no_redir_cmd[i] == 34)
				len--;//on enlève le dernier $
			else if (ft_isdigit(no_redir_cmd[i]))
			{
				len -= 2;
				i++;
			}
			else if (no_redir_cmd[i] && no_redir_cmd[i] == '?')
				i++;
			i--;
		}
		i++;
	}
	return (len);
}

/*	***** PARSING | undoll_cmd - CONTENT *****
**	<SUMMARY>
**	Creates the new string to be copied as 'undoll_cmd' in the t_cmd
**	'cmd' linked list
**	<PARAM>		{char *} no_redir_cmd
				{int} len --> previously calculated len
**	<RETURNS>	the new string value (char *) without useless $ & spaces
*/


// TO BE NORMED
char	*ft_fill_undoll_cmd(char *no_redir_cmd, int len)
{
	char	*undoll_cmd;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	undoll_cmd = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	// undoll_cmd = malloc(sizeof(char) * (len + 1));
	// if (!undoll_cmd)
	// 	return (NULL);// FREE TOUT CE QU IL Y A A FREE
	while (no_redir_cmd[i])
	{
		if (no_redir_cmd[i] == 34 || no_redir_cmd[i] == 39)
		{
			c = no_redir_cmd[i];
			undoll_cmd[j] = no_redir_cmd[i];
			i++;
			j++;
			while (no_redir_cmd[i] && no_redir_cmd[i] != c)
			{
				if (no_redir_cmd[i] == '$' && c == 34)
				{
					i++;
					while (no_redir_cmd[i] != c && no_redir_cmd[i] == '$')
						i++;
					if (no_redir_cmd[i] == '?')
					{
						undoll_cmd[j] = '$';
						j++;
						undoll_cmd[j] = no_redir_cmd[i];
						j++;
					}
					else if (ft_isdigit(no_redir_cmd[i]) == 0 && no_redir_cmd[i] != c)
					{
						undoll_cmd[j] = '$';
						j++;
						undoll_cmd[j] = no_redir_cmd[i];
						j++;
					}
					else if (no_redir_cmd[i] == c)
					{
						undoll_cmd[j] = '$';
						j++;
						i--;
					}
				}
				else
				{
					undoll_cmd[j] = no_redir_cmd[i];
					j++;
				}
				i++;
			}
			if (no_redir_cmd[i] == c)
			{
				undoll_cmd[j] = c;
				j++;
			}
		}
		else if (no_redir_cmd[i] == ' ')//ajout de cette condition pour nettoyer nos espaces suite aux redir
		{
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] == ' ')
				i++;
			if (no_redir_cmd[i] != '\0')
			{
				undoll_cmd[j] = ' ';
				j++;
			}
			i--;
		}
		else if (no_redir_cmd[i] == '$')
		{
			i++;
			while (no_redir_cmd[i] && no_redir_cmd[i] == '$')
				i++;
			if (no_redir_cmd[i] == 39 || no_redir_cmd[i] == 34)
				i--;//on enlève le dernier $
			else if (!ft_isdigit(no_redir_cmd[i]))
			{
				undoll_cmd[j] = '$';
				j++;
				if (no_redir_cmd[i] == '\0')
				{
					undoll_cmd[j] = '\0';
					return (undoll_cmd);
				}
				else if (no_redir_cmd[i] != '\0')
				{
					undoll_cmd[j] = no_redir_cmd[i];
					j++;
				}
			}
		}
		else
		{
			undoll_cmd[j] = no_redir_cmd[i];
			j++;
		}
		i++;
	}
	undoll_cmd[j] = '\0';
	return (undoll_cmd);
}

void	ft_neg_dolls(char *undoll_cmd)
{
	int		i;

	i = 0;
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == 39)
		{
			i++;
			while (undoll_cmd[i] && undoll_cmd[i] != 39)
			{
				if (undoll_cmd[i] == '$')
					undoll_cmd[i] = (-1) * undoll_cmd[i];
				i++;
			}
		}
		else if (undoll_cmd[i] == 34)
		{
			i++;
			while (undoll_cmd[i] && undoll_cmd[i] != 34)
			{
				if (undoll_cmd[i] == '$' && (undoll_cmd[i + 1] == 34 || undoll_cmd[i + 1] == 39 || undoll_cmd[i + 1] == ' ' || undoll_cmd[i + 1] == '<' || undoll_cmd[i + 1] == '>'))
					undoll_cmd[i] = (-1) * undoll_cmd[i];
				i++;
			}
		}
		else if (undoll_cmd[i] == '$')
		{
			if (undoll_cmd[i + 1] == '\0' || undoll_cmd[i + 1] < 0 || undoll_cmd[i + 1] == 39 || undoll_cmd[i + 1] == ' ' || undoll_cmd[i + 1] == '<' || undoll_cmd[i + 1] == '>')
				undoll_cmd[i] = (-1) * undoll_cmd[i];
		}
		i++;
	}
}

/*	***** PARSING | undoll_cmd *****
**	<SUMMARY>
**	Gets an updated cmd without useless $ and spaces (undoll_cmd) in 2 steps:
**	1. Defines the length of the new string by removing useless $
**	2. Copies the matching string in 'undoll_cmd' of the t_cmd 'cmd' linked list
**	<PARAM>		{t_data *} data
**	<RETURNS>	t_cmd 'cmd' linked list --> with an additional string
**	<REMARKS>	1. useless dollars are those:
**					- when there are consecutive dollars: keep only 1
**					- when the next character is a digit and they are not into
**					simple quotes
**				2. useless spaces consecutive ones outside closed quotes that could
**					appear again because of removed redirections
*/
int	ft_del_dolls(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	len = 0;
	cmd = data->cmd;
	while (cmd)
	{
		len = ft_undoll_cmd_len(cmd->no_redir_cmd);
		cmd->undoll_cmd = ft_fill_undoll_cmd(cmd->no_redir_cmd, len);

		// // TEST PARSER
		// ft_handle_malloc(DELONE, cmd->undoll_cmd, 0, 0);
		// cmd->undoll_cmd = NULL;
		// dprintf(2, "check si undoll cmd = NULL\n");
		// ft_handle_malloc(ADD_M, cmd->undoll_cmd, TAB_STR1, 0);

		if (!cmd->undoll_cmd)
			return (1);
		ft_neg_dolls(cmd->undoll_cmd);
		// dprintf(2, "undoll cmd     = %s --> len = %d vs. strlen = %ld\n", cmd->undoll_cmd, len, ft_strlen(cmd->undoll_cmd));
		cmd = cmd->next;
	}
	return (0);
}
