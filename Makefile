NAME		:= minishell

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBFT		libft
#
# INCS		include directories
#
# SRC_DIR	source directory
# SRCS		source files
#
# OBJ_DIR	build directory
# OBJS		object files
#
# CC		compiler
# CFLAGS	compiler flags
# CPPFLAGS	preprocessor flags
# LDFLAGS	linker flags
# LDLIBS	library names

LIBFT		:= lib/libft/libft.a

SRC_DIR		:= srcs
SRCS 		:= \
			minishell.c \
			utils.c \
			utils2.c \
			parser/parser.c \
			parser/env.c \
			parser/lexer.c \
			parser/get_commands.c \
			parser/cmd_list.c \
			parser/built_in.c \
			parser/del_spaces.c \
			parser/get_redir.c \
			parser/token_list.c \
			parser/del_dolls.c \
			parser/expand_2.c \
			parser/token_2.c \
			parser/clean_token_3.c \
			parser/type_token.c \
			parser/clean_redir.c \
			parser/clean_heredoc.c \
			parser/del_empty_token.c \
			parser/space_quotes.c \
			parser/del_nwords.c \
			built_in/built_in.c \
			built_in/echo.c \
			built_in/pwd.c \
			built_in/env.c \
			built_in/export.c \
			built_in/unset.c \
			built_in/cd.c \
			built_in/exit.c \
			exec/exec.c \
			exec/env_path.c \
			exec/init.c \
			exec/cmd_path.c \
			exec/clean.c \
			exec/signal.c \
			bin_collect/bin_coll.c \
			bin_collect/bin_list.c \

SRCS		:= $(addprefix $(SRC_DIR)/,$(SRCS))

OBJ_DIR		:= obj
OBJS		:= $(subst .c,.o,$(SRCS))
OBJS		:= $(subst $(SRC_DIR),$(OBJ_DIR),$(OBJS))

CC			:= clang
# CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -I lib/libft -I includes
LDFLAGS		:= -L lib/libft
LDLIBS		:= -l ft -l readline

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM		cleaning command

RM			:= rm -f
MAKE		:= $(MAKE) --silent --jobs --no-print-directory
DIR_DUP		= mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all		default goal
# %.o		compilation .c -> .o
# $(NAME)	link .o -> archive
# clean		remove .o
# fclean	remove .o + binary
# re		remake default goal
# run		run the program
# info		print the default goal recipe

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(dir $(LIBFT))

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(MAKE) -C $(dir $(LIBFT)) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(dir $(LIBFT)) fclean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:
