/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:48:07 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/26 00:30:07 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERRFIL "Error: too many files descriptors"
# define ERRINI "minishell : could not initialise minishell"
# define ERRSTX "Syntax error near unexpected token"
# define ERRMAL "Error: memory allocation failure"
# define ERRCMD "command not found"
# define ERRDIR "is a directory"
# define ERRNDR "not a directory"
# define ERRFOD "no such file or directory"
# define ERRMSG "Error: "
# define ERRFEW "too few arguments"
# define ERRNAM "not a valid identifier"
# define ERRARG "too many arguments"
# define ERRHOM "HOME not set"
# define ERRFAR ".: filename argument required"
# define ERRFAU ".: usage: . filename [arguments]"
# define ERRPRD "permission denied"
# define ERRARC "invalid number of arguments"
# define ERRCWD "error retrieving current directory: getcwd: cannot access \
parent directories: No such file or directory"

typedef void	(*t_sighandler)(int);

typedef enum s_type
{
	COMMAND			= 0,
	BUILTIN			= 1,
	WORD			= 2,
	WORD_N			= 3,
	SP_QUOTES		= 4,
	GREAT			= 10,
	OUTFILE			= 20,
	D_GREAT			= 11,
	OUTFILE_APPEND	= 21,
	LESS			= 12,
	INFILE			= 22,
	D_LESS			= 13,
	HERE_DOC		= 23,
}	t_type;

typedef enum s_sizetype
{
	TAB_INT1		= 100,
	TAB_INT2		= 200,
	TAB_INTS		= 300,
	TAB_STR1		= 400,
	TAB_STR2		= 500,
	TAB_STRS		= 600,
	LST_ENV			= 700,
	LST_CMD			= 800,
	LST_TOK			= 900,
}	t_sizetype;

typedef enum s_flag
{
	ADD_C			= 1000,
	MALLOC_C		= 1001,
	ADD_M			= 2000,
	MALLOC_M		= 2001,
	DELONE			= 3000,
}	t_flag;

typedef struct s_int
{
	int	i;
	int	j;
}	t_int;

typedef struct s_bin
{
	void			*ptr;
	int				type;
	int				size;
	struct s_bin	*next;
}	t_bin;

typedef struct s_token
{
	char			*token;
	int				type;
	int				fd;
	int				env;
	int				printed;
	int				hd_quotes;
	int				plus;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*var_equal;
	char			*content;
	char			*envp;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*raw_cmd;
	char			*unspace_cmd;
	char			*no_redir_cmd;
	char			*undoll_cmd;
	char			*clean_cmd;
	t_token			*token;
	t_token			*tok_redir;
	int				infile;
	int				outfile;
	int				stin;
	int				stout;
	int				file_err;
	char			**cmd_opt;
	char			*cmd_path;
	char			*heredoc_path;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*line;
	char			*prompt;
	t_env			*env;
	char			**s_env;
	t_env			*export;
	char			*cwd;
	char			*oldpwd;
	char			*home;
	int				val_exit;
	char			*str_exit;
	int				nb_pipes;
	int				nb_redir;
	t_cmd			*cmd;
	char			**built_in;
	int				*pid;
	int				**pipe_fd;
	t_env			*env_path;
	char			**s_env_path;
	char			*tmp_oldpwd;
	int				sigint_hd;
}	t_data;

/*	***** INIT *****	*/
/*	*****************	*/

void	ft_minishell(t_data *data);
int		ft_clean_cmdline(t_data *data);
void	ft_exit_ctrl_d(t_data *data);

t_env	*ft_get_env(char **envp, t_data *data);
char	**ft_get_s_env(t_data *data);
char	**ft_built_in(void);
int		ft_only_space(char *line);
int		ft_init_data_1(t_data *data, char **envp);
void	ft_get_home(t_data *data, int flag);

/*	env_path */

void	ft_get_env_path(t_data *data, int flag);
int		ft_lstadd_env2(t_env **env_path, char *s_env_path_i, \
	t_data *data, int flag);

void	ft_count_btw_quotes(char *line, int *i);
void	ft_nb_csq_redir(char *line, int *i, int *len);
char	*ft_fill_btw_quotes(char *src, int *i, char *dst, int *j);
// int		ft_count_space(char *line, int i);
// int		ft_nb_csq_redir(char *line, int i);

