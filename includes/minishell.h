/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:48:07 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/19 12:04:03 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define ERRSTX "syntax error"
# define ERRMAL "memory allocation error"

typedef enum s_type
{
	COMMAND 		= 0,
	BUILTIN 		= 1,
	WORD 			= 2,
	WORD_N 			= 3,
	SP_QUOTES		= 4,
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
	char			*unspace_cmd;//raw_cmd_no_space;//modifié
	char			*no_redir_cmd;
	char			*undoll_cmd;
	char			*clean_cmd;//modifier par expand_cmd ??
	t_token			*token;
	t_token			*tok_redir;
	int				infile;//
	int				outfile;//
	char			**cmd_opt;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*line;
	char			*prompt;
	t_env			*env;
	int				val_exit;
	char			*str_exit;
	int				nb_pipes;
	t_cmd			*cmd;
	char			**built_in;
	int				*pid;//
	int				**pipe_fd;//nb de fd[][]
	t_env			*env_path;
}	t_data;

/*	***** INIT *****	*/
/*	*****************	*/

t_env	*ft_get_env(char **envp);
char	**ft_built_in(void);
int		ft_only_space(char *line);


/*	***** LEXER *****	*/
/*	*****************	*/

int		ft_lexer(char *line);
int		ft_quote(char *line);
int		ft_pipe(char *line);
int		ft_count_pipe(char *line);
int		ft_first_pipe(char *line);
int		ft_redir(char *line);
int		ft_check_redir(char *line, int i);

/*	***** PARSER *****	*/
/*	******************	*/

/*	Step 1	get_commands */

t_cmd	*ft_get_commands(t_data *data);
char	*ft_get_raw_cmd(t_data *data, int i);
//int		ft_get_pipe(char *line, int i);// mise en static
//int		ft_next_pipe(char *line, int i);// mise en static

/*	Step 2	del_spaces */

int		ft_del_spaces(t_data *data);
int		ft_unspace_cmd_len(char	*raw_cmd);
char	*ft_fill_unspace_cmd(char *raw_cmd, int len);

/*	Step 3	extract_redir */

int		ft_get_redir(t_data *data);
int		ft_len_no_redir(char *unspace_cmd);
char	*ft_fill_no_redir(char *unspace_cmd, int len);
int		ft_get_redir_list(char *unspace_cmd, t_token **tok_redir);
int		ft_is_redir(char *unspace_cmd, int *j);

/*	Step (x)	clean_redir */

int		ft_clean_redir(t_cmd *cmd, t_data *data);
int		ft_fill_undoll_redir(t_token *token, int len);
int		ft_fill_expand_redir(t_token *token, int len, t_data *data);
int		ft_fill_consec_quotes_redir(t_token *token, int len);
int		ft_fill_clean_redir(t_token *token, int len);

/*	Step (x + 1)	clean_heredoc */

int		ft_clean_heredoc(t_token *token);
int		ft_undoll_heredoc_len(char *token);
int		ft_fill_undoll_heredoc(t_token *token, int len);
int		ft_unquote_heredoc_len(char *token);
int		ft_fill_unquote_heredoc(t_token *token, int len);

/*	Step 4	del_dolls */

int		ft_del_dolls(t_data *data);
int		ft_undoll_cmd_len(char *no_redir_cmd);
char	*ft_fill_undoll_cmd(char *no_redir_cmd, int len);
void	ft_neg_dolls(char *undoll_cmd);

/*	Step 5	expand */

int		ft_expand(t_data *data);
int		ft_expand_cmd_len(char *undoll_cmd, t_data *data);
int		ft_get_expand_size(char *undoll_cmd, int *i, t_data *data);
int		ft_get_error_size(t_data *data);
char	*ft_fill_clean_cmd(char *undoll_cmd, int len, t_data *data);//modifier le nom de la fonction
void	ft_fill_expand(char *undoll_cmd, int *i, char *clean_cmd, int *j, t_data *data);

