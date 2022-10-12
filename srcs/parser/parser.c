/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:00:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/12 17:34:37 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Appeler cette fonction dans minishell.c DANS la boucle infinie
*/
int	ft_parser(t_data *data)
{
	data->nb_pipes = ft_count_pipe(data->line);
	data->cmd = ft_get_commands(data);//separation des commandes en fonction du nb de pipes
	ft_del_spaces(data);
	ft_get_redir(data);
	ft_del_dolls(data);
	ft_expand(data);
	ft_tokenizer(data);
	ft_heredoc_path(data);
	return (0);
}
