/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:01:52 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/19 20:05:59 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/*	<SUMMARY> Checks if absolute path as a directory & its access
**
**	Details (TO BE REMOVED) !!!!!!!!!!!!!!!!!!!!!!!!!!
**	Check #1: is it a directory?
**	- if yes: 'is a directory', 126
**	- if no:
**		Check #2: is the last character of token a '/' (slash)?
**		- if no:
**			Check #3: is access 'F_OK' = success?
**				- if yes:
**					Check #4: is access 'X_OK' = success?
**						- if yes: return token
**						- it no: 'permission denied', 126
**				- if no: 'no such file or directory', 127
**		- if yes (last char = '/')
**			Check #5: is access 'F_OK' = success?
**				- if yes: 'not a directory', 126
**				- if no: 'no such file or directory', 127
*/

void	ft_check_abspath_directory(char *token, char *full_path)
{
	DIR		*directory;

	directory = NULL;
	directory = opendir(full_path);
	if (directory != NULL)
	{
		closedir(directory);
		g_val_exit = ft_msg(126, token, ": ", ERRDIR);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (g_val_exit);
	}
}

char	*ft_abs_no_last_slash(char *token, char *full_path)
{
	if (access((const char *)full_path, F_OK) == 0)
	{
		if (access((const char *)full_path, X_OK) == 0)
			return (ft_strdup(full_path));
		else
		{
			g_val_exit = ft_msg(126, token, ": ", ERRPRD);
			ft_handle_malloc(0, NULL, 0, NULL);
			exit (g_val_exit);
		}
	}
	return (NULL);
}

void	ft_abs_last_slash(char *token, char *full_path, t_data *data, char *tmp)
{
	tmp = ft_substr(full_path, 0, ft_strlen(full_path) - 1);
	ft_handle_malloc(ADD_M + TAB_STR1, tmp, 0, data);
	if (access((const char *)tmp, F_OK) == 0)
	{
		ft_handle_malloc(DELONE, tmp, 0, NULL);
		g_val_exit = ft_msg(126, token, ": ", ERRNDR);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (g_val_exit);
	}
	if (tmp)
		ft_handle_malloc(DELONE, tmp, 0, NULL);
	if (full_path)
		ft_handle_malloc(DELONE, full_path, 0, NULL);
}

char	*ft_check_abs_path(char *token, char *full_path, t_data *data, int len)
{
	char	*tmp;

	tmp = NULL;
	if (!token)
		return (NULL);
	ft_check_abspath_directory(token, full_path);
	if (token[len - 1] != '/')
	{
		tmp = ft_abs_no_last_slash(token, full_path);
		if (tmp != NULL)
			return (tmp);
	}
	else
		ft_abs_last_slash(token, full_path, data, tmp);
	g_val_exit = ft_msg(127, token, ": ", ERRFOD);
	ft_handle_malloc(0, NULL, 0, NULL);
	exit (g_val_exit);
	return (NULL);
}