/*	Step 6	to_tokens */

int		ft_tokenizer(t_data *data);
int		ft_get_token(t_cmd *cmd);
int		ft_clean_token(t_cmd *cmd, t_data *data);
int		ft_consec_quotes_len(char *token);
char	*ft_fill_consec_quotes(char *token, int len);
int		ft_space_quotes(char *tmp_token, t_token *token);
int		ft_clean_len(char *token);
char	*ft_fill_clean_token(char *tmp_token, int len);
void	ft_positive_token(t_token *token);
//int		ft_del_empty_token(t_cmd **cmd, t_data *data);
int		ft_del_empty_token(t_cmd *cmd, t_data *data);
int		ft_type_token(t_cmd *cmd, t_data *data);
int		ft_check_built_in(char *token, t_data *data, int tok_len);
t_token	*ft_get_token_echo(t_token **token);
void	ft_echo_join_words_fill(t_token *token);
int		ft_del_nword(t_cmd *cmd);

	/*	env_list */

t_env	*ft_lstlast_env(t_env *lst);
int		ft_lstadd_env(t_env **env, char *envp);
void	ft_lstdelone_env(t_env *node);
void	ft_free_env(t_env **env);

	/*	cmd_list */

t_cmd	*ft_lstlast_cmd(t_cmd *lst);
int		ft_lstadd_cmd(t_cmd **cmd, char *cmdline);
void	ft_lstdelone_cmd(t_cmd *node);
void	ft_free_cmd(t_cmd **cmd);

	/*	token_list */

t_token	*ft_lstlast_tok(t_token *lst);
int		ft_lstadd_token(t_token **tok, int type, char *token);
void	ft_lstdelone_tok(t_token *node);
void	ft_lstclear_token(t_token *token);
void	ft_free_token(t_token **token);

	/*	utils */

void	*ft_free_tabstr(char **tab_str);
int		ft_new_strchr(const char *s, int c);
void	*ft_free_tabint(int **tab_int, int size);

/*	***** EXEC *****	*/
/*	****************	*/

char	*ft_echo(t_cmd *cmd, t_data *data);
int		ft_exec(t_data *data);
int		*ft_init_pid(t_data *data);
int		**ft_init_pipe(t_data *data);
void	ft_get_env_path(t_data *data, char **envp);
t_env	*ft_lst_env_path(char **tab_path);
int		ft_lstadd_env2(t_env **env, char *tab_path);
void	ft_child_process(t_data *data, int i);
int		ft_get_files_io(t_data *data);
int		ft_redirect_inout(t_data *data, t_cmd *cmd, int i);

// ***** ex-del_quotes *****

//int		ft_del_quotes(t_data *data);
//int		ft_unquote_cmd_len(char *undoll_cmd);
//int		ft_is_allspace(char *str, int i, char c);
//char	*ft_fill_unquote_cmd(char *undoll_cmd, int len);
//int		ft_contains_doll(char *undoll_cmd, int i, char c);

// ***** doublon expand *****

// int		ft_expand(t_data *data);
// int		ft_expand_cmd_len(char *unquote_cmd, t_data *data);
// int		ft_get_expand_size(char *unquote_cmd, int *i, t_data *data);
// char	*ft_fill_clean_cmd(char *unquote_cmd, int len, t_data *data);

// ***** old token & redir management *****

//int		ft_check_word_n(char *clean_cmd_no_redir, int *i, t_token **token);
//int		ft_first_token(t_token *token, int len);
//int		ft_is_redir(char *clean_cmd, int *i);
//int		ft_get_redir(t_cmd *cmd);
//void	ft_fill_no_redir(char *clean_cmd, char *clean_cmd_no_redir);
//int		ft_get_redir_list(char *clean_cmd, t_token **tok_redir);
//int		ft_len_no_redir(char *clean_cmd);

#endif
