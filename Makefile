NAME        := minishell

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBFT     libft
#
# INCS      include directories
#
# SRC_DIR   source directory
# SRCS      source files
#
# OBJ_DIR   build directory
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
# LDFLAGS   linker flags
# LDLIBS    library names

LIBFT       := lib/libft/libft.a

SRC_DIR     := srcs
SRCS 		:= 	\
            minishell.c \
			utils.c \
			env.c \
			lexer.c \
			get_commands.c \
			cmd_list.c \
			built_in.c \
			del_spaces.c \
			get_redir.c \
			token_list.c \
			del_dolls.c \
			expand_2.c \
			token_2.c \
			clean_token_3.c \
			type_token.c \
			clean_redir.c \
			clean_heredoc.c \
			del_empty_token.c \
			space_quotes.c \
			del_nwords.c \
			built_in/echo.c \
			built_in/exec.c 
SRCS        := $(addprefix $(SRC_DIR)/,$(SRCS))

OBJ_DIR     := obj
OBJS        := $(subst .c,.o,$(SRCS))
OBJS        := $(subst $(SRC_DIR),$(OBJ_DIR),$(OBJS))

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I lib/libft -I includes 
LDFLAGS     := -L lib/libft
LDLIBS      := -l ft -l readline

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm -f
MAKE        := $(MAKE) --silent --jobs --no-print-directory
DIR_DUP		= mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   link .o -> archive
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
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