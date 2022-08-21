# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 16:02:06 by lmelard           #+#    #+#              #
#    Updated: 2022/08/17 16:25:36 by lmelard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./srcs/minishell.c

OBJS = ${SRCS:.c=.o}

CC = clang
RM = rm -rf

CFLAGS = -Wall -Werror -Wextra

LIBFLAGS = -L./libft -lft

.c.o:
#	${CC} ${CFLAGS} -g3 -lreadline -c $< -o ${<:.c=.o}
	${CC} ${CFLAGS} -g3 -c $< -o ${<:.c=.o}

all: ${NAME}

$(NAME): ${OBJS}
	@echo "Compiling the libft..."
	@make -C libft
	@echo "Compiling the mandatory part..."
#	${CC} ${CFLAGS} -g3 -lreadline -o ${NAME} ${OBJS} ${LIBFLAGS}
	${CC} ${CFLAGS} -g3 -o ${NAME} ${OBJS} ${LIBFLAGS} -lreadline
	@echo "---> minishell is ready to be used <---"

clean:
	@echo "Removing libft's objects..."
	@make clean -C libft
	@echo "Removing objects..."
	${RM} ${OBJS}

fclean: clean
	@echo "Removing libft archive..."
	@make fclean -C libft
	@echo "Removing minishell ..."
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re