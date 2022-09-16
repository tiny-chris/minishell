/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:58:04 by cgaillag          #+#    #+#             */
/*   Updated: 2022/07/21 16:10:03 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

/*	Function that open provided files in command line
**	- open infile to be read
**	- open outfile to be written and replace current content
*/
void	ft_get_files_io(t_data *d_ref)
{
	d_ref->file_in = open(d_ref->av[1], O_RDONLY);
	if (d_ref->file_in < 0)
		ft_msg(errno, d_ref->av[1], ": ", strerror(errno));
	d_ref->file_out = open(d_ref->av[d_ref->ac - 1], O_CREAT | O_RDWR | \
			O_TRUNC, 0644);
	if (d_ref->file_out < 0)
		ft_msg(errno, d_ref->av[d_ref->ac - 1], ": ", strerror(errno));
}

/*	Function that redirects pipex' fds (file1, file2 or generated **fds) 
**	to stdin & to sdtout in each appropriate process using dup2()
**	Parameters: 
**	- ref structure that contains all key data for pipex prog, 
**	- the index of the command to be executed (equiv to the child #) 
**	Return value: 0 if all went good, -1 if something went wrong
**	**********
**	cf.: depending on command index, child'x' will execute cmd'x'
**	e.g. for i = 0, fd input = file1 and fd output = f[0][1] (pipewrite)
**		 for i = 1, fd input = f[0][0] (piperead) and fd output = file2 
*/
int	ft_redirect_inout(t_data *d_ref, int i)
{
	if (i == 0)
	{
		if (dup2(d_ref->file_in, STDIN_FILENO) == -1 \
			|| dup2(d_ref->fd[i][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (i == (d_ref->nb_cmd - 1))
	{
		if (dup2(d_ref->fd[i - 1][0], STDIN_FILENO) == -1 \
			|| dup2(d_ref->file_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(d_ref->fd[i - 1][0], STDIN_FILENO) == -1 \
			|| dup2(d_ref->fd[i][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}
