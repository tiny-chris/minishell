/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 09:43:32 by cgaillag          #+#    #+#             */
/*   Updated: 2022/07/21 16:23:44 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ERMSG_AC "Invalid number of arguments provided"
# define ERMSG_CM "Command not found"
# define ERMSG_ER "Error: "
# define ERMSG_MA "Memory allocation failure"
# define ERMSG_NF "No such file or directory"
# define ERMSG_UE "Unexpected error"

/********************************* STRUCTURE **********************************/
/*	***** Monitoring structure for pipex *****
*/
typedef struct s_data
{
	int		ac;
	char	**av;
	char	**envp;
	int		file_in;
	int		file_out;
	int		nb_cmd;
	int		nb_fd;
	int		*pid;
	int		**fd;
	char	**cmd;
	char	**tab_path;
	char	**cmd_opt;
	char	*cmd_path;
}	t_data;

/****************************** PIPEX FUNCTIONS *******************************/

/*	***** INIT ***** */
int		**ft_init_fd_pp(int nb_fd);
char	**ft_init_cmd_pp(char **argv, int nb_cmd);
char	**ft_init_cmd_opt_pp(char **cmd, int index_cmd);
t_data	*ft_init_t_data_pp(int argc, char **argv, char **envp);

/*	***** PARSING ***** */
char	**ft_get_tab_paths(t_data *d_ref);
char	*ft_find_cmd_path(t_data *d_ref, char *cmd);
char	*ft_find_cmd_path2(t_data *d_ref, char *cmd);

/*	***** FILES ***** */
void	ft_get_files_io(t_data *d_ref);
int		ft_redirect_inout(t_data *d_ref, int i);

/*	***** CLEAN ***** */
void	*ft_free_rev_tabstr_pp(char **tab_str, int i_min, int i_max);
void	ft_free_tabstr_1line_pp(char **tab_str);
void	ft_close_fd_pp(t_data *d_ref);
void	ft_exit_pp(int res, t_data *d_ref);
int		ft_msg(int res, char *msg1, char *msg2, char *msg3);

/*	***** PROG ***** */
int		pipex(t_data *d_ref, int exit_status);
void	ft_child_process(t_data *d_ref, int i);
int		ft_parent_process(t_data *d_ref, int exit_status);

#endif
