/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:58:31 by cgaillag          #+#    #+#             */
/*   Updated: 2022/07/21 16:16:31 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

/*	Function that frees (created) strings of an arrray of strings 'tab_str'
**	from index i_min to index i_max, both included and then free the table
**	of strings
*/
void	*ft_free_rev_tabstr_pp(char **tab_str, int i_min, int i_max)
{
	int	i;

	i = i_max;
	while (i >= i_min)
	{
		free(tab_str[i]);
		i--;
	}
	free(tab_str);
	tab_str = NULL;
	return (NULL);
}

/*	Function that frees (created) strings of an arrray of strings 'tab_str'
**	from index i_min to index i_max, both included and then free the table
**	of strings
*/
void	ft_free_tabstr_1line_pp(char **tab_str)
{
	if (tab_str)
	{
		free(tab_str[0]);
		free(tab_str);
	}
}

/*	Function **CLOSE ALL FD pipex** that closes:
**	- infile and/or outfile if still open 
**	- fd pipes to read fd[i][0] or to write fd[i][1] 
**	Useful in case of error and after redirections 
*/
void	ft_close_fd_pp(t_data *d_ref)
{
	int	i;

	i = 0;
	if (d_ref->file_in != -1)
		close(d_ref->file_in);
	if (d_ref->file_out != -1)
		close(d_ref->file_out);
	while (i < d_ref->nb_fd)
	{
		if (d_ref->fd[i][0] != -1)
			close(d_ref->fd[i][0]);
		if (d_ref->fd[i][1] != -1)
			close(d_ref->fd[i][1]);
		i++;
	}
}

/*	Function **EXIT pipex** that:
**	1. cleans & frees the t_data structure if it exists
**	Actions prior freeing d_ref:
**		- close fds 
**		- clean int*	'pid' if not NULL
**		- clean char*	'cmd_path' if not NULL 
**		- clean int**	'fd' if not NULL
**		- clean char**	'cmd', 'tab_path', 'cmd_opt' if not NULL  
**	2. and exits as success or failure depending on provided 'res'
**		(0 = success, else = failure as error number) 
**	***********
**	Parameters:
**	- res = result for the exit (equiv to errno)
**		the function ft_res_msg can be called and return the res
**	- t_data = struct 'd_ref' to clean
*/
void	ft_exit_pp(int res, t_data *d_ref)
{
	if (d_ref != NULL)
	{
		if (d_ref->pid != NULL)
			free(d_ref->pid);
		if (d_ref->fd != NULL)
			ft_free_tabint(d_ref->fd, (d_ref->nb_fd - 1));
		if (d_ref->cmd != NULL)
			ft_free_tabstr(d_ref->cmd);
		if (d_ref->tab_path != NULL)
			ft_free_tabstr(d_ref->tab_path);
		if (d_ref->cmd_opt != NULL)
		{
			if (ft_strncmp(d_ref->cmd_opt[0], " ", \
				ft_strlen(d_ref->cmd_opt[0])) == 0)
				ft_free_tabstr_1line_pp(d_ref->cmd_opt);
			else
				ft_free_tabstr_rev(d_ref->cmd_opt, \
					ft_lines_tabstr(d_ref->cmd_opt));
		}
		if (d_ref->cmd_path != NULL)
			ft_free_str(d_ref->cmd_path);
		free(d_ref);
	}
	exit(res);
}

/*	Function **RES MSG pipex** that displays a message on stderr 
**	(if failure)
*/
int	ft_msg(int res, char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(msg2, 2);
	ft_putendl_fd(msg3, 2);
	return (res);
}
