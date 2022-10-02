/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:47:49 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 15:47:49 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_get_shlvl(t_data *data) */
/* { */

/* 	temp = ft_getenv (&data, data->envlist, "SHLVL"); */
/* 	data->shlvl = ft_atoi(temp); */
/* 	ft_free (temp); */
/* } */

/*
 ** Update the SHLVL.
 */

void	ft_shlvl_update(t_data *data)
{
	char	*str;
	char	**unsetcmd;
	char	**exportcmd;
	char	*temp;

	temp = ft_getenv (data, data->envlist, "SHLVL");
	data->shlvl = ft_atoi(temp);
	ft_free (temp);
	unsetcmd = ft_split ("unset SHLVL", ' ');
	if (!unsetcmd)
		ft_exitmsg (data, "malloc");
	ft_unset (data, unsetcmd);
	ft_free_tab (unsetcmd);
	str = ft_strjoin_free_s2 ("export SHLVL=", ft_itoa (++data->shlvl));
	exportcmd = ft_split(str, ' ');
	if (!exportcmd)
		ft_exitmsg (data, "malloc");
	ft_free (str);
	ft_export (data, exportcmd);
	ft_free_tab (exportcmd);
	temp = ft_getenv (data, data->envlist, "SHLVL");
	data->shlvl = ft_atoi(temp);
	ft_free (temp);
}
