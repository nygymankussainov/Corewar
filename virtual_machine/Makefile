# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:56:58 by hfrankly          #+#    #+#              #
#    Updated: 2019/10/30 20:06:08 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

INCLUDES = -I ./includes -I ../includes -I ../libft -I ../libft/ft_printf
LIBS = -L ../libft -lft -L ../libft/ft_printf -lftprintf

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:%.c=%)

FLAGS = -Wall -Wextra -Werror

all: make_libs $(OBJ_DIR) $(OBJS)

%: %.o
	gcc $(FLAGS) $(INCLUDES) $< -c $@ -o $(NAME)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $<

$(OBJ_DIR):
	mkdir obj

make_libs:
	make -C ../libft
	make -C ../libft/ft_printf

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re