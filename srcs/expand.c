// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expand.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/08/18 11:27:05 by marvin            #+#    #+#             */
// /*   Updated: 2022/09/12 17:02:02 by cgaillag         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// int	ft_get_expand_size(char *unquote_cmd, int *i, t_data *data)
// {
// 	t_env	*env;
// 	int		len;
// 	int		j;
// 	char	*var_to_expand;

// 	len = 0;
// 	j = *i;
// 	env = data->env;
// 	while (unquote_cmd[j] && (unquote_cmd[j] > 0) && unquote_cmd[j] != '\0' \
// 		&& unquote_cmd[j] != '$' && unquote_cmd[j] != '<' && unquote_cmd[j] != ' ' \
// 		&& unquote_cmd[j] != '>' && unquote_cmd[j] != 34 && unquote_cmd[j] != 39
// 		&& unquote_cmd[j] != '?')
// 		j++;
// 	var_to_expand = ft_substr(unquote_cmd, *i, (j - *i));
// 	//printf("var to expand = %s, size = %ld\n", var_to_expand, ft_strlen(var_to_expand));
// 	if (!var_to_expand)
// 		return (0);// A CHECKER POUR FREE SI PB DE MALLOC - garbage collector
// 	while (env)
// 	{
// 		if ((ft_strlen(var_to_expand) == ft_strlen(env->var)) \
// 			&& (ft_strncmp(var_to_expand, env->var, (j - *i)) == 0))
// 		{
// 			len = ft_strlen(env->content);
// 			// printf("len de env->content = %d\n", len);
// 			// printf("len de var_to_expand = %ld\n", ft_strlen(var_to_expand));
// 			break ;
// 		}
// 		env = env->next;
// 	}
// 	*i = j;
// 	free(var_to_expand);
// 	//printf("expand len = %d et le i =%d\n", len, *i);
// 	return (len);
// }

// int	ft_get_error_size(t_data *data)
// {
// 	char	*str_exit;
// 	int		len;

// 	len = 0;
// 	str_exit = ft_itoa(data->val_exit);
// 	if (!str_exit)
// 		return (-1); ///free tout ce qu'il y a à free + exit
// 	len = ft_strlen(str_exit);
// 	data->str_exit = str_exit;
// 	return (len);
// }
// /*
// 	calcul taille à malloc pour chaque unquote_cmd (cas expand dans une fonction dédiée)

// 	/!\ $$ is the process ID of the current shell instance
// */
// int	ft_expand_cmd_len(char *unquote_cmd, t_data *data)
// {
// 	int			i;
// 	int			len;
// 	signed char	*cmd;

// 	i = 0;
// 	len = 0;
// 	cmd = (signed char *)unquote_cmd;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '$')
// 		{
// 			i++;
// 			if (cmd[i] == '\0')
// 			{
// 				len++;
// 				return (len);
// 			}
// 			//ce sont les séparateurs : y compris les caractères négatifs --> dans ce cas, on compte juste le $ comme caractère
// 			else if (cmd[i] < 0 || cmd[i] == 39 || cmd[i] == ' ' || cmd[i] == '<' || cmd[i] == '>')
// 				len++;
// 			else if (cmd[i] == '?')
// 				len += ft_get_error_size(data) - 1;
// 			else
// 				len += ft_get_expand_size(unquote_cmd, &i, data);
// 				//faire le cas particulier des expand pour calcul len
// 				// + envoyer adresse de i
// 		}
// 		else
// 		{
// 			i++;
// 			len++;
// 		}
// 	}
// 	//printf("len clean cmd = %d\n", len);
// 	return (len);
// }

// static void	ft_fill_expand(char *unquote_cmd, int *i, char *clean_cmd, int *j, t_data *data)
// {
// 	t_env	*env;
// 	char	*var_to_expand;
// 	int		k;
// 	int		l;

// 	env = data->env;
// 	k = *i;
// 	l = 0;
// 	while (unquote_cmd[k] > 0 && unquote_cmd[k] != '\0' && unquote_cmd[k] != '$' \
// 		&& unquote_cmd[k] != '<' && unquote_cmd[k] != '>' && unquote_cmd[k] != 34 \
// 		&& unquote_cmd[k] != 39 && unquote_cmd[k] != ' ' && unquote_cmd[k] != '?')
// 		k++;
// 	var_to_expand = ft_substr(unquote_cmd, *i, (k - *i));
// 	if (!var_to_expand)
// 		return ;// A CHECKER POUR FREE SI PB DE MALLOC - garbage collector
// 	while (env)
// 	{
// 		if ((ft_strlen(var_to_expand) == ft_strlen(env->var)) \
// 			&& (ft_strncmp(var_to_expand, env->var, (k - *i)) == 0))
// 		{
// 			while (env->content[l])
// 			{
// 				clean_cmd[*j] = env->content[l];
// 				(*j)++;
// 				l++;
// 			}
// 			break ;
// 		}
// 		env = env->next;
// 	}
// 	free(var_to_expand);
// 	*i = k;
// 	return ;
// }

