# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/29 16:30:24 by ler-rech          #+#    #+#              #
#    Updated: 2021/02/02 15:31:48 by ler-rech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
GCC = gcc
FILES_C =	test.c \
			main.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c \
			src/read.c \
			src/parce.c \
			src/execute.c \
			src/built_in.c \
			src/echo.c \
			src/helper.c \
			src/export.c \

FILES_O =	test.o main.o src/read.o src/parce.o src/execute.o built_in.o echo.o helper.o export.o

NAME = minishell

FILE_H = libft.h

all: lib $(NAME)

lib:
	cd libft; make

$(NAME):
	@$(GCC) -o minishell $(FILES_C) libft/libft.a -fsanitize=address -g

clean:
	rm -rf minishell; cd libft; make clean

fclean: clean
	cd libft; make fclean

re: fclean all

bonus: all

test:
	@rm -rf minishell
	@$(GCC) -o minishell $(FILES_C) libft/libft.a -fsanitize=address -g
	@./minishell