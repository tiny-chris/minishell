#------------------------------------------------------------------------------#
#                  TODO                                                        #
#------------------------------------------------------------------------------#

PREFIX		= minishell
NAME		= $(PREFIX)

LIB_DIR		= lib
LIB			= libft

INC_DIR		= include

SRC_DIR		= src
SRCS		= main.c 					\
			  utils/shlvl.c				\
			  utils/envlist.c			\
			  utils/envlist_2.c			\
			  utils/explist.c			\
			  utils/explist_2.c			\
			  utils/explist_3.c			\
			  utils/prompt.c			\
			  exec/heredoc_utils.c		\
			  lexer/lexer.c				\
			  utils/toklist.c			\
			  parser/parser.c			\
			  parser/parser_2.c			\
			  parser/parse_quote.c		\
			  parser/parse_pipe.c		\
			  parser/expand_var.c		\
			  parser/expand_var_2.c		\
			  parser/expand_var_3.c		\
			  parser/expand_var_4.c		\
			  parser/expand_quote.c		\
			  parser/expand_quote_2.c	\
			  parser/expand_quote_3.c	\
			  parser/parse_space.c		\
			  parser/parse_redir.c		\
			  utils/redlist.c			\
			  parser/expand_tilde.c		\
			  utils/pipe.c				\
			  parser/parse_command.c	\
			  parser/parse_command_2.c	\
			  parser/parser_utils.c		\
			  utils/cmdlist.c			\
			  exec/exec.c				\
			  exec/exec_2.c				\
			  exec/exec_builtin.c		\
			  exec/heredoc.c			\
			  exec/heredoc_expansion.c	\
			  exec/file.c				\
			  exec/sig_heredoc.c		\
			  exec/exec_error.c			\
			  builtin/env.c				\
			  builtin/unset.c			\
			  builtin/export.c			\
			  builtin/export_2.c		\
			  builtin/pwd.c				\
			  builtin/echo.c			\
			  utils/utils.c				\
			  utils/exit_utils.c		\
			  utils/wrappers.c			\
			  utils/wrappers_2.c		\
			  builtin/cd.c				\
			  builtin/cd_2.c			\
			  builtin/exit.c

OBJ_DIR 	= obj

CFLAGS		=
CPPFLAGS	=
LDFLAGS		=
LDLIBS		= -lreadline

#------------------------------------------------------------------------------#
#                  NOT-TODO                                                    #
#------------------------------------------------------------------------------#

LIB			:= $(LIB:%=$(LIB_DIR)/%)
INC			= $(INC_DIR)
INC_DIR		= include
INC			= $(INC_DIR) \
			  $(LIB:%=%/$(INC_DIR)) $(LIB)
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			= gcc
CFLAGS		:= $(CFLAGS) -Wall -Wextra -Werror
CPPFLAGS	:= $(CPPFLAGS) $(INC:%=-I%)
LDFLAGS 	:= $(LDFLAGS) $(LIB:%=-L%)
LDLIBS		:= $(LDLIBS) $(LIB:$(LIB_DIR)/lib%=-l%)

#------------------------------------------------------------------------------#
#                  SHELL CMDS                                                  #
#------------------------------------------------------------------------------#

RM			= rm -rf
MAKE		= make --silent --jobs --directory

#------------------------------------------------------------------------------#
#                  RECIPES                                                     #
#------------------------------------------------------------------------------#

.PHONY: all sani clean fclean norm update re test leak

all: $(NAME)

sani: CFLAGS := $(CFLAGS) -g3 -fsanitize=address,undefined,signed-integer-overflow -Wconversion -Wsign-conversion
sani: $(NAME)

$(NAME): $(OBJS)
	@for f in $(LIB); do $(MAKE) $$f --no-print-directory; done
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

clean:
	@for f in $(LIB); do $(MAKE) $$f clean --no-print-directory; done
	@[ -d $(OBJ_DIR) ] \
		&& $(RM) $(OBJ_DIR) && $(ECHO)"$(R)removed$(END) $(OBJ_DIR)/\n" || true

fclean: clean
	@for f in $(LIB); do $(MAKE) $$f fclean --no-print-directory; done
	@[ -f $(NAME) ] \
		&& $(RM) $(NAME) && $(ECHO)"$(R)removed$(END) $(NAME)\n" || true

norm:
	@for f in $(LIB); do $(MAKE) $$f norm --no-print-directory; done
	@norminette -R CheckForbiddenSourceHeader $(SRCS) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) sources\n"
	@norminette -R CheckDefine $(INC_DIR) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) headers\n"

update:
	@git pull
	@git submodule update --init
	@$(ECHO)"$(G)updated$(END)\n"

re : fclean all

#------------------------------------------------------------------------------#
#                  STDOUT                                                      #
#------------------------------------------------------------------------------#

R		= $(shell tput setaf 1)
G		= $(shell tput setaf 2)
Y		= $(shell tput setaf 3)
B		= $(shell tput setaf 4)
M		= $(shell tput setaf 5)
C		= $(shell tput setaf 6)
W		= $(shell tput setaf 7)
K		= $(shell tput setaf 8)
END		= $(shell tput sgr0)
ECHO	= echo -n "\r\033[K$(PREFIX): "
