/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:27:05 by marvin            #+#    #+#             */
/*   Updated: 2022/09/08 16:35:34 by lmelard          ###   ########.fr       */
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
	printf("j = %d\n", j);
	env = data->env;
	while (unquote_cmd[j] && (unquote_cmd[j] > 0) && unquote_cmd[j] != '\0' \
		&& unquote_cmd[j] != '$' && unquote_cmd[j] != '<' && unquote_cmd[j] != ' ' \
		&& unquote_cmd[j] != '>' && unquote_cmd[j] != 34 && unquote_cmd[j] != 39
		&& unquote_cmd[j] != '?')
		j++;
	printf("j2 = %d\n", j);
	var_to_expand = ft_substr(unquote_cmd, *i, (j - *i));
	//printf("var to expand = %s, size = %ld\n", var_to_expand, ft_strlen(var_to_expand));
	if (!var_to_expand)
		return (0);// A CHECKER POUR FREE SI PB DE MALLOC - garbage collector
	while (env)
	{
		if ((ft_strlen(var_to_expand) == ft_strlen(env->var)) \
			&& (ft_strncmp(var_to_expand, env->var, (j - *i)) == 0))
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
	printf("expand len = %d et le i =%d\n", len, *i);
	return (len);
}

int	ft_get_error_size(t_data *data)
{
	char	*str_exit;
	int		len;

	len = 0;
	str_exit = ft_itoa(data->val_exit);
	if (!str_exit)
		return (-1); ///free tout ce qu'il y a à free + exit
	len = ft_strlen(str_exit);
	data->str_exit = str_exit;
	return (len);
}
/*
	calcul taille à malloc pour chaque unquote_cmd (cas expand dans une fonction dédiée)

	/!\ $$ is the process ID of the current shell instance
*/
int	ft_expand_cmd_len(char *unquote_cmd, t_data *data)
{
	int			i;
	int			len;
	signed char	*cmd;

	i = 0;
	len = 0;
	cmd = (signed char *)unquote_cmd;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			i++;
			if (cmd[i] == '\0')
			{
				len++;
				return (len);
			}
			//ce sont les séparateurs : y compris les caractères négatifs --> dans ce cas, on compte juste le $ comme caractère
			else if (cmd[i] < 0 || cmd[i] == 39 || cmd[i] == ' ' || cmd[i] == '<' || cmd[i] == '>')
				len++;
			else if (cmd[i] == '?')
				len += ft_get_error_size(data) - 1;
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
	printf("len clean cmd = %d\n", len);
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
	while (unquote_cmd[k] > 0 && unquote_cmd[k] != '\0' && unquote_cmd[k] != '$' \
		&& unquote_cmd[k] != '<' && unquote_cmd[k] != '>' && unquote_cmd[k] != 34 \
		&& unquote_cmd[k] != 39 && unquote_cmd[k] != ' ' && unquote_cmd[k] != '?')
		k++;
	var_to_expand = ft_substr(unquote_cmd, *i, (k - *i));
	if (!var_to_expand)
		return ;// A CHECKER POUR FREE SI PB DE MALLOC - garbage collector
	while (env)
	{
		if ((ft_strlen(var_to_expand) == ft_strlen(env->var)) \
			&& (ft_strncmp(var_to_expand, env->var, (k - *i)) == 0))
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
	char		*clean_cmd;
	int			i;
	int			j;
	int			k;
	signed char	*cmd;

	i = 0;
	j = 0;
	k = 0;
	cmd = (signed char *)unquote_cmd;
	clean_cmd = malloc(sizeof(char) * (len + 1));
	if (!clean_cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			i++;
			if (cmd[i] == '\0')
			{
				clean_cmd[j] = '$';
				j++;///// attention doublon
				break;
			}
			else if (cmd[i] < 0 || cmd[i] == 39 || cmd[i] == ' ' || cmd[i] == '<' || cmd[i] == '>')
			{
				clean_cmd[j] = '$';
				j++;
			}
			else if (cmd[i] == '?')
			{
				while (data->str_exit[k])
				{
					clean_cmd[j] = data->str_exit[k];
					j++;
					k++;
				}
				i++;
				k = 0;
			}
			else
				ft_fill_expand(unquote_cmd, &i, clean_cmd, &j, data);
				//faire le cas particulier des expand pour calcul len
				// + envoyer adresse de i
		}
		// else if (unquote_cmd[i] == (-1) * '$')  // a mettre plutot dans clean token pour conserver le $? en négatif
		// {
		// 	clean_cmd[j] = '$';
		// 	j++;
		// 	i++;
		// }
		else
		{
			clean_cmd[j] = cmd[i];
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
		printf("clean_cmd = %s, size = %ld\n", cmd->clean_cmd, ft_strlen(cmd->clean_cmd));
		cmd = cmd->next;
	}
	return (0);
}
