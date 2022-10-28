/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:41 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/28 17:27:25 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

int	ft_get_expand_size(char *undoll_cmd, int *i, t_data *data)
{
	t_env	*env;
	int		len;
	int		j;
	char	*var_to_expand;

	len = 0;
	j = *i;
	env = data->env;
	while (undoll_cmd[j] && (undoll_cmd[j] > 0) && ft_isalnum(undoll_cmd[j]))
		j++;
	var_to_expand = ft_substr(undoll_cmd, *i, (j - *i));
	ft_handle_malloc(ADD_M + TAB_STR1, var_to_expand, 0, NULL);
	while (env)
	{
		if ((ft_strlen(var_to_expand) == ft_strlen(env->var)) \
			&& (ft_strncmp(var_to_expand, env->var, (j - *i)) == 0))
		{
			len = ft_strlen(env->content);
			break ;
		}
		env = env->next;
	}
	*i = j;
	ft_handle_malloc(DELONE, var_to_expand, 0, NULL);
	return (len);
}

int	ft_get_error_size(t_data *data)
{
	char	*str_exit;
	int		len;

	len = 0;
	str_exit = ft_itoa(g_val_exit);
	ft_handle_malloc(ADD_M + TAB_STR1, str_exit, 0, data);
	len = ft_strlen(str_exit);
	data->str_exit = str_exit;
	return (len);
}

/*	Gets the length of the cmd including expands
**		1. if quotes : if quotes 34 then $ then digit --> expand to nothing
**		2. if $ : if followed by a digit --> expand to nothing
**		3. else 
*/
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
			else if (ft_isdigit(undoll_cmd[i]))
				i++;
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

int	ft_expand(t_data *data)
{
	t_cmd	*cmd;
	int		len;

	cmd = data->cmd;
	dprintf(2, "val de undoll cmd = %s\n", cmd->undoll_cmd);
	len = 0;
	while (cmd)
	{
		len = ft_expand_cmd_len(cmd->undoll_cmd, data);
		dprintf(2, "len de expand = %d\n", len);//
		cmd->clean_cmd = ft_fill_clean_cmd(cmd->undoll_cmd, len, data);
		cmd = cmd->next;
	}
	return (0);
}
