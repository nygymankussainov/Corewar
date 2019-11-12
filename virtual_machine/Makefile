# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:56:58 by hfrankly          #+#    #+#              #
#    Updated: 2019/11/12 14:40:19 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

ARCHIVE = corewar.a

NAME = corewar

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a

INCLUDES = -I ./includes  -I ../includes -I $(LIB) -I ../libft

LIBS = -L ../libft -lft -L ../libft/ft_printf -lftprintf

SRCDIR = src
OBJDIR = obj

SOURCES =	main.c \
			initialization/initialization.c \
			initialization/set_params.c\
			parsing/parse_arguments.c \
			validation/read_byte_code.c \
			war/start_war.c \
			war/operations.c \
			war/check.c \
			war/carriage_execution.c \
			war/execute_op.c \
			exit.c \


SRC = $(addprefix $(SRCDIR)/, $(SOURCES))

OBJ = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

CCFL = -g

all: obj_dir library $(ARCHIVE) $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

library:
	@make -sC $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

$(ARCHIVE): $(OBJ)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

$(NAME): $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A)
	@echo "$(LOG_GREEN)Corewar has compiled successfully!$(LOG_NOCOLOR)"

clean:
	@make clean -sC $(LIB)

fclean: clean
	@/bin/rm -f $(ARCHIVE)
	@/bin/rm -f $(NAME)
	@make fclean -sC $(LIB)

re: fclean all

.PHONY: all clean fclean re library obj_dir