/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:48:07 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/29 22:02:30 by cgaillag         ###   ########.fr       */
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
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERRSTX "syntax error"
# define ERRMAL "memory allocation error"
# define ERRCMD "command not found"
# define ERRDIR "is a directory"
# define ERRNDR "not a directory"
# define ERRFOD "no such file or directory"
# define ERRMSG "Error: "
# define ERRFEW "too few arguments"
# define ERRNAM "not a valid identifier"
# define ERRARG "too many arguments"
# define ERRHOM "HOME not set"

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

// /* **************************** */
// /* début - branch CR_ft_malloc2 */

// typedef enum s_sizetype
// {
// 	TAB_INT1		= 100,
// 	TAB_INTS		= 101,
// 	TAB_STR1		= 102,
// 	TAB_STRS		= 103,
// 	LST_ENV			= 104,
// 	LST_CMD			= 105,
// 	LST_TOK			= 106,
// }	t_sizetype;

// typedef struct s_bin
// {
// 	void			*ptr;
// 	int				type;// ou un void ??? tester pour les listes chainees
// 	int				size;
// 	struct s_bin	*next;
// }	t_bin;

// // cf. suite dans la liste des fonctions en-dessous

// /*	fin - branch CR_ft_malloc2 */
// /* *************************** */

typedef struct s_token
{
	char			*token;
	int				type;
	int				fd;
	int				env;
	int				printed;//pour env - init à 0 et passe à 1 si printé dans built-in env
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
	char			*unspace_cmd;//raw_cmd_no_space;//modifié
	char			*no_redir_cmd;
	char			*undoll_cmd;
	char			*clean_cmd;//modifier par expand_cmd ??
	t_token			*token;
	t_token			*tok_redir;
	int				infile;//
	int				outfile;//
	int				file_err;
	char			**cmd_opt;
	char			*cmd_path;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*line;
	char			*prompt;
	t_env			*env;
	char			*cwd;//current work directory
	char			*oldpwd;
	char			*home;
	int				val_exit;
	char			*str_exit;
	int				nb_pipes;
	t_cmd			*cmd;
	char			**built_in;
	int				*pid;//
	int				**pipe_fd;//nb de fd[][]
	t_env			*env_path;
	char			**s_env_path;
	//t_bin			*bin;//ajoutée pour le bin collector
}	t_data;

/*	***** INIT *****	*/
/*	*****************	*/

t_env	*ft_get_env(char **envp);
char	**ft_built_in(void);
int		ft_only_space(char *line);
int		ft_init_data_1(t_data *data, char **envp);
void	ft_get_home(t_data *data);

/*	env_path */

/* 1ere partie - à désactiver pour tester export y.c. pour PATH*/

	// void	ft_get_env_path(t_data *data, char **envp);
	// t_env	*ft_lst_env_path(char **tab_path);
	// char	**ft_get_str_env_path(t_data *data);
	// int		ft_lstadd_env2(t_env **env, char *tab_path);

/* 2e partie - à activer pour tester export y.c. pour PATH*/

	void 	ft_get_env_path(t_data *data);
	int		ft_lstadd_env2(t_env **env, char *s_env_path_i);

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

int		ft_parser(t_data *data);

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

/*	Step 7 del_empty_cmd */

int		ft_get_cmd_lst_size(t_data *data);
int		ft_del_empty_cmd(t_data *data);

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

int		ft_exec(t_data *data);

/*	exec MAIN */

int		**ft_init_pipe(t_data *data);
int		*ft_init_pid(t_data *data);
int		ft_get_files_io(t_data *data);
int		ft_exec_uniq_builtin(t_data *data);
void	ft_child_process(t_data *data, int i);
int		ft_parent_process(t_data *data);

/*	exec CHILD */

int		ft_redirect_inout(t_data *data, t_cmd *cmd, int i);
int		ft_exec_built_in(t_cmd *cmd, t_data *data);
char	**ft_init_cmd_opt(t_cmd *cmd, t_data *data);
char	*ft_find_cmd_path2(t_cmd *cmd, t_data *data);
char	*ft_find_cmd_path(t_cmd *cmd, t_data *data);

/*	exec CLEAN */

int		ft_msg(int val_exit, char *msg1, char *msg2, char *msg3);
void	ft_close_fd(t_data *data);
void	ft_close_std(void);
void	ft_exit_exec(t_data *data);//, int val_exit);
void	ft_free_data_child(t_data *data);

int		ft_clean_cmdline(t_data *data);
int		ft_clean_loop(t_data *data);

/*	built-ins */

int		ft_echo(t_cmd *cmd, t_data *data);

int		ft_pwd(t_data *data);

int		ft_env(t_cmd *cmd, t_data *data);
void	ft_display_env(t_data *data, t_token *token);

int		ft_export(t_cmd *cmd, t_data *data);
int		ft_check_export(t_token *token, t_data *data);

int		ft_unset(t_cmd *cmd, t_data *data);
int		ft_check_unset(t_token *token, t_data *data);

int		ft_cd(t_cmd *cmd, t_data *data);
void	ft_update_pwd(t_cmd *cmd, t_data *data);
void	ft_update_cwd(t_data *data);

// /* **************************** */
// /* début - branch CR_ft_malloc2 */

// /*	bin collector */

// void	*ft_malloc(t_data *data, void *ptr, int type, int size);
// int		ft_get_sizeof(int type);

// int		ft_lstadd_bin(t_bin **bin, void *ptr, int type, int size);
// t_bin	*ft_lstlast_bin(t_bin *bin);
// void	ft_lstclear_bin(t_bin *bin);
// void	ft_lstdelone_bin(t_bin *node);
// void	ft_free_bin(void *ptr, int type, int size);

// char	*ft_substr_malloc(void *data, const char *str, unsigned int start, size_t len);
// char	*ft_strdup_malloc(void *data, const char *s1);

// /*	fin - branch CR_ft_malloc2 */
// /* *************************** */

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