char	*ft_fill_unspace_btw_q(char *raw, int *i, char *unspace, int *j);
char	*ft_fill_btw_quotes(char *src, int *i, char *dst, int *j);

/*	***** LEXER *****	*/
/*	*****************	*/

int		ft_lexer(char *line);
int		ft_quote(char *line);
int		ft_count_pipe(char *line);
int		ft_pipe(char *line, int count);
int		ft_redir(char *line);

/*	***** PARSER *****	*/
/*	******************	*/

int		ft_parser(t_data *data);

/*	Step 1	get_commands */

t_cmd	*ft_get_commands(t_data *data);
void	ft_init_cmd(t_cmd *cmd);
char	*ft_get_raw_cmd(t_data *data, int i);

/*	Step 2	del_spaces */

int		ft_del_spaces(t_data *data);
int		ft_unspace_cmd_len(char	*raw_cmd);
char	*ft_fill_unspace_cmd(char *raw_cmd, int len);

/*	Step 3	extract_redir */

int		ft_get_redir(t_data *data);
int		ft_len_no_redir(char *unspace_cmd);
char	*ft_fill_no_redir(char *unspace_cmd, int len);
int		ft_get_redir_lst(char *cmd, t_token **tok_redir, t_data *d, int type);

/*	Step (x)	clean_redir */

int		ft_clean_redir(t_cmd *cmd, t_data *data);
int		ft_fill_undoll_redir(t_token *token, int len);
int		ft_fill_expand_redir(t_token *token, int len, t_data *data);
int		ft_fill_consec_quotes_redir(t_token *token, int len);
int		ft_fill_clean_redir(t_token *token, int len);

/*	Step (x + 1)	clean_heredoc */

int		ft_clean_heredoc(t_token *token);
int		ft_undoll_heredoc_len(char *token);
void	ft_undoll_hd_len_doll(char *token, int *i, int *j, int *len);
int		ft_fill_undoll_heredoc(t_token *token, int len);
void	ft_fill_hd_doll(t_token *token, char *undoll_token, int *i, int *j);
void	ft_fill_hd_quotes(t_token *token, char *undoll_token, int *i, int *j);
int		ft_unquote_heredoc_len(char *token);
int		ft_fill_unquote_heredoc(t_token *token, int len);
void	ft_fill_unquote_hd2(t_token *token, char *unquote_token, \
	int *i, int *j);

/*	Step 4	del_dolls */

int		ft_del_dolls(t_data *data);
int		ft_undoll_cmd_len(char *no_redir_cmd);
char	*ft_fill_undoll_cmd(char *no_redir_cmd, int len, int i, int j);
void	ft_fill_undoll_quotes(char *no_redir, int *i, char *undoll, int *j);
void	ft_neg_dolls(char *undoll_cmd);
int		ft_fill_undoll_doll(char *no_redir, int *i, char *undoll, int *j);

/*	Step 5	expand */

int		ft_expand(t_data *data);
int		ft_expand_cmd_len(char *undoll_cmd, t_data *data);
int		ft_get_expand_size(char *undoll_cmd, int *i, t_data *data);
int		ft_get_error_size(t_data *data);
char	*ft_fill_clean_cmd(char *undoll_cmd, int len, t_data *data);
void	ft_fill_ex2(char *undoll_cmd, t_int *var, \
	char *clean_cmd, t_data *data);
void	ft_fill_ex3(t_env *env, char *clean_cmd, t_int *var);
void	ft_fill_return_code(t_data *data, char *clean_cmd, int *j);
void	ft_fill_normal(char *clean_cmd, char *undoll_cmd, int *i, int *j);

/*	Step 6	tokens */