// char	*ft_fill_clean_cmd(char *unquote_cmd, int len, t_data *data)
// {
// 	char		*clean_cmd;
// 	int			i;
// 	int			j;
// 	int			k;
// 	signed char	*cmd;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	cmd = (signed char *)unquote_cmd;
// 	clean_cmd = malloc(sizeof(char) * (len + 1));
// 	if (!clean_cmd)
// 		return (NULL);
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '$')
// 		{
// 			i++;
// 			if (cmd[i] == '\0')
// 			{
// 				clean_cmd[j] = '$';
// 				j++;///// attention doublon
// 				break;
// 			}
// 			else if (cmd[i] < 0 || cmd[i] == 39 || cmd[i] == ' ' || cmd[i] == '<' || cmd[i] == '>')
// 			{
// 				clean_cmd[j] = '$';
// 				j++;
// 			}
// 			else if (cmd[i] == '?')
// 			{
// 				while (data->str_exit[k])
// 				{
// 					clean_cmd[j] = data->str_exit[k];
// 					j++;
// 					k++;
// 				}
// 				i++;
// 				k = 0;
// 			}
// 			else
// 				ft_fill_expand(unquote_cmd, &i, clean_cmd, &j, data);
// 				//faire le cas particulier des expand pour calcul len
// 				// + envoyer adresse de i
// 		}
// 		// else if (unquote_cmd[i] == (-1) * '$')  // a mettre plutot dans clean token pour conserver le $? en négatif
// 		// {
// 		// 	clean_cmd[j] = '$';
// 		// 	j++;
// 		// 	i++;
// 		// }
// 		else
// 		{
// 			clean_cmd[j] = cmd[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	clean_cmd[j] = '\0';
// 	return (clean_cmd);
// }

// int	ft_consec_quotes_len(char *tmp_cmd)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	c;

// 	i = 0;
// 	len = ft_strlen(tmp_cmd);
// 	while (tmp_cmd[i])
// 	{
// 		if (tmp_cmd[i] == -34 || tmp_cmd[i] == -39)
// 		{
// 			c = tmp_cmd[i];
// 			i++;
// 			while (tmp_cmd[i] && tmp_cmd[i] != c)
// 				i++;
// 		}
// 		else if (tmp_cmd[i] == 39 || tmp_cmd[i] == 34)
// 		{
// 			c = tmp_cmd[i];
// 			if (tmp_cmd[i + 1] == c)
// 			{
// 				if (i == 0 && tmp_cmd[i + 2] != '\0')
// 				{
// 					if (tmp_cmd[i + 2] != ' ')
// 					{
// 						i += 2;
// 						while (tmp_cmd[i] && (tmp_cmd[i] == 34 || tmp_cmd[i] == 39)  && tmp_cmd[i + 1] && (tmp_cmd[i + 1] == 34 || tmp_cmd[i + 1] == 39))
// 							i += 2;
// 						if (tmp_cmd[i] == '\0' || tmp_cmd[i] == ' ')
// 						{
// 							len = 2;
// 							return (2);
// 						}
// 						else
// 							len -= i;
// 					}
// 				}
// 				else if (i > 0 && tmp_cmd[i + 2] != '\0')
// 				{
// 					j = i;
// 					j += 2;
// 					while (tmp_cmd[j] && (tmp_cmd[j] == 34 || tmp_cmd[j] == 39)  && tmp_cmd[j + 1] && (tmp_cmd[j + 1] == 34 || tmp_cmd[j + 1] == 39))
// 						j += 2;
// 					if (tmp_cmd[i - 1] == ' ' && (tmp_cmd[j] == '\0' || tmp_cmd[j] == ' '))
// 						len -= (j - i) + 2;
// 					else
// 						len -= (j - i);
// 					i = j;
// 					i--;
// 				}
// 				else if (i > 0 && tmp_cmd[i + 2] == '\0')
// 				{
// 					if (tmp_cmd[i - 1] != ' ')
// 						len -= 2;
// 					i++;
// 				}
// 			}
// 			else
// 			{
// 				i++;
// 				while (tmp_cmd[i] && tmp_cmd[i] != c)
// 					i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (len);
// }

