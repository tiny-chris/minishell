/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:17:53 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/16 14:13:44 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	***** PARSING | cmd_no_redir - LEN *****
**	<SUMMARY>
**	Defines the length of the new string (cmd_ne_redir) by removing
**	redirections & corresponding files (or here doc)
**	<PARAM>		{char *} unspace_cmd --> from del_spaces.c
**	<RETURNS>	the size of the new string to be copied as 'cmd_no_redir" (int)
*/



// TO BE NORMED
/*	Notes pour nous:
	tant que le char * de ref existe (unspace_cmd):
	si on rencontre des quotes simples ou doubles, alors on avance jusqu'à la prochaine quote correspondante + 1
		puis on recommence au début de la boucle
	si on atteint un chevron (hors quotes), alors on retire -1 à la len et on check la valeur du caractère suivant :
		- si c'est un chevron identique alors on avance de +1 (et on retire -1 à la len), sinon on reste sur ce caractère
		et on passe à la ligne suivante :
			--> si le caractère n'est pas NULL et si c'est une quote, alors on avance jusqu'à la fin de la quote comprise et on retire tout de len
				et on continue de checker après la quote: tant qu'on n'est pas sur un espace ou un chevron (ou la fin du char *), alors on avance et on retire de la len
				puis, quand on a atteint un séparateur (NULL, chevron ou espace), on fonctionne ainsi:
					- si c'est un espace: alors on va retirer l'espace de la len qui ne sera pas compté (car i++ à la fin)
					- si c'est un NULL ou un chevron, alors on recule de -1 (car i++ à la fin)
				puis on recommence au début de la boucle
			--> autrement (pas d'espace juste après une redir car déjà supprimé): tant que le caractère n'est pas NULL et qu'il ne s'agit pas d'espace ni de chevron,
				on avance et on retire le tout de la len
				puis, comme ci-dessus, quand on a atteint un séparateur (NULL, chevron ou espace), on fonctionne ainsi:
					- si c'est un espace: alors on va retirer l'espace de la len qui ne sera pas compté (car i++ à la fin)
					- si c'est un NULL ou un chevron, alors on recule de -1 (car i++ à la fin)
				puis on recommence au début de la boucle
	à la fin, on retourne la len
*/
int	ft_len_no_redir(char *unspace_cmd)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(unspace_cmd);
	while (unspace_cmd[i])
	{
		if (unspace_cmd[i] == 34 || unspace_cmd[i] == 39)
		{
			c = unspace_cmd[i];
			i++;
			while (unspace_cmd[i] && unspace_cmd[i] != c)// ajout condition si existe
				i++;
		}
		else if (unspace_cmd[i] == '>' || unspace_cmd[i] == '<')
		{
			len--;
			i++;
			if (unspace_cmd[i] && (unspace_cmd[i] == '>' || unspace_cmd[i] == '<'))
			{
				len--;
				i++;
			}
			while (unspace_cmd[i] && unspace_cmd[i] != ' ' && unspace_cmd[i] != '>' && unspace_cmd[i] != '<')
			{
				if (unspace_cmd[i] && (unspace_cmd[i] == 34 || unspace_cmd[i] == 39))
				{
					c = unspace_cmd[i];
					i++;
					len--;
					while (unspace_cmd[i] && unspace_cmd[i] != c)// ajout condition si existe
					{
						i++;
						len--;
					}
					len--;
				}
				else
					len--;
				i++;
			}
			if (!unspace_cmd[i] || unspace_cmd[i] == ' ' || unspace_cmd[i] == '>' || unspace_cmd[i] == '<')// modif ici avec ajout si null
				i--;
		}
		i++;
	}
	return (len);
}

// TO BE NORMED
/*	Notes pour nous:
	tant que le char * de ref existe (unspace_cmd):
	1. si on rencontre des quotes simples ou doubles, alors on copie et on avance jusqu'à la prochaine quote correspondante incluse
		puis on recommence au début de la boucle
	2. si on atteint un chevron (hors quotes), alors on avance de +1 et on check la valeur du caractère suivant :
		- si c'est un chevron identique alors on avance de +1, sinon on reste sur ce caractère
		et on passe à la ligne suivante :
			--> si le caractère n'est pas NULL et si c'est une quote, alors on avance jusqu'à la fin de la quote comprise
				et on continue de checker après la quote: tant qu'on n'est pas sur un espace ou un chevron (ou la fin du char *), alors on avance
				puis, quand on a atteint un séparateur (NULL, chevron ou espace), on fonctionne ainsi:
					- si c'est un espace: alors on va retirer l'espace de la len qui ne sera pas compté (car i++ à la fin)
					- si c'est un NULL ou un chevron, alors on recule de -1 (car i++ à la fin)
				puis on recommence au début de la boucle
	3. sinon, on copie et on avance
		puis on recommence au début de la boucle
	à la fin, on retourne la nouvelle string
*/
char	*ft_fill_no_redir(char *unspace_cmd, int len)
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
	while (unspace_cmd[i])
	{
		if (unspace_cmd[i] == 34 || unspace_cmd[i] == 39)
		{
			c = unspace_cmd[i];
			no_redir_cmd[j] = c;
			i++;
			j++;
			while (unspace_cmd[i] && unspace_cmd[i] != c)
			{
				no_redir_cmd[j] = unspace_cmd[i];
				i++;
				j++;
			}
			no_redir_cmd[j] = c;
			j++;
		}
		else if (unspace_cmd[i] == '>' || unspace_cmd[i] == '<')
		{
			i++;
			if (unspace_cmd[i] && (unspace_cmd[i] == '>' || unspace_cmd[i] == '<'))
				i++;
			while (unspace_cmd[i] && unspace_cmd[i] != ' ' && unspace_cmd[i] != '>' && unspace_cmd[i]!= '<')
			{
				if (unspace_cmd[i] && (unspace_cmd[i] == 34 || unspace_cmd[i] == 39))
				{
					c = unspace_cmd[i];
					i++;
					while (unspace_cmd[i] && unspace_cmd[i] != c)
						i++;
				}
				i++;
			}
			if (!unspace_cmd[i] || unspace_cmd[i] == ' ' || unspace_cmd[i] == '>' || unspace_cmd[i] == '<')// modif ici avec ajout si null
				i--;
		}
		else
		{
			no_redir_cmd[j] = unspace_cmd[i];
			j++;
		}
		i++;
	}
	no_redir_cmd[j] = '\0';
	return (no_redir_cmd);
}

