/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:48:07 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/02 17:51:12 by cgaillag         ###   ########.fr       */
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
# define ERRMAL "memory allocation error"

typedef enum s_type
{
	COMMAND 		= 0,
	BUILTIN 		= 1,
	WORD 			= 2,
	WORD_N 			= 3,
	GREAT 			= 10,
	OUTFILE 		= 20,
	D_GREAT			= 11,
	OUTFILE_APPEND 	= 21,
	LESS			= 12,
	INFILE 			= 22,
	D_LESS			= 13,
	HERE_DOC 		= 23,
}	t_type;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*raw_cmd;
	char			*unquote_cmd;
	char			*clean_cmd;
	char			*clean_cmd_no_redir;
	t_token			*token;
	t_token			*tok_redir;
	int				infile;//
	int				outfile;//
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*line;
	char			*prompt;
	t_env			*env;
	int				val_exit;
	int				nb_pipes;
	t_cmd			*cmd;
	char			**built_in;
	int				*pid;//
	int				**pipe;//nb de fd[][]
	char			**env_path;//
}	t_data;

char	**ft_built_in(void);
void	*ft_free_tabstr(char **tab_str);
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

int		ft_get_pipe(char *line, int i);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
int		ft_lstadd_cmd(t_cmd **cmd, char *cmdline);
char	*ft_get_cmdline(t_data *data, int i);
int		ft_next_pipe(char *line, int i);
t_cmd	*ft_get_commands(t_data *data);
void	ft_lstdelone_cmd(t_cmd *node);
void	ft_free_cmd(t_cmd **cmd);

int		ft_del_quotes(t_data *data);
int		ft_unquote_cmd_len(char *raw_cmd);
int		ft_is_allspace(char *str, int i, char c);
char	*ft_fill_unquote_cmd(char *raw_cmd, int len);

int		ft_expand(t_data *data);
int		ft_expand_cmd_len(char *unquote_cmd, t_data *data);
int		ft_get_expand_size(char *unquote_cmd, int *i, t_data *data);
char	*ft_fill_clean_cmd(char *unquote_cmd, int len, t_data *data);

int		ft_tokenizer(t_data *data);
t_token	*ft_get_token(t_cmd *cmd, t_data *data);
int		ft_check_built_in(char *clean_cmd, t_data *data, int i);
int		ft_check_word_n(char *clean_cmd_no_redir, int *i, t_token **token);
void	ft_clean_token(t_cmd *cmd, t_data *data);
int		ft_is_redir(char *clean_cmd, int *i);
int		ft_lstadd_token(t_token **tok, int type, char *token);
t_token	*ft_lstlast_tok(t_token *lst);
void	ft_free_token(t_token **token);
void	ft_lstdelone_tok(t_token *node);
void	ft_lstclear_token(t_token *token);
int		ft_get_redir(t_cmd *cmd);
void	ft_fill_no_redir(char *clean_cmd, char *clean_cmd_no_redir);
int		ft_get_redir_list(char *clean_cmd, t_token **tok_redir);
int		ft_len_no_redir(char *clean_cmd);
void	ft_echo_join_words_fill(t_token *token);
t_token	*ft_get_token_echo(t_token **token);

#endif
