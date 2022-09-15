# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 16:02:06 by lmelard           #+#    #+#              #
#    Updated: 2022/09/15 17:27:14 by cgaillag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

#CC		=	clang
CC		=	gcc
RM		=	rm -rf
#INC		=	-I./includes -I./libft
CFLAGS	=	-Wall -Werror -Wextra
#CFLAGS	=	-Wall -Wextra
LIBFLAGS =	-L./libft -lft

SRCS 	= 	minishell.c \
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

SRCDIR	=	srcs
OBJDIR	=	objs

SOURCES	:=	${addprefix ${SRCDIR}/, ${SRCS}}
OBJS	:=	${SOURCES:${SRCDIR}/%.c=${OBJDIR}/%.o}

${OBJDIR}/%.o: ${SRCDIR}/%.c
			@[ ! -d ${OBJDIR} ] && mkdir -p ${OBJDIR} || true
			@${CC} ${CFLAGS} -c $< -o $@
#			@${CC} ${CFLAGS} -c ${INC} $< -o $@

all: ${NAME}

$(NAME): ${OBJS}
			@echo "Compiling the libft..."
			@make -C libft
			@echo "Compiling the mandatory part..."
#			${CC} ${CFLAGS} -g3 -lreadline -o ${NAME} ${OBJS} ${LIBFLAGS}
			${CC} ${CFLAGS} -g3 -o ${NAME} ${OBJS} ${LIBFLAGS} -lreadline
			@echo "---> minishell is ready to be used <---"

clean:
			@echo "Removing libft's object files..."
			@make clean -C libft
			@echo "Removing minishell mandatory's object files..."
			${RM} ${OBJS}
			${RM} ${OBJDIR}

fclean: 	clean
			@echo "Removing libft's archive..."
			@make fclean -C libft
			@echo "Removing binary files..."
			${RM} ${NAME}

re: 		fclean all

.PHONY: 	all clean fclean re
