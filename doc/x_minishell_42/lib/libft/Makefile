# ========== [ Project files ]

# TODO set name
PREFIX		= libft
NAME 		= $(PREFIX).a

INC_DIR 	= include
INC			= $(INC_DIR)

# TODO set sources
SRC_DIR		= src
SRCS 		= all/ft_atoi.c 						\
			  all/ft_atol.c 						\
			  all/ft_bzero.c 						\
			  all/ft_calloc.c 						\
			  all/ft_isalnum.c 						\
			  all/ft_isalpha.c 						\
			  all/ft_isascii.c 						\
			  all/ft_isdigit.c 						\
			  all/ft_isprint.c 						\
			  all/ft_memchr.c 						\
			  all/ft_memcmp.c 						\
			  all/ft_memcpy.c 						\
			  all/ft_memmove.c 						\
			  all/ft_memset.c 						\
			  all/ft_strchr.c 						\
			  all/ft_strlcat.c 						\
			  all/ft_strlcpy.c 						\
			  all/ft_strlen.c 						\
			  all/ft_strncmp.c 						\
			  all/ft_strcmp.c 						\
			  all/ft_strnstr.c 						\
			  all/ft_strrchr.c 						\
			  all/ft_tolower.c 						\
			  all/ft_toupper.c 						\
			  all/ft_strdup.c 						\
			  all/ft_substr.c 						\
			  all/ft_strjoin.c 						\
			  all/ft_strtrim.c 						\
			  all/ft_split.c 						\
			  all/ft_itoa.c 						\
			  all/ft_strmapi.c 						\
			  all/ft_striteri.c						\
			  all/ft_putchar_fd.c 					\
			  all/ft_putstr_fd.c 					\
			  all/ft_putendl_fd.c					\
			  all/ft_putnbr_fd.c					\
			  linked_list/ft_lstadd_back.c 			\
			  linked_list/ft_lstadd_front.c			\
			  linked_list/ft_lstclear.c				\
			  linked_list/ft_lstdelfirst.c			\
			  linked_list/ft_lstdelone.c 			\
			  linked_list/ft_lstiter.c 				\
			  linked_list/ft_lstlast.c 				\
			  linked_list/ft_lstmap.c				\
			  linked_list/ft_lstnew.c 				\
			  linked_list/ft_lstsize.c 				\
			  double_linked_list/ft_dlstadd_back.c 	\
			  double_linked_list/ft_dlstadd_front.c	\
			  double_linked_list/ft_dlstclear.c		\
			  double_linked_list/ft_dlstdelfirst.c	\
			  double_linked_list/ft_dlstdelone.c 	\
			  double_linked_list/ft_dlstiter.c 		\
			  double_linked_list/ft_dlstlast.c 		\
			  double_linked_list/ft_dlstmap.c		\
			  double_linked_list/ft_dlstnew.c 		\
			  double_linked_list/ft_dlstsize.c 		\
			  ft_printf/ft_printf.c 				\
			  ft_printf/options1.c 					\
			  ft_printf/options2.c 					\
			  ft_printf/utils.c						\
			  get_next_line/get_next_line.c			\
			  extra/ft_min.c 						\
			  extra/ft_max.c 						\
			  extra/ft_abs.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJ_DIR 	= obj
OBJS 		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ========== [ Compiler flags ]

CC 			= gcc

# TODO set extra compiler flags
CFLAGS 		=

# TODO set extra linker flags
CPPFLAGS	=

CFLAGS 		+= -Wall -Wextra -Werror -Wconversion -Wsign-conversion
CPPFLAGS	+= $(INC:%=-I%)

# ========== [ Misc ]

RM 			= rm -rf

# ========== [ Recipe ]

all: $(NAME)

sanitizer: CFLAGS += -fsanitize=address,undefined,signed-integer-overflow
sanitizer: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@$(ECHO)"$(G)created$(END) $(END)$(NAME)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

clean:
	@[ -d $(OBJ_DIR) ] \
		&& $(RM) $(OBJ_DIR) && $(ECHO)"$(R)removed$(END) $(OBJ_DIR)/\n" || true

fclean: clean
	@[ -f "$(NAME)" ] && $(RM) $(NAME) && $(ECHO)"$(R)removed$(END) $(NAME)\n" || true

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) sources\n"
	@norminette -R CheckDefine $(INC_DIR) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) headers\n"

update:
	@git pull
	@$(ECHO)"$(G)updated$(END)\n"

re: fclean all

.PHONY: all clean fclean norm update re

# ========== [ Stdout ]

R		= $(shell tput setaf 1)
G		= $(shell tput setaf 2)
Y		= $(shell tput setaf 3)
B		= $(shell tput setaf 4)
M		= $(shell tput setaf 5)
C		= $(shell tput setaf 6)
W		= $(shell tput setaf 7)
K		= $(shell tput setaf 8)
END		= $(shell tput sgr0)
ECHO  	= echo -n "\r\033[K$(PREFIX): "
