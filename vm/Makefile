# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/11/26 20:55:03 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

NAME = corewar

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a

INCLUDES = -I ./includes  -I ../ -I $(LIB) -I ../libft

SOURCES = vm.c validation.c check_bytecode.c rev_bytes.c read_from_fd.c modify_players_id.c \

SRCDIR = src
OBJDIR = obj

SRC = $(addprefix $(SRCDIR)/, $(SOURCES))

OBJ = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re library obj_dir debug

all: obj_dir $(NAME)

debug: all
	@gcc $(CCFL) -o $(NAME) $(SRC) ../libft/src/ft_swap.c $(LIB_A) $(INCLUDES) -g

obj_dir:
	@mkdir -p $(OBJDIR)

library:
	@make -sC $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

$(NAME): library $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(OBJ) $(LIB_A)
	@echo "$(LOG_GREEN)VM has compiled successfully!$(LOG_NOCOLOR)"

clean:
	@make clean -sC $(LIB)
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -sC $(LIB)

re: fclean all