// char	*ft_fill_consec_quotes(char *tmp_cmd, int len)
// {
// 	char	*clean_cmd;
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	c;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	clean_cmd = malloc(sizeof(char) * (len + 1));
// 	if (!clean_cmd)
// 		return (NULL); // FREE TOUTTTT + EXIT OF COURSE
// 	while (tmp_cmd[i])
// 	{
// 		if (tmp_cmd[i] == -34 || tmp_cmd[i] == -39)
// 		{
// 			c = tmp_cmd[i];
// 			clean_cmd[j] = tmp_cmd[i];
// 			i++;
// 			j++;
// 			while (tmp_cmd[i] && tmp_cmd[i] != c)
// 			{
// 				clean_cmd[j] = tmp_cmd[i];
// 				i++;
// 				j++;
// 			}
// 			clean_cmd[j] = tmp_cmd[i];
// 			j++;
// 		}
// 		else if (tmp_cmd[i] == 39 || tmp_cmd[i] == 34)
// 		{
// 			c = tmp_cmd[i];
// 			if (tmp_cmd[i + 1] == c)
// 			{
// 				// if (i == 0 && tmp_cmd[i + 2] != '\0')
// 				// {
// 				// 	if (tmp_cmd[i + 2] != ' ')
// 				// 		i++;
// 				// }
// 				if (i == 0 && tmp_cmd[i + 2] != '\0')
// 				{
// 					if (tmp_cmd[i + 2] != ' ')
// 					{
// 						i += 2;
// 						while ((tmp_cmd[i] && (tmp_cmd[i] == 34 || tmp_cmd[i] == 39))  && (tmp_cmd[i + 1] && (tmp_cmd[i + 1] == 34 || tmp_cmd[i + 1] == 39)))
// 							i += 2;
// 						if (tmp_cmd[i] == '\0' || tmp_cmd[i] == ' ')
// 						{
// 							clean_cmd[j] = c;
// 							j++;
// 							clean_cmd[j] = c;
// 							j++;
// 						}
// 						i--;
// 					}
// 				}
// 				else if (i > 0 && tmp_cmd[i + 2] != '\0')
// 				{
// 					k = i;
// 					k += 2;
// 					while (tmp_cmd[k] && (tmp_cmd[k] == 34 || tmp_cmd[k] == 39)  && tmp_cmd[k+ 1] && (tmp_cmd[k + 1] == 34 || tmp_cmd[k + 1] == 39))
// 						k += 2;
// 					if (tmp_cmd[i - 1] == ' ' && (tmp_cmd[k] == '\0' || tmp_cmd[k] == ' '))
// 					{
// 						clean_cmd[j] = tmp_cmd[i];
// 						j++;
// 						clean_cmd[j] = tmp_cmd[i];
// 						j++;
// 					}
// 					i = k;
// 					i--;
// 				}
// 				else if (i > 0 && tmp_cmd[i + 2] == '\0')
// 				{
// 					if (tmp_cmd[i - 1] == ' ')
// 					{
// 						clean_cmd[j] = tmp_cmd[i];
// 						j++;
// 						clean_cmd[j] = tmp_cmd[i];
// 						j++;
// 					}
// 					i++;
// 				}
// 			}
// 			else
// 			{
// 				clean_cmd[j] = tmp_cmd[i];
// 				i++;
// 				j++;
// 				while (tmp_cmd[i] && tmp_cmd[i] != c)
// 				{
// 					clean_cmd[j] = tmp_cmd[i];
// 					i++;
// 					j++;
// 				}
// 				clean_cmd[j] = tmp_cmd[i];
// 				j++;
// 			}
// 		}
// 		else
// 		{
// 			clean_cmd[j] = tmp_cmd[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	clean_cmd[j] = '\0';
// 	return (clean_cmd);
// }
// /*
// 	create a function similar to del_quote
// 	- malloc la taille de chaque expand_cmd
// */
// int	ft_expand(t_data *data)
// {
// 	t_cmd	*cmd;
// 	char	*tmp_cmd;
// 	int		len;

// 	cmd = data->cmd;
// 	len = 0;
// 	while (cmd)
// 	{
// 		tmp_cmd = NULL;
// 		len = ft_expand_cmd_len(cmd->unquote_cmd, data);//function that get the len of clean_cmd
// 		//printf("len avec expand = %d\n", len);
// 		tmp_cmd = ft_fill_clean_cmd(cmd->unquote_cmd, len, data);
// 		if (!tmp_cmd)
// 			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!!
// 		//new len
// 		dprintf(2, "clean_cmd_tmp= %s\n", tmp_cmd);
// 		dprintf(2, "clean_cmd len_tmp = %d vs. strlen = %ld\n", len, ft_strlen(tmp_cmd));
// 		len = ft_consec_quotes_len(tmp_cmd);
// 		cmd->clean_cmd = ft_fill_consec_quotes(tmp_cmd, len);
// 		free(tmp_cmd);
// 		//clean cmd sans quotes positives consecutives suivies ou précédées d'un texte
// 		dprintf(2, "clean_cmd = %s\n", cmd->clean_cmd);
// 		dprintf(2, "clean_cmd len = %d vs. strlen = %ld\n", len, ft_strlen(cmd->clean_cmd));
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }
