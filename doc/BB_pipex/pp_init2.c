/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:58:04 by cgaillag          #+#    #+#             */
/*   Updated: 2022/07/21 16:09:31 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <stdlib.h>

/*	Initialises an array of strings that only contains 'commands'
**	**********
**	Extract of 'char **argv' that does not take into account:
**	- executable --> argv[0]
**	- infile & outfile --> argv[1] & argv[argc - 1]
**	- (bonus - not pushed) here_doc string and limiter --> argv[1] & argv[2]
*/
char	**ft_init_cmd_pp(char **argv, int nb_cmd)
{
	char	**tab_str;
	int		i;

	if (argv == NULL || nb_cmd <= 0)
		return (NULL);
	tab_str = (char **) malloc(sizeof(char *) * (nb_cmd + 1));
	if (tab_str == NULL)
		return (free(tab_str), NULL);
	tab_str[nb_cmd] = NULL;
	i = 0;
	while (i < nb_cmd)
	{
		tab_str[i] = ft_strdup(argv[2 + i]);
		if (!tab_str[i])
		{
			ft_free_tabstr(tab_str);
			break ;
		}
		i++;
	}
	return (tab_str);
}

/*	Initialises pairs of integers to create pipes
**	**********
**	Number of file descriptors = (number of commands - 1)
**	e.g. for 'cmd1' --> fd[0]: read on fd[0][0] & write on fd[0][1]
*/
int	**ft_init_fd_pp(int nb_fd)
{
	int	**tab_int;
	int	i;

	tab_int = (int **) malloc(sizeof(int *) * nb_fd);
	if (tab_int == NULL)
		return (free(tab_int), NULL);
	i = 0;
	while (i < nb_fd)
	{
		tab_int[i] = (int *) malloc(sizeof(int) * 2);
		if (!tab_int[i])
		{
			ft_free_tabint(tab_int, i - 1);
			break ;
		}
		i++;
	}
	return (tab_int);
}

/*	Initialises the options of the specifies commnd 'cmd'
**	by splitting the 'cmd' string with delimiter ' '
*/
char	**ft_init_cmd_opt_pp(char **cmd, int index_cmd)
{
	char	**cmd_options;

	cmd_options = NULL;
	if (cmd == NULL || index_cmd < 0 || \
		(ft_strncmp(cmd[index_cmd], "\0", 1) == 0))
		return (NULL);
	if (ft_strncmp(cmd[index_cmd], " ", ft_strlen(cmd[index_cmd])) == 0)
	{
		cmd_options = (char **) malloc(sizeof(char *) * (1 + 1));
		if (!cmd_options)
			return (NULL);
		cmd_options[0] = ft_strdup(" ");
		cmd_options[1] = "\0";
		return (cmd_options);
	}
	cmd_options = ft_split(cmd[index_cmd], ' ');
	if (!cmd_options || cmd_options[0][0] == 0)
	{
		ft_free_tabstr(cmd_options);
		cmd_options = NULL;
		return (NULL);
	}
	return (cmd_options);
}
