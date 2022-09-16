/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:46:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/07/21 18:25:50 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*	Gets all possible 'env' paths for commands to be executed (from PATH line)
**	and store them in a char ** 
**	For each path, checks if there is already a '/' character at the end of it,
**	if not, appends a '/' at the end of the path
*/
char	**ft_get_tab_paths(t_data *d_ref)
{
	char	*ptr_path;
	char	**tab_path;
	int		i;

	i = 0;
	ptr_path = NULL;
	tab_path = NULL;
	while (d_ref->envp[i] != NULL && d_ref->envp[i][0] != '\0')
	{
		if (ft_strncmp(d_ref->envp[i], "PATH=", 5) == 0)
		{
			ptr_path = ft_strdup(d_ref->envp[i] + 5);
			break ;
		}
		i++;
	}
	if (!ptr_path)
		return (NULL);
	tab_path = ft_split(ptr_path, ':');
	ft_free_str(ptr_path);
	if (!tab_path)
		return (NULL);
	return (tab_path);
}

/*	Finds the correct path for the required command 
**	STEP 1 - This function checks potential given path out of PATH:
**	- via absolute path (if '/' already mentioned at the beginning)
**	- via a relative path (in the current directory) --> use './'
**	Return value: command path (NULL if none is found)
**	--> leads to STEP 2 - if no '/': check via env PATH
*/
char	*ft_find_cmd_path(t_data *d_ref, char *cmd)
{
	char	*cmd_path;

	if (ft_is_in_set(cmd, '/'))
	{
		if (ft_strlen(cmd) == 1)
			return (ft_msg(127, cmd, ": ", ERMSG_CM), NULL);
		else if (cmd[0] == '/')
		{
			if (access((const char *) cmd, F_OK | X_OK) == 0)
				return (cmd);
			return (ft_msg(2, cmd, ": ", ERMSG_NF), NULL);
		}
		cmd_path = ft_strjoin("./", (const char *) cmd);
		if (!cmd_path)
		{
			ft_close_fd_pp(d_ref);
			ft_exit_pp(ft_msg(-1, ERMSG_ER, ": ", ERMSG_MA), d_ref);
		}
		if (access((const char *) cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		return (free(cmd_path), ft_msg(2, cmd, ": ", ERMSG_NF), NULL);
	}
	cmd_path = ft_find_cmd_path2(d_ref, cmd);
	return (cmd_path);
}

/*	Finds the correct path in the envp for the required command 
**	STEP 2 - Function that checks is env is existing and if there
**	is any correct path to execute the command cmd
**	Return value: command path (NULL if none is acceptable)
*/
char	*ft_find_cmd_path2(t_data *d_ref, char *cmd)
{
	char	*new_path;
	char	*cmd_path;
	int		i;
	int		j;

	cmd_path = NULL;
	if (!d_ref->tab_path)
		return (ft_msg(127, cmd, ": ", ERMSG_CM), NULL);
	i = -1;
	while (d_ref->tab_path[++i])
	{
		j = ft_strlen(d_ref->tab_path[i]) - 1;
		if (d_ref->tab_path[i][j] != '/')
			new_path = ft_strjoin((const char *) d_ref->tab_path[i], "/");
		else
			new_path = ft_strdup(d_ref->tab_path[i]);
		cmd_path = ft_strjoin((const char *) new_path, (const char *) cmd);
		free(new_path);
		if (access((const char *) cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	ft_msg(127, cmd, ": ", ERMSG_CM);
	return (NULL);
}
