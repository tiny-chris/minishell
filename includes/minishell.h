/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:48:07 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/17 17:36:05 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env{
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

t_env	*ft_get_env(char **envp);
int		ft_lstadd_env(t_env **env, char *envp);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_new_strchr(const char *s, int c);

#endif