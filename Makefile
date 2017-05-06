# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwang <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/04 00:43:43 by lwang             #+#    #+#              #
#    Updated: 2017/05/04 00:43:45 by lwang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c minishell.c get_info.c free.c parse_line.c

OBJ = $(SRC:.c=.o)


CFLAGS = -Wall -Wextra -Werror -g -Ilibft

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

all: $(NAME)

$(OBJ): minishell.h

clean:
	make -C ./libft clean
	rm -f *.o

fclean:
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
