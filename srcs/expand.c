/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:27:05 by marvin            #+#    #+#             */
/*   Updated: 2022/09/01 13:21:02 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_expand_size(char *unquote_cmd, int *i, t_data *data)
{
	t_env	*env;
	int		len;
	int		j;
	char	*var_to_expand;

	len = 0;
	j = *i;
	env = data->env;
	while (unquote_cmd[j] != '\0' && unquote_cmd[j] != '$' && unquote_cmd[j] != '<' \
		&& unquote_cmd[j] != '>' && unquote_cmd[j] != 34 && unquote_cmd[j] != 39 \
		&& unquote_cmd[j] != ' ' && unquote_cmd[j])
		j++;
	var_to_expand = ft_substr(unquote_cmd, *i, (j - *i));
	if (!var_to_expand)
		return (0);// A CHECKER POUR FREE SI PB DE MALLOC - garbage collector
	while (env)
	{
		if (ft_strncmp(var_to_expand, env->var, (j - *i)) == 0)
		{
			len = ft_strlen(env->content);
			// printf("len de env->content = %d\n", len);
			// printf("len de var_to_expand = %ld\n", ft_strlen(var_to_expand));
			break ;
		}
		env = env->next;
	}
	*i = j;
	free(var_to_expand);
	return (len);
}

/*
	calcul taille à malloc pour chaque unquote_cmd (cas expand dans une fonction dédiée)

	/!\ $$ is the process ID of the current shell instance
*/
int	ft_expand_cmd_len(char *unquote_cmd, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (unquote_cmd[i])
	{
		if (unquote_cmd[i] == '$')
		{
			i++;
			if (unquote_cmd[i] == '\0')
			{
				len++;
				return (len);
			}
			//inclure les caractères négatifs comme séparateur --> on compte juste le $ comme caractère
			else if (unquote_cmd[i] < 0 || unquote_cmd[i] == ' ' || unquote_cmd[i] == '<' || unquote_cmd[i] == '>')
				len++;
			else
				len += ft_get_expand_size(unquote_cmd, &i, data);
				//faire le cas particulier des expand pour calcul len
				// + envoyer adresse de i
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

static void	ft_fill_expand(char *unquote_cmd, int *i, char *clean_cmd, int *j, t_data *data)
{
	t_env	*env;
	char	*var_to_expand;
	int		k;
	int		l;

	env = data->env;
	k = *i;
	l = 0;
	while (unquote_cmd[k] != '\0' && unquote_cmd[k] != '$' && unquote_cmd[k] != '<' \
		&& unquote_cmd[k] != '>' && unquote_cmd[k] != 34 && unquote_cmd[k] != 39 \
		&& unquote_cmd[k] != ' ')
		k++;
	var_to_expand = ft_substr(unquote_cmd, *i, (k - *i));
	if (!var_to_expand)
		return ;// A CHECKER POUR FREE SI PB DE MALLOC - garbage collector
	while (env)
	{
		if (ft_strncmp(var_to_expand, env->var, (k - *i)) == 0)
		{
			while (env->content[l])
			{
				clean_cmd[*j] = env->content[l];
				(*j)++;
				l++;
			}
			break ;
		}
		env = env->next;
	}
	free(var_to_expand);
	*i = k;
	return ;
}

char	*ft_fill_clean_cmd(char *unquote_cmd, int len, t_data *data)
{
	char	*clean_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean_cmd = NULL;
	clean_cmd = malloc(sizeof(char) * (len + 1));
	if (!clean_cmd)
		return (NULL);
	while (unquote_cmd[i])
	{
		if (unquote_cmd[i] == '$')
		{
			i++;
			if (unquote_cmd[i] == '\0')
			{
				clean_cmd[j] = '$';
				j++;///// attention doublon
				break;
			}
			else if (unquote_cmd[i] < 0 || unquote_cmd[i] == ' ' || unquote_cmd[i] == '<' || unquote_cmd[i] == '>')
			{
				clean_cmd[j] = '$';
				j++;
			}
			else
				ft_fill_expand(unquote_cmd, &i, clean_cmd, &j, data);
				//faire le cas particulier des expand pour calcul len
				// + envoyer adresse de i
		}
		else if (unquote_cmd[i] == (-1) * '$')
		{
			clean_cmd[j] = '$';
			j++;
			i++;
		}
		else/// a finaliser
		{
			clean_cmd[j] = unquote_cmd[i];
			i++;
			j++;
		}
	}
	clean_cmd[j] = '\0';
	return (clean_cmd);
}

/*
	create a function similar to del_quote
	- malloc la taille de chaque expand_cmd
*/
int	ft_expand(t_data *data)
{
	t_cmd	*cmd;
	int		expand_cmd_len;

	cmd = data->cmd;
	expand_cmd_len = 0;
	while (cmd)
	{
		expand_cmd_len = ft_expand_cmd_len(cmd->unquote_cmd, data);//function that get the len of clean_cmd
		//printf("len avec expand = %d\n", expand_cmd_len);
		cmd->clean_cmd = ft_fill_clean_cmd(cmd->unquote_cmd, expand_cmd_len, data);
		if (!cmd->clean_cmd)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!!
		//printf("clean_cmd = %s\n", cmd->clean_cmd);
		cmd = cmd->next;
	}
	return (0);
}
