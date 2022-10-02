/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:39:23 by athirion          #+#    #+#             */
/*   Updated: 2022/07/14 16:56:25 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 ** =========[ Includes ]==========
 */

# include "libft.h"

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/*
 ** =========[ Defines ]===========
 */

/*
 ** [ TOKENS ]
 **
 ** WHITE_SPACE ' '
 ** PIPE		'|'
 ** DOLLAR		'$'
 ** QUOTE		'''
 ** D_QUOTE		'"'
 ** GREAT		'>'
 ** D_GREAT		'>>'
 ** LESS		'<'
 ** D_LESS		'<<'
 ** FILE		'file'
 ** S_WORD		'EOF'
 ** WORD		'str'
 ** EXPAND		'env var val'
 */

# define WS 0
# define PP 1
# define DO 2
# define QT 3
# define DQ 4
# define GT 5
# define DG 6
# define LS 7
# define DL 8
# define FI 9
# define SW 10
# define WD 11
# define EX 12
# define RV 13

/*
 ** [ RETURN ]
 */

# define SUCCESS 0
# define FAILURE 1

# define FALSE 0
# define TRUE 1

/*
 ** =========[ Structures ]========
 */

typedef void	(*t_sighandler)(int);

/*
 ** Tokens
 */

typedef struct s_tok
{
	int		tokid;
	int		tokpos;
	char	*tok;

}			t_tok;

/*
 ** Environ
 */

typedef struct s_env
{
	char	*key;
	char	*val;

}			t_env;

/*
 ** Commands
 */

typedef struct s_cmd
{
	int		cmdid;
	int		cmdpos;
	size_t	nb_arg;
	char	**cmd;
	char	*prg;
	int		fd[2];
	int		type_in;
	int		type_out;
	char	*file_in;
	char	*file_out;
	char	*stop_word;
	int		is_here_doc;
	int		fd_in;
	int		fd_out;
	int		in;
	int		out;

}			t_cmd;

/*
 ** Export
 */

typedef struct s_exp
{
	char	*key;
	char	*val;

}			t_exp;

/*
 ** Redirection
 */

typedef struct s_redir
{
	int				type;
	int				cmdid;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;

}				t_redir;

/*
 ** heredoc
 */

typedef struct s_hd
{
	int		i[2];
	int		len_var;
	char	*temp;
	int		len;
	char	*temp_var;
	char	*var;

	char	*expand;
	int		fd_file;

}				t_hd;

/*
 ** Data
 */

typedef struct s_data
{
	int		cmdid;
	int		cmdcount;
	char	*cmdline;
	char	**environ;
	char	**envtab;

	t_dlist	*toklist;
	t_dlist	*cmdlist;
	t_dlist	*envlist;
	t_dlist	*explist;
	t_dlist	*redlist;

	char	*cwd;
	char	*oldcwd;

	int		nb_pipes;
	char	*cwdpath;
	char	**cmd_path;
	int		last_in;
	int		last_out;
	int		prevpipeout;

	int		shlvl;

	int		toggle;

}			t_data;

/*
 ** =========[ Prototypes ]========
 */

/* #----------------------------------------------------------------------# */
/* #				  UTILS   											  # */
/* #----------------------------------------------------------------------# */

/*
 ** [ utils/wrappers_2.c ] NORMED
 */

void	ft_w_signal(t_data *data, int signum, t_sighandler handler);

/*
 ** [ utils/wrappers.c ] NORMED
 */

void	ft_w_dup2(t_data *data, int fd, int std);
void	*ft_w_malloc(t_data *data, size_t size);
char	*ft_w_getcwd(t_data *data);
char	*ft_w_substr(t_data *data, char const *s, size_t start, size_t len);
char	*ft_w_strdup(t_data *data, const char *s1);

/*
 ** [ utils/exit_utils.c ] NORMED
 */

void	ft_free_tab(char **tab);
void	ft_free(void *ptr);
void	ft_free_all(t_data *data);
void	ft_exitmsg(t_data *data, char *str);

/*
 ** [ utils/utils.c ] NORMED
 */

