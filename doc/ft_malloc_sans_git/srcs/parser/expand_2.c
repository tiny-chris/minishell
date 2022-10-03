/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:24:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/16 14:13:44 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_get_expand_size(char *undoll_cmd, int *i, t_data *data)
{
	t_env	*env;
	int		len;
	int		j;
	char	*var_to_expand;

	len = 0;
	j = *i;
	env = data->env;
	while (undoll_cmd[j] && (undoll_cmd[j] > 0) && undoll_cmd[j] != '\0' \
		&& undoll_cmd[j] != '$' && undoll_cmd[j] != '<' && undoll_cmd[j] != ' ' \
		&& undoll_cmd[j] != '>' && undoll_cmd[j] != 34 && undoll_cmd[j] != 39
		&& undoll_cmd[j] != '?')
		j++;
	var_to_expand = ft_substr(undoll_cmd, *i, (j - *i));
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
	//printf("expand len = %d et le i =%d\n", len, *i);
	return (len);
}

int	ft_expand_cmd_len(char *undoll_cmd, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == '$')
		{
			i++;
			if (undoll_cmd[i] == '?')
				len += ft_get_error_size(data) - 1;
			else
				len += ft_get_expand_size(undoll_cmd, &i, data);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	ft_fill_expand(char *undoll_cmd, int *i, char *clean_cmd, int *j, t_data *data)
{
	t_env	*env;
	char	*var_to_expand;
	int		k;
	int		l;

	env = data->env;
	k = *i;
	l = 0;
	while (undoll_cmd[k] > 0 && undoll_cmd[k] != '\0' && undoll_cmd[k] != '$' \
		&& undoll_cmd[k] != '<' && undoll_cmd[k] != '>' && undoll_cmd[k] != 34 \
		&& undoll_cmd[k] != 39 && undoll_cmd[k] != ' ' && undoll_cmd[k] != '?')
		k++;
	var_to_expand = ft_substr(undoll_cmd, *i, (k - *i));
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

char	*ft_fill_clean_cmd(char *undoll_cmd, int len, t_data *data)
{
	char	*clean_cmd;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	clean_cmd = malloc(sizeof(char) * (len + 1));
	if (!clean_cmd)
		return (NULL);// FREE TOUT ET EXIT !!
	while (undoll_cmd[i])
	{
		if (undoll_cmd[i] == '$')
		{
			i++;
			if (undoll_cmd[i] == '?')
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
				ft_fill_expand(undoll_cmd, &i, clean_cmd, &j, data);
		}
		else
		{
			clean_cmd[j] = undoll_cmd[i];
			i++;
			j++;
		}
	}
	clean_cmd[j] = '\0';
	return (clean_cmd);
}

int	ft_expand(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	cmd = data->cmd;
	len = 0;
	while (cmd)
	{
		len = ft_expand_cmd_len(cmd->undoll_cmd, data);//function that get the len of clean_cmd
	//	printf("len avec expand = %d\n", len);
		cmd->clean_cmd = ft_fill_clean_cmd(cmd->undoll_cmd, len, data);
		 if (!cmd->clean_cmd)
			return (1);// FREE TOUT CE QUI A ETE MALLOC !!!!!!
		dprintf(2, "expand cmd     = %s --> len = %d vs. strlen = %ld\n", cmd->clean_cmd, len, ft_strlen(cmd->clean_cmd));
		cmd = cmd->next;
	}
	return (0);
}