int		ft_tokenizer(t_data *data);
int		ft_get_token(t_cmd *cmd, t_data *data);
int		ft_check_end(t_cmd *cmd, char *clean_cmd, t_token *token, t_int *var);
int		ft_get_token_end(t_cmd *cmd, char *clean_cmd, t_token *token, int *j);
void	ft_get_token_quotes(char *clean_cmd, int *j);
int		ft_clean_token(t_cmd *cmd, t_data *data);
int		ft_consec_quotes_len(char *token);
char	*ft_fill_consec_quotes(char *token, int len);
int		ft_space_quotes(char *tmp_token, t_token *token);
int		ft_clean_len(char *token);
char	*ft_fill_clean_token(char *tmp_token, int len);
void	ft_positive_token(t_token *token);
int		ft_del_empty_token(t_cmd *cmd, t_data *data);
int		ft_type_token(t_cmd *cmd, t_data *data);
void	ft_token_env(t_data *data, t_cmd *cmd, t_token *token);
t_token	*ft_token_env_2(t_cmd *cmd, t_token *token);
void	ft_token_env_3(t_token *token);
void	ft_token_env_4(t_data *data, t_cmd *cmd, t_token *token);
int		ft_check_built_in(char *token, t_data *data, int tok_len);
t_token	*ft_get_token_echo(t_token **token);
void	ft_echo_join_words_fill(t_token *token);
int		ft_del_nword(t_cmd *cmd);

/*  Step 7	 heredoc_path  */

int		ft_heredoc_path(t_data *data);

	/*	env_list */

t_env	*ft_lstlast_env(t_env *lst);
int		ft_lstadd_env(t_env **env, char *envp, t_data *data, int flag);
void	ft_lstdelone_env(t_env *node);
void	ft_lstdelone_env_bin(t_env *node);
void	ft_free_env(t_env **env);
void	ft_lstclearone_env(t_env **env_head, t_env *ptr);

	/*	cmd_list */

t_cmd	*ft_lstlast_cmd(t_cmd *lst);
int		ft_lstadd_cmd(t_cmd **cmd, char *cmdline, t_data *data);
void	ft_lstdelone_cmd(t_cmd *node);
void	ft_lstdelone_cmd_bin(t_cmd *node);
void	ft_free_cmd(t_cmd **cmd);

	/*	token_list */

t_token	*ft_lstlast_tok(t_token *lst);
int		ft_lstadd_tok(t_token **tok, int type, char *token, t_data *data);
void	ft_lstdelone_tok(t_token *node);
void	ft_lstdelone_tok_bin(t_token *node);
void	ft_free_token(t_token **token);

	/*	utils */

// CLEAN
void	ft_free_strs(char *str1, char *str2, char *str3);
void	*ft_free_tabstr(char **tab_str);
void	*ft_free_tabstr2(char **tab_str, int type);
void	*ft_free_tabstr_bin(char **tab_str, int type);

void	ft_free_ints(int *t_int1, int *t_int2, int *t_int3);
void	*ft_free_tabint(int **tab_int, int size);
void	*ft_free_tabint2(int **tab_int, int size, int type);
void	*ft_free_tabint_bin(int **tab_int, int size, int type);

// UTILS
int		ft_new_strchr(const char *s, int c);
int		ft_new_strrchr(const char *s, int c);
int		ft_is_in_set(const char *set, char c);
int		ft_nb_word(char const *str, char c);

/*	***** EXEC *****	*/
/*	****************	*/

int		ft_exec(t_data *data);
void	ft_make_pipe(t_data *data);
void	ft_fork(t_data *data, int *res);

/*	exec init */

int		**ft_init_pipe(t_data *data);
int		*ft_init_pid(t_data *data);
int		ft_get_files_io(t_data *data);

/*	exec check exec	*/

int		ft_no_pipe_no_token(t_data *data);
int		ft_check_sigint_heredoc(t_data *data);
int		ft_check_heredoc(t_data *data);

/* 	exec Unique Built in */

int		ft_unique_builtin(t_data *data);
void	ft_handle_ub_fd(t_data *data);
int		ft_redirect_std(t_cmd *cmd);
int		ft_redirect_builtin(t_cmd *cmd);

/*	exec CHILD */

void	ft_child_process(t_data *data, int i);
int		ft_redirect_inout(t_data *data, t_cmd *cmd, int i);
int		ft_exec_built_in(t_cmd *cmd, t_data *data, int flag);
char	**ft_init_cmd_opt(t_cmd *cmd, t_data *data);

char	*ft_find_cmd_path(t_cmd *cmd, t_data *data);
void	ft_path_given(t_data *data, t_cmd *cmd, char *full_path);
char	*ft_check_abs_path(char *token, char *full_path, t_data *data, int len);
void	ft_abs_last_slash(char *token, char *full_path, \
	t_data *data, char *tmp);
