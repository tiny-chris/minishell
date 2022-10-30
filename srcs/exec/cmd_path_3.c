/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:40:34 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/30 12:44:01 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

/*	<SUMMARY> Checks if absolute path as a directory & its access
*/

static void	ft_check_directory(char *token, char *full_path)
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

static char	*ft_check_abs_path_nobackslash(char *full_path, char *token)
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

static void	ft_check_abs_backslash(char *full_path, char *token, t_data *data)
{
	char	*tmp;

	tmp = NULL;
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

static void	ft_check_sub_directory(char *token, char *tmp)
{
	DIR		*directory;

	directory = NULL;
	directory = opendir(tmp);
	if (directory == NULL)
	{
		g_val_exit = ft_msg(126, token, ": ", ERRNDR);
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (g_val_exit);
	}
	closedir(directory);
}

char	*ft_check_abs_path(char *token, char *full_path, t_data *data, int len)
{
	char	*tmp;

	tmp = NULL;
	if (!token)
		return (NULL);
	ft_check_directory(token, full_path);
	if (token[len - 1] != '/')
	{
		tmp = ft_path_last_slash(full_path, tmp);
		if (tmp)
		{
			ft_check_sub_directory(token, tmp);
			ft_handle_malloc(DELONE, tmp, 0, NULL);
		}
		if (access((const char *)full_path, F_OK) == 0)
			return (ft_check_abs_path_nobackslash(full_path, token));
	}
	else
	{
		ft_check_abs_backslash(full_path, token, data);
	}
	g_val_exit = ft_msg(127, token, ": ", ERRFOD);
	ft_handle_malloc(0, NULL, 0, NULL);
	exit (g_val_exit);
	return (NULL);
}
