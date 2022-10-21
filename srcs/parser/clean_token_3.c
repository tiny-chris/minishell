/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:58:32 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 13:33:01 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_cq4(char *token, char *tmp_cmd, char c, t_int *var)
{
	tmp_cmd[var->j] = c;
	(var->j)++;
	(var->i)++;
	while (token[var->i] && token[var->i] != c)
	{
		tmp_cmd[var->j] = token[var->i];
		(var->i)++;
		(var->j)++;
	}
	tmp_cmd[var->j] = c;
	(var->j)++;
}

static void	ft_fill_cq3(char *token, t_int *var)
{
	(var->i) += 2;
	while (token[var->i] && (token[var->i] == 34 || token[var->i] == 39)
		&& (token[var->i + 1] && token[var->i + 1] == token[var->i]))
		(var->i) += 2;
	(var->i)--;
}

static char	*ft_fill_cq2(char *token, char *tmp_cmd, char c, t_int *var)
{
	if (var->i == 0)
	{
		(var->i) += 2;
		while (token[var->i] && (token[var->i] == 34 || token[var->i] == 39)
			&& (token[var->i + 1] && token[var->i + 1] == token[var->i]))
			(var->i) += 2;
		if (token[var->i] == '\0')
		{
			tmp_cmd[var->j] = c;
			(var->j)++;
			tmp_cmd[var->j] = c;
			(var->j)++;
			tmp_cmd[var->j] = '\0';
			return (tmp_cmd);
		}
		(var->i)--;
	}
	else if (var->i > 0)
		ft_fill_cq3(token, var);
	return (NULL);
}

static char	*ft_fill_cq1(char *token, char *tmp_cmd, t_int *var)
{
	char	c;

	c = token[var->i];
	if (token[var->i + 1] == c)
	{
		if (ft_fill_cq2(token, tmp_cmd, c, var))
			return (tmp_cmd);
	}
	else
		ft_fill_cq4(token, tmp_cmd, c, var);
	return (NULL);
}

char	*ft_fill_consec_quotes(char *token, int len)
{
	char	*tmp_cmd;
	t_int	var;

	var.i = 0;
	var.j = 0;
	tmp_cmd = ft_handle_malloc(MALLOC_M + TAB_STR1, NULL, (len + 1), NULL);
	while (token[var.i])
	{
		if (token[var.i] == 34 || token[var.i] == 39)
		{
			if (ft_fill_cq1(token, tmp_cmd, &var))
				return (tmp_cmd);
		}
		else
		{
			tmp_cmd[var.j] = token[var.i];
			(var.j)++;
		}
		(var.i)++;
	}
	tmp_cmd[var.j] = '\0';
	return (tmp_cmd);
}