char	*ft_abs_no_last_slash(char *token, char *full_path);
void	ft_check_abspath_directory(char *token, char *full_path);

char	*ft_get_path_parent(char *cwd_update, t_data *data);
char	*ft_get_full_path(t_cmd *cmd, t_data *data);
void	ft_update_path(t_cmd *cmd, t_data *data, int i, int j);

char	*ft_find_cmd_path2(t_cmd *cmd, t_data *data);
char	*ft_try_access_path(t_env *env_path, t_data *data, t_cmd *cmd);
char	*ft_get_new_path(t_env *env_path, t_data *data);
void	ft_check_error_cmd_path(t_data *data, t_cmd *cmd, int res);

/*	exec parent		*/

int		ft_parent_process(t_data *data);
int		ft_parent_exit(t_data *data, int res);

/*	exec CLEAN */

int		ft_msg(int val_exit, char *msg1, char *msg2, char *msg3);
void	ft_close_fd(t_data *data);
void	ft_close_std(void);
void	ft_clean_exec(t_data *data);
int		ft_free_data_child(int res, t_data *data);

int		ft_clean_cmdline(t_data *data);
int		ft_clean_loop(t_data *data);

int		ft_free_exit(int val_exit);

/*	built-ins */

int		ft_echo(t_cmd *cmd, t_data *data, int flag);

int		ft_pwd(t_data *data);

int		ft_env(t_cmd *cmd, t_data *data);
void	ft_display_env(t_data *data, t_token *token);

int		ft_export(t_cmd *cmd, t_data *data, int flag);
int		ft_check_export(t_token *token, t_data *data, int flag);
void	ft_display_export(t_data *data, int flag);
int		ft_add_export(t_token *token, t_data *data, int flag);

int		ft_unset(t_cmd *cmd, t_data *data);
int		ft_check_unset(t_token *token, t_data *data);

int		ft_cd(t_cmd *cmd, t_data *data, int flag);
int		ft_update_pwd(t_cmd *cmd, t_data *data, int flag);
int		ft_update_cwd(t_token *token, t_data *data, int flag);
int		ft_exec_cd(t_token *token, t_cmd *cmd, t_data *data, int flag);
void	ft_new_oldpwd(t_env *env, t_data *data, int flag, int pwd_null);
void	ft_oldpwd_pwd(t_env *env, t_data *data, int flag);
void	ft_oldpwd_nopwd(t_env *env, t_data *data, int flag);
int		ft_new_pwd(t_env *env, t_data *data, t_token *token, int flag);
int		ft_pwd_content(t_env *env, t_data *data, t_token *token, int flag);
void	ft_handle_malloc_pwd(t_env *env, t_data *data, int flag);

int		ft_exit(t_cmd *cmd, t_data *data, int flag);
int		ft_check_digit(char *token);
char	*ft_get_check2(char *token, int flag, t_data *data);

/*  signaux  */

void	sig_int(int sig);
void	ft_init_signals(t_data *data);
void	ft_signal(t_data *data, int signum, t_sighandler handler);
void	ft_sigquit_child(t_data *data, int signum, t_sighandler handler);
void	sig_quit(int sig);

/*   heredoc  */

void	ft_heredoc(t_data *data, t_cmd *cmd, t_token *tok_redir);
char	*ft_get_prompt_line(t_data *data);
void	ft_add_line(t_data *data, t_token *tok_redir, char *line);
t_env	*ft_check_env(t_data *data, char *line);
void	ft_heredoc_sigint(int sig);
void	ft_end_of_file(t_token *tok_redir);
void	ft_exec_hd(t_data *data, t_token *tok_redir, char *line, int stdin_dup);

/*	bin collector  */

void	*ft_handle_malloc(int flag_type, void *ptr, int size, t_data *data);
void	ft_free_ptr_type(void *ptr, int type, int size);

/*	bin list  */

int		ft_lstadd_bin(t_bin **bin, void *ptr, int type, int size);
void	ft_lstdelone_bin(t_bin *node);
void	ft_lstclearone_bin(t_bin **bin_head, void *ptr);
void	ft_free_bin(t_bin **bin);

#endif
