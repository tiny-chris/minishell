/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_init1_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:58:45 by cgaillag          #+#    #+#             */
/*   Updated: 2022/07/20 19:13:12 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*  ***** FT_INIT_CLEAN_T_DATA pipex *****
**  *************************
**	Initialises the reference data structure with no data in it
**	--> put -1 for 'int' elements and NULL for tab (* or **)
**	as 0 is a valid fd and should not be used for initialisation
**	Returns the newly initialized data structure
*/
static void	ft_init_clean_t_data(t_data *d_ref)
{
	d_ref->ac = -1;
	d_ref->av = NULL;
	d_ref->envp = NULL;
	d_ref->file_in = -1;
	d_ref->file_out = -1;
	d_ref->nb_cmd = -1;
	d_ref->nb_fd = -1;
	d_ref->pid = NULL;
	d_ref->fd = NULL;
	d_ref->cmd = NULL;
	d_ref->tab_path = NULL;
	d_ref->cmd_opt = NULL;
	d_ref->cmd_path = NULL;
}

/*  ***** FT_INIT_T_DATA pipex *****
**  *************************
**  Initialises the reference structure that will gather all necessary data
**	to run pipex 
*/
t_data	*ft_init_t_data_pp(int argc, char **argv, char **envp)
{
	t_data	*d_ref;

	d_ref = malloc(sizeof(t_data));
	if (d_ref == NULL)
		ft_exit_pp(ft_msg(1, ERMSG_ER, ": ", ERMSG_MA), NULL);
	ft_init_clean_t_data(d_ref);
	d_ref->ac = argc;
	d_ref->av = argv;
	d_ref->envp = envp;
	ft_get_files_io(d_ref);
	d_ref->nb_cmd = argc - 3;
	d_ref->nb_fd = d_ref->nb_cmd - 1;
	d_ref->fd = ft_init_fd_pp(d_ref->nb_fd);
	d_ref->pid = (int *) malloc(sizeof(int) * d_ref->nb_cmd);
	if (d_ref->pid == NULL)
		ft_exit_pp(ft_msg(1, "PID error", strerror(errno), ""), d_ref);
	d_ref->cmd = ft_init_cmd_pp(d_ref->av, d_ref->nb_cmd);
	d_ref->tab_path = ft_get_tab_paths(d_ref);
	if (d_ref->fd == NULL || d_ref->cmd == NULL)
		ft_exit_pp(ft_msg(1, ERMSG_ER, ": ", ERMSG_MA), d_ref);
	return (d_ref);
}
