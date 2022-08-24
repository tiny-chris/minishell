/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:48:07 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/24 16:47:24 by cgaillag         ###   ########.fr       */
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

# define ERRSTX "syntax error"

typedef struct s_env{
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*raw_cmd;
	char			*clean_cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*line;
	char			*prompt;
	t_env			*env;
	int				val_exit;
	t_cmd			*cmd;
}	t_data;

t_env	*ft_get_env(char **envp);
int		ft_lstadd_env(t_env **env, char *envp);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_new_strchr(const char *s, int c);
void	ft_lstdelone_env(t_env *node);
void	ft_free_env(t_env **env);

int		ft_quote(char *line);
int		ft_pipe(char *line);
int		ft_first_pipe(char *line);
int		ft_count_pipe(char *line);
int		ft_redir(char *line);
int		ft_check_redir(char *line, int i);
int		ft_lexer(char *line);



#endif