void	ft_dlst_elem_dup(t_data *data, t_dlist **lst, t_dlist *dup);
char	*ft_strjoin_free_s2(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*ft_strjoin_free(char *s1, char *s2);

/* #----------------------------------------------------------------------# */
/* #				  BUILTINS											  # */
/* #----------------------------------------------------------------------# */

/*
 ** [ builtin/exit.c ] NORMED
 */

/* static int	ft_isnumeric(char *str) */
void	ft_exit_cases(char **cmd);
void	ft_exit(t_data *data, char **cmd);

/*
 ** [ builtin/cd_2.c ] NORMED
 */

void	ft_update_pwd(t_data *data, char *newpwd);
/* static void ft_update_oldpwd_2(t_data *data, char **exportcmd) */
void	ft_update_oldpwd(t_data *data, char *oldpwd);

/*
 ** [ builtin/cd.c ] NORMED
 */

/* static int  ft_chdir(char *path) */
/* static int  ft_cd_path(t_data *data, char *cmd) */
/* static int  ft_cd_hyphen(t_data *data) */
/* static int  ft_cd_alone(t_data *data) */
int		ft_cd(t_data *data, char **cmd);

/*
 ** [ builtin/pwd.c ] NORMED
 */

int		ft_pwd(t_data *data);

/*
 ** [ builtin/export_2.c ] NORMED
 */

/* ft_explist_export_2(t_data *data, char *cmd, t_dlist *temp, char **val) */
/* ft_explist_export_1(t_data *data, char *cmd, char **key, char **val) */
void	ft_explist_export(t_data *data, char *cmd);
/* ft_envlist_export_2(t_data *data, char *cmd, char **val, t_dlist *temp) */
void	ft_envlist_export(t_data *data, char *cmd);

/*
 ** [ builtin/export.c ] NORMED
 */

/* static void ft_data_export_pwd(t_data *data, char *cmd, char **val) */
/* static void ft_data_export_oldpwd(t_data *data, char *cmd, char **val) */
/* static void ft_data_export(t_data *data, char *cmd) */
/* static int  ft_is_valid_export(char *key) */
int		ft_export(t_data *data, char **cmd);

/*
 ** [ builtin/unset.c ] NORMED
 */

/* static void	ft_explist_unset(t_data *data, char *key) */
/* static void	ft_envlist_unset(t_data *data, char *key); */
/* static int	ft_is_valid_unset(char *key) */
int		ft_unset(t_data *data, char **args);

/*
 ** [ builtin/echo.c ] NORMED
 */

/* static int	ft_is_n_flag(char *arg) */
int		ft_echo(t_data *data, char **arg);

/*
 ** [ builtin/env.c ] NORMED
 */

/* static char	**ft_update_envtab(t_data *data) */
int		ft_env(t_dlist *envlist);

/* #----------------------------------------------------------------------# */
/* #				  EXECUTION											  # */
/* #----------------------------------------------------------------------# */

/*
 ** [ exec/exec_error.c ] NORMED
 */

/* static void ft_cmd_error(t_data *data, t_dlist *cmd, int error) */
void	ft_file_error(t_data *data, char *file, int error);
void	ft_perror(t_data *data, t_dlist *cmd, int error);

/*
 ** [ exec/heredoc_utils.c ] NORMED
 */

int		ft_isspace(char c);
int		ft_valid_var_format(size_t i, char *str);
char	*ft_update_str(char **temp, char *str, char *key, char *val);
int		ft_has_a_var(char *str);

/*
 ** [ exec/sig_heredoc.c ] NORMED
 */

void	ft_heredoc_sigint(int sig);
void	ft_heredoc_signals(t_data *data);

/*
 ** [ exec/expand_heredoc.c ] NORMED
 */

char	*ft_expand_heredoc(t_data *data, char *str);

/*
 ** [ exec/heredoc.c ] NORMED
 */

void	ft_end_heredoc(t_dlist *cmd);
void	ft_here_doc_4(t_data *data, t_dlist *cmd, t_hd *hd, char *file);
void	ft_here_doc_3(t_data *data, t_hd *hd);
int		ft_here_doc_2(t_data *data, t_hd *hd);
void	ft_here_doc(t_data *data, t_dlist *cmd, t_dlist *redir, char *file);

/*
 ** [ exec/file.c ] NORMED
 */

int		ft_open_2(t_data *data, t_dlist *cmd, t_dlist *temp, int redir_in_ok);
int		ft_open_3(t_data *data, t_dlist *cmd, t_dlist *temp, int redir_in_ok);
int		ft_open(t_data *data, t_dlist *cmd);
void	ft_close(t_data *data, t_dlist *cmd, int *fd);

/*
 ** [ exec/exec_builtin.c ] NORMED
 */

int		ft_fork_builtin(t_dlist *cmd);
int		ft_is_builtin(t_dlist *cmd);
int		ft_exec_builtin(t_data *data, t_dlist *cmd, int builtin_id);

/*
 ** [ exec/exec_2.c ] NORMED
 */

/* static void ft_parent_2(t_data *data, t_dlist *cmd, int pid) */
int		ft_parent(t_data *data, t_dlist *cmd, int pid);
/* static void ft_child_2(t_data *data, t_dlist *cmd) */
void	ft_child(t_data *data, t_dlist *cmd);

/*
 ** [ exec/exec.c ] NORMED
 */

void	ft_exec_cmd(t_data *data, t_dlist *cmd);
/* static t_dlist *ft_init_pipe(t_data *data) */
int		ft_exec(t_data *data);

/* #----------------------------------------------------------------------# */
/* #				  PARSER											  # */
/* #----------------------------------------------------------------------# */

/*
 ** [ utils/cmdlist.c ] NORMED
 */

void	ft_remove_cmd(t_dlist *cmdlist, t_dlist *cmd);
void	ft_init_cmd(t_data *data, t_cmd **cmd);
void	ft_create_cmdlist(t_data *data);
void	ft_add_cmd(t_data *data);
void	ft_clearlist_cmd(t_dlist **lst, void (*del)(void *));

/*
 ** [ parser/parser_utils.c ] NORMED
 */

int		ft_is_tokid(t_dlist *toklist, int tokid);

/*
 ** [ parser/parse_command_2.c ]
 */

char	*ft_command(t_data *data, char *command);
char	**ft_arg_cmd(t_data *data, t_dlist **cmd, t_dlist **toklist);
/*
 ** [ parser/parse_command.c ]
 */

void	ft_parse_command_redir_1(t_data *data, t_dlist **cmd, t_dlist **temp);
void	ft_parse_command_redir_2(t_data *data, t_dlist **cmd, t_dlist **temp);
void	ft_parse_command_2(t_data *data, t_dlist **cmd, t_dlist **temp, int *c);
void	ft_parse_command(t_data *data);

/*
 ** [ utils/pipe.c ] NORMED
 */

void	ft_count_pipe(t_data *data);

/*
 ** [ parser/expand_tilde.c ] NORMED
 */

char	*ft_concat_path(t_data *data, char *home, char *path);
t_dlist	*ft_expand_tilde_3(t_data *data, t_dlist *temp, char *home);
t_dlist	*ft_expand_tilde_2(t_dlist *temp);
void	ft_expand_tilde(t_data *data);

/*
 ** [ utils/redlist.c ] NORMED
 */

void	ft_create_redlist(t_data *data);
void	ft_add_red(t_data *data, t_dlist *token, int nb_cmd);
void	ft_printlist_redir(t_dlist *lst);
void	ft_clearlist_red(t_dlist **lst, void (*del)(void *));

/*
 ** [ parser/parse_redir.c ] NORMED
 */

void	ft_parse_redir(t_data *data);

/*
 ** [ parser/parse_space.c ] NORMED
 */

/* static void ft_remove_spaces(t_data *data) */
void	ft_parse_space(t_data *data);

/*
 ** [ parser/expand_quote_3.c ] NORMED
 */

void	ft_clear_emptyquote(t_data *data);
char	*ft_concat_quoted_words(t_data *data, t_dlist *toklist);

/*
 ** [ parser/expand_quote_2.c ] NORMED
 */

void	ft_remove_empty_q_2(t_data *data, t_dlist **tmp, t_dlist **new, int wt);
void	ft_remove_empty_quotes(t_data *data);
int		ft_is_equal_sign(char *str);

/*
 ** [ parser/expand_quote.c ] NORMED
 */

void	ft_expand_quote2_2(t_data *data, t_dlist **new, t_dlist **tmp, char *s);
void	ft_expand_quote2(t_data *data, t_dlist **new, t_dlist **tp);
void	ft_expand_quote(t_data *data);

/*
 ** [ parser/expand_var_4.c ] NORMED
 */

char	*ft_expand_var_2(t_data *data, char *key, int i);
char	*ft_expand_var(t_data *data, char *key);

/*
 ** [ parser/expand_var_3.c ] NORMED
 */

void	ft_expand_to_word(t_data *data);
void	ft_concat_expand(t_data *data);
void	ft_remove_dollar(t_data *data);
void	ft_heredoc_dollar_2(t_dlist **temp);

/*
 ** [ parser/expand_var_2.c ] NORMED
 */

void	ft_heredoc_dollar(t_data *data);
void	ft_simple_quote_2(t_data *data, t_dlist **temp, char *str);
void	ft_simple_quote(t_data *data);
void	ft_expand_dollar(t_data *data);
void	ft_var_exit_status(t_data *data);

/*
 ** [ parser/expand_var.c ] NORMED
 */

void	ft_multiple_dollar_2(t_data *data, t_dlist **temp, t_dlist **new);
void	ft_multiple_dollar(t_data *data);
void	ft_expand_vars_2(t_data *data, t_dlist **temp);
void	ft_expand_vars(t_data *data);

/*
 ** [ parser/parse_pipe.c ] NORMED
 */

/* static int  ft_multiple_pipe(t_dlist **token) */
/* static int  ft_last_tok_is_pipe(t_dlist *token) */
/* static int  ft_just_pipe(t_dlist *token) */
int		ft_parse_pipe(t_data *data);

/*
 ** [ parser/parse_quote.c ] NORMED
 */

/* static int  ft_check_last_tok(t_dlist *toklist) */
/* static void ft_set_word_token(t_dlist **token) */
/* static void ft_quoted_becomes_words(t_dlist *toklist) */
/* static int  ft_check_quote_pairs(t_dlist *toklist) */
int		ft_parse_quote(t_data *data, t_dlist *toklist);

/*
 ** [ parser/parser.c ] NORMED
 */

int		ft_parse_special_tok(t_data *data);
int		ft_parse_empty_cmd(t_data *data);
int		ft_check_redir(t_data *data);

/*
 ** [ parser/parser.c ] NORMED
 */

t_dlist	*ft_concat_consec_word_2(t_data *data, t_dlist *temp);
void	ft_concat_consecutive_word(t_data *data);
void	ft_parser_2(t_data *data);
void	ft_parser(t_data *data);

/* #----------------------------------------------------------------------# */
/* #				  LEXER												  # */
/* #----------------------------------------------------------------------# */

/*
 ** [ utils/toklist.c ] NORMED
 */

void	ft_update_tokpos(t_dlist *toklist);
void	ft_remove_tok(t_dlist *toklist, t_dlist *token);
void	ft_add_tok(t_data *data, int tokid, int tokpos, char *tok);
void	ft_printlist_tok(t_dlist *toklist);
void	ft_clearlist_tok(t_dlist **toklist, void (*del)(void *));

/*
 ** [ lexer/lexer.c ] NORMED
 */

/* static int	ft_set_token(char *tok) */
/* static size_t	ft_token_size(char *cmdchar) */
/* static void	ft_tokenize(t_data *data, char **cmdline, int *pos) */
void	ft_lexer(t_data *data);

/* #----------------------------------------------------------------------# */
/* #																	  # */
/* #----------------------------------------------------------------------# */

/*
 ** [ utils/prompt.c ] NORMED
 */

/* static char *ft_prompt_prefix(t_data *data) */
/* static char *ft_prompt_line(t_data *data) */
/* static void ft_readline(t_data *data) */
/* static char **ft_split_path(t_data *data) */
void	ft_prompt(t_data *data);

/*
 ** [ utils/explist_3.c ] NORMED
 */

int		ft_check_exp_entry(t_dlist *explist, char *key);
char	*ft_getexp(t_data *data, t_dlist *explist, char *key);
t_dlist	*ft_sort_exp_2(t_data *data, t_dlist *new);
void	ft_sort_exp(t_data *data, t_dlist *explist);

/*
 ** [ utils/explist_2.c ] NORMED
 */

t_dlist	*ft_remove_exp(t_dlist *explist, t_dlist *entry);
void	ft_init_minimal_exp(t_data *data);
void	ft_init_exp_2(t_data *data, unsigned int i, unsigned int j);
void	ft_init_exp(t_data *data);

/*
 ** [ utils/explist.c ] NORMED
 */

void	ft_add_exp(t_data *data, char *key, char *val);
void	ft_printlist_elem_exp(t_data *data, t_dlist *explist, char *key);
void	ft_printlist_exp_2(t_dlist *temp);
void	ft_printlist_exp(t_data *data, t_dlist *explist);
void	ft_clearlist_exp(t_dlist **explist, void (*del)(void *));

/*
 ** [ utils/envlist_2.c ] NORMED
 */

char	**ft_update_envtab(t_data *data);
int		ft_check_env_entry(t_dlist *envlist, char *key);
char	*ft_getenv(t_data *data, t_dlist *envlist, char *key);
void	ft_init_minimal_env(t_data *data);
void	ft_init_env(t_data *data);

/*
 ** [ utils/envlist.c ] NORMED
 */

t_dlist	*ft_remove_env(t_dlist *envlist, t_dlist *entry);
void	ft_add_env(t_data *data, char *key, char *val);
void	ft_printlist_elem_env(t_data *data, t_dlist *envlist, char *key);
void	ft_printlist_env(t_dlist *envlist);
void	ft_clearlist_env(t_dlist **envlist, void (*del)(void *));

/*
 ** [ utils/shlvl.c ] NORMED
 */

void	ft_shlvl_update(t_data *data);

/*
 ** [ main.c ] NORMED
 */

/* static void ft_sigint(int sig) */
void	ft_init_signals(t_data *data);
/* static void ft_init_data(t_data *data) */
int		main(int ac, char **av);

#endif
