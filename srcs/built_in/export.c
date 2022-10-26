/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/26 13:24:18 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_end_var(t_token *token, int *res)
{
	int	i;

	i = 0;
	while (token->token[i] && token->token[i] != '=' && token->token[i] != '+')
	{
		if ((ft_isalnum(token->token[i]) == 0))
		{
			*res = ft_msg(1, token->token, ": ", ERRNAM);
			break ;
		}
		else
		{
			i++;
			*res = 0;
		}
	}
	return (i);
}

static char	*ft_update_plus_token(t_token **tok, t_data *data, int flag)
{
	char	*var_name;
	char	*tmp1;
	char	*tmp2;
	int		i;

	var_name = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	i = ft_new_strchr((*tok)->token, '=');
	if ((*tok)->plus == 1)
	{
		tmp1 = ft_substr((*tok)->token, 0, i - 1);
		ft_handle_malloc(flag + TAB_STR1, tmp1, 0, data);
		tmp2 = ft_substr((*tok)->token, i, ft_strlen((*tok)->token) - i + 1);
		ft_handle_malloc(flag + TAB_STR1, tmp2, 0, data);
		ft_handle_malloc(DELONE, (*tok)->token, 0, NULL);
		(*tok)->token = ft_strjoin(tmp1, tmp2);
		ft_handle_malloc(flag + TAB_STR1, (*tok)->token, 0, data);
		ft_handle_malloc(DELONE, tmp1, 0, NULL);
		ft_handle_malloc(DELONE, tmp2, 0, NULL);
		i = i - 1;
	}
	var_name = ft_substr((*tok)->token, 0, i);
	ft_handle_malloc(flag + TAB_STR1, var_name, 0, data);
	return (var_name);
}

static int	ft_get_export(t_data *data, t_token *token, int *res, int flag)
{
	int		i;
	char	*var_name;

	var_name = NULL;
	i = ft_get_end_var(token, res);
	if (token->token[i] == '+')
	{
		if (token->token[i + 1] == '\0' \
			|| (token->token[i + 1] && token->token[i + 1] != '='))
			*res = ft_msg(1, token->token, ": ", ERRNAM);
		else
		{
			token->plus = 1;
			var_name = ft_update_plus_token(&token, data, flag);
			*res = ft_check_export(token, data, flag, var_name);
		}
	}
	else if (token->token[i] == '=')
	{
		var_name = ft_update_plus_token(&token, data, flag);
		*res = ft_check_export(token, data, flag, var_name);
	}
	else if (token->token[i] == '\0')
		*res = ft_add_export(token, data, flag, ft_strlen(token->token));
	return (0);
}

int	ft_export(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;
	int		res;
	int		res2;

	token = cmd->token;
	res = 0;
	res2 = 0;
	if (token->next == NULL)
		return (ft_display_export(data, flag), 0);
	token = token->next;
	while (token)
	{
		if ((ft_isalpha(token->token[0]) == 0) && (token->token[0] != '_'))
			res = ft_msg(1, token->token, ": ", ERRNAM);
		else if ((token->token[0] == '_') && (token->token[1] == '='))
			res = 0;
		else
			ft_get_export(data, token, &res, flag);
		if (res == 0 && res2 == 0)
			res2 = 0;
		else
			res2 = 1;
		token = token->next;
	}
	return (res2);
}