int	ft_is_redir(char *unspace_cmd, int *j)
{
	if (unspace_cmd[*j] == '<')
	{
		(*j)++;
		if (unspace_cmd[*j] && unspace_cmd[*j] == '<')
		{
			(*j)++;
			return (13);
		}
		else
			return (12);
	}
	else if (unspace_cmd[*j] == '>')
	{
		(*j)++;
		if (unspace_cmd[*j] && unspace_cmd[*j] == '>')
		{
			(*j)++;
			return (11);
		}
		else
			return (10);
	}
	return (0);
}

int	ft_get_redir_list(char *unspace_cmd, t_token **tok_redir)
{
	int		i;
	int		j;
	int		type;
	char	c;

	i = 0;
	j = 0;
	type = 0;
	while(unspace_cmd[i])
	{
		if (unspace_cmd[i] == 34 || unspace_cmd[i] == 39)
		{
			c = unspace_cmd[i];
			i++;
			while (unspace_cmd[i] && unspace_cmd[i] != c)
				i++;
		}
		else //if (unspace_cmd[i] == '>' || unspace_cmd[i] == '<')// ajout possible
		{
			type = ft_is_redir(unspace_cmd, &j);
			if (type)
			{
				if (ft_lstadd_token(tok_redir, type, ft_substr(unspace_cmd, i, (j - i))))
					return (1); //free tout ce qu'il y a à free
				i = j;
				while (unspace_cmd[j] && unspace_cmd[j] != ' ' && unspace_cmd[j] != '>' && unspace_cmd[j] != '<')
				{
					if (unspace_cmd[j] && (unspace_cmd[j] == 34 || unspace_cmd[j] == 39))
					{
						c = unspace_cmd[j];
						j++;
						while (unspace_cmd[j] != c)
							j++;
					}
					j++;
				}
				if (ft_lstadd_token(tok_redir, type + 10, ft_substr(unspace_cmd, i, j - i)))
					return (1); //free tout ce qu'il y a à free
				i = j - 1;
			}
			type = 0;//ajout
		}
		i++;
		j = i;
	}
	return (0);
}

/*	***** PARSING | no_redir_cmd *****
**	<SUMMARY>
**	1. Gets an updated cmd without unquoted redirections (no_redir_cmd) :
**	   - Defines the length of the new string by removing redirections &
**		corresponding files (or here doc)
**	   - Copies the matching string in 'no_redir_cmd' of the t_cmd 'cmd'
**		linked list
**	2. Creates a redir linked list & corresponding file (or here doc)
**	<PARAM>		{t_data *} data
**	<RETURNS>	t_cmd 'cmd' linked list --> with an additional string
*/
int	ft_get_redir(t_data *data)
{
	t_cmd	*cmd;
	char	*trim_cmd;
	int		len;

	cmd = data->cmd;
	trim_cmd = NULL;
	len = 0;
	while (cmd)
	{
		len = ft_len_no_redir(cmd->unspace_cmd);
		trim_cmd = ft_fill_no_redir(cmd->unspace_cmd, len);
		if (!trim_cmd)
			return (1); // FREE tout ce qu'il y a à free
		cmd->no_redir_cmd = ft_strtrim(trim_cmd, " ");
		free(trim_cmd);
		dprintf(2, "no redir cmd   = %s --> len = %d vs. strlen = %ld\n", cmd->no_redir_cmd, len, ft_strlen(cmd->no_redir_cmd));
		if (ft_get_redir_list(cmd->unspace_cmd, &cmd->tok_redir))
			return (1); // FREE tout ce qu'il y a à free
		ft_clean_redir(cmd, data);
		cmd = cmd->next;
	}
// EN COURS D'ECRITURE POUR NOS TOKEN REDIR
//
//	if (ft_clean_redir(data))
//		return (1); // FREE tout ce qu'il y a à free + EXIT

	/* 	TEMPORARY --> TO PRINT */
	/*	start */
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
	/*	end */
	return (0);
}
